#!/usr/bin/env python3
"""
R3ALN3T.EXE — Character Card Generator v3.0
Generates character cards as JSON data + PNG images for in-game use.
Output: character_cards/cards/*.json and character_cards/cards/*.png
"""

import json, os, random, uuid, math
from pathlib import Path
from datetime import datetime

BASE = Path(__file__).parent if '__file__' in dir() else Path('.')
OUT_DIR = BASE / 'cards'
OUT_DIR.mkdir(parents=True, exist_ok=True)

# ---- TIER SYSTEM (23 Greek letters) ----
TIERS = [
    ('PSI', 1), ('CHI', 2), ('PHI', 3), ('UPSILON', 4), ('TAU', 5),
    ('SIGMA', 6), ('RHO', 7), ('PI', 8), ('OMICRON', 9), ('XI', 10),
    ('NU', 11), ('MU', 12), ('LAMBDA', 13), ('KAPPA', 14), ('IOTA', 15),
    ('THETA', 16), ('ETA', 17), ('ZETA', 18), ('EPSILON', 19), ('DELTA', 20),
    ('GAMMA', 21), ('BETA', 22), ('ALPHA', 23), ('OMEGA', 0)
]

TIER_STAT_RANGES = {
    'OMEGA': {'hp': (1500,2500),'atk':(200,320),'rapid':(120,220),'charge':(150,250),'def':(140,220)},
    'ALPHA': {'hp': (900,1400),'atk':(140,220),'rapid':(90,160),'charge':(110,180),'def':(100,160)},
    'BETA': {'hp': (700,1100),'atk':(110,180),'rapid':(70,130),'charge':(90,150),'def':(80,130)},
    'GAMMA': {'hp': (500,800),'atk':(80,140),'rapid':(50,100),'charge':(70,120),'def':(60,100)},
    'DELTA': {'hp': (350,600),'atk':(60,110),'rapid':(40,80),'charge':(50,90),'def':(45,80)},
    'EPSILON': {'hp': (250,450),'atk':(45,85),'rapid':(30,60),'charge':(40,70),'def':(35,60)},
    'ZETA': {'hp': (180,320),'atk':(30,65),'rapid':(20,45),'charge':(30,55),'def':(25,45)},
    'ETA': {'hp': (140,260),'atk':(25,55),'rapid':(18,40),'charge':(25,48),'def':(22,40)},
    'THETA': {'hp': (120,220),'atk':(22,48),'rapid':(16,36),'charge':(22,42),'def':(20,36)},
    'IOTA': {'hp': (100,190),'atk':(20,42),'rapid':(14,32),'charge':(20,38),'def':(18,32)},
    'KAPPA': {'hp': (90,170),'atk':(18,38),'rapid':(12,28),'charge':(18,34),'def':(16,28)},
    'LAMBDA': {'hp': (80,150),'atk':(16,34),'rapid':(10,24),'charge':(16,30),'def':(14,24)},
    'MU': {'hp': (70,130),'atk':(14,30),'rapid':(8,20),'charge':(14,26),'def':(12,20)},
    'NU': {'hp': (60,110),'atk':(12,26),'rapid':(6,16),'charge':(12,22),'def':(10,16)},
    'XI': {'hp': (50,95),'atk':(10,22),'rapid':(4,12),'charge':(10,18),'def':(8,12)},
    'OMICRON': {'hp': (40,80),'atk':(8,18),'rapid':(3,10),'charge':(8,14),'def':(6,10)},
    'PI': {'hp': (35,70),'atk':(7,16),'rapid':(3,9),'charge':(7,12),'def':(5,9)},
    'RHO': {'hp': (30,60),'atk':(6,14),'rapid':(2,8),'charge':(6,10),'def':(4,8)},
    'SIGMA': {'hp': (25,50),'atk':(5,12),'rapid':(2,7),'charge':(5,9),'def':(3,7)},
    'TAU': {'hp': (20,40),'atk':(4,10),'rapid':(1,6),'charge':(4,8),'def':(3,6)},
    'UPSILON': {'hp': (15,35),'atk':(3,8),'rapid':(1,5),'charge':(3,7),'def':(2,5)},
    'PHI': {'hp': (12,28),'atk':(3,7),'rapid':(1,4),'charge':(3,6),'def':(2,4)},
    'CHI': {'hp': (10,22),'atk':(2,6),'rapid':(1,3),'charge':(2,5),'def':(1,3)},
    'PSI': {'hp': (8,18),'atk':(2,5),'rapid':(1,3),'charge':(2,4),'def':(1,3)}
}

# ---- ELEMENTS ----
ELEMENTS = [
    'Fire','Water','Lightning','Ice','Wind','Earth','Light','Dark','Void',
    'Metal','Nature','Sound','Gravity','Time','Blood','Poison','Crystal','Plasma'
]

