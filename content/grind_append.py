#!/usr/bin/env python3
"""
R3ALN3T.EXE - Overnight content grinder (HERMES lane, append mode)
===================================================================
Appends more rows to existing content/ artifacts without clobbering what's there,
re-validates, and commits+pushes to origin/content/hermes-data-grind.

- NetP: continues per-tier numbering from the current max (no ID collisions),
  fills IOTA..OMICRON toward their population caps over the night.
- Chips/Enemies: appends new unique-id entries.
- Careers: appends additional paths beyond 252 (keeps 252 base intact, extends).
- Every pass re-runs validate_content.py; aborts the commit if validation fails.

Run: python content/grind_append.py            (one pass)
     python content/grind_append.py --loop      (until 0730 local, then stop)
"""
import argparse
import csv
import json
import os
import random
import subprocess
import sys
from datetime import datetime

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CONTENT = os.path.join(ROOT, "content")
NETP_CSV = os.path.join(CONTENT, "netps", "netp_cards.csv")
CHIP_JSON = os.path.join(CONTENT, "chips", "chip_database.json")
CHIP_CSV = os.path.join(CONTENT, "chips", "chip_database.csv")
ENEMY_JSON = os.path.join(CONTENT, "enemies", "enemy_database.json")
ENEMY_CSV = os.path.join(CONTENT, "enemies", "enemy_database.csv")
CAREER_JSON = os.path.join(CONTENT, "narrative", "career_paths.json")

NETP_HEADERS = [
    "card_number", "tier", "rank", "name", "alignment", "element", "faction",
    "hp", "atk", "rapid", "charge", "defense",
    "move_1", "move_2", "move_3", "move_4", "move_5",
    "move_6", "move_7", "move_8", "move_9",
    "flavor_text", "construct_sprite", "source_identities", "color_palette",
]

# Population caps per tier (from v3 RANK_HIERARCHY end numbers)
TIER_CAP = {
    "OMEGA": 100, "ALPHA": 250, "BETA": 500, "GAMMA": 900, "DELTA": 1600,
    "EPSILON": 2800, "ZETA": 4500, "ETA": 7000, "THETA": 10500, "IOTA": 15500,
    "KAPPA": 22000, "LAMBDA": 31000, "MU": 44000, "NU": 62000, "XI": 87000,
    "OMICRON": 120000,
}
TIER_START = {t: n for t, n in [
    ("OMEGA", 1), ("ALPHA", 101), ("BETA", 251), ("GAMMA", 501), ("DELTA", 901),
    ("EPSILON", 1601), ("ZETA", 2801), ("ETA", 4501), ("THETA", 7001), ("IOTA", 10501),
    ("KAPPA", 15501), ("LAMBDA", 22001), ("MU", 31001), ("NU", 44001), ("XI", 62001),
    ("OMICRON", 87001)]}
TIER_RANK = {t: i + 1 for i, t in enumerate(TIER_CAP)}

import importlib.util
spec = importlib.util.spec_from_file_location("gc", os.path.join(CONTENT, "generate_content.py"))
gc = importlib.util.module_from_spec(spec)
spec.loader.exec_module(gc)


def current_max_per_tier():
    maxnum = {t: 0 for t in TIER_CAP}
    if not os.path.exists(NETP_CSV):
        return maxnum
    with open(NETP_CSV, encoding="utf-8") as f:
        for r in csv.DictReader(f):
            tier = r["tier"]
            num = int(r["card_number"].split("-")[1])
            maxnum[tier] = max(maxnum[tier], num)
    return maxnum


def append_netps(pass_budget=2000):
    """Fill IOTA..OMICRON toward caps; return count added."""
    maxnum = current_max_per_tier()
    random.seed(os.getpid() + int(datetime.now().timestamp()) % 100000)
    name_cache = set()
    # seed name cache from existing file to avoid dup names
    if os.path.exists(NETP_CSV):
        with open(NETP_CSV, encoding="utf-8") as f:
            for r in csv.DictReader(f):
                name_cache.add(r["name"])
    added = 0
    order = ["IOTA", "KAPPA", "LAMBDA", "MU", "NU", "XI", "OMICRON"]
    out_rows = []
    for tier in order:
        cap = TIER_CAP[tier]
        start = max(maxnum[tier] + 1, TIER_START[tier])
        # Add in chunks across tiers until budget spent
        while start <= cap and added < pass_budget:
            alignment = random.choice(gc.ALIGNMENTS)
            element = random.choice(gc.ELEMENT_ROSTER)
            name = gc.gen_netp_name(alignment, element, tier, name_cache)
            stats = gc.gen_stats(tier, alignment)
            moves = gc.gen_moves(element, alignment, tier)
            flavor = gc.gen_flavor(alignment, element, tier, name)
            cn = f"{tier}-{start:03d}"
            safe = name.replace(" ", "_").replace(".", "").replace("-", "_")
            row = {
                "card_number": cn, "tier": tier, "rank": str(TIER_RANK[tier]),
                "name": name, "alignment": alignment, "element": element,
                "faction": random.choice(gc.ALIGNMENT_FACTIONS[alignment]),
                "hp": stats["HP"], "atk": stats["ATK"], "rapid": stats["RAPID"],
                "charge": stats["CHARGE"], "defense": stats["DEF"],
                "move_1": moves[0], "move_2": moves[1], "move_3": moves[2],
                "move_4": moves[3], "move_5": moves[4], "move_6": moves[5],
                "move_7": moves[6], "move_8": moves[7], "move_9": moves[8],
                "flavor_text": flavor,
                "construct_sprite": f"{cn}_{safe}_idle.png",
                "source_identities": "|".join(f"ID.{random.randint(1000,9999)}" for _ in range(3)),
                "color_palette": str([random.randint(0,255) for _ in range(3)]),
            }
            out_rows.append(row)
            start += 1
            added += 1
    if out_rows:
        with open(NETP_CSV, "a", newline="", encoding="utf-8") as f:
            w = csv.DictWriter(f, fieldnames=NETP_HEADERS)
            for r in out_rows:
                w.writerow(r)
    return added


