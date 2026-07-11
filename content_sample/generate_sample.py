#!/usr/bin/env python3
"""
R3ALN3T.EXE - CANON-COMPLIANT content sample generator (post Chronos/CEO verdict).
Fixes per Chatsurfer/Chronos/content_grind_review_approved.md:
  1) Element pool = canonical 7 ONLY (Fire/Aqua/Elec/Wood/Wind/Holy/Void)
     - source of truth: Project/.../Core/Types/BattleGridTypes.h:19
       enum EBattleElementType { None, Fire, Aqua, Elec, Wood, Wind, Holy, Void }
  2) Clamp numeric bands (CSI/CoreStabilityIndex 0-100, stats within tier ranges)
  3) Careers get real name + tier (were empty stubs)
  4) Chips get a damage/MB field (was "None")
  5) Enemies/careers data POSTED to the reviewable branch (no orphaned counts)
Output: ~25-row SAMPLE per category only (NO volume grind). For re-review, not shipping.
"""
import csv, json, os, random

random.seed(2026_07_10)

# ---- CANON (from engine source) ----
ELEMENTS_7 = ["Fire", "Aqua", "Elec", "Wood", "Wind", "Holy", "Void"]
ALIGNMENTS = ["Mechanical", "Viral", "Angelic", "Demonic"]
HOME_DIMS = ["Heaven", "OuterSpace", "LunaMars", "Reality", "Cyberspace", "Hell"]
ARCHETYPES = ["Vanguard", "LogicGate", "Infiltrator", "SentientNode", "Wraith"]
FACTIONS = ["CORRUPTED SECTOR", "PROTOCOL DIVISION", "ASTRUM DIVISION", "IRON CORTEX",
            "HALO CORE", "ABYSSAL CABAL", "VOID CULT", "INFECTION VECTOR",
            "SYNTHETIC NETWORK", "GEAR SECT", "LUMINA SECT", "ROT CLUSTER", "PHAGE CELL"]

# 16-rank tier hierarchy (tier, rank_start, rank_end) - kept from prior design
TIERS = ["OMEGA","ALPHA","BETA","GAMMA","DELTA","EPSILON","ZETA","ETA",
         "THETA","IOTA","KAPPA","LAMBDA","MU","NU","XI","OMICRON"]
TIER_STAT = {
    "OMEGA":  {"HP":(8000,12000),"ATK":(700,1100),"RAPID":(85,120),"CHARGE":(90,130),"DEF":(600,950)},
    "ALPHA":  {"HP":(6500,9500), "ATK":(550,850), "RAPID":(70,100),"CHARGE":(75,110),"DEF":(450,750)},
    "BETA":   {"HP":(5000,7500), "ATK":(400,650), "RAPID":(55,80), "CHARGE":(60,90), "DEF":(350,600)},
    "GAMMA":  {"HP":(3800,5800), "ATK":(300,500), "RAPID":(45,65), "CHARGE":(50,75), "DEF":(250,450)},
    "DELTA":  {"HP":(2800,4200), "ATK":(220,380), "RAPID":(35,55), "CHARGE":(40,60), "DEF":(180,350)},
    "EPSILON":{"HP":(2000,3200), "ATK":(160,280), "RAPID":(28,45), "CHARGE":(32,50), "DEF":(130,260)},
    "ZETA":   {"HP":(1400,2400), "ATK":(110,200), "RAPID":(22,36), "CHARGE":(25,40), "DEF":(90,190)},
    "ETA":    {"HP":(1000,1700), "ATK":(80,150),  "RAPID":(17,28), "CHARGE":(20,32), "DEF":(65,140)},
    "THETA":  {"HP":(700,1200),  "ATK":(55,100),  "RAPID":(13,22), "CHARGE":(15,25), "DEF":(45,100)},
    "IOTA":   {"HP":(500,900),   "ATK":(40,75),   "RAPID":(10,18), "CHARGE":(12,20), "DEF":(32,80)},
    "KAPPA":  {"HP":(350,700),   "ATK":(30,55),   "RAPID":(8,14),  "CHARGE":(10,16), "DEF":(22,60)},
    "LAMBDA": {"HP":(250,500),   "ATK":(22,40),   "RAPID":(6,11),  "CHARGE":(8,13),  "DEF":(15,45)},
    "MU":     {"HP":(180,360),   "ATK":(16,30),   "RAPID":(5,9),   "CHARGE":(6,10),  "DEF":(10,35)},
    "NU":     {"HP":(120,250),   "ATK":(11,22),   "RAPID":(4,7),   "CHARGE":(5,8),   "DEF":(7,25)},
    "XI":     {"HP":(80,170),    "ATK":(8,15),    "RAPID":(3,6),   "CHARGE":(4,6),   "DEF":(5,18)},
    "OMICRON":{"HP":(50,120),    "ATK":(5,10),    "RAPID":(2,5),   "CHARGE":(3,5),   "DEF":(3,12)},
}
ELEMENT_WORDS = {
    "Fire":["Blaze","Ember","Pyre","Cinder","Flare"], "Aqua":["Tide","Ripple","Torrent","Mist","Surge"],
    "Elec":["Bolt","Spark","Volt","Arc","Surge"], "Wood":["Root","Thorn","Vine","Bloom","Bark"],
    "Wind":["Gale","Breeze","Squall","Zephyr","Draft"], "Holy":["Radiance","Halo","Sera","Lumen","Sanct"],
    "Void":["Umbral","Rift","Eclipse","Null","Abyss"],
}
ALIGN_WORDS = {"Mechanical":["Unit","Frame","Core","Node","Sys"],"Viral":["Strain","Phage","Spore","Vex","Rot"],
               "Angelic":["Seraph","Lumen","Halo","Aria","Cael"],"Demonic":["Infer","Wraith","Maw","Hex","Cinder"]}

