#!/usr/bin/env python3
"""
R3ALN3T.EXE - Content Data Generator (HERMES lane: CONTENT-ONLY, asset-free)
============================================================================
Generates text/JSON/CSV content data that merges cleanly into the repo:

  1. content/chips/chip_database.json + .csv     -> Battle Chip database expansion (MMBN-style)
  2. content/netps/netp_cards.csv                 -> NetP profile DataTable rows (v3 25-col schema)
  3. content/enemies/enemy_database.json + .csv  -> Enemy definitions
  4. content/narrative/career_paths.json         -> 252 Career Path profiles (narrative text)
  5. content/narrative/act_end_scenes.json       -> Act-end scene dialogue/narrative

Design rules honored:
  - NetP CSV columns == generate_netp_v3_complete.py HEADERS (so it merges with the
    other agents' canonical pipeline / UE DataTable import).
  - Alignments restricted to the 4 philosophical types from v3: Mechanical, Viral,
    Angelic, Demonic.
  - Elements restricted to v3's 18-element roster.
  - Tiers follow v3's 16-rank Greek hierarchy (OMEGA..OMICRON).
  - All IDs unique. All stats within the documented tier bands.
  - Deterministic (seeded) so re-runs are reproducible.

Run:  python content/generate_content.py
"""

import csv
import json
import math
import os
import random

# -----------------------------------------------------------------------------
# VOCAB (mirrors generate_netp_v3_complete.py so outputs are compatible)
# -----------------------------------------------------------------------------
ALIGNMENTS = ["Mechanical", "Viral", "Angelic", "Demonic"]
ELEMENT_ROSTER = [
    "Fire", "Water", "Lightning", "Ice", "Wind", "Earth", "Light", "Dark",
    "Void", "Metal", "Nature", "Sound", "Gravity", "Time", "Blood",
    "Poison", "Crystal", "Plasma",
]
# 16-rank hierarchy: (tier, start, end, population_weight)
RANK_HIERARCHY = [
    ("OMEGA",   1,    100,   100),
    ("ALPHA",   101,  250,   150),
    ("BETA",    251,  500,   250),
    ("GAMMA",   501,  900,   400),
    ("DELTA",   901,  1600,  700),
    ("EPSILON", 1601, 2800,  1200),
    ("ZETA",    2801, 4500,  1700),
    ("ETA",     4501, 7000,  2500),
    ("THETA",   7001, 10500, 3500),
    ("IOTA",    10501, 15500, 5000),
    ("KAPPA",   15501, 22000, 6500),
    ("LAMBDA",  22001, 31000, 9000),
    ("MU",      31001, 44000, 13000),
    ("NU",      44001, 62000, 18000),
    ("XI",      62001, 87000, 25000),
    ("OMICRON", 87001, 120000, 33000),
]

