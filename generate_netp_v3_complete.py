#!/usr/bin/env python3
"""
R3ALN3T.EXE - NetP Card Generator v3.0
======================================
Generates Network Persona (NetP) cards for the R3ALN3T.EXE TCG.

Hierarchy: 16-rank Greek system per THE MYTHOS ORIGIN_3026
Alignments: 4 types (Mechanical, Viral, Angelic, Demonic)
Elements: 18 (Fire, Water, Lightning, Ice, Wind, Earth, Light, Dark, Void,
              Metal, Nature, Sound, Gravity, Time, Blood, Poison, Crystal, Plasma)

Usage:
    python generate_netp.py --count 100
    python generate_netp.py --tier OMEGA --count 10
    python generate_netp.py --batch 1000 --no-images
"""

import argparse
import csv
import json
import math
import os
import random
import sys
import uuid
from dataclasses import dataclass, field
from pathlib import Path
from typing import List, Dict, Optional, Tuple

# =============================================================================
# 1. THE TRINITY MATRIX - 16-RANK HIERARCHY (Mythos Origin Compliant)
# =============================================================================

RANK_HIERARCHY = [
    # (rank, greek, prefix, start_num, end_num, population, tier_label)
    (1,  "OMEGA",   "Ω",  1,     100,    100,   "PRIME"),
    (2,  "ALPHA",   "Α",  101,   250,    150,   "ELITE"),
    (3,  "BETA",    "Β",  251,   500,    250,   "VETERAN"),
    (4,  "GAMMA",   "Γ",  501,   900,    400,   "SEASONED"),
    (5,  "DELTA",   "Δ",  901,   1600,   700,   "ADEPT"),
    (6,  "EPSILON", "Ε",  1601,  2800,   1200,  "SKILLED"),
    (7,  "ZETA",    "Ζ",  2801,  4500,   1700,  "PROVEN"),
    (8,  "ETA",     "Η",  4501,  7000,   2500,  "CAPABLE"),
    (9,  "THETA",   "Θ",  7001,  10500,  3500,  "ESTABLISHED"),
    (10, "IOTA",    "Ι",  10501, 15500,  5000,  "COMPETENT"),
    (11, "KAPPA",   "Κ",  15501, 22000,  6500,  "PRACTICED"),
    (12, "LAMBDA",  "Λ",  22001, 31000,  9000,  "TRAINED"),
    (13, "MU",      "Μ",  31001, 44000,  13000, "INITIATE"),
    (14, "NU",      "Ν",  44001, 62000,  18000, "NOVICE"),
    (15, "XI",      "Ξ",  62001, 87000,  25000, "APPRENTICE"),
    (16, "OMICRON", "Ο",  87001, 120000, 33000, "RECRUIT"),
]

# Build lookup structures
TIER_BY_NAME = {row[1]: {
    "rank": row[0],
    "greek": row[1],
    "prefix": row[2],
    "start": row[3],
    "end": row[4],
    "population": row[5],
    "label": row[6],
} for row in RANK_HIERARCHY}

TIER_NAMES = [row[1] for row in RANK_HIERARCHY]
TIER_WEIGHTS = [row[5] for row in RANK_HIERARCHY]  # Population-weighted for random roll

# Stat ranges per tier (HP, ATK, RAPID, CHARGE, DEF)
# Higher rank = better stats, wider variance at apex
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

# =============================================================================
# 2. THE TYPE - 4 Philosophical Alignments
# =============================================================================

ALIGNMENTS = {
    "Mechanical": {
        "stat_bias": ["DEF", "RAPID"],
        "factions": ["SYNTHETIC NETWORK", "IRON CORTEX", "GEAR SECT", "PROTOCOL DIVISION"],
        "keywords": ["Protocol", "System", "Unit", "Construct", "Drone", "Core", "Matrix"],
        "shape": "angular_armored",
        "body_traits": ["plate_segments", "hydraulic_joints", "optical_sensors", "exposed_wiring"],
    },
    "Viral": {
        "stat_bias": ["RAPID", "ATK"],
        "factions": ["CORRUPTED SECTOR", "PHAGE CELL", "ROT CLUSTER", "INFECTION VECTOR"],
        "keywords": ["Strain", "Vector", "Host", "Plague", "Decay", "Spread", "Mutate"],
        "shape": "amorphous_glitch",
        "body_traits": ["tendril_appendages", "pixel_decay", "bio_luminescence", "fragmenting_form"],
    },
    "Angelic": {
        "stat_bias": ["HP", "DEF", "CHARGE"],
        "factions": ["CELESTIAL ORDER", "ASTRUM DIVISION", "HALO CORE", "LUMINA SECT"],
        "keywords": ["Seraph", "Halo", "Wing", "Grace", "Divine", "Aegis", "Sanctum"],
        "shape": "winged_humanoid",
        "body_traits": ["feathered_wings", "radiant_aura", "halo_crown", "flowing_robes"],
    },
    "Demonic": {
        "stat_bias": ["ATK", "RAPID"],
        "factions": ["PANDEMONIUM NET", "ABYSSAL CABAL", "BRIMSTONE CELL", "VOID CULT"],
        "keywords": ["Imp", "Fiend", "Horn", "Claw", "Inferno", "Doom", "Terror"],
        "shape": "horned_beast",
        "body_traits": ["curved_horns", "barbed_tail", "burning_eyes", "scaled_hide"],
    },
}

# =============================================================================
# 3. THE ELEMENT - 18 Combat/Environmental Synchronization Loop
# =============================================================================