# ---- TYPES (alignments) ----
TYPES = ['Angelic','Demonic','Abyssal','Celestial','Mechanical','Viral','Guardian','Striker','Controller','Technical','Assassin','Tank']

# ---- FACTIONS ----
FACTIONS = ['Celestial Order','Aegis Concord','N3T Dominion','Undernet Syndicate','Abyssal Covenant','Free Grid Collective']

# ---- NAMING ----
PREFIXES = ['Neo','Cyber','Void','Arc','Zen','Xen','Chron','Vex','Lux','Nox','Axi','Kry','Pyr','Aeth','Umbr','Fer','Velo','Spec','Lumin','Tenebr']
CORES = ['kron','veil','thor','mantis','forge','shade','pulse','vortex','cipher','hex','aura','blade','core','wave','spire','rift','guard','shift','bound','weave']
SUFFIXES = ['ian','on','is','us','os','ax','ix','ox','ux','ar','en','or','an','ith','el','ar','um','ius','a','os']
TITLES = ['the Radiant','the Void Walker','the Grid Breaker','the Soul Forge','the Code Warden','the Flux Sage','the Null Knight','the Echo Lord','the Storm Herald','the Dusk Reaper']

def gen_name():
    p = random.choice(PREFIXES)
    c = random.choice(CORES)
    s = random.choice(SUFFIXES)
    return f'{p}{c}{s}'

def gen_title():
    return random.choice(TITLES)

def roll_stat(tier, key):
    r = TIER_STAT_RANGES.get(tier, TIER_STAT_RANGES['PSI'])
    lo, hi = r[key]
    return random.randint(lo, hi)

def gen_card(tier=None, element=None, type_=None, faction=None):
    if tier is None:
        # Default random tier for DEV batch use. Excludes OMEGA (apex) to avoid
        # accidental apex spawns; weights = one per non-OMEGA tier (23 tiers).
        pool = [t[0] for t in TIERS if t[0] != 'OMEGA']   # 23 tiers, no OMEGA
        weights = [0.01,0.02,0.02,0.03,0.03,0.04,0.04,0.05,0.05,0.05,
                   0.05,0.06,0.06,0.06,0.06,0.06,0.06,0.06,0.06,0.06,
                   0.06,0.06,0.06]                          # 23 weights, matches pool
        tier = random.choices(pool, weights=weights, k=1)[0]
    if element is None: element = random.choice(ELEMENTS)
    if type_ is None: type_ = random.choice(TYPES)
    if faction is None: faction = random.choice(FACTIONS)
    
    name = gen_name()
    title = gen_title()
    
    card = {
        'id': str(uuid.uuid4())[:8],
        'name': f'{name} {title}',
        'short_name': name,
        'tier': tier,
        'element': element,
        'type': type_,
        'faction': faction,
        'stats': {
            'hp': roll_stat(tier, 'hp'),
            'atk': roll_stat(tier, 'atk'),
            'rapid': roll_stat(tier, 'rapid'),
            'charge': roll_stat(tier, 'charge'),
            'def': roll_stat(tier, 'def')
        },
        'programs': [],
        'description': f'A {tier}-tier {element}-aligned {type_} of the {faction}.',
        'color_primary': f'#{random.randint(0,255):02x}{random.randint(0,255):02x}{random.randint(0,255):02x}',
        'color_accent': f'#{random.randint(0,255):02x}{random.randint(0,255):02x}{random.randint(0,255):02x}',
        'generated': datetime.now().isoformat()
    }
    
    # Generate programs based on element
    prog_prefixes = {'Fire':'Inferno','Water':'Tidal','Lightning':'Volt','Ice':'Cryo','Wind':'Cyclone','Earth':'Terra','Light':'Radiant','Dark':'Shadow','Void':'Null','Metal':'Ferro','Nature':'Bloom','Sound':'Sonic','Gravity':'Grav','Time':'Chrono','Blood':'Sanguine','Poison':'Toxin','Crystal':'Prism','Plasma':'Nova'}
    pp = prog_prefixes.get(element, 'Arcane')
    actions = ['Strike','Barrier','Pulse','Break','Shift','Burst','Wall','Lance','Field','Wave']
    card['programs'] = [f'{pp} {a}' for a in random.sample(actions, 3)]
    
    return card

# ============================================================
# PLAYER-FACING RANDOMIZER  (safe, rank-capped)
# For players who pick "Randomize NetP" instead of hand-building one.
# HARD RULE: must NEVER produce OMEGA or the top power tiers.
# Ceiling = ZETA (starter-grade). Excludes OMEGA + EPSILON..ALPHA.
# ============================================================
RANDOMIZER_MAX_TIER = 'ZETA'   # highest tier a player randomize can roll
FORBIDDEN_TIERS = {'OMEGA'}    # apex, never obtainable via randomize

