#!/usr/bin/env python3
"""
R3ALN3T.EXE — NetP Card Generator v2.0
======================================
Generates both CSV card data AND visual card PNG images with 3D-style
character renders.

Usage:
    python generate_netp.py
    python generate_netp.py --count 50
    python generate_netp.py --tier OMEGA --count 10
    python generate_netp.py --batch 1000

Output:
    - generated_cards.csv  (card data)
    - Cards/*.png          (visual card images)
"""

import csv
import random
import os
import sys
import argparse
from pathlib import Path
from datetime import datetime

# Try to import Pillow for card image generation
try:
    from PIL import Image, ImageDraw, ImageFont, ImageFilter, ImageEnhance
    PIL_AVAILABLE = True
except ImportError:
    PIL_AVAILABLE = False
    print("WARNING: Pillow not installed. Card images will NOT be generated.")
    print("Install with: pip install Pillow")

try:
    import numpy as np
    NUMPY_AVAILABLE = True
except ImportError:
    NUMPY_AVAILABLE = False

# --- SYSTEM CONFIGURATION ---
# Auto-detect paths based on script location
SCRIPT_DIR = Path(__file__).parent.resolve()
SOURCE_FILE = SCRIPT_DIR / "characters.csv"
OUTPUT_FILE = SCRIPT_DIR / "generated_cards.csv"
CARDS_DIR = SCRIPT_DIR / "Cards"

HEADERS = [
    "Card Number", "Name", "Surname or MOTTO", "Construct Class", "Origin Matrix",
    "Programs", "Profile", "Core Stats", "Code", "Ascension Protocol",
    "Construct Sprites", "Color Palette", "Lore Data", "Signature Program",
    "Overclock Gauge", "Faction", "Threat Rank"
]

# --- 22-TIER GREEK RARITY LADDER STAT BOUNDARIES ---
RARITY_LADDER = {
    "PSI":     {"hp": (120, 220),   "atk": (35, 70),   "rapid": (35, 70),   "charge": (35, 70),   "def": (35, 70)},
    "CHI":     {"hp": (180, 300),   "atk": (50, 90),   "rapid": (45, 85),   "charge": (45, 85),   "def": (45, 85)},
    "PHI":     {"hp": (240, 360),   "atk": (65, 105),  "rapid": (55, 95),   "charge": (55, 95),   "def": (55, 95)},
    "UPSILON": {"hp": (300, 430),   "atk": (80, 120),  "rapid": (65, 110),  "charge": (65, 110),  "def": (65, 110)},
    "TAU":     {"hp": (360, 500),   "atk": (95, 135),  "rapid": (75, 120),  "charge": (75, 120),  "def": (75, 120)},
    "SIGMA":   {"hp": (430, 580),   "atk": (110, 150), "rapid": (85, 130),  "charge": (85, 130),  "def": (85, 130)},
    "RHO":     {"hp": (500, 660),   "atk": (125, 165), "rapid": (95, 140),  "charge": (95, 140),  "def": (95, 140)},
    "PI":      {"hp": (580, 740),   "atk": (140, 180), "rapid": (105, 150), "charge": (105, 150), "def": (105, 150)},
    "OMICRON": {"hp": (660, 820),   "atk": (155, 195), "rapid": (115, 160), "charge": (115, 160), "def": (115, 160)},
    "XI":      {"hp": (740, 900),   "atk": (170, 210), "rapid": (125, 170), "charge": (125, 170), "def": (125, 170)},
    "NU":      {"hp": (820, 980),   "atk": (185, 225), "rapid": (135, 180), "charge": (135, 180), "def": (135, 180)},
    "MU":      {"hp": (900, 1060),  "atk": (200, 240), "rapid": (145, 190), "charge": (145, 190), "def": (145, 190)},
    "LAMBDA":  {"hp": (980, 1140),  "atk": (215, 255), "rapid": (155, 200), "charge": (155, 200), "def": (155, 200)},
    "KAPPA":   {"hp": (1060, 1220), "atk": (230, 270), "rapid": (165, 210), "charge": (165, 210), "def": (165, 210)},
    "IOTA":    {"hp": (1140, 1300), "atk": (245, 285), "rapid": (175, 220), "charge": (175, 220), "def": (175, 220)},
    "THETA":   {"hp": (1220, 1380), "atk": (260, 300), "rapid": (185, 230), "charge": (185, 230), "def": (185, 230)},
    "ETA":     {"hp": (1300, 1460), "atk": (275, 315), "rapid": (195, 240), "charge": (195, 240), "def": (195, 240)},
    "ZETA":    {"hp": (1380, 1540), "atk": (290, 330), "rapid": (205, 250), "charge": (205, 250), "def": (205, 250)},
    "EPSILON": {"hp": (1460, 1620), "atk": (305, 345), "rapid": (215, 260), "charge": (215, 260), "def": (215, 260)},
    "DELTA":   {"hp": (1540, 1700), "atk": (320, 360), "rapid": (225, 270), "charge": (225, 270), "def": (225, 270)},
    "GAMMA":   {"hp": (1620, 1780), "atk": (335, 375), "rapid": (235, 280), "charge": (235, 280), "def": (235, 280)},
    "BETA":    {"hp": (1700, 1860), "atk": (350, 390), "rapid": (245, 290), "charge": (245, 290), "def": (245, 290)},
    "ALPHA":   {"hp": (1780, 1940), "atk": (365, 405), "rapid": (255, 300), "charge": (255, 300), "def": (255, 300)},
    "OMEGA":   {"hp": (1950, 3200), "atk": (240, 420), "rapid": (170, 320), "charge": (180, 360), "def": (170, 320)}
}