ELEMENT_ROSTER = {
    "Fire": {
        "words": ["Ignite", "Blaze", "Ember", "Inferno", "Scorch", "Combust"],
        "effect": "Burn DOT + ATK boost on critical",
        "palette": [(255, 69, 0), (255, 140, 0), (178, 34, 34), (220, 20, 60)],
    },
    "Water": {
        "words": ["Torrent", "Tide", "Abyss", "Current", "Surge", "Depth"],
        "effect": "Heal over time + DEF scaling",
        "palette": [(0, 105, 148), (64, 164, 223), (0, 191, 255), (25, 25, 112)],
    },
    "Lightning": {
        "words": ["Volt", "Spark", "Arc", "Thunder", "Static", "Surge"],
        "effect": "Chain damage + RAPID scaling",
        "palette": [(255, 255, 0), (147, 112, 219), (75, 0, 130), (240, 230, 140)],
    },
    "Ice": {
        "words": ["Frost", "Glacier", "Chill", "Crystal", "Freeze", "Hail"],
        "effect": "Slow + DEF shred on hit",
        "palette": [(176, 224, 230), (0, 255, 255), (240, 248, 255), (119, 136, 153)],
    },
    "Wind": {
        "words": ["Gale", "Zephyr", "Cyclone", "Draft", "Squall", "Breeze"],
        "effect": "Dodge chance + RAPID boost",
        "palette": [(152, 251, 152), (144, 238, 144), (50, 205, 50), (34, 139, 34)],
    },
    "Earth": {
        "words": ["Quake", "Stone", "Terra", "Core", "Mountain", "Fissure"],
        "effect": "Shield generation + HP scaling",
        "palette": [(139, 69, 19), (160, 82, 45), (210, 180, 140), (85, 107, 47)],
    },
    "Light": {
        "words": ["Radiance", "Beam", "Prism", "Dawn", "Solar", "Lumen"],
        "effect": "Blind + CHARGE generation",
        "palette": [(255, 255, 224), (255, 215, 0), (255, 250, 205), (255, 223, 0)],
    },
    "Dark": {
        "words": ["Shadow", "Void", "Umbra", "Night", "Eclipse", "Abyss"],
        "effect": "Stealth + critical damage amp",
        "palette": [(25, 25, 25), (47, 79, 79), (72, 61, 139), (0, 0, 0)],
    },
    "Void": {
        "words": ["Null", "Erase", "Abyss", "Zero", "Entropy", "Collapse"],
        "effect": "Nullify buffs + true damage",
        "palette": [(75, 0, 130), (25, 25, 112), (0, 0, 139), (72, 61, 139)],
    },
    "Metal": {
        "words": ["Iron", "Steel", "Alloy", "Forge", "Plate", "Titan"],
        "effect": "Armor stacking + reflect damage",
        "palette": [(192, 192, 192), (169, 169, 169), (112, 128, 144), (47, 79, 79)],
    },
    "Nature": {
        "words": ["Bloom", "Thorn", "Root", "Canopy", "Spore", "Vine"],
        "effect": "Regen + summon minions",
        "palette": [(34, 139, 34), (107, 142, 35), (154, 205, 50), (85, 107, 47)],
    },
    "Sound": {
        "words": ["Resonance", "Echo", "Frequency", "Pulse", "Wave", "Tone"],
        "effect": "Stun + area disruption",
        "palette": [(255, 20, 147), (199, 21, 133), (218, 112, 214), (221, 160, 221)],
    },
    "Gravity": {
        "words": ["Crush", "Weight", "Singularity", "Pull", "Anchor", "Mass"],
        "effect": "Root + HP% damage",
        "palette": [(72, 61, 139), (25, 25, 112), (0, 0, 128), (47, 79, 79)],
    },
    "Time": {
        "words": ["Chrono", "Era", "Epoch", "Shift", "Loop", "Paradox"],
        "effect": "Rewind HP + action speed",
        "palette": [(0, 206, 209), (64, 224, 208), (72, 209, 204), (0, 128, 128)],
    },
    "Blood": {
        "words": ["Sanguine", "Hemorrhage", "Vital", "Pulse", "Crimson", "Vein"],
        "effect": "Life drain + ATK scaling on missing HP",
        "palette": [(139, 0, 0), (178, 34, 34), (220, 20, 60), (128, 0, 0)],
    },
    "Poison": {
        "words": ["Toxin", "Venom", "Plague", "Miasma", "Contagion", "Blight"],
        "effect": "Stacking DOT + debuff spread",
        "palette": [(0, 128, 0), (107, 142, 35), (85, 107, 47), (34, 139, 34)],
    },
    "Crystal": {
        "words": ["Shard", "Prism", "Facet", "Gem", "Lattice", "Geode"],
        "effect": "Barrier + stat amplification",
        "palette": [(255, 182, 193), (255, 192, 203), (219, 112, 147), (199, 21, 133)],
    },
    "Plasma": {
        "words": ["Ion", "Flux", "Nebula", "Star", "Fusion", "Solar"],
        "effect": "Penetration + burn + chain",
        "palette": [(255, 0, 255), (238, 130, 238), (218, 112, 214), (186, 85, 211)],
    },
}

ACTION_WORDS = {
    "Assault": ["Strike", "Slam", "Rush", "Barrage", "Charge", "Onslaught"],
    "Control": ["Lock", "Bind", "Suppress", "Silence", "Stun", "Drain"],
    "Support": ["Shield", "Restore", "Boost", "Cleanse", "Ward", "Empower"],
    "Burst": ["Overdrive", "Catalyst", "Apotheosis", "Cataclysm", "Zenith", "Terminus"],
}