TIER_STAT_RANGES = {
    "OMEGA":   {"HP": (8000, 12000), "ATK": (700, 1100), "RAPID": (85, 120), "CHARGE": (90, 130), "DEF": (600, 950)},
    "ALPHA":   {"HP": (6500, 9500),  "ATK": (550, 850),  "RAPID": (70, 100), "CHARGE": (75, 110), "DEF": (450, 750)},
    "BETA":    {"HP": (5000, 7500),  "ATK": (400, 650),  "RAPID": (55, 80),  "CHARGE": (60, 90),  "DEF": (350, 600)},
    "GAMMA":   {"HP": (3800, 5800),  "ATK": (300, 500),  "RAPID": (45, 65),  "CHARGE": (50, 75),  "DEF": (250, 450)},
    "DELTA":   {"HP": (2800, 4200),  "ATK": (220, 380),  "RAPID": (35, 55),  "CHARGE": (40, 60),  "DEF": (180, 350)},
    "EPSILON": {"HP": (2000, 3200),  "ATK": (160, 280),  "RAPID": (28, 45),  "CHARGE": (32, 50),  "DEF": (130, 260)},
    "ZETA":    {"HP": (1400, 2400),  "ATK": (110, 200),  "RAPID": (22, 36),  "CHARGE": (25, 40),  "DEF": (90, 190)},
    "ETA":     {"HP": (1000, 1700),  "ATK": (80, 150),   "RAPID": (17, 28),  "CHARGE": (20, 32),  "DEF": (65, 140)},
    "THETA":   {"HP": (700, 1200),   "ATK": (55, 100),   "RAPID": (13, 22),  "CHARGE": (15, 25),  "DEF": (45, 100)},
    "IOTA":    {"HP": (480, 850),    "ATK": (38, 72),    "RAPID": (10, 17),  "CHARGE": (11, 19),  "DEF": (30, 70)},
    "KAPPA":   {"HP": (320, 600),    "ATK": (25, 50),    "RAPID": (7, 13),   "CHARGE": (8, 14),   "DEF": (20, 48)},
    "LAMBDA":  {"HP": (200, 400),    "ATK": (16, 34),    "RAPID": (5, 9),    "CHARGE": (5, 10),   "DEF": (12, 32)},
    "MU":      {"HP": (120, 260),    "ATK": (10, 22),    "RAPID": (3, 6),    "CHARGE": (3, 7),    "DEF": (7, 20)},
    "NU":      {"HP": (70, 160),     "ATK": (6, 14),     "RAPID": (2, 4),    "CHARGE": (2, 5),    "DEF": (4, 12)},
    "XI":      {"HP": (40, 100),     "ATK": (3, 9),      "RAPID": (1, 3),    "CHARGE": (1, 3),    "DEF": (2, 7)},
    "OMICRON": {"HP": (20, 60),      "ATK": (2, 6),      "RAPID": (1, 2),    "CHARGE": (1, 2),    "DEF": (1, 4)},
}

ALIGNMENT_BIAS = {
    "Mechanical": ["DEF", "RAPID"],
    "Viral":      ["RAPID", "ATK"],
    "Angelic":    ["HP", "DEF", "CHARGE"],
    "Demonic":    ["ATK", "RAPID"],
}

ALIGNMENT_FACTIONS = {
    "Mechanical": ["SYNTHETIC NETWORK", "IRON CORTEX", "GEAR SECT", "PROTOCOL DIVISION"],
    "Viral":      ["CORRUPTED SECTOR", "PHAGE CELL", "ROT CLUSTER", "INFECTION VECTOR"],
    "Angelic":    ["CELESTIAL ORDER", "ASTRUM DIVISION", "HALO CORE", "LUMINA SECT"],
    "Demonic":    ["PANDEMONIUM NET", "ABYSSAL CABAL", "BRIMSTONE CELL", "VOID CULT"],
}

ELEMENT_WORDS = {
    "Fire": ["Ignite", "Blaze", "Ember", "Inferno", "Scorch", "Combust"],
    "Water": ["Torrent", "Tide", "Abyss", "Current", "Surge", "Depth"],
    "Lightning": ["Volt", "Spark", "Arc", "Thunder", "Static", "Surge"],
    "Ice": ["Frost", "Glacier", "Chill", "Crystal", "Freeze", "Hail"],
    "Wind": ["Gale", "Zephyr", "Cyclone", "Draft", "Squall", "Breeze"],
    "Earth": ["Quake", "Stone", "Terra", "Core", "Mountain", "Fissure"],
    "Light": ["Radiance", "Beam", "Prism", "Dawn", "Solar", "Lumen"],
    "Dark": ["Shadow", "Void", "Umbra", "Night", "Eclipse", "Abyss"],
    "Void": ["Null", "Erase", "Zero", "Entropy", "Collapse", "Abyss"],
    "Metal": ["Iron", "Steel", "Alloy", "Forge", "Plate", "Titan"],
    "Nature": ["Bloom", "Thorn", "Root", "Canopy", "Spore", "Vine"],
    "Sound": ["Resonance", "Echo", "Frequency", "Pulse", "Wave", "Tone"],
    "Gravity": ["Crush", "Weight", "Singularity", "Pull", "Anchor", "Mass"],
    "Time": ["Chrono", "Era", "Epoch", "Shift", "Loop", "Paradox"],
    "Blood": ["Sanguine", "Hemorrhage", "Vital", "Pulse", "Crimson", "Vein"],
    "Poison": ["Toxin", "Venom", "Plague", "Miasma", "Contagion", "Blight"],
    "Crystal": ["Shard", "Prism", "Facet", "Gem", "Lattice", "Geode"],
    "Plasma": ["Ion", "Flux", "Nebula", "Star", "Fusion", "Solar"],
}