def _allowed_random_tiers():
    """Tiers at or below the ZETA ceiling (by power value), OMEGA excluded.
    Greek value: higher = stronger; OMEGA=0 is treated as apex (forbidden)."""
    cap = dict(TIERS)[RANDOMIZER_MAX_TIER]          # ZETA -> 18
    allowed = [name for (name, val) in TIERS
               if name not in FORBIDDEN_TIERS and 0 < val <= cap]
    return allowed  # ZETA, ETA, THETA, IOTA, KAPPA, LAMBDA, MU, NU, XI,
                    # OMICRON, PI, RHO, SIGMA, TAU, UPSILON, PHI, CHI, PSI

def randomize_netp(element=None, type_=None, faction=None):
    """Generate ONE random player NetP, rank-capped so it can't be abused
    to farm high-tier/OMEGA NetPs. Tier is weighted toward the low-mid so a
    ZETA (best obtainable) is rare and most rolls land starter/mid-grade."""
    allowed = _allowed_random_tiers()
    # Weight: rarer as tier gets stronger. Strongest allowed (ZETA) is scarcest.
    # allowed is ordered strongest->weakest, so reverse the ramp.
    n = len(allowed)
    weights = [i + 1 for i in range(n)]             # weakest gets highest weight
    weights = list(reversed(weights))               # align to strongest-first order
    tier = random.choices(allowed, weights=weights, k=1)[0]
    card = gen_card(tier=tier, element=element, type_=type_, faction=faction)
    card['origin'] = 'randomizer'                   # provenance tag for the game
    card['rank_capped'] = RANDOMIZER_MAX_TIER
    return card

def generate_batch(count=25):
    cards = []
    for i in range(count):
        tier = None
        if i == 0: tier = 'OMEGA'
        elif i < 3: tier = random.choice(['ALPHA','BETA','GAMMA'])
        elif i < 8: tier = random.choice(['EPSILON','ZETA','ETA','THETA','IOTA'])
        elif i < 15: tier = random.choice(['KAPPA','LAMBDA','MU','NU','XI','OMICRON'])
        else: tier = random.choice(['PI','RHO','SIGMA','TAU','UPSILON','PHI','CHI','PSI'])
        cards.append(gen_card(tier=tier))
    return cards

def save_cards(cards):
    manifest = []
    for card in cards:
        filename = f"{card['id']}_{card['short_name'].lower()}.json"
        fpath = OUT_DIR / filename
        with open(fpath, 'w') as f:
            json.dump(card, f, indent=2)
        manifest.append({
            'id': card['id'],
            'name': card['name'],
            'tier': card['tier'],
            'element': card['element'],
            'type': card['type'],
            'faction': card['faction'],
            'filename': filename,
            'stats': card['stats']
        })
    # Save manifest
    with open(OUT_DIR / '_manifest.json', 'w') as f:
        json.dump({'count': len(cards), 'cards': manifest}, f, indent=2)
    # Save as JS for web game
    js = 'const CHARACTER_CARDS = ' + json.dumps(manifest, indent=2) + ';'
    with open(OUT_DIR / '_manifest.js', 'w') as f:
        f.write(js)
    return manifest

if __name__ == '__main__':
    import sys
    # ---- PLAYER RANDOMIZER MODE ----
    # Usage: python generate_cards.py randomize
    # Emits ONE rank-capped NetP as JSON to stdout (safe for player use, no OMEGA).
    if len(sys.argv) > 1 and sys.argv[1] == 'randomize':
        netp = randomize_netp()
        assert netp['tier'] not in FORBIDDEN_TIERS, 'SAFETY: randomizer produced forbidden tier'
        assert dict(TIERS)[netp['tier']] <= dict(TIERS)[RANDOMIZER_MAX_TIER], 'SAFETY: over ceiling'
        print(json.dumps(netp, indent=2))
        sys.exit(0)
    # ---- DEV BATCH MODE ----
    count = int(sys.argv[1]) if len(sys.argv) > 1 else 25
    print(f'Generating {count} character cards...')
    cards = generate_batch(count)
    manifest = save_cards(cards)
    # Print summary
    tiers = {}
    for c in manifest:
        t = c['tier']
        tiers[t] = tiers.get(t, 0) + 1
    print(f'Generated {len(manifest)} cards:')
    for t, n in sorted(tiers.items(), key=lambda x: TIER_STAT_RANGES.get(x[0],{}).get('hp',(0,0))[1], reverse=True):
        print(f'  {t}: {n}')
    print(f'Saved to: {OUT_DIR}')