# --- TYPE / ALIGNMENT STRUCTURES ---
FLAVORS = {
    "Angelic":    {"roles": ["Sentinel", "Oracle", "Seraph", "Judge"], "factions": ["CELESTIAL ORDER // SERAPHIM VANGUARD", "CELESTIAL ORDER // SANCTUARY ARRAY"]},
    "Demonic":    {"roles": ["Warden", "Harbinger", "Reaper", "Heretic", "Tyrant"], "factions": ["PANDEMONIUM NET // THE CHASM WATCH", "VOID SYNDICATE // ABYSSAL REAPERS"]},
    "Abyssal":    {"roles": ["Warden", "Harbinger", "Reaper", "Heretic"], "factions": ["VOID SYNDICATE // SUB-TRENCH NODES", "DEEP LATTICE RIFT // ANCHORS"]},
    "Celestial":  {"roles": ["Sentinel", "Oracle", "Seraph", "Judge"], "factions": ["CELESTIAL ORDER // KEEPERS OF BALANCE", "ASTRUM DIVISION // PRISM HORIZON"]},
    "Mechanical": {"roles": ["Architect", "Emissary", "Anchor", "Executor"], "factions": ["SYNTHETIC NETWORK // LOGIC FRAMEWORKS", "THE IRON CORES // CORE ROUTERS"]},
    "Viral":      {"roles": ["Architect", "Executor", "Archon", "Heretic"], "factions": ["CORRUPTED SECTOR // INVASIVE DRIFTERS", "STATIC ECLIPSE // GLITCH FRACTION"]}
}

# --- 18-AXIS ELEMENT ROSTER MATRIX ---
ELEMENT_ROSTER = {
    "Fire":      {"words": ["Ember", "Pyre", "Nova", "Ash", "Cinder", "Furnace"], "effect": "burn pressure and damage over time", "colors": [(255, 69, 0), (255, 140, 0), (255, 215, 0), (139, 0, 0)]},
    "Water":     {"words": ["Tide", "Current", "Surge", "Flow", "Deep", "Ripple"], "effect": "fluid flow, healing, control, and adaptation", "colors": [(30, 144, 255), (0, 191, 255), (135, 206, 250), (0, 0, 139)]},
    "Lightning": {"words": ["Volt", "Arc", "Spark", "Pulse", "Flash", "Static"], "effect": "blinding speed, high burst, and stuns", "colors": [(255, 255, 0), (255, 215, 0), (255, 250, 205), (75, 0, 130)]},
    "Ice":       {"words": ["Frost", "Glacier", "Chilled", "Rime", "Spike", "Vertex"], "effect": "target slows, freezing locks, and elevated defense", "colors": [(0, 206, 209), (135, 206, 235), (176, 224, 230), (70, 130, 180)]},
    "Wind":      {"words": ["Gale", "Zephyr", "Aero", "Blast", "Vortex", "Squall"], "effect": "increased evasion, node disruption, and mobility", "colors": [(240, 248, 255), (230, 230, 250), (176, 196, 222), (119, 136, 153)]},
    "Earth":     {"words": ["Stone", "Quarry", "Crag", "Boulder", "Mantle", "Basalt"], "effect": "unyielding tanking, heavy shields, and stability", "colors": [(139, 69, 19), (210, 105, 30), (160, 82, 45), (85, 107, 47)]},
    "Light":     {"words": ["Radiant", "Halo", "Aurora", "Prism", "Seraph", "Sanctum"], "effect": "debuff cleansing, hidden data reveal, and stat amplification", "colors": [(255, 248, 220), (255, 250, 240), (255, 215, 0), (255, 165, 0)]},
    "Dark":      {"words": ["Abyss", "Void", "Grave", "Shade", "Heretic", "Black Sun"], "effect": "system curses, health drains, and stealth concealment", "colors": [(47, 47, 47), (75, 0, 130), (128, 0, 128), (0, 0, 0)]},
    "Void":      {"words": ["Null", "Empty", "Rift", "Zero", "Erase", "Vacuum"], "effect": "attribute erasure, space distortion, and suppression", "colors": [(25, 25, 35), (50, 50, 70), (80, 80, 100), (20, 20, 30)]},
    "Metal":     {"words": ["Iron", "Steel", "Alloy", "Blade", "Plated", "Forge"], "effect": "reinforced armor, piercing damage, and structural integrity", "colors": [(192, 192, 192), (169, 169, 169), (211, 211, 211), (105, 105, 105)]},
    "Nature":    {"words": ["Bloom", "Vine", "Thorn", "Root", "Sylvan", "Timber"], "effect": "growth mechanics, automated restoration, and structural binds", "colors": [(34, 139, 34), (50, 205, 50), (144, 238, 144), (0, 100, 0)]},
    "Sound":     {"words": ["Sonic", "Echo", "Chime", "Blast", "Sonar", "Resonance"], "effect": "kinetic shockwaves, targeting confusion, and frequency resonance", "colors": [(255, 20, 147), (199, 21, 133), (219, 112, 147), (139, 0, 139)]},
    "Gravity":   {"words": ["Pull", "Crush", "Attract", "Singularity", "Weight", "Orbit"], "effect": "spatial pulls, heavy crushing, and total immobilization", "colors": [(72, 61, 139), (106, 90, 205), (123, 104, 238), (48, 25, 52)]},
    "Time":      {"words": ["Delay", "Chrono", "Phase", "Rewind", "Shift", "Epoch"], "effect": "cooldown delay, speed acceleration, and status rewind", "colors": [(0, 128, 128), (32, 178, 170), (64, 224, 208), (0, 206, 209)]},
    "Blood":     {"words": ["Bleed", "Gore", "Siphon", "Vein", "Pulse", "Sanguine"], "effect": "strategic sacrifice, life sustain, and code corruption", "colors": [(139, 0, 0), (178, 34, 34), (220, 20, 60), (128, 0, 0)]},
    "Poison":    {"words": ["Viper", "Toxic", "Venom", "Miasma", "Decay", "Spore"], "effect": "code decay, status weakening, and stacking damage layers", "colors": [(0, 128, 0), (34, 139, 34), (107, 142, 35), (85, 107, 47)]},
    "Crystal":   {"words": ["Shard", "Quartz", "Mirror", "Glass", "Prism", "Facet"], "effect": "reflective barriers, light redirection, and shattering shards", "colors": [(224, 255, 255), (175, 238, 238), (127, 255, 212), (72, 209, 204)]},
    "Plasma":    {"words": ["Ion", "Solar", "Flare", "Fission", "Fusion", "Thermal"], "effect": "high-energy burn configurations, chain damage, and system overload", "colors": [(255, 0, 255), (255, 105, 180), (255, 20, 147), (199, 21, 133)]}
}