ACTION_WORDS = {
    "Assault": ["Strike", "Slam", "Rush", "Barrage", "Charge", "Onslaught"],
    "Control": ["Lock", "Bind", "Suppress", "Silence", "Stun", "Drain"],
    "Support": ["Shield", "Restore", "Boost", "Cleanse", "Ward", "Empower"],
    "Burst": ["Overdrive", "Catalyst", "Apotheosis", "Cataclysm", "Zenith", "Terminus"],
}

MYTHIC_WORDS = ["Aether", "Nexus", "Prime", "Eternal", "Celestial", "Nether", "Astral",
                "Chrono", "Omni", "Void", "Solar", "Lunar", "Stellar", "Ethereal",
                "Prismatic", "Quantum", "Neural", "Synaptic", "Digital", "Phantom"]

NAME_PREFIXES = ["Xen", "Kael", "Vor", "Zyr", "Thal", "Nex", "Om", "Ryx", "Vex", "Lun",
                 "Sol", "Aer", "Mor", "Dra", "Kry", "Fen", "Gor", "Hel", "Ish", "Jor",
                 "Kal", "Lyr", "Myr", "Nyx", "Oph", "Pyr", "Qor", "Rav", "Syl", "Tor",
                 "Ulr", "Vyr", "Wyn", "Xal", "Yor", "Zep", "Axi", "Bry", "Cel", "Dus"]
NAME_CORES = ["thas", "dros", "mion", "vius", "rios", "nax", "gorn", "lis", "tor", "vek",
              "dra", "sion", "phos", "mir", "gon", "thos", "vax", "ron", "xis", "lor",
              "thar", "vion", "mire", "kros", "zane", "phir", "dune", "vex", "nir", "sol",
              "vire", "morn", "kale", "zire", "pher", "dris", "vorn", "xel"]
NAME_SUFFIXES = ["ion", "ax", "os", "is", "ar", "eth", "on", "us", "ir", "an",
                 "iel", "ael", "oth", "ath", "un", "or", "as", "en", "il", "ur"]
FACTION_TITLES = {
    "Mechanical": ["Unit", "Drone", "Construct", "Core", "Protocol", "Frame"],
    "Viral":      ["Strain", "Vector", "Host", "Plague", "Mutant", "Cell"],
    "Angelic":    ["Seraph", "Guardian", "Warden", "Sentinel", "Archon", "Saint"],
    "Demonic":    ["Fiend", "Reaver", "Dread", "Terror", "Horror", "Beast"],
}

# -----------------------------------------------------------------------------
# NetP card generation (v3-compatible)
# -----------------------------------------------------------------------------
NETP_HEADERS = [
    "card_number", "tier", "rank", "name", "alignment", "element", "faction",
    "hp", "atk", "rapid", "charge", "defense",
    "move_1", "move_2", "move_3", "move_4", "move_5",
    "move_6", "move_7", "move_8", "move_9",
    "flavor_text", "construct_sprite", "source_identities", "color_palette",
]


def gen_netp_name(alignment, element, tier, cache):
    for _ in range(100):
        style = random.choice(["compound", "titled", "suffixed", "mythic"])
        if style == "compound":
            name = random.choice(NAME_PREFIXES) + random.choice(NAME_CORES)
        elif style == "titled":
            name = random.choice(NAME_CORES).capitalize() + " " + random.choice(FACTION_TITLES.get(alignment, ["Entity"]))
        elif style == "suffixed":
            name = random.choice(NAME_PREFIXES) + random.choice(NAME_SUFFIXES)
        else:
            name = random.choice(MYTHIC_WORDS) + random.choice(NAME_CORES).capitalize()
        if tier == "OMEGA":
            name = name.upper()
            if not name.endswith("TRINITY"):
                name = name + " TRINITY"
        if name not in cache:
            cache.add(name)
            return name
    fid = "%08X" % random.getrandbits(32)
    cache.add(fid)
    return "NETP-" + fid