MYTHIC_WORDS = [
    "Aether", "Nexus", "Prime", "Eternal", "Celestial", "Nether", "Astral",
    "Chrono", "Omni", "Void", "Solar", "Lunar", "Stellar", "Ethereal",
    "Prismatic", "Quantum", "Neural", "Synaptic", "Digital", "Phantom",
]

# =============================================================================
# 4. NAME GENERATION
# =============================================================================

NAME_PREFIXES = [
    "Xen", "Kael", "Vor", "Zyr", "Thal", "Nex", "Om", "Ryx", "Vex", "Lun",
    "Sol", "Aer", "Mor", "Dra", "Kry", "Fen", "Gor", "Hel", "Ish", "Jor",
    "Kal", "Lyr", "Myr", "Nyx", "Oph", "Pyr", "Qor", "Rav", "Syl", "Tor",
    "Ulr", "Vyr", "Wyn", "Xal", "Yor", "Zep", "Axi", "Bry", "Cel", "Dus",
]

NAME_CORES = [
    "thas", "dros", "mion", "vius", "rios", "nax", "gorn", "lis", "tor", "vek",
    "dra", "sion", "phos", "mir", "gon", "thos", "vax", "ron", "xis", "lor",
    "thar", "vion", "mire", "kros", "zane", "phir", "dune", "vex", "nir", "sol",
    "thos", "vire", "morn", "kale", "zire", "pher", "dris", "vorn", "mire", "xel",
]

NAME_SUFFIXES = [
    "ion", "ax", "os", "is", "ar", "eth", "on", "us", "ir", "an",
    "iel", "ael", "oth", "ath", "un", "or", "as", "en", "il", "ur",
    "ix", "ox", "ex", "az", "ez", "oz", "uz", "am", "em", "im",
]

FACTION_TITLES = {
    "Mechanical": ["Unit", "Drone", "Construct", "Core", "Protocol", "Frame"],
    "Viral":      ["Strain", "Vector", "Host", "Plague", "Mutant", "Cell"],
    "Angelic":    ["Seraph", "Guardian", "Warden", "Sentinel", "Archon", "Saint"],
    "Demonic":    ["Fiend", "Reaver", "Dread", "Terror", "Horror", "Beast"],
}

# =============================================================================
# 5. DATA CLASSES
# =============================================================================

@dataclass
class SourceCharacter:
    name: str
    identity: str
    base_class: str
    level: int
    element: str

@dataclass
class NetPCard:
    card_number: str
    tier: str
    rank: int
    name: str
    alignment: str
    element: str
    faction: str
    hp: int
    atk: int
    rapid: int
    charge: int
    defense: int
    moves: List[str]
    flavor_text: str
    construct_sprite: str
    source_identities: List[str]
    color_palette: List[Tuple[int, int, int]]

# =============================================================================
# 6. NAME DRAFTING ENGINE
# =============================================================================

generated_names_cache: set = set()

def generate_unique_name(alignment: str, element: str, tier: str) -> str:
    """Generate a unique fantasy name for a NetP construct."""
    max_attempts = 100
    for attempt in range(max_attempts):
        style = random.choice(["compound", "titled", "suffixed", "mythic"])

        if style == "compound":
            prefix = random.choice(NAME_PREFIXES)
            core = random.choice(NAME_CORES)
            name = f"{prefix}{core}"
        elif style == "titled":
            core = random.choice(NAME_CORES).capitalize()
            title = random.choice(FACTION_TITLES.get(alignment, ["Entity"]))
            name = f"{core} {title}"
        elif style == "suffixed":
            prefix = random.choice(NAME_PREFIXES)
            suffix = random.choice(NAME_SUFFIXES)
            name = f"{prefix}{suffix}"
        else:  # mythic
            mythic = random.choice(MYTHIC_WORDS)
            core = random.choice(NAME_CORES).capitalize()
            name = f"{mythic}{core}"

        # OMEGA special: force uppercase, add TRINITY suffix
        if tier == "OMEGA":
            name = name.upper()
            if not name.endswith("TRINITY"):
                name = f"{name} TRINITY"

        if name not in generated_names_cache:
            generated_names_cache.add(name)
            return name

    # Fallback with UUID-based suffix (guarantees uniqueness)
    unique_id = str(uuid.uuid4())[:8].upper()
    fallback_name = f"NETP-{unique_id}"
    generated_names_cache.add(fallback_name)
    return fallback_name

# =============================================================================
# 7. STAT GENERATION
# =============================================================================

def generate_stats(tier: str, alignment: str) -> Dict[str, int]:
    """Generate RPG stats biased toward alignment strengths."""
    ranges = TIER_STAT_RANGES.get(tier, TIER_STAT_RANGES["OMICRON"])
    bias_stats = ALIGNMENTS.get(alignment, {}).get("stat_bias", [])

    stats = {}
    for stat, (low, high) in ranges.items():
        if stat in bias_stats:
            # Biased: upper 75% of range (using proper math.ceil for rounding)
            range_size = high - low
            biased_low = low + int(math.ceil(range_size * 0.25))
            val = random.randint(biased_low, high)
        else:
            val = random.randint(low, high)
        stats[stat] = val

    return stats

# =============================================================================
# 8. MOVE GENERATION
# =============================================================================