ACTION_WORDS = {
    "Assault": ["Break", "Crash", "Rend", "Strike", "Fang", "Burst"],
    "Control": ["Lock", "Seal", "Snare", "Bind", "Freeze", "Quell"],
    "Support": ["Ward", "Grace", "Bloom", "Halo", "Restore", "Bastion"],
    "Burst":   ["Nova", "Zero", "Exodus", "Eclipse", "Dominion", "Cataclysm"]
}

MYTHIC_WORDS = ["Exodus", "Dominion", "Cataclysm", "Genesis", "Infinity", "Absolute"]

# --- RARITY VISUAL STYLING ---
RARITY_COLORS = {
    "PSI": (169, 169, 169), "CHI": (0, 128, 0), "PHI": (0, 100, 200),
    "UPSILON": (0, 0, 255), "TAU": (0, 0, 180), "SIGMA": (128, 0, 128),
    "RHO": (128, 0, 128), "PI": (153, 50, 204), "OMICRON": (186, 85, 211),
    "XI": (138, 43, 226), "NU": (148, 0, 211), "MU": (139, 0, 139),
    "LAMBDA": (255, 140, 0), "KAPPA": (255, 165, 0), "IOTA": (255, 215, 0),
    "THETA": (255, 69, 0), "ETA": (255, 0, 0), "ZETA": (220, 20, 60),
    "EPSILON": (199, 21, 133), "DELTA": (255, 20, 147), "GAMMA": (255, 105, 180),
    "BETA": (255, 182, 193), "ALPHA": (255, 255, 255), "OMEGA": (255, 215, 0)
}

RARITY_STARS = {
    "PSI": "★", "CHI": "★★", "PHI": "★★★", "UPSILON": "★★★★", "TAU": "★★★★★",
    "SIGMA": "★★★★★", "RHO": "★★★★★", "PI": "★★★★★", "OMICRON": "★★★★★",
    "XI": "★★★★★", "NU": "★★★★★", "MU": "★★★★★", "LAMBDA": "★★★★★",
    "KAPPA": "★★★★★", "IOTA": "★★★★★", "THETA": "★★★★★", "ETA": "★★★★★",
    "ZETA": "★★★★★", "EPSILON": "★★★★★", "DELTA": "★★★★★", "GAMMA": "★★★★★",
    "BETA": "★★★★★", "ALPHA": "★★★★★", "OMEGA": "★★★★★★★"
}


# =============================================================================
# CORE FUNCTIONS (from original)
# =============================================================================

def load_source_characters(file_path):
    if not os.path.exists(file_path):
        print(f"ERROR: Source file not found: {file_path}")
        print("Creating dummy characters.csv for testing...")
        create_dummy_characters(file_path)
    with open(file_path, mode='r', encoding='utf-8') as f:
        return list(csv.DictReader(f))


