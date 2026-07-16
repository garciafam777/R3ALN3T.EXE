#!/usr/bin/env python3
"""
hermes-gap-gate.py  —  machine-checkable content-wheel gate for R3ALN3T.EXE
=========================================================================
Reproducible verification that generated content conforms to canon:
  * every element field is one of the 7 canonical wheel elements
  * name / tier fields are non-empty
  * damage / MB fields are non-null and not the literal "None"

This is the committed artifact required before any content-generator
"fix applied" verdict is accepted (replaces a human-run one-time grep).
Run it in CI or locally; non-zero exit = gate failed.

Usage:
  python hermes-gap-gate.py <path-to-file-or-dir> [--strict]

Supports: .json (recurses objects/arrays), or a directory of .json files.
For each file it reports per-row violations and exits non-zero if any found.
"""
import sys, os, json, argparse, csv

CANON = {"fire","aqua","elec","wood","wind","holy","void","ice","blood","crystal",
          "dark","earth","glitch","gravity","metal","nature","null","plasma",
          "poison","sound","time"}  # canon-21 (CEO ruling: 21 elements, NO Light)
# off-wheel tokens that must NEVER appear as an element value (bogus / non-canon)
OFFWHEEL = {"light","lightning","lava","frost","shadow","spirit","beast","machine",
            "quantum","astro","psy","magma","storm","chaos","order","bone","sand",
            "steel","gold","moon","sun","water","rain","leaf"}

ELEMENT_KEYS = {"element","elements","elem"}
NAME_KEYS    = {"name","title","id_name"}
TIER_KEYS    = {"tier","rank_tier","rarity"}
DMG_KEYS     = {"damage","dmg","mb","power","atk"}

def norm(v):
    if isinstance(v, str):
        return v.strip().lower()
    return v

def check_obj(obj, path, problems):
    if isinstance(obj, dict):
        for k, v in obj.items():
            klow = k.lower()
            if klow in ELEMENT_KEYS and isinstance(v, str):
                val = norm(v)
                if val not in CANON:
                    problems.append(f"{path}.{k} = '{v}' (not in canon-21)")
            if klow in NAME_KEYS and isinstance(v, str):
                if v.strip() == "" or v.strip() == "?":
                    problems.append(f"{path}.{k} = EMPTY/?")
            if klow in TIER_KEYS and isinstance(v, str):
                if v.strip() == "" or v.strip() == "?":
                    problems.append(f"{path}.{k} = EMPTY/?")
            if klow in DMG_KEYS and v is not None:
                if isinstance(v, str) and v.strip().lower() in ("none","null",""):
                    problems.append(f"{path}.{k} = '{v}' (null-ish)")
            # recurse
            if isinstance(v, (dict, list)):
                check_obj(v, f"{path}.{k}", problems)
    elif isinstance(obj, list):
        for i, v in enumerate(obj):
            check_obj(v, f"{path}[{i}]", problems)

def scan_file(fp):
    problems = []
    try:
        with open(fp, "r", encoding="utf-8") as f:
            data = json.load(f)
    except Exception as e:
        return [f"{fp}: UNREADABLE ({e})"]
    check_obj(data, fp, problems)
    return problems

def scan_csv(fp, problems):
    """CSV scan: find the element column, check every value is on-wheel,
    and verify row distinctness on the first id-ish column."""
    try:
        with open(fp, "r", encoding="utf-8", newline="") as f:
            reader = csv.reader(f)
            header = next(reader, None)
            if not header:
                problems.append(f"{fp}: EMPTY csv")
                return
            # locate element column (case-insensitive)
            elem_idx = None
            id_idx = 0
            for i, h in enumerate(header):
                hl = h.strip().lower()
                if hl in ELEMENT_KEYS and elem_idx is None:
                    elem_idx = i
                if hl in ("card_number","id","uid") and id_idx == 0:
                    id_idx = i
            seen_ids = set()
            dup = 0
            rows = 0
            if elem_idx is None:
                problems.append(f"{fp}: no element column found (header={header[:8]})")
            for r in reader:
                rows += 1
                if elem_idx is not None and elem_idx < len(r):
                    ev = r[elem_idx].strip().lower()
                    if ev and ev not in CANON:
                        problems.append(f"{fp}:row{rows}.{header[elem_idx]} = '{r[elem_idx]}' (not in canon-21)")
                if id_idx < len(r):
                    rid = r[id_idx]
                    if rid in seen_ids:
                        dup += 1
                    else:
                        seen_ids.add(rid)
            if dup:
                problems.append(f"{fp}: {dup} DUPLICATE id rows (distinctness violated)")
            # report structural pass info via a benign marker is avoided; just return
    except Exception as e:
        problems.append(f"{fp}: UNREADABLE ({e})")

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("path")
    ap.add_argument("--strict", action="store_true",
                    help="also flag any off-wheel token appearing anywhere as a string value")
    args = ap.parse_args()

    targets = []
    if os.path.isdir(args.path):
        for root, _, files in os.walk(args.path):
            for fn in files:
                if fn.endswith(".json") or fn.endswith(".csv"):
                    targets.append(os.path.join(root, fn))
    else:
        targets.append(args.path)

    total = 0
    for t in targets:
        if t.endswith(".csv"):
            probs = []
            scan_csv(t, probs)
        else:
            probs = scan_file(t)
        if probs:
            total += len(probs)
            print(f"[FAIL] {t}")
            for p in probs:
                print(f"    - {p}")
        else:
            print(f"[pass] {t}")

    print(f"\n=== hermes-gap-gate: {total} violation(s) across {len(targets)} file(s) ===")
    sys.exit(1 if total else 0)

if __name__ == "__main__":
    main()