def gen_stats(tier, alignment):
    ranges = TIER_STAT_RANGES.get(tier, TIER_STAT_RANGES["OMICRON"])
    bias = ALIGNMENT_BIAS.get(alignment, [])
    out = {}
    for stat, (low, high) in ranges.items():
        if stat in bias:
            lo = low + int(math.ceil((high - low) * 0.25))
            out[stat] = random.randint(lo, high)
        else:
            out[stat] = random.randint(low, high)
    return out


def gen_moves(element, alignment, tier):
    words = ELEMENT_WORDS.get(element, ["Action"])
    moves = []
    for action_type, count in [("Assault", 3), ("Control", 2), ("Support", 2), ("Burst", 2)]:
        for _ in range(count):
            w = random.choice(words)
            a = random.choice(ACTION_WORDS[action_type])
            moves.append(f"DIVINE.{w.upper()}.{a.upper()}" if tier == "OMEGA" else f"{w} {a}")
    random.shuffle(moves)
    return moves


def gen_flavor(alignment, element, tier, name):
    fac = random.choice(ALIGNMENT_FACTIONS[alignment])
    tmpl = {
        "Mechanical": f"Unit {name} deployed from {fac}. Core temperature stable. Elemental sync: {element}.",
        "Viral": f"Strain {name} breaches containment. {element}-mutation sequence active. Quarantine failed.",
        "Angelic": f"{name} descends from the {fac}. {element} radiance shields the faithful.",
        "Demonic": f"{name} claws forth from the {fac}. {element} burns in its wake.",
    }[alignment]
    return ("[PRIME LEADER] " + tmpl + " THREAT LEVEL: MAXIMUM.") if tier == "OMEGA" else tmpl


def gen_netp_cards(target_counts, seed=777):
    """target_counts: dict tier->count. Returns list of row-dicts (v3 schema)."""
    random.seed(seed)
    name_cache = set()
    tier_rank = {t[0]: i + 1 for i, t in enumerate(RANK_HIERARCHY)}
    rows = []
    for tier, count in target_counts.items():
        start = next(t[1] for t in RANK_HIERARCHY if t[0] == tier)
        for i in range(count):
            alignment = random.choice(ALIGNMENTS)
            element = random.choice(ELEMENT_ROSTER)
            name = gen_netp_name(alignment, element, tier, name_cache)
            stats = gen_stats(tier, alignment)
            moves = gen_moves(element, alignment, tier)
            flavor = gen_flavor(alignment, element, tier, name)
            card_number = f"{tier}-{start + i:03d}"
            safe = name.replace(" ", "_").replace(".", "").replace("-", "_")
            row = {
                "card_number": card_number,
                "tier": tier,
                "rank": str(tier_rank[tier]),
                "name": name,
                "alignment": alignment,
                "element": element,
                "faction": random.choice(ALIGNMENT_FACTIONS[alignment]),
                "hp": stats["HP"], "atk": stats["ATK"], "rapid": stats["RAPID"],
                "charge": stats["CHARGE"], "defense": stats["DEF"],
                "move_1": moves[0], "move_2": moves[1], "move_3": moves[2],
                "move_4": moves[3], "move_5": moves[4], "move_6": moves[5],
                "move_7": moves[6], "move_8": moves[7], "move_9": moves[8],
                "flavor_text": flavor,
                "construct_sprite": f"{card_number}_{safe}_idle.png",
                "source_identities": "|".join(f"ID.{random.randint(1000,9999)}" for _ in range(3)),
                "color_palette": str(ELEMENT_WORDS.get(element, [["#000000"]]) and ELEMENT_WORDS.get(element, {}).get("palette", ["#10101A"])) if False else str([random.randint(0,255) for _ in range(3)]),
            }
            rows.append(row)
    return rows


# -----------------------------------------------------------------------------
# Battle Chip database (MMBN-style)
# -----------------------------------------------------------------------------
CHIP_CODES = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "L", "P",
              "R", "S", "T", "U", "V", "W", "Z", "*"]
CHIP_CLASSES = ["Attack", "Recovery", "Program", "Support", "Summon", "Shield"]
CHIP_RARITY = ["Common", "Uncommon", "Rare", "Mega", "Giga"]