def create_dummy_characters(file_path):
    """Create a sample characters.csv if none exists."""
    dummy_names = [
        "Aetherion.DRIFT", "Nyxshade.NULL", "Vexcore.IRON", "Solara.PRISM",
        "Kaelthas.VOID", "Morrigan.BLOOD", "Zephyros.GALE", "Terrakhan.STONE",
        "Ignis.PYRE", "Aquarius.TIDE", "Lumina.HALO", "Umbra.SHADE",
        "Voltan.ARC", "Glacius.RIME", "Sylvana.BLOOM", "Chronos.PHASE",
        "Gravitas.CRUSH", "Sonicus.ECHO", "Toxina.VIPER", "Crystallis.SHARD"
    ]
    with open(file_path, 'w', newline='', encoding='utf-8') as f:
        writer = csv.writer(f)
        writer.writerow(["name", "type", "origin", "class"])
        for name in dummy_names:
            alignment = random.choice(list(FLAVORS.keys()))
            writer.writerow([name, alignment, "NET_CORE", random.choice(["NetP", "Construct", "Avatar"])])
    print(f"Created dummy file with {len(dummy_names)} characters.")


def generate_program_list(element_name, tier):
    """Composes 9 localized moves utilizing the designated element's word dictionary."""
    bases = ELEMENT_ROSTER[element_name]["words"]
    actions = []
    for category in ACTION_WORDS.values():
        actions.extend(category)
    generated = set()
    while len(generated) < 9:
        base = random.choice(bases)
        action = random.choice(actions)
        val = random.randint(110, 180) if tier != "OMEGA" else random.randint(120, 200)
        generated.add(f"{base} {action} [S // {val}]")
    return " | ".join(list(generated))


def roll_stat(tier, stat_name, alignment):
    bounds = RARITY_LADDER[tier][stat_name]
    min_val, max_val = bounds[0], bounds[1]
    lean = False
    if alignment == "Angelic" and stat_name in ["hp", "def", "charge"]: lean = True
    elif alignment == "Demonic" and stat_name in ["atk", "rapid"]: lean = True
    elif alignment == "Abyssal" and stat_name in ["hp", "charge"]: lean = True
    elif alignment == "Mechanical" and stat_name in ["def", "rapid"]: lean = True
    elif alignment == "Viral" and stat_name in ["rapid", "atk"]: lean = True
    if lean:
        quarter_point = min_val + int((max_val - min_val) * 0.25)
        return random.randint(quarter_point, max_val)
    return random.randint(min_val, max_val)


def generate_card(card_id, char1, char2, char3, forced_tier="RANDOM"):
    get_name = lambda d: next((v for k, v in d.items() if k.lower().strip() == 'name'), 'UNKNOWN')
    char1_name = get_name(char1)
    fused_identity = char1_name.split('.')[0] if '.' in char1_name else char1_name

    get_type = lambda d: next((v for k, v in d.items() if k.lower().strip() == 'type'), 'Viral')
    alignment = get_type(char1).capitalize()
    if alignment not in FLAVORS: alignment = "Viral"

    if forced_tier == "RANDOM":
        tier = random.choice(list(RARITY_LADDER.keys()))
    else:
        tier = forced_tier

    element = random.choice(list(ELEMENT_ROSTER.keys()))
    elem_word = random.choice(ELEMENT_ROSTER[element]["words"])
    elem_effect = ELEMENT_ROSTER[element]["effect"]

    role = random.choice(FLAVORS[alignment]["roles"])
    faction_name = random.choice(FLAVORS[alignment]["factions"])

    if tier == "OMEGA":
        omega_index = random.randint(4, 100)
        card_num_str = f"OMEGA-{omega_index:03d} - PRIME LEADER"
        full_title = f"{fused_identity.upper()} {elem_word.upper()} TRINITY"
        construct_class = f"OMEGA-ASCENDENT [{element.upper()}] NetP"
        faction_name = f"{alignment.upper()} SUPREME APEX CORE // {element.upper()} MATRIX"
        threat_rank = "★★★★★★★"
    else:
        card_num_str = f"{card_id:03d} - STANDARD CONSTRUCT"
        full_title = f"{tier} {fused_identity.upper()} {elem_word.upper()} {role.upper()}"
        construct_class = f"{tier}-RANK [{element.upper()}] NetP"
        threat_rank = "★★★★★"

    motto = f"The {alignment} alignment convergence channeling {element} core metrics under array {tier}."

    hp = roll_stat(tier, "hp", alignment)
    attack = roll_stat(tier, "atk", alignment)
    rapid = roll_stat(tier, "rapid", alignment)
    charge = roll_stat(tier, "charge", alignment)
    defense = roll_stat(tier, "def", alignment)
    core_stats = f"HP: {hp} / ATK: {attack} / RAPID: {rapid} / CHARGE: {charge} / DEF: {defense}"

    programs_block = generate_program_list(element, tier)
    sig_program = f"{elem_word} {random.choice(MYTHIC_WORDS)} [S // 200]"

    netp_code = f"DIVINE.{fused_identity.upper()}.{element.upper()}" if tier == "OMEGA" else f"{tier}.{fused_identity.upper()}.{element.upper()}"
    origin_matrix = f"1. {char1_name} | 2. {get_name(char2)} | 3. {get_name(char3)}"

    return {
        "Card Number": card_num_str,
        "Name": full_title,
        "Surname or MOTTO": motto,
        "Construct Class": construct_class,
        "Origin Matrix": origin_matrix,
        "Programs": programs_block,
        "Profile": f"A specialized {alignment} fusion configuration engineered for {elem_effect}.",
        "Core Stats": core_stats,
        "Code": netp_code,
        "Ascension Protocol": f"Initializes localized {element.upper()} core synchronization loops.",
        "Construct Sprites": f"{fused_identity.lower()}_idle.png; {fused_identity.lower()}_move.png",
        "Color Palette": f"Mapped to {element} Spectrum Protocols",
        "Lore Data": f"Core extraction routine matches code parameters of an active {element}-aligned grid network.",
        "Signature Program": sig_program,
        "Overclock Gauge": "100%",
        "Faction": faction_name,
        "Threat Rank": threat_rank
    }, {
        "tier": tier,
        "element": element,
        "alignment": alignment,
        "hp": hp,
        "attack": attack,
        "rapid": rapid,
        "charge": charge,
        "defense": defense,
        "fused_identity": fused_identity,
        "elem_word": elem_word,
        "role": role,
        "card_id": card_id
    }