def generate_moves(element: str, alignment: str, tier: str) -> List[str]:
    """Generate 9 localized moves from element + action pools."""
    element_words = ELEMENT_ROSTER.get(element, {}).get("words", ["Action"])
    moves = []

    # 3 Assault, 2 Control, 2 Support, 2 Burst
    action_distribution = [
        ("Assault", 3), ("Control", 2), ("Support", 2), ("Burst", 2)
    ]

    for action_type, count in action_distribution:
        action_list = ACTION_WORDS.get(action_type, ["Act"])
        for _ in range(count):
            word = random.choice(element_words) if element_words else "Action"
            action = random.choice(action_list)

            # OMEGA special formatting
            if tier == "OMEGA":
                move = f"DIVINE.{word.upper()}.{action.upper()}"
            else:
                move = f"{word} {action}"

            moves.append(move)

    random.shuffle(moves)
    assert len(moves) == 9, f"Move generation failed: expected 9 moves, got {len(moves)}"
    return moves

# =============================================================================
# 9. FLAVOR TEXT GENERATION
# =============================================================================

def generate_flavor(alignment: str, element: str, tier: str, name: str) -> str:
    """Generate lore-appropriate flavor text."""
    templates = {
        "Mechanical": [
            f"Unit {name} deployed from {random.choice(ALIGNMENTS['Mechanical']['factions'])}. Core temperature stable. Elemental sync: {element}.",
            f"Constructed in the forges of the {random.choice(ALIGNMENTS['Mechanical']['factions'])}. {element}-infused plating detected.",
            f"Autonomous warframe {name}. Primary directive: neutralize. Secondary: adapt to {element} vectors.",
        ],
        "Viral": [
            f"Strain {name} breaches containment. {element}-mutation sequence active. Quarantine failed.",
            f"Host {name} exhibits {element}-resonant corruption. Origin: {random.choice(ALIGNMENTS['Viral']['factions'])}.",
            f"Infection vector {name} spreads through {element}-saturated networks. No firewall stops it.",
        ],
        "Angelic": [
            f"{name} descends from the {random.choice(ALIGNMENTS['Angelic']['factions'])}. {element} radiance shields the faithful.",
            f"Seraph-class entity {name} channels {element} through halo conduits. Blessings upon activation.",
            f"Warden {name} of the {random.choice(ALIGNMENTS['Angelic']['factions'])}. {element} sanctum protocols engaged.",
        ],
        "Demonic": [
            f"{name} claws forth from the {random.choice(ALIGNMENTS['Demonic']['factions'])}. {element} burns in its wake.",
            f"Fiend {name} bound by {element} pacts. Blood price: eternal. Contract signed in ash.",
            f"Terror-class {name} hunts through {element}-veiled shadows. The {random.choice(ALIGNMENTS['Demonic']['factions'])} claims another soul.",
        ],
    }

    text = random.choice(templates[alignment])

    if tier == "OMEGA":
        text = f"[PRIME LEADER] {text} THREAT LEVEL: MAXIMUM."

    return text

# =============================================================================
# 10. CARD NUMBERING
# =============================================================================

# Global counter for sequential numbering per tier
tier_counters: Dict[str, int] = {}

def get_next_card_number(tier: str) -> str:
    """Get the next sequential card number for a tier."""
    if tier not in tier_counters:
        tier_counters[tier] = TIER_BY_NAME[tier]["start"] - 1
    
    tier_counters[tier] += 1
    num = tier_counters[tier]
    
    # Validate within tier bounds
    tier_info = TIER_BY_NAME[tier]
    if num > tier_info["end"]:
        raise ValueError(f"Tier {tier} card counter ({num}) exceeds max ({tier_info['end']})")
    
    # Format: TIER-### (e.g., OMEGA-001, ALPHA-101)
    return f"{tier}-{num:03d}"

# =============================================================================
# 11. SOURCE CHARACTER LOADING
# =============================================================================

def load_source_characters(csv_path: str) -> List[SourceCharacter]:
    """Load source characters from CSV."""
    characters = []

    if not os.path.exists(csv_path):
        # Create dummy data for testing
        print(f"[WARN] {csv_path} not found. Generating dummy source characters...")
        for i in range(500):
            characters.append(SourceCharacter(
                name=f"Source_{i}",
                identity=f"ID.{random.randint(1000, 9999)}",
                base_class=random.choice(["Warrior", "Mage", "Rogue", "Tank", "Healer"]),
                level=random.randint(1, 99),
                element=random.choice(list(ELEMENT_ROSTER.keys())),
            ))
        return characters

    with open(csv_path, 'r', encoding='utf-8') as f:
        reader = csv.DictReader(f)
        for row in reader:
            characters.append(SourceCharacter(
                name=row.get("name", f"Unknown_{len(characters)}"),
                identity=row.get("identity", f"ID.{random.randint(1000, 9999)}"),
                base_class=row.get("class", "Unknown"),
                level=int(row.get("level", random.randint(1, 99))),
                element=row.get("element", random.choice(list(ELEMENT_ROSTER.keys()))),
            ))

    return characters

# =============================================================================
# 12. CARD GENERATION ENGINE
# =============================================================================