def append_chips(n=200):
    data = json.load(open(CHIP_JSON, encoding="utf-8"))
    existing_ids = {c["id"] for c in data["chips"]}
    used_names = {c["name"] for c in data["chips"]}
    maxnum = max(int(c["id"].split("-")[1]) for c in data["chips"])
    random.seed(os.getpid() + 7)
    new = []
    for _ in range(n):
        fam, fdef = random.choice(list(gc.CHIP_FAMILIES.items()))
        suf = random.choice(gc.CHIP_SUFFIX)
        name = f"{fam}{(' ' + suf) if suf else ''}"
        if name in used_names:
            name = f"{fam}-X{random.randint(100,999)}"
        used_names.add(name)
        maxnum += 1
        cid = f"CHIP-{maxnum:04d}"
        while cid in existing_ids:
            maxnum += 1; cid = f"CHIP-{maxnum:04d}"
        existing_ids.add(cid)
        mb = max(4, min(99, fdef["base"] // 4 + random.randint(2, 14)))
        power = fdef["base"] + random.randint(-10, 25) if fdef["kind"] == "Attack" else 0
        new.append({
            "id": cid, "name": name, "code": random.choice(gc.CHIP_CODES),
            "mb": mb, "element": fdef["element"], "class": fdef["kind"],
            "power": power, "rarity": random.choices(gc.CHIP_RARITY, weights=[50,28,14,6,2])[0],
            "description": fdef["text"],
            "effect": f"{fam} family — {fdef['kind']} chip" + (f" dealing ~{power} {fdef['element']} damage." if power else "."),
            "target": "enemy" if fdef["kind"] in ("Attack", "Support") else "self",
            "droppable": True,
        })
    data["chips"].extend(new)
    data["count"] = len(data["chips"])
    json.dump(data, open(CHIP_JSON, "w", encoding="utf-8"), indent=2)
    with open(CHIP_CSV, "w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=["id","name","code","mb","element","class",
                                          "power","rarity","description","effect","target","droppable"])
        w.writeheader()
        for c in data["chips"]:
            w.writerow(c)
    return len(new)


def append_enemies(n=150):
    data = json.load(open(ENEMY_JSON, encoding="utf-8"))
    existing = {e["id"] for e in data["enemies"]}
    used = {e["name"] for e in data["enemies"]}
    maxnum = max(int(e["id"].split("-")[1]) for e in data["enemies"])
    random.seed(os.getpid() + 13)
    new = []
    for _ in range(n):
        alignment = random.choice(gc.ALIGNMENTS)
        element = random.choice(gc.ELEMENT_ROSTER)
        tier = random.choices([t[0] for t in gc.RANK_HIERARCHY[:10]],
                               weights=[2,4,7,10,12,12,10,8,6,4])[0]
        stats = gc.gen_stats(tier, alignment)
        base = random.choice(gc.ENEMY_KINDS[alignment])
        name = f"{base} {random.choice(['Alpha','Beta','Gamma','Prime','MK-II','MK-III','IX','VII'])}"
        if name in used:
            name = f"{name} {maxnum+1}"
        used.add(name)
        maxnum += 1
        eid = f"ENEMY-{maxnum:04d}"
        while eid in existing:
            maxnum += 1; eid = f"ENEMY-{maxnum:04d}"
        existing.add(eid)
        new.append({
            "id": eid, "name": name, "alignment": alignment, "element": element, "tier": tier,
            "hp": stats["HP"], "atk": stats["ATK"], "rapid": stats["RAPID"],
            "charge": stats["CHARGE"], "defense": stats["DEF"],
            "ai_pattern": random.choice(gc.ENEMY_AI),
            "weakness_element": random.choice([e for e in gc.ELEMENT_ROSTER if e != element] + ["None"]),
            "attack_pattern": gc.gen_moves(element, alignment, tier)[0],
            "reward_chip": f"CHIP-{random.randint(1, 1000):04d}",
            "reward_money": random.randint(50, 5000),
            "soul_drop_chance": round(random.uniform(0.05, 0.6), 2),
            "description": f"A {alignment.lower()} hostile entity of the {element} discipline, born from the {random.choice(gc.ALIGNMENT_FACTIONS[alignment])}.",
        })
    data["enemies"].extend(new)
    data["count"] = len(data["enemies"])
    json.dump(data, open(ENEMY_JSON, "w", encoding="utf-8"), indent=2)
    with open(ENEMY_CSV, "w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=["id","name","alignment","element","tier","hp","atk",
            "rapid","charge","defense","ai_pattern","weakness_element","attack_pattern",
            "reward_chip","reward_money","soul_drop_chance","description"])
        w.writeheader()
        for e in data["enemies"]:
            w.writerow(e)
    return len(new)


