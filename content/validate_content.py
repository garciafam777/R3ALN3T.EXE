#!/usr/bin/env python3
"""
R3ALN3T.EXE - Content validator (HERMES lane)
Verifies all generated content/ artifacts: parse, unique IDs, tier bands, schema.
Run: python content/validate_content.py
"""
import csv
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CONTENT = os.path.join(ROOT, "content")
errors = []
ok = []


def check(cond, msg):
    (ok if cond else errors).append(msg)


# --- Tier bands (from generate_content.py) ---
TIER_STAT_RANGES = {
    "OMEGA": {"HP": (8000, 12000), "ATK": (700, 1100), "RAPID": (85, 120), "CHARGE": (90, 130), "DEF": (600, 950)},
    "ALPHA": {"HP": (6500, 9500), "ATK": (550, 850), "RAPID": (70, 100), "CHARGE": (75, 110), "DEF": (450, 750)},
    "BETA": {"HP": (5000, 7500), "ATK": (400, 650), "RAPID": (55, 80), "CHARGE": (60, 90), "DEF": (350, 600)},
    "GAMMA": {"HP": (3800, 5800), "ATK": (300, 500), "RAPID": (45, 65), "CHARGE": (50, 75), "DEF": (250, 450)},
    "DELTA": {"HP": (2800, 4200), "ATK": (220, 380), "RAPID": (35, 55), "CHARGE": (40, 60), "DEF": (180, 350)},
    "EPSILON": {"HP": (2000, 3200), "ATK": (160, 280), "RAPID": (28, 45), "CHARGE": (32, 50), "DEF": (130, 260)},
    "ZETA": {"HP": (1400, 2400), "ATK": (110, 200), "RAPID": (22, 36), "CHARGE": (25, 40), "DEF": (90, 190)},
    "ETA": {"HP": (1000, 1700), "ATK": (80, 150), "RAPID": (17, 28), "CHARGE": (20, 32), "DEF": (65, 140)},
    "THETA": {"HP": (700, 1200), "ATK": (55, 100), "RAPID": (13, 22), "CHARGE": (15, 25), "DEF": (45, 100)},
    "IOTA": {"HP": (480, 850), "ATK": (38, 72), "RAPID": (10, 17), "CHARGE": (11, 19), "DEF": (30, 70)},
    "KAPPA": {"HP": (320, 600), "ATK": (25, 50), "RAPID": (7, 13), "CHARGE": (8, 14), "DEF": (20, 48)},
    "LAMBDA": {"HP": (200, 400), "ATK": (16, 34), "RAPID": (5, 9), "CHARGE": (5, 10), "DEF": (12, 32)},
    "MU": {"HP": (120, 260), "ATK": (10, 22), "RAPID": (3, 6), "CHARGE": (3, 7), "DEF": (7, 20)},
    "NU": {"HP": (70, 160), "ATK": (6, 14), "RAPID": (2, 4), "CHARGE": (2, 5), "DEF": (4, 12)},
    "XI": {"HP": (40, 100), "ATK": (3, 9), "RAPID": (1, 3), "CHARGE": (1, 3), "DEF": (2, 7)},
    "OMICRON": {"HP": (20, 60), "ATK": (2, 6), "RAPID": (1, 2), "CHARGE": (1, 2), "DEF": (1, 4)},
}
VALID_TIERS = set(TIER_STAT_RANGES)
VALID_ALIGN = {"Mechanical", "Viral", "Angelic", "Demonic"}
VALID_ELEM = {"Fire", "Water", "Lightning", "Ice", "Wind", "Earth", "Light", "Dark",
              "Void", "Metal", "Nature", "Sound", "Gravity", "Time", "Blood",
              "Poison", "Crystal", "Plasma"}

# 1. Chips JSON
p = os.path.join(CONTENT, "chips", "chip_database.json")
check(os.path.exists(p), "chips JSON exists")
data = json.load(open(p, encoding="utf-8"))
chips = data["chips"]
ids = [c["id"] for c in chips]
check(len(ids) == len(set(ids)), f"chip IDs unique ({len(ids)})")
check(all(c["mb"] > 0 and c["mb"] <= 99 for c in chips), "chip MB in (0,99]")
ok.append(f"chips: {len(chips)} rows, all parse OK")

# 2. NetP CSV (v3 schema)
p = os.path.join(CONTENT, "netps", "netp_cards.csv")
rows = list(csv.DictReader(open(p, encoding="utf-8")))
check(len(rows) > 0, "NetP CSV non-empty")
netp_ids = [r["card_number"] for r in rows]
check(len(netp_ids) == len(set(netp_ids)), f"NetP card_number unique ({len(netp_ids)})")
for r in rows:
    check(r["tier"] in VALID_TIERS, f"tier valid {r['card_number']}")
    check(r["alignment"] in VALID_ALIGN, f"align valid {r['card_number']}")
    check(r["element"] in VALID_ELEM, f"elem valid {r['card_number']}")
    band = TIER_STAT_RANGES[r["tier"]]
    for s in ["hp", "atk", "rapid", "charge", "defense"]:
        v = int(r[s])
        lo, hi = band[s.upper().replace("DEFENSE", "DEF")]
        check(lo <= v <= hi, f"stat {s} in band {r['card_number']} ({v})")
    check(len([r[f"move_{i}"] for i in range(1, 10) if r[f"move_{i}"]]) == 9, f"9 moves {r['card_number']}")
ok.append(f"netps: {len(rows)} rows, schema/band/unique checks done")

# 3. Enemies
p = os.path.join(CONTENT, "enemies", "enemy_database.json")
data = json.load(open(p, encoding="utf-8"))
enemies = data["enemies"]
ids = [e["id"] for e in enemies]
check(len(ids) == len(set(ids)), f"enemy IDs unique ({len(ids)})")
for e in enemies:
    check(e["tier"] in VALID_TIERS, f"enemy tier {e['id']}")
    check(e["alignment"] in VALID_ALIGN, f"enemy align {e['id']}")
ok.append(f"enemies: {len(enemies)} rows, parse OK")

# 4. Career paths
p = os.path.join(CONTENT, "narrative", "career_paths.json")
data = json.load(open(p, encoding="utf-8"))
careers = data["career_paths"]
ids = [c["id"] for c in careers]
check(len(careers) == 252, f"career count == 252 (got {len(careers)})")
check(len(ids) == len(set(ids)), "career IDs unique")
check(all(c["lore"] and c["opening_line"] for c in careers), "career text present")
ok.append(f"careers: {len(careers)} paths, text present")

# 5. Act-end scenes
p = os.path.join(CONTENT, "narrative", "act_end_scenes.json")
data = json.load(open(p, encoding="utf-8"))
acts = data["acts"]
check(len(acts) == 8, f"acts == 8 (got {len(acts)})")
for a in acts:
    check(a["dialogue"] and len(a["dialogue"]) >= 4, f"act {a['act']} dialogue present")
ok.append(f"acts: {len(acts)} end scenes, dialogue present")

print("=== VALIDATION REPORT ===")
for m in ok:
    print("  [ok] " + m)
if errors:
    print(f"\n!!! {len(errors)} FAILURES:")
    for m in errors[:40]:
        print("  [FAIL] " + m)
    sys.exit(1)
print("\nALL CHECKS PASSED.")