def generate_card(
    source_chars: List[SourceCharacter],
    forced_tier: Optional[str] = None,
    forced_alignment: Optional[str] = None,
    forced_element: Optional[str] = None,
) -> NetPCard:
    """Generate a single NetP card from 3 source characters."""

    # Select 3 source characters
    if len(source_chars) < 3:
        # Pad with random if not enough
        selected = source_chars + [random.choice(source_chars) for _ in range(3 - len(source_chars))]
    else:
        selected = random.sample(source_chars, 3)

    host = selected[0]

    # Determine tier
    if forced_tier:
        tier = forced_tier.upper()
    else:
        tier = random.choices(TIER_NAMES, weights=TIER_WEIGHTS, k=1)[0]

    # Determine alignment
    if forced_alignment:
        alignment = forced_alignment
    else:
        alignment = random.choice(list(ALIGNMENTS.keys()))

    # Determine element
    if forced_element:
        element = forced_element
    else:
        element = random.choice(list(ELEMENT_ROSTER.keys()))

    # Generate name
    name = generate_unique_name(alignment, element, tier)

    # Generate stats
    stats = generate_stats(tier, alignment)

    # Generate moves
    moves = generate_moves(element, alignment, tier)

    # Generate flavor
    flavor = generate_flavor(alignment, element, tier, name)

    # Get faction
    faction = random.choice(ALIGNMENTS[alignment]["factions"])

    # Card number
    card_number = get_next_card_number(tier)

    # Construct sprite filename
    safe_name = name.replace(" ", "_").replace(".", "").replace("-", "_")
    construct_sprite = f"{card_number}_{safe_name}_idle.png"

    # Color palette
    palette = ELEMENT_ROSTER[element]["palette"]

    return NetPCard(
        card_number=card_number,
        tier=tier,
        rank=TIER_BY_NAME[tier]["rank"],
        name=name,
        alignment=alignment,
        element=element,
        faction=faction,
        hp=stats["HP"],
        atk=stats["ATK"],
        rapid=stats["RAPID"],
        charge=stats["CHARGE"],
        defense=stats["DEF"],
        moves=moves,
        flavor_text=flavor,
        construct_sprite=construct_sprite,
        source_identities=[c.identity for c in selected],
        color_palette=palette,
    )

# =============================================================================
# 13. CARD IMAGE GENERATION (Pillow-based procedural art)
# =============================================================================