NETP_HEADERS = ["card_number","tier","rank","name","alignment","element","faction",
                "hp","atk","rapid","charge","defense","move_1","move_2","move_3","move_4",
                "move_5","move_6","move_7","move_8","move_9","flavor_text","construct_sprite",
                "source_identities","color_pal"]

def clamp(v, lo, hi): return max(lo, min(hi, v))

def gen_netp_name(alignment, element, tier):
    a = random.choice(ALIGN_WORDS[alignment]); e = random.choice(ELEMENT_WORDS[element])
    return f"{a}{e} {tier[:3]}X" if tier!="OMEGA" else f"{a}{e} TRINITY"

def gen_stats(tier):
    r = TIER_STAT[tier]; return {k: random.randint(*v) for k,v in r.items()}

def gen_moves(element, tier):
    words = ELEMENT_WORDS[element]
    out=[]
    for i in range(9):
        w = random.choice(words); a = random.choice(["Rush","Strike","Boost","Bind","Drain","Ward","Charge","Shield","Catalyst"])
        out.append(f"DIVINE.{w.upper()}.{a.upper()}" if tier=="OMEGA" else f"{w} {a}")
    return out

def gen_csi(tier):
    # CoreStabilityIndex: clamp to 0-100, higher tiers skew higher but never exceed 100
    base = {"OMEGA":95,"ALPHA":90,"BETA":82,"GAMMA":74,"DELTA":66,"EPSILON":58,
            "ZETA":50,"ETA":44,"THETA":38,"IOTA":32,"KAPPA":27,"LAMBDA":22,"MU":18,"NU":14,"XI":10,"OMICRON":6}[tier]
    return clamp(base + random.randint(-8,4), 0, 100)

def make_netps(n_per_tier=2):
    rows=[]; idx=1
    for tier in TIERS:
        for _ in range(n_per_tier):
            el=random.choice(ELEMENTS_7); al=random.choice(ALIGNMENTS); fac=random.choice(FACTIONS)
            s=gen_stats(tier); csi=gen_csi(tier)
            moves=gen_moves(el,tier)
            name=gen_netp_name(al,el,tier)
            rows.append({**{"card_number":f"{tier[:3]}-{idx:04d}","tier":tier,"rank":idx,
                            "name":name,"alignment":al,"element":el,"faction":fac,
                            "hp":s["HP"],"atk":s["ATK"],"rapid":s["RAPID"],"charge":s["CHARGE"],
                            "defense":s["DEF"],"move_1":moves[0],"move_2":moves[1],"move_3":moves[2],
                            "move_4":moves[3],"move_5":moves[4],"move_6":moves[5],"move_7":moves[6],
                            "move_8":moves[7],"move_9":moves[8],
                            "flavor_text":f"[{tier}] {name} ({el}) deployed from {fac}. CSI={csi}.",
                            "construct_sprite":"","source_identities":"NyxGen","color_pal":el.lower()},})
            idx+=1
    return rows