# =============================================================================
# 3D CHARACTER & CARD IMAGE GENERATOR
# =============================================================================

class CardImageGenerator:
    """Generates visual TCG card PNGs with 3D-style character renders."""

    CARD_WIDTH = 750
    CARD_HEIGHT = 1050

    def __init__(self, output_dir):
        self.output_dir = Path(output_dir)
        self.output_dir.mkdir(parents=True, exist_ok=True)
        if not PIL_AVAILABLE:
            raise ImportError("Pillow required. Install: pip install Pillow")

    def _get_font(self, size, bold=False, italic=False):
        """Try to load system fonts, fallback to default."""
        font_paths = [
            "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf" if bold else "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
            "/usr/share/fonts/truetype/liberation/LiberationSans-Bold.ttf" if bold else "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
            "/System/Library/Fonts/Helvetica.ttc",
            "C:/Windows/Fonts/arialbd.ttf" if bold else "C:/Windows/Fonts/arial.ttf",
        ]
        for path in font_paths:
            if os.path.exists(path):
                try:
                    return ImageFont.truetype(path, size)
                except:
                    pass
        return ImageFont.load_default()

    def _draw_background(self, draw, element, tier):
        """Draw element-themed gradient background."""
        colors = ELEMENT_ROSTER[element]["colors"]
        base = colors[0] if colors else (30, 30, 30)

        for y in range(self.CARD_HEIGHT):
            progress = y / self.CARD_HEIGHT
            r = int(base[0] * (1 - progress * 0.5))
            g = int(base[1] * (1 - progress * 0.5))
            b = int(base[2] * (1 - progress * 0.5))
            draw.line([(0, y), (self.CARD_WIDTH, y)], fill=(r, g, b, 255))

        # Add noise texture
        if NUMPY_AVAILABLE:
            arr = np.zeros((self.CARD_HEIGHT, self.CARD_WIDTH, 3), dtype=np.uint8)
            for y in range(self.CARD_HEIGHT):
                progress = y / self.CARD_HEIGHT
                r = int(base[0] * (1 - progress * 0.5))
                g = int(base[1] * (1 - progress * 0.5))
                b = int(base[2] * (1 - progress * 0.5))
                arr[y, :] = [r, g, b]
            noise = np.random.randint(-8, 8, arr.shape, dtype=np.int16)
            arr = np.clip(arr.astype(np.int16) + noise, 0, 255).astype(np.uint8)
            # We can't easily paste this back, so skip for now

    def _draw_3d_character(self, card, element, alignment, tier, fused_identity):
        """Draw a 3D-style character silhouette/render in the art area."""
        art_x, art_y = 55, 120
        art_w, art_h = 640, 480

        art_layer = Image.new('RGBA', (art_w, art_h), (0, 0, 0, 0))
        art_draw = ImageDraw.Draw(art_layer)

        colors = ELEMENT_ROSTER[element]["colors"]
        primary = colors[0] if colors else (128, 128, 128)
        secondary = colors[1] if len(colors) > 1 else primary
        glow = colors[2] if len(colors) > 2 else (255, 255, 255)

        # Background glow
        for i in range(20, 0, -1):
            alpha = int(15 * (20 - i) / 20)
            art_draw.ellipse(
                [art_w//2 - 150 - i*5, art_h//2 - 200 - i*5,
                 art_w//2 + 150 + i*5, art_h//2 + 200 + i*5],
                outline=(*primary, alpha), width=2
            )

        # Body type based on alignment
        body_types = {
            "Angelic": "winged_humanoid", "Demonic": "horned_humanoid",
            "Abyssal": "tentacled_form", "Celestial": "radiant_humanoid",
            "Mechanical": "armored_construct", "Viral": "glitching_form"
        }
        body = body_types.get(alignment, "humanoid")

        cx, cy = art_w // 2, art_h // 2 + 30

        # Head (glowing core)
        head_size = 35
        art_draw.ellipse([cx - head_size, cy - 180, cx + head_size, cy - 110],
                          fill=(*primary, 200), outline=(*glow, 255), width=3)
        # Inner core
        art_draw.ellipse([cx - head_size//2, cy - 165, cx + head_size//2, cy - 125],
                          fill=(*glow, 255))

        # Torso
        torso_points = [(cx, cy - 110), (cx - 50, cy + 20), (cx + 50, cy + 20)]
        art_draw.polygon(torso_points, fill=(*primary, 180), outline=(*secondary, 220), width=2)

        # Chest core
        art_draw.ellipse([cx - 15, cy - 60, cx + 15, cy - 30],
                          fill=(*glow, 230), outline=(*primary, 255), width=2)

        # Arms
        art_draw.polygon([(cx - 50, cy - 80), (cx - 90, cy + 40), (cx - 70, cy + 50), (cx - 40, cy - 20)],
                          fill=(*primary, 160), outline=(*secondary, 200), width=2)
        art_draw.polygon([(cx + 50, cy - 80), (cx + 90, cy + 40), (cx + 70, cy + 50), (cx + 40, cy - 20)],
                          fill=(*primary, 160), outline=(*secondary, 200), width=2)

        # Legs
        art_draw.polygon([(cx - 30, cy + 20), (cx - 45, cy + 180), (cx - 20, cy + 190), (cx - 10, cy + 30)],
                          fill=(*primary, 170), outline=(*secondary, 210), width=2)
        art_draw.polygon([(cx + 30, cy + 20), (cx + 45, cy + 180), (cx + 20, cy + 190), (cx + 10, cy + 30)],
                          fill=(*primary, 170), outline=(*secondary, 210), width=2)

        # Alignment-specific features
        if alignment == "Angelic":
            # Wings
            wing_color = (*glow, 120)
            art_draw.polygon([(cx - 40, cy - 100), (cx - 180, cy - 200), (cx - 60, cy - 60)], fill=wing_color)
            art_draw.polygon([(cx + 40, cy - 100), (cx + 180, cy - 200), (cx + 60, cy - 60)], fill=wing_color)
        elif alignment == "Demonic":
            # Horns
            art_draw.polygon([(cx - 20, cy - 180), (cx - 50, cy - 240), (cx - 10, cy - 185)], fill=(*secondary, 255))
            art_draw.polygon([(cx + 20, cy - 180), (cx + 50, cy - 240), (cx + 10, cy - 185)], fill=(*secondary, 255))
            # Tail
            art_draw.polygon([(cx + 30, cy + 100), (cx + 80, cy + 220), (cx + 50, cy + 230), (cx + 20, cy + 120)],
                              fill=(*secondary, 200))
        elif alignment == "Mechanical":
            # Mechanical joints
            for joint_y in [cy - 80, cy - 20, cy + 60]:
                art_draw.ellipse([cx - 8, joint_y - 8, cx + 8, joint_y + 8], fill=(100, 100, 100, 255))
            # Shoulder plates
            art_draw.rectangle([cx - 100, cy - 100, cx - 60, cy - 60], fill=(*secondary, 200), outline=(150, 150, 150, 255))
            art_draw.rectangle([cx + 60, cy - 100, cx + 100, cy - 60], fill=(*secondary, 200), outline=(150, 150, 150, 255))
        elif alignment == "Viral":
            # Glitch particles
            for _ in range(15):
                px = random.randint(50, art_w - 50)
                py = random.randint(50, art_h - 50)
                art_draw.rectangle([px, py, px + random.randint(5, 20), py + 3], fill=(*glow, 150))

        # Tier glow effect
        if tier in ["ALPHA", "OMEGA"]:
            for i in range(30):
                alpha = int(100 * (1 - i/30))
                art_draw.ellipse([cx - 200 + i*3, cy - 250 + i*3, cx + 200 - i*3, cy + 250 - i*3],
                                  outline=(*glow, alpha), width=1)

        # Element symbol
        symbol = {
            "Fire": "🔥", "Water": "💧", "Lightning": "⚡", "Ice": "❄️",
            "Wind": "🌪️", "Earth": "🪨", "Light": "☀️", "Dark": "🌑",
            "Void": "⬛", "Metal": "⚙️", "Nature": "🌿", "Sound": "🎵",
            "Gravity": "🪐", "Time": "⏳", "Blood": "🩸", "Poison": "☠️",
            "Crystal": "💎", "Plasma": "☄️"
        }.get(element, "◆")

        # Paste art onto card
        card.paste(art_layer, (art_x, art_y), art_layer)

        # Art border
        border_draw = ImageDraw.Draw(card)
        border_draw.rectangle([art_x - 3, art_y - 3, art_x + art_w + 3, art_y + art_h + 3],
                              outline=(100, 100, 100, 255), width=3)

        return art_layer

    def generate_card_image(self, card_data, meta_data):
        """Generate a complete visual card PNG."""
        tier = meta_data["tier"]
        element = meta_data["element"]
        alignment = meta_data["alignment"]
        fused_identity = meta_data["fused_identity"]

        rarity_color = RARITY_COLORS.get(tier, (169, 169, 169))

        # Create base card
        card = Image.new('RGBA', (self.CARD_WIDTH, self.CARD_HEIGHT), (0, 0, 0, 255))
        draw = ImageDraw.Draw(card)

        # Background
        self._draw_background(draw, element, tier)

        # Frame
        border_width = 6 if tier in ["ALPHA", "OMEGA"] else 4
        draw.rectangle(
            [border_width // 2, border_width // 2,
             self.CARD_WIDTH - border_width // 2, self.CARD_HEIGHT - border_width // 2],
            outline=(*rarity_color, 255), width=border_width
        )

        # Inner frame for high rarity
        if tier in ["LAMBDA", "KAPPA", "IOTA", "THETA", "ETA", "ZETA", "EPSILON", "DELTA", "GAMMA", "BETA", "ALPHA", "OMEGA"]:
            inner_color = tuple(min(255, c + 60) for c in rarity_color)
            draw.rectangle([20, 20, self.CARD_WIDTH - 20, self.CARD_HEIGHT - 20],
                           outline=(*inner_color, 200), width=2)

        # 3D Character Art
        self._draw_3d_character(card, element, alignment, tier, fused_identity)

        # Name banner
        draw.rectangle([30, 30, self.CARD_WIDTH - 30, 110], fill=(10, 10, 15, 240), outline=(*rarity_color, 255))

        font_name = self._get_font(28, bold=True)
        font_title = self._get_font(18)
        font_small = self._get_font(14)
        font_stat = self._get_font(16, bold=True)
        font_val = self._get_font(14)
        font_ability = self._get_font(15, bold=True)
        font_desc = self._get_font(12)

        # Name
        name = card_data["Name"]
        draw.text((50, 38), name, fill=(255, 255, 255, 255), font=font_name)

        # Class / Element
        class_text = f"{card_data['Construct Class']}  |  {card_data['Faction']}"
        draw.text((50, 78), class_text, fill=(200, 200, 200, 255), font=font_title)

        # Card number
        draw.text((self.CARD_WIDTH - 200, 82), card_data["Card Number"], fill=(150, 150, 150, 255), font=font_small)

        # Profile box
        profile_y = 620
        draw.rectangle([55, profile_y, self.CARD_WIDTH - 55, profile_y + 70],
                       fill=(15, 15, 20, 230), outline=(80, 80, 80, 255))
        profile_text = card_data["Profile"]
        if len(profile_text) > 90:
            profile_text = profile_text[:87] + "..."
        draw.text((65, profile_y + 8), profile_text, fill=(180, 180, 160, 255), font=font_desc)
        draw.text((65, profile_y + 28), f'"{card_data["Surname or MOTTO"]}"', fill=(160, 160, 140, 255), font=font_desc)

        # Stats
        stats_y = 710
        stats = [
            ("HP", meta_data["hp"]), ("ATK", meta_data["attack"]),
            ("RAPID", meta_data["rapid"]), ("CHG", meta_data["charge"]), ("DEF", meta_data["defense"])
        ]
        box_w = 120
        for i, (label, val) in enumerate(stats):
            x = 60 + i * (box_w + 10)
            draw.rectangle([x, stats_y, x + box_w, stats_y + 45],
                           fill=(20, 20, 25, 230), outline=(100, 100, 100, 255))
            draw.text((x + 8, stats_y + 4), label, fill=(150, 150, 150, 255), font=font_stat)
            val_color = (255, 255, 255, 255) if val < 500 else (255, 220, 100, 255) if val < 1000 else (100, 255, 100, 255)
            draw.text((x + box_w - 45, stats_y + 4), str(val), fill=val_color, font=font_stat)

        # Programs (abilities)
        prog_y = 770
        programs = card_data["Programs"].split(" | ")[:4]  # Show first 4
        for i, prog in enumerate(programs):
            y = prog_y + i * 55
            draw.rectangle([55, y, self.CARD_WIDTH - 55, y + 50],
                           fill=(18, 18, 25, 230), outline=(80, 80, 100, 255))
            # Parse program name
            prog_name = prog.split(" [S //")[0] if " [S //" in prog else prog
            prog_val = prog.split(" [S //")[1].replace("]", "") if " [S //" in prog else ""
            draw.text((65, y + 5), prog_name, fill=(200, 200, 255, 255), font=font_ability)
            if prog_val:
                draw.text((self.CARD_WIDTH - 120, y + 5), f"S//{prog_val}", fill=(150, 150, 255, 255), font=font_desc)

        # Signature Program
        sig_y = prog_y + len(programs) * 55 + 10
        draw.rectangle([55, sig_y, self.CARD_WIDTH - 55, sig_y + 40],
                       fill=(40, 30, 20, 240), outline=(255, 200, 100, 255), width=2)
        draw.text((65, sig_y + 8), f"SIG: {card_data['Signature Program']}", fill=(255, 220, 150, 255), font=font_stat)

        # Footer info
        footer_y = 1000
        draw.text((60, footer_y), f"Code: {card_data['Code']}", fill=(150, 150, 150, 255), font=font_small)
        draw.text((60, footer_y + 18), f"Origin: {card_data['Origin Matrix']}", fill=(120, 120, 120, 255), font=font_small)

        # Rarity stars
        stars = RARITY_STARS.get(tier, "★")
        draw.text((self.CARD_WIDTH - 150, footer_y), stars, fill=(*rarity_color, 255), font=font_title)
        draw.text((self.CARD_WIDTH - 150, footer_y + 20), tier, fill=(*rarity_color, 255), font=font_stat)

        # Overclock gauge
        draw.rectangle([self.CARD_WIDTH - 200, footer_y + 45, self.CARD_WIDTH - 60, footer_y + 60],
                       fill=(30, 30, 30, 255), outline=(100, 100, 100, 255))
        draw.rectangle([self.CARD_WIDTH - 200, footer_y + 45, self.CARD_WIDTH - 60, footer_y + 60],
                       fill=(*rarity_color, 180))
        draw.text((self.CARD_WIDTH - 190, footer_y + 47), "OVERCLOCK: 100%", fill=(255, 255, 255, 255), font=font_small)

        # Save
        safe_name = card_data["Name"].replace(' ', '_').replace('/', '_').replace('\', '_')
        card_path = self.output_dir / f"{safe_name}.png"
        card.save(card_path, 'PNG')
        return str(card_path)


# =============================================================================
# MAIN EXECUTION
# =============================================================================

def main():
    parser = argparse.ArgumentParser(description="R3ALN3T.EXE NetP Card Generator")
    parser.add_argument("--count", type=int, default=10, help="Number of cards to generate")
    parser.add_argument("--tier", type=str, default="RANDOM", help="Force a specific tier (e.g., OMEGA, ALPHA)")
    parser.add_argument("--batch", type=int, default=0, help="Large batch mode (overrides --count)")
    parser.add_argument("--no-images", action="store_true", help="Skip PNG generation, CSV only")
    parser.add_argument("--source", type=str, default=str(SOURCE_FILE), help="Path to characters.csv")
    parser.add_argument("--output", type=str, default=str(OUTPUT_FILE), help="Path to output CSV")
    parser.add_argument("--cards-dir", type=str, default=str(CARDS_DIR), help="Directory for card PNGs")
    args = parser.parse_args()

    count = args.batch if args.batch > 0 else args.count
    source_file = args.source
    output_file = args.output
    cards_dir = args.cards_dir

    print("=" * 60)
    print("R3ALN3T.EXE — NetP Card Generator v2.0")
    print("=" * 60)
    print(f"Source:     {source_file}")
    print(f"Output CSV: {output_file}")
    print(f"Cards Dir:  {cards_dir}")
    print(f"Count:      {count}")
    print(f"Tier:       {args.tier}")
    print(f"Images:     {'DISABLED' if args.no_images else 'ENABLED'}")
    print("=" * 60)

    # Load characters
    characters = load_source_characters(source_file)
    if len(characters) < 3:
        print(f"ERROR: Need at least 3 characters, found {len(characters)}")
        return

    print(f"Loaded {len(characters)} source characters.")

    # Setup image generator
    image_gen = None
    if not args.no_images and PIL_AVAILABLE:
        image_gen = CardImageGenerator(cards_dir)
        print(f"Card image generator ready. Output: {cards_dir}")
    elif not PIL_AVAILABLE and not args.no_images:
        print("WARNING: Pillow not installed. Images skipped. Run: pip install Pillow")

    # Generate cards
    generated_cards = []
    generated_images = []

    # Shuffle for random fusion combinations
    random.shuffle(characters)

    for i in range(count):
        # Pick 3 characters (with wraparound if needed)
        idx1 = (i * 3) % len(characters)
        idx2 = (i * 3 + 1) % len(characters)
        idx3 = (i * 3 + 2) % len(characters)
        char1, char2, char3 = characters[idx1], characters[idx2], characters[idx3]

        card_data, meta_data = generate_card(i + 1, char1, char2, char3, forced_tier=args.tier)
        generated_cards.append(card_data)

        # Generate image
        if image_gen:
            try:
                img_path = image_gen.generate_card_image(card_data, meta_data)
                generated_images.append(img_path)
                print(f"[{i+1:04d}/{count}] {card_data['Name']} ({meta_data['tier']}) -> {img_path}")
            except Exception as e:
                print(f"[{i+1:04d}/{count}] {card_data['Name']} ({meta_data['tier']}) -> IMAGE ERROR: {e}")
        else:
            print(f"[{i+1:04d}/{count}] {card_data['Name']} ({meta_data['tier']}) -> CSV only")

    # Write CSV
    with open(output_file, 'w', newline='', encoding='utf-8') as f:
        writer = csv.DictWriter(f, fieldnames=HEADERS)
        writer.writeheader()
        writer.writerows(generated_cards)

    # Summary
    print("=" * 60)
    print("GENERATION COMPLETE")
    print("=" * 60)
    print(f"Cards generated: {len(generated_cards)}")
    print(f"CSV saved: {output_file}")
    if generated_images:
        print(f"Images saved: {len(generated_images)} in {cards_dir}")

    # Rarity breakdown
    tier_counts = {}
    for card in generated_cards:
        tier = card["Card Number"].split(" - ")[0] if " - " in card["Card Number"] else "UNKNOWN"
        tier_counts[tier] = tier_counts.get(tier, 0) + 1
    print(f"\nRarity Distribution:")
    for tier, count in sorted(tier_counts.items()):
        print(f"  {tier:12s}: {count:4d}")

    # Element breakdown
    elem_counts = {}
    for card in generated_cards:
        elem = card["Construct Class"].split("[")[1].replace("] NetP", "").replace("]", "") if "[" in card["Construct Class"] else "UNKNOWN"
        elem_counts[elem] = elem_counts.get(elem, 0) + 1
    print(f"\nElement Distribution:")
    for elem, count in sorted(elem_counts.items(), key=lambda x: -x[1]):
        print(f"  {elem:12s}: {count:4d}")


if __name__ == "__main__":
    main()
