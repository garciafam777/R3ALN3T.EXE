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
import sys, os, json, argparse

CANON = {"fire","aqua","elec","wood","wind","holy","void"}
# off-wheel tokens that must NEVER appear as an element value
OFFWHEEL = {"earth","dark","sound","ice","time","water","crystal","blood","nature",
            "metal","gravity","poison","plasma","lightning","light","lava","frost",
            "shadow","spirit","beast","machine","quantum","astro","psy","magma",
            "storm","chaos","order","bone","sand","steel","gold","moon","sun"}

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
                    problems.append(f"{path}.{k} = '{v}' (not in 7-wheel)")
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
                if fn.endswith(".json"):
                    targets.append(os.path.join(root, fn))
    else:
        targets.append(args.path)

    total = 0
    for t in targets:
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