CHIP_FAMILIES = {
    "Cannon":   {"element": "Null",  "kind": "Attack",  "base": 40,  "text": "Fires a straight shot down the row."},
    "Shot":     {"element": "Null",  "kind": "Attack",  "base": 50,  "text": "Homes in on the nearest enemy."},
    "Bomb":     {"element": "Null",  "kind": "Attack",  "base": 60,  "text": "Explodes on impact, splash damage."},
    "Sword":    {"element": "Sword", "kind": "Attack",  "base": 80,  "text": "Slashes the enemy in the same column."},
    "Zap":      {"element": "Elec",  "kind": "Attack",  "base": 70,  "text": "Paralyzes and chains to adjacent foes."},
    "Fire":     {"element": "Fire",  "kind": "Attack",  "base": 90,  "text": "Engulfs the target in flames (Burn DOT)."},
    "Aqua":     {"element": "Aqua",  "kind": "Attack",  "base": 80,  "text": "Douses fire panels, heals on contact."},
    "Ice":      {"element": "Ice",   "kind": "Attack",  "base": 85,  "text": "Freezes the target, slows movement."},
    "Wind":     {"element": "Wind",  "kind": "Attack",  "base": 75,  "text": "Knocks the enemy back a tile."},
    "Wood":     {"element": "Wood",  "kind": "Attack",  "base": 70,  "text": "Roots the target, regen on hit."},
    "Panel":    {"element": "Null",  "kind": "Program", "base": 0,   "text": "Transforms panels under the enemy."},
    "Recover":  {"element": "Recov", "kind": "Recovery","base": 0,   "text": "Restores HP to the NetP."},
    "Sub":      {"element": "Null",  "kind": "Shield",  "base": 0,   "text": "Deploys a barrier with its own HP pool."},
    "Barrier":  {"element": "Null",  "kind": "Shield",  "base": 0,   "text": "Blocks the next incoming attack."},
    "Time":     {"element": "Time",  "kind": "Program", "base": 0,   "text": "Rewinds the NetP's HP by a few seconds."},
    "Shadow":   {"element": "Shadow","kind": "Attack",  "base": 95,  "text": "Strikes from the dark; crit amp."},
    "Break":    {"element": "Break", "kind": "Attack",  "base": 100, "text": "Breaks through defenses (ignores DEF)."},
    "Poison":   {"element": "Poison","kind": "Attack",  "base": 65,  "text": "Stacking damage-over-time on hit."},
    "Light":    {"element": "Light", "kind": "Attack",  "base": 88,  "text": "Blinds the target, boosts CHARGE."},
    "Void":     {"element": "Void",  "kind": "Attack",  "base": 105, "text": "Nullifies buffs, deals true damage."},
    "Plasma":   {"element": "Plasma","kind": "Attack",  "base": 98,  "text": "Penetrates and chains with burn."},
    "Crystal":  {"element": "Crystal","kind": "Attack", "base": 82,  "text": "Generates a barrier, amplifies stats."},
    "Sound":    {"element": "Sound", "kind": "Attack",  "base": 78,  "text": "Stuns in an area around the target."},
    "Gravity":  {"element": "Gravity","kind": "Attack", "base": 92,  "text": "Roots and deals HP% damage."},
    "Blood":    {"element": "Blood", "kind": "Attack",  "base": 90,  "text": "Life-drains; scales on missing HP."},
}

CHIP_SUFFIX = ["V1", "V2", "V3", "EX", "SP", "S", "R", "X", "Z", "Plus", "M", ""]