class CardImageGenerator:
    """Generate visual TCG card PNGs with procedural 3D-style character art."""

    CARD_WIDTH = 750
    CARD_HEIGHT = 1050

    def __init__(self, output_dir: str):
        self.output_dir = Path(output_dir)
        self.output_dir.mkdir(parents=True, exist_ok=True)

        try:
            from PIL import Image, ImageDraw, ImageFont, ImageFilter
            self.Image = Image
            self.ImageDraw = ImageDraw
            self.ImageFont = ImageFont
            self.ImageFilter = ImageFilter
            self.has_pil = True
        except ImportError:
            self.has_pil = False
            print("[WARN] Pillow not installed. Card images will not be generated.")
            print("       Install with: pip install Pillow")

    def _get_font(self, size: int):
        """Get a font, falling back to default if not available."""
        try:
            # Try to load a monospace font for cyberpunk feel
            return self.ImageFont.truetype("DejaVuSansMono.ttf", size)
        except:
            try:
                return self.ImageFont.truetype("arial.ttf", size)
            except:
                return self.ImageFont.load_default()

    def _draw_3d_character(self, draw, card: NetPCard, cx: int, cy: int, w: int, h: int):
        """Draw a procedural 3D-style character silhouette based on alignment/element."""
        alignment = card.alignment
        element = card.element
        tier = card.tier
        palette = card.color_palette

        primary = palette[0]
        secondary = palette[1] if len(palette) > 1 else primary
        accent = palette[2] if len(palette) > 2 else secondary

        # Tier-based glow intensity
        glow_mult = {
            "OMEGA": 3.0, "ALPHA": 2.5, "BETA": 2.0, "GAMMA": 1.7,
            "DELTA": 1.5, "EPSILON": 1.3, "ZETA": 1.2, "ETA": 1.1,
        }.get(tier, 1.0)

        # Body shape based on alignment
        if alignment == "Angelic":
            self._draw_angelic_form(draw, cx, cy, w, h, primary, secondary, accent, glow_mult)
        elif alignment == "Demonic":
            self._draw_demonic_form(draw, cx, cy, w, h, primary, secondary, accent, glow_mult)
        elif alignment == "Mechanical":
            self._draw_mechanical_form(draw, cx, cy, w, h, primary, secondary, accent, glow_mult)
        else:  # Viral
            self._draw_viral_form(draw, cx, cy, w, h, primary, secondary, accent, glow_mult)

        # Element aura effect
        self._draw_element_aura(draw, cx, cy, w, h, element, primary, glow_mult)

    def _draw_angelic_form(self, draw, cx, cy, w, h, p, s, a, glow):
        # Winged humanoid silhouette
        body_w, body_h = w // 3, h // 2
        x1, y1 = cx - body_w // 2, cy - body_h // 3
        x2, y2 = x1 + body_w, y1 + body_h

        # Body
        draw.ellipse([x1, y1, x2, y2], fill=p)
        # Wings
        wing_span = body_w * 2
        draw.polygon([
            (cx, y1 + 10),
            (cx - wing_span // 2, y1 - body_h // 3),
            (cx - wing_span // 3, y1 + body_h // 4),
            (cx + wing_span // 3, y1 + body_h // 4),
            (cx + wing_span // 2, y1 - body_h // 3),
        ], fill=s)
        # Halo
        draw.ellipse([cx - 15, y1 - 25, cx + 15, y1 - 5], outline=a, width=3)

    def _draw_demonic_form(self, draw, cx, cy, w, h, p, s, a, glow):
        # Horned beast silhouette
        body_w, body_h = w // 3, h // 2
        x1, y1 = cx - body_w // 2, cy - body_h // 3
        x2, y2 = x1 + body_w, y1 + body_h

        # Body (wider at top)
        draw.polygon([
            (cx, y1 - 20),
            (x2 + 10, y1 + body_h // 2),
            (cx, y2 + 20),
            (x1 - 10, y1 + body_h // 2),
        ], fill=p)
        # Horns
        draw.polygon([
            (cx - 15, y1 - 10),
            (cx - 35, y1 - 50),
            (cx - 5, y1 - 15),
        ], fill=s)
        draw.polygon([
            (cx + 15, y1 - 10),
            (cx + 35, y1 - 50),
            (cx + 5, y1 - 15),
        ], fill=s)
        # Tail
        draw.polygon([
            (x2 - 5, y2 - 10),
            (x2 + 30, y2 + 20),
            (x2 - 5, y2 + 5),
        ], fill=a)

    def _draw_mechanical_form(self, draw, cx, cy, w, h, p, s, a, glow):
        # Angular armored silhouette
        body_w, body_h = w // 3, h // 2
        x1, y1 = cx - body_w // 2, cy - body_h // 3
        x2, y2 = x1 + body_w, y1 + body_h

        # Main chassis (rectangular)
        draw.rectangle([x1, y1, x2, y2], fill=p, outline=s, width=3)
        # Shoulder plates
        draw.rectangle([x1 - 15, y1, x1 + 5, y1 + 25], fill=s)
        draw.rectangle([x2 - 5, y1, x2 + 15, y1 + 25], fill=s)
        # Optical sensor
        draw.ellipse([cx - 8, y1 + 10, cx + 8, y1 + 24], fill=a)
        # Hydraulic joints
        draw.line([(x1, y2), (x1 - 10, y2 + 30)], fill=s, width=4)
        draw.line([(x2, y2), (x2 + 10, y2 + 30)], fill=s, width=4)

    def _draw_viral_form(self, draw, cx, cy, w, h, p, s, a, glow):
        # Amorphous glitch silhouette
        body_w, body_h = w // 3, h // 2
        x1, y1 = cx - body_w // 2, cy - body_h // 3
        x2, y2 = x1 + body_w, y1 + body_h

        # Main blob (irregular)
        points = [
            (cx, y1 - 15),
            (x2 + 10, y1 + 20),
            (x2 + 5, y2 - 10),
            (cx + 15, y2 + 15),
            (cx - 15, y2 + 10),
            (x1 - 10, y2 - 15),
            (x1 - 5, y1 + 15),
        ]
        draw.polygon(points, fill=p)
        # Tendrils
        for i in range(3):
            tx = x1 - 20 - i * 15
            ty = y1 + 30 + i * 25
            draw.line([(x1, y1 + 30 + i * 20), (tx, ty)], fill=s, width=3)
            draw.ellipse([tx - 5, ty - 5, tx + 5, ty + 5], fill=a)
        # Glitch particles
        for _ in range(8):
            px = random.randint(x1 - 30, x2 + 30)
            py = random.randint(y1 - 20, y2 + 20)
            draw.rectangle([px, py, px + 4, py + 4], fill=a)

    def _draw_element_aura(self, draw, cx, cy, w, h, element, color, glow):
        """Draw element-specific aura effects around the character."""
        aura_radius = int(80 * glow)

        if element in ["Fire", "Plasma", "Lightning"]:
            # Flame particles
            for _ in range(int(12 * glow)):
                angle = random.uniform(0, 6.28)
                dist = random.randint(aura_radius - 20, aura_radius + 20)
                px = int(cx + dist * 0.5 * (1 if random.random() > 0.5 else -1) * abs(__import__('math').cos(angle)))
                py = int(cy + dist * __import__('math').sin(angle) * 0.3)
                size = random.randint(2, 6)
                draw.ellipse([px, py, px + size, py + size], fill=color)

        elif element in ["Ice", "Water", "Crystal"]:
            # Floating crystals/droplets
            for _ in range(int(8 * glow)):
                angle = random.uniform(0, 6.28)
                dist = random.randint(aura_radius - 15, aura_radius + 15)
                px = int(cx + dist * __import__('math').cos(angle))
                py = int(cy + dist * __import__('math').sin(angle) * 0.5)
                size = random.randint(3, 8)
                draw.polygon([
                    (px, py - size), (px + size, py), (px, py + size), (px - size, py)
                ], fill=color)

        elif element in ["Light", "Void", "Gravity"]:
            # Ring aura
            for r in range(int(40 * glow), int(60 * glow), 5):
                draw.ellipse([cx - r, cy - r // 2, cx + r, cy + r // 2], outline=color, width=1)

        else:
            # General particle field
            for _ in range(int(10 * glow)):
                px = random.randint(cx - aura_radius, cx + aura_radius)
                py = random.randint(cy - aura_radius // 2, cy + aura_radius // 2)
                draw.point((px, py), fill=color)

    def generate_card_image(self, card: NetPCard) -> str:
        """Generate a full card PNG and return the filepath."""
        if not self.has_pil:
            return ""

        img = self.Image.new('RGB', (self.CARD_WIDTH, self.CARD_HEIGHT), (15, 15, 25))
        draw = self.ImageDraw.Draw(img)

        primary = card.color_palette[0]
        secondary = card.color_palette[1] if len(card.color_palette) > 1 else primary

        # Background gradient simulation (simple blocks)
        for y in range(0, self.CARD_HEIGHT, 4):
            shade = int(15 + (y / self.CARD_HEIGHT) * 30)
            draw.line([(0, y), (self.CARD_WIDTH, y)], fill=(shade, shade, shade + 10))

        # Rarity border
        border_colors = {
            "OMEGA": (255, 215, 0),    # Gold
            "ALPHA": (192, 192, 192),  # Silver
            "BETA": (205, 127, 50),    # Bronze
        }
        border_color = border_colors.get(card.tier, (primary[0]//2, primary[1]//2, primary[2]//2))

        # Card border
        draw.rectangle([10, 10, self.CARD_WIDTH - 10, self.CARD_HEIGHT - 10], outline=border_color, width=6)
        draw.rectangle([18, 18, self.CARD_WIDTH - 18, self.CARD_HEIGHT - 18], outline=border_color, width=2)

        # Header bar
        draw.rectangle([20, 20, self.CARD_WIDTH - 20, 80], fill=(border_color[0]//3, border_color[1]//3, border_color[2]//3))

        # Card number & tier
        font_small = self._get_font(16)
        font_medium = self._get_font(20)
        font_large = self._get_font(28)
        font_title = self._get_font(32)

        draw.text((30, 25), f"[{card.card_number}]", fill=(255, 255, 255), font=font_medium)

        # Tier badge
        tier_x = self.CARD_WIDTH - 120
        draw.rectangle([tier_x, 25, tier_x + 100, 55], fill=border_color)
        tier_text = card.tier
        draw.text((tier_x + 10, 27), tier_text, fill=(0, 0, 0), font=font_medium)

        # Name
        name_y = 90
        draw.text((self.CARD_WIDTH // 2, name_y), card.name, fill=(255, 255, 255), font=font_title, anchor="mm")

        # Subtitle: Alignment | Element | Faction
        subtitle = f"{card.alignment}  |  {card.element}  |  {card.faction}"
        draw.text((self.CARD_WIDTH // 2, name_y + 40), subtitle, fill=secondary, font=font_small, anchor="mm")

        # Art area background
        art_y = 160
        art_h = 400
        draw.rectangle([40, art_y, self.CARD_WIDTH - 40, art_y + art_h], fill=(20, 20, 30), outline=border_color, width=2)

        # Draw 3D character in art area
        self._draw_3d_character(draw, card, self.CARD_WIDTH // 2, art_y + art_h // 2, 300, 300)

        # Element label in art area
        draw.rectangle([50, art_y + 10, 180, art_y + 40], fill=primary)
        draw.text((55, art_y + 13), card.element.upper(), fill=(0, 0, 0), font=font_small)

        # Stats box
        stats_y = art_y + art_h + 20
        stat_w = (self.CARD_WIDTH - 100) // 5
        stats = [("HP", card.hp), ("ATK", card.atk), ("RAPID", card.rapid), 
                 ("CHARGE", card.charge), ("DEF", card.defense)]

        for i, (label, val) in enumerate(stats):
            x = 40 + i * stat_w
            draw.rectangle([x, stats_y, x + stat_w - 5, stats_y + 60], fill=(30, 30, 40), outline=border_color, width=1)
            draw.text((x + 5, stats_y + 5), label, fill=(150, 150, 150), font=font_small)
            draw.text((x + 5, stats_y + 25), str(val), fill=(255, 255, 255), font=font_medium)

        # Moves section
        moves_y = stats_y + 80
        draw.text((40, moves_y), "PROTOCOL MOVES:", fill=border_color, font=font_medium)

        for i, move in enumerate(card.moves):
            y = moves_y + 30 + i * 28
            # Alternate background
            if i % 2 == 0:
                draw.rectangle([40, y - 2, self.CARD_WIDTH - 40, y + 22], fill=(25, 25, 35))

            # Action type indicator
            action_type = "???"
            if "DIVINE." in move or any(a in move for a in ACTION_WORDS["Assault"]):
                action_type = "A"
                type_color = (255, 80, 80)
            elif any(c in move for c in ACTION_WORDS["Control"]):
                action_type = "C"
                type_color = (80, 80, 255)
            elif any(s in move for s in ACTION_WORDS["Support"]):
                action_type = "S"
                type_color = (80, 255, 80)
            else:
                action_type = "B"
                type_color = (255, 215, 0)

            draw.rectangle([42, y, 62, y + 20], fill=type_color)
            draw.text((47, y + 2), action_type, fill=(0, 0, 0), font=font_small)
            draw.text((70, y + 2), move[:45], fill=(220, 220, 220), font=font_small)

        # Flavor text
        flavor_y = moves_y + 30 + 9 * 28 + 15
        draw.rectangle([40, flavor_y, self.CARD_WIDTH - 40, flavor_y + 60], fill=(20, 20, 25), outline=(60, 60, 60), width=1)

        # Wrap flavor text
        flavor = card.flavor_text
        words = flavor.split()
        lines = []
        current = ""
        for word in words:
            if len(current) + len(word) < 55:
                current += word + " "
            else:
                lines.append(current.strip())
                current = word + " "
        lines.append(current.strip())

        for i, line in enumerate(lines[:3]):
            draw.text((50, flavor_y + 5 + i * 18), line, fill=(180, 180, 180), font=font_small)

        # Footer
        draw.text((self.CARD_WIDTH // 2, self.CARD_HEIGHT - 25), 
                  f"R3ALN3T.EXE // NETP CONSTRUCT // {card.card_number}", 
                  fill=(100, 100, 100), font=font_small, anchor="mm")

        # Save
        safe_name = card.name.replace(" ", "_").replace(".", "").replace("-", "_")
        filename = f"{card.card_number}_{safe_name}.png"
        filepath = self.output_dir / filename
        img.save(filepath, "PNG")

        return str(filepath)

# =============================================================================
# 14. CSV EXPORT
# =============================================================================

HEADERS = [
    "card_number", "tier", "rank", "name", "alignment", "element", "faction",
    "hp", "atk", "rapid", "charge", "defense",
    "move_1", "move_2", "move_3", "move_4", "move_5",
    "move_6", "move_7", "move_8", "move_9",
    "flavor_text", "construct_sprite", "source_identities", "color_palette"
]

def card_to_row(card: NetPCard) -> Dict[str, str]:
    """Convert a NetPCard to a CSV row dict."""
    row = {
        "card_number": card.card_number,
        "tier": card.tier,
        "rank": str(card.rank),
        "name": card.name,
        "alignment": card.alignment,
        "element": card.element,
        "faction": card.faction,
        "hp": str(card.hp),
        "atk": str(card.atk),
        "rapid": str(card.rapid),
        "charge": str(card.charge),
        "defense": str(card.defense),
        "flavor_text": card.flavor_text,
        "construct_sprite": card.construct_sprite,
        "source_identities": "|".join(card.source_identities),
        "color_palette": str(card.color_palette),
    }

    for i, move in enumerate(card.moves, 1):
        row[f"move_{i}"] = move

    # Fill empty moves
    for i in range(len(card.moves) + 1, 10):
        row[f"move_{i}"] = ""

    return row

# =============================================================================
# 15. MAIN EXECUTION
# =============================================================================

def main():
    parser = argparse.ArgumentParser(description="R3ALN3T.EXE NetP Card Generator v3.0")
    parser.add_argument("--count", type=int, default=10, help="Number of cards to generate")
    parser.add_argument("--tier", type=str, default=None, help="Force a specific tier (OMEGA, ALPHA, etc.)")
    parser.add_argument("--alignment", type=str, default=None, help="Force a specific alignment")
    parser.add_argument("--element", type=str, default=None, help="Force a specific element")
    parser.add_argument("--batch", type=int, default=None, help="Large batch mode (shorthand for --count)")
    parser.add_argument("--no-images", action="store_true", help="Skip PNG generation (CSV only)")
    parser.add_argument("--characters", type=str, default="characters.csv", help="Path to source characters CSV")
    parser.add_argument("--output-csv", type=str, default="generated_cards.csv", help="Output CSV path")
    parser.add_argument("--output-images", type=str, default="Cards", help="Output directory for card PNGs")
    parser.add_argument("--omega-start", type=int, default=4, help="OMEGA numbering start (default: 4)")

    args = parser.parse_args()

    count = args.batch if args.batch else args.count

    # Validate tier
    if args.tier and args.tier.upper() not in TIER_NAMES:
        print(f"[ERROR] Invalid tier: {args.tier}")
        print(f"Valid tiers: {', '.join(TIER_NAMES)}")
        sys.exit(1)

    # Validate alignment
    if args.alignment and args.alignment not in ALIGNMENTS:
        print(f"[ERROR] Invalid alignment: {args.alignment}")
        print(f"Valid alignments: {', '.join(ALIGNMENTS.keys())}")
        sys.exit(1)

    # Validate element
    if args.element and args.element not in ELEMENT_ROSTER:
        print(f"[ERROR] Invalid element: {args.element}")
        print(f"Valid elements: {', '.join(ELEMENT_ROSTER.keys())}")
        sys.exit(1)

    # Set OMEGA start
    if args.omega_start != 4:
        tier_counters["OMEGA"] = args.omega_start
    else:
        tier_counters["OMEGA"] = 4  # 001-003 already exist

    # Load source characters
    print(f"[INFO] Loading source characters from: {args.characters}")
    source_chars = load_source_characters(args.characters)
    print(f"[INFO] Loaded {len(source_chars)} source characters")

    # Initialize image generator
    image_gen = None if args.no_images else CardImageGenerator(args.output_images)

    # Generate cards
    print(f"[INFO] Generating {count} NetP cards...")
    cards = []

    for i in range(count):
        card = generate_card(
            source_chars=source_chars,
            forced_tier=args.tier,
            forced_alignment=args.alignment,
            forced_element=args.element,
        )
        cards.append(card)

        # Generate image
        if image_gen:
            img_path = image_gen.generate_card_image(card)
            if img_path:
                print(f"  [{i+1}/{count}] {card.card_number} | {card.name} | {card.tier} | {card.alignment} | {card.element} -> {img_path}")
            else:
                print(f"  [{i+1}/{count}] {card.card_number} | {card.name} | {card.tier} | {card.alignment} | {card.element} (no image)")
        else:
            print(f"  [{i+1}/{count}] {card.card_number} | {card.name} | {card.tier} | {card.alignment} | {card.element}")

    # Write CSV
    print(f"[INFO] Writing CSV to: {args.output_csv}")
    file_exists = os.path.exists(args.output_csv)

    with open(args.output_csv, 'a', newline='', encoding='utf-8') as f:
        writer = csv.DictWriter(f, fieldnames=HEADERS)
        if not file_exists or os.path.getsize(args.output_csv) == 0:
            writer.writeheader()
        for card in cards:
            writer.writerow(card_to_row(card))

    # Summary
    tier_counts = {}
    align_counts = {}
    elem_counts = {}
    for c in cards:
        tier_counts[c.tier] = tier_counts.get(c.tier, 0) + 1
        align_counts[c.alignment] = align_counts.get(c.alignment, 0) + 1
        elem_counts[c.element] = elem_counts.get(c.element, 0) + 1

    print("\n" + "="*60)
    print("GENERATION COMPLETE")
    print("="*60)
    print(f"Total cards generated: {count}")
    print(f"CSV output: {args.output_csv}")
    if image_gen:
        print(f"Image output: {args.output_images}/")
    print(f"\nBy Tier:")
    for tier in TIER_NAMES:
        if tier in tier_counts:
            print(f"  {tier:12s}: {tier_counts[tier]}")
    print(f"\nBy Alignment:")
    for align in ALIGNMENTS:
        print(f"  {align:12s}: {align_counts.get(align, 0)}")
    print(f"\nTop Elements:")
    for elem, cnt in sorted(elem_counts.items(), key=lambda x: -x[1])[:5]:
        print(f"  {elem:12s}: {cnt}")
    print("="*60)

if __name__ == "__main__":
    main()