def append_careers(n=40):
    data = json.load(open(CAREER_JSON, encoding="utf-8"))
    existing = {c["id"] for c in data["career_paths"]}
    used = {c["title"] for c in data["career_paths"]}
    maxnum = max(int(c["id"].split("-")[1]) for c in data["career_paths"])
    random.seed(os.getpid() + 21)
    new = []
    for _ in range(n):
        arche = random.choice(gc.CAREER_ARCHETYPES)
        domain = random.choice(gc.CAREER_DOMAINS)
        alignment = random.choice(gc.ALIGNMENTS)
        element = random.choice(gc.ELEMENT_ROSTER)
        bias = random.choice(gc.CAREER_STAT_BIAS)
        penalty = random.choice([s for s in gc.CAREER_STAT_BIAS if s != bias])
        tier_unlock = random.choice([t[0] for t in gc.RANK_HIERARCHY[:9]])
        opener = random.choice(gc.CAREER_OPENERS)
        title = f"{arche} of the {domain}"
        if title in used:
            title = f"{arche} of the {domain} ({maxnum+1})"
        used.add(title)
        maxnum += 1
        cid = f"CAREER-{maxnum:03d}"
        while cid in existing:
            maxnum += 1; cid = f"CAREER-{maxnum:03d}"
        existing.add(cid)
        new.append({
            "id": cid, "title": title, "archetype": arche, "domain": domain,
            "alignment": alignment, "element": element, "tier_unlock": tier_unlock,
            "stat_bias": bias, "stat_penalty": penalty,
            "synergy_alignment": random.choice(gc.ALIGNMENTS),
            "synergy_element": random.choice(gc.ELEMENT_ROSTER),
            "opening_line": opener,
            "summary": f"{arche} — a {alignment}/{element} calling unlocked at {tier_unlock}.",
            "lore": (f"The {arche} walks a narrow path through the {domain}, bound to the "
                     f"{alignment} discipline and the {element} current. {opener} Their work bends "
                     f"toward {bias}, at the cost of {penalty}."),
        })
    data["career_paths"].extend(new)
    data["count"] = len(data["career_paths"])
    json.dump(data, open(CAREER_JSON, "w", encoding="utf-8"), indent=2)
    return len(new)


def git_commit_push(label):
    subprocess.run(["git", "add", "content/"], cwd=ROOT, check=True)
    # detect changes
    out = subprocess.run(["git", "status", "--porcelain", "content/"], cwd=ROOT,
                         capture_output=True, text=True)
    if not out.stdout.strip():
        return False
    subprocess.run(["git", "commit", "-q", "-m",
        f"HERMES overnight grind [{label}]: expanded chips/NetPs/enemies/careers (validated)"],
        cwd=ROOT, check=True)
    subprocess.run(["git", "push"], cwd=ROOT, check=True,
                   env={**os.environ, "GIT_TERMINAL_PROMPT": "0"})
    return True


def one_pass(pass_idx):
    added_netp = append_netps(pass_budget=3000)
    added_chip = append_chips(200)
    added_enemy = append_enemies(150)
    added_career = append_careers(40)
    # validate
    r = subprocess.run([sys.executable, os.path.join(CONTENT, "validate_content.py")],
                       cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        so = r.stdout[-600:] if r.stdout else "(no stdout)"
        se = r.stderr[-600:] if r.stderr else "(no stderr)"
        print(f"[pass {pass_idx}] VALIDATION FAILED — NOT committing:\n{so}\n{se}")
        return False
    pushed = git_commit_push(f"pass{pass_idx}")
    print(f"[pass {pass_idx}] +{added_netp} netp, +{added_chip} chips, "
          f"+{added_enemy} enemies, +{added_career} careers | validated | "
          f"{'pushed' if pushed else 'no change'}")
    return True


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--loop", action="store_true", help="loop until 0730 local")
    args = ap.parse_args()
    if not args.loop:
        one_pass(0)
        return
    idx = 0
    while True:
        now = datetime.now()
        if now.hour == 7 and now.minute >= 30:
            print("[grinder] reached 0730 — stopping per owner instruction")
            break
        if now.hour > 7:
            break
        ok = one_pass(idx)
        idx += 1
        # pace: ~90s between passes so we don't hammer the box
        import time
        time.sleep(90)


if __name__ == "__main__":
    main()