def gen_chips(count, seed=2024):
    random.seed(seed)
    chips = []
    used_names = set()
    tiers_pool = list(CHIP_FAMILIES.items())
    for n in range(1, count + 1):
        fam, fdef = random.choice(tiers_pool)
        # vary the name with a suffix to expand the DB
        attempts = 0
        while True:
            suf = random.choice(CHIP_SUFFIX)
            name = f"{fam}{(' ' + suf) if suf else ''}"
            if name not in used_names:
                used_names.add(name)
                break
            attempts += 1
            if attempts > 20:
                name = f"{fam}-{n}"
                used_names.add(name)
                break
        mb = max(4, min(99, fdef["base"] // 4 + random.randint(2, 14)))
        power = fdef["base"] + random.randint(-10, 25) if fdef["kind"] == "Attack" else 0
        rarity = random.choices(CHIP_RARITY, weights=[50, 28, 14, 6, 2])[0]
        code = random.choice(CHIP_CODES)
        chip = {
            "id": f"CHIP-{n:04d}",
            "name": name,
            "code": code,
            "mb": mb,
            "element": fdef["element"],
            "class": fdef["kind"],
            "power": power,
            "rarity": rarity,
            "description": fdef["text"],
            "effect": f"{fam} family — {fdef['kind']} chip"
                       + (f" dealing ~{power} {fdef['element']} damage." if power else "."),
            "target": "enemy" if fdef["kind"] in ("Attack", "Support") else "self",
            "droppable": True,
        }
        chips.append(chip)
    return chips


# -----------------------------------------------------------------------------
# Enemy definitions
# -----------------------------------------------------------------------------
ENEMY_KINDS = {
    "Mechanical": ["Sentinel Drone", "Patrol Construct", "Iron Warden", "Protocol Hound"],
    "Viral":      ["Phage Spore", "Rot Cluster", "Infection Node", "Decay Wraith"],
    "Angelic":    ["Fallen Seraph", "Halo Corruptor", "Lumina Stalker", "Astrum Judge"],
    "Demonic":    ["Brimstone Fiend", "Abyssal Reaver", "Void Terror", "Pandemonium Hound"],
}
ENEMY_AI = ["Rushdown", "Zone Control", "Buff Carrier", "Debuffer", "Sniper", "Summoner", "Tank", "Swarm"]


def gen_enemies(count, seed=909):
    random.seed(seed)
    enemies = []
    used = set()
    for n in range(1, count + 1):
        alignment = random.choice(ALIGNMENTS)
        element = random.choice(ELEMENT_ROSTER)
        tier = random.choices([t[0] for t in RANK_HIERARCHY[:10]],
                               weights=[2, 4, 7, 10, 12, 12, 10, 8, 6, 4])[0]
        stats = gen_stats(tier, alignment)
        base = random.choice(ENEMY_KINDS[alignment])
        name = f"{base} {random.choice(['Alpha','Beta','Gamma','Prime','MK-II','MK-III','IX','VII'])}"
        if name in used:
            name = f"{name} {n}"
        used.add(name)
        weak = random.choice([e for e in ELEMENT_ROSTER if e != element] + ["None"])
        enemies.append({
            "id": f"ENEMY-{n:04d}",
            "name": name,
            "alignment": alignment,
            "element": element,
            "tier": tier,
            "hp": stats["HP"], "atk": stats["ATK"], "rapid": stats["RAPID"],
            "charge": stats["CHARGE"], "defense": stats["DEF"],
            "ai_pattern": random.choice(ENEMY_AI),
            "weakness_element": weak,
            "attack_pattern": f"{gen_moves(element, alignment, tier)[0]}",
            "reward_chip": f"CHIP-{random.randint(1, 250):04d}",
            "reward_money": random.randint(50, 5000),
            "soul_drop_chance": round(random.uniform(0.05, 0.6), 2),
            "description": f"A {alignment.lower()} hostile entity of the {element} discipline, "
                           f"born from the {random.choice(ALIGNMENT_FACTIONS[alignment])}.",
        })
    return enemies


# -----------------------------------------------------------------------------
# Career Paths (252) + Act-end scenes (narrative text)
# -----------------------------------------------------------------------------
CAREER_ARCHETYPES = [
    "Grid Ranger", "Soul Binder", "Null Knight", "Cipher Monk", "Volt Lancer",
    "Cryo Warden", "Ember Templar", "Void Bishop", "Iron Sentinel", "Plague Herald",
    "Storm Caller", "Stone Fist", "Lumen Priest", "Umbra Stalker", "Pulse Smith",
    "Gravity Adept", "Chrono Walker", "Sanguine Lord", "Toxin Weaver", "Prism Mage",
    "Plasma Forge", "Beast Tamer", "Ghost Operative", "Echo Singer", "Mass Weaver",
    "Root Shaper", "Anvil Saint", "Static Ronin", "Zephyr Dervish", "Terra Colossus",
]
CAREER_DOMAINS = [
    "Cyber Square", "The Deep N3T", "Rogue Mesh", "Corporate Grid", "Free Node",
    "Celestial Order", "Abyssal Cabal", "Synthetic Network", "Phage Cluster", "Quiet Sector",
]
CAREER_STAT_BIAS = ["HP", "ATK", "RAPID", "CHARGE", "DEF"]
CAREER_OPENERS = [
    "You jack in at dawn, the grid still humming with leftover traffic.",
    "The first time the N3T spoke your name, you were already halfway gone.",
    "They told you the NetPs chose their handlers. They were wrong.",
    "A soul band is just a scar you can read. Yours opened on a Tuesday.",
    "The Kernal interface lit up and, for once, did not lie to you.",
    "Some careers are earned. Yours was inherited from a deleted account.",
    "You traded a body for a bandwidth cap and never looked back.",
    "There is a district that only opens for the desperate. You found the key.",
]


def gen_career_paths(count, seed=4242):
    random.seed(seed)
    paths = []
    used_titles = set()
    for n in range(1, count + 1):
        arche = random.choice(CAREER_ARCHETYPES)
        domain = random.choice(CAREER_DOMAINS)
        alignment = random.choice(ALIGNMENTS)
        element = random.choice(ELEMENT_ROSTER)
        bias = random.choice(CAREER_STAT_BIAS)
        penalty = random.choice([s for s in CAREER_STAT_BIAS if s != bias])
        tier_unlock = random.choice([t[0] for t in RANK_HIERARCHY[:9]])
        opener = random.choice(CAREER_OPENERS)
        title = f"{arche} of the {domain}"
        if title in used_titles:
            title = f"{arche} of the {domain} ({n})"
        used_titles.add(title)
        lore = (f"The {arche} walks a narrow path through the {domain}, bound to the "
                f"{alignment} discipline and the {element} current. {opener} Their work bends "
                f"toward {bias}, at the cost of {penalty}. The {random.choice(ALIGNMENT_FACTIONS[alignment])} "
                f"either recruits them or hunts them — there is rarely a middle tile.")
        paths.append({
            "id": f"CAREER-{n:03d}",
            "title": title,
            "archetype": arche,
            "domain": domain,
            "alignment": alignment,
            "element": element,
            "tier_unlock": tier_unlock,
            "stat_bias": bias,
            "stat_penalty": penalty,
            "synergy_alignment": random.choice(ALIGNMENTS),
            "synergy_element": random.choice(ELEMENT_ROSTER),
            "opening_line": opener,
            "summary": f"{arche} — a {alignment}/{element} calling unlocked at {tier_unlock}.",
            "lore": lore,
        })
    return paths


ACTS = [
    ("I", "Jack-In", "The R34L Room flickers as the PED finishes its handshake with the N3T."),
    ("II", "The Rogue Mesh", "The Rogue Mesh opens like a wound in the network's side."),
    ("III", "Corporate Grid", "Tower lights spill across the datastream; someone is auditing souls."),
    ("IV", "The Phage Bloom", "Viral static crawls up the columns; the Quiet Sector is no longer quiet."),
    ("V", "Celestial Fall", "A seraph fractures mid-flight and the Halo Core goes dark."),
    ("VI", "Abyssal Accord", "The Abyssal Cabal tables a treaty written in missing packets."),
    ("VII", "Synthetic Rebellion", "The Iron Cortex votes, and the result is not in the logs."),
    ("VIII", "Trinity Convergence", "Three soul bands — Serene, Twisted, Fractured — pull toward one point."),
]


def gen_act_end_scenes(seed=313):
    random.seed(seed)
    scenes = []
    for i, (num, title, setting) in enumerate(ACTS, 1):
        speakers = ["NetAdmin", "Trinity", "Tyranny", "Eternity", "System Voice"]
        dialogue = []
        for _ in range(random.randint(4, 6)):
            sp = random.choice(speakers)
            line = random.choice([
                "You were never supposed to reach this tile.",
                "The soul band holds. For now.",
                "They deleted the exit. So we build one.",
                "Every NetP you lost is still in the grid. Listen.",
                "Convergence is not a place. It is a decision.",
                "I am the part of you that refused to decrypt.",
                "The N3T remembers what the PED forgets.",
                "If we win, nobody credits the deleted accounts. Fine.",
            ])
            dialogue.append({"speaker": sp, "line": line})
        next_label = "FINALE" if i >= len(ACTS) else f"{ACTS[i][0]}"
        scenes.append({
            "act": num,
            "title": title,
            "scene_id": f"ACT{i}_END",
            "setting": setting,
            "participants": speakers,
            "dialogue": dialogue,
            "narration": f"Act {num} closes on the {title}. {setting} "
                         f"The choice you make here seeds the next act's grid.",
            "next_act_gate": f"Unlock ACT{next_label} by holding soul integrity above the cracked band.",
        })
    return scenes


# -----------------------------------------------------------------------------
# Output
# -----------------------------------------------------------------------------
def main():
    root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    out = {
        "chips": os.path.join(root, "content", "chips"),
        "netps": os.path.join(root, "content", "netps"),
        "enemies": os.path.join(root, "content", "enemies"),
        "narrative": os.path.join(root, "content", "narrative"),
    }
    for d in out.values():
        os.makedirs(d, exist_ok=True)

    # 1. Chips
    chips = gen_chips(800)
    with open(os.path.join(out["chips"], "chip_database.json"), "w", encoding="utf-8") as f:
        json.dump({"version": 1, "count": len(chips), "chips": chips}, f, indent=2)
    with open(os.path.join(out["chips"], "chip_database.csv"), "w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=["id", "name", "code", "mb", "element", "class",
                                          "power", "rarity", "description", "effect", "target", "droppable"])
        w.writeheader()
        for c in chips:
            w.writerow(c)
    print(f"[chips] {len(chips)} chips -> content/chips/")

    # 2. NetP DataTable rows (v3 schema)
    # Fill OMEGA..THETA to full tier capacity in the initial batch; the overnight
    # grinder (grind_append.py) fills IOTA..OMICRON progressively.
    netp_targets = {
        "OMEGA": 100, "ALPHA": 150, "BETA": 250, "GAMMA": 400, "DELTA": 700,
        "EPSILON": 1200, "ZETA": 1700, "ETA": 2500, "THETA": 3500,
    }
    netp_rows = gen_netp_cards(netp_targets)
    csv_path = os.path.join(out["netps"], "netp_cards.csv")
    with open(csv_path, "w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=NETP_HEADERS)
        w.writeheader()
        for r in netp_rows:
            w.writerow(r)
    print(f"[netps] {len(netp_rows)} NetP profile rows -> content/netps/netp_cards.csv")

    # 3. Enemies
    enemies = gen_enemies(600)
    with open(os.path.join(out["enemies"], "enemy_database.json"), "w", encoding="utf-8") as f:
        json.dump({"version": 1, "count": len(enemies), "enemies": enemies}, f, indent=2)
    with open(os.path.join(out["enemies"], "enemy_database.csv"), "w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=["id", "name", "alignment", "element", "tier",
                                          "hp", "atk", "rapid", "charge", "defense",
                                          "ai_pattern", "weakness_element", "attack_pattern",
                                          "reward_chip", "reward_money", "soul_drop_chance", "description"])
        w.writeheader()
        for e in enemies:
            w.writerow(e)
    print(f"[enemies] {len(enemies)} enemies -> content/enemies/")

    # 4. Career paths (252)
    careers = gen_career_paths(252)
    with open(os.path.join(out["narrative"], "career_paths.json"), "w", encoding="utf-8") as f:
        json.dump({"version": 1, "count": len(careers), "career_paths": careers}, f, indent=2)
    print(f"[narrative] {len(careers)} career paths -> content/narrative/career_paths.json")

    # 5. Act-end scenes
    acts = gen_act_end_scenes()
    with open(os.path.join(out["narrative"], "act_end_scenes.json"), "w", encoding="utf-8") as f:
        json.dump({"version": 1, "count": len(acts), "acts": acts}, f, indent=2)
    print(f"[narrative] {len(acts)} act-end scenes -> content/narrative/act_end_scenes.json")

    print("\nDONE. All content written under content/.")


if __name__ == "__main__":
    main()