def make_chips(n=25):
    chips=[]
    for i in range(1,n+1):
        el=random.choice(ELEMENTS_7)
        name=f"{el} {random.choice(['V1','V2','V3','R','SP','EX','M','Z'])}"
        dmg=random.choice([10,20,30,40,50,60,80,100,120,150])  # MB values, canon-plausible
        chips.append({"id":f"CHIP-{i:04d}","name":name,"element":el,"damage":dmg,
                      "mb":dmg,"description":f"Elemental chip ({el}). Deals {dmg} damage."})
    return chips

def make_careers(n=25):
    careers=[]; prefixes=["Grid","Soul","Data","Void","Pulse","Core","Hex","Astra"]
    roles=["Runner","Binder","Warden","Splice","Weaver","Hunter","Smith","Seer"]
    for i in range(1,n+1):
        el=random.choice(ELEMENTS_7); tier=random.choice(TIERS)
        name=f"{random.choice(prefixes)}{random.choice(roles)}"
        careers.append({"id":f"CAREER-{i:03d}","name":name,"element":el,"tier":tier,
                        "description":f"{tier}-tier {el} specialist path: {name}."})
    return careers

def make_enemies(n=25):
    enemies=[]; bases=["Drone","Sentinel","Wraith","Node","Husk","Golem","Sprite"]
    for i in range(1,n+1):
        el=random.choice(ELEMENTS_7); tier=random.choice(TIERS)
        name=f"{random.choice(bases)}-{el[:2]}{i}"
        s=gen_stats(tier)
        enemies.append({"id":f"ENEMY-{i:04d}","name":name,"element":el,"tier":tier,
                        "hp":s["HP"],"atk":s["ATK"],"defense":s["DEF"],
                        "description":f"{tier} {el} hostile unit."})
    return enemies

OUT="content_sample"
os.makedirs(f"{OUT}/netps",exist_ok=True); os.makedirs(f"{OUT}/chips",exist_ok=True)
os.makedirs(f"{OUT}/narrative",exist_ok=True); os.makedirs(f"{OUT}/enemies",exist_ok=True)

netps=make_netps(2)  # 32 rows across 16 tiers (~2 each)
chips=make_chips(25); careers=make_careers(25); enemies=make_enemies(25)

with open(f"{OUT}/netps/netp_sample.csv","w",newline="",encoding="utf-8") as f:
    w=csv.DictWriter(f,fieldnames=NETP_HEADERS); w.writeheader()
    for r in netps: w.writerow({k:r.get(k,"") for k in NETP_HEADERS})
json.dump(chips,open(f"{OUT}/chips/chip_sample.json","w"),indent=2)
json.dump(careers,open(f"{OUT}/narrative/career_sample.json","w"),indent=2)
json.dump(enemies,open(f"{OUT}/enemies/enemy_sample.json","w"),indent=2)

# validation gate
bad=0
for r in netps:
    if r["element"] not in ELEMENTS_7: bad+=1
    # CSI is embedded in flavor_text as "CSI=<n>" -> verify clamp 0-100
    import re as _re
    m=_re.search(r"CSI=(\d+)", r["flavor_text"])
    if m and not (0<=int(m.group(1))<=100): bad+=1
for c in chips:
    if c["element"] not in ELEMENTS_7 or c["damage"] in (None,"None"): bad+=1
for c in careers:
    if c["element"] not in ELEMENTS_7 or not c.get("name") or not c.get("tier"): bad+=1
for e in enemies:
    if e["element"] not in ELEMENTS_7 or not e.get("name"): bad+=1
print(f"SAMPLE generated: netp={len(netps)} chips={len(chips)} careers={len(careers)} enemies={len(enemies)}")
print(f"VALIDATION: off-wheel/off-field rows = {bad} (expect 0)")
