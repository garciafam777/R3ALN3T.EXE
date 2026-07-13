#!/usr/bin/env python3
"""gen_netp_career_matrix.py — generate 272 FR3ALN3TNetP entries (one per career).
Rules (CEO 07.13):
- Element fixed per category (canon 21). transportation->Glitch. Poison reserved for skins.
- Construct per archetype (rule B). GreekTier: cat=Delta, job=Zeta.
- Moves: 9 total = specials (2 normal / 3 apex Void/Light/Dark/Plasma) + utility.
  OMEGA rank would add +1 special (not applied here; base tiers only).
- 3 Constructs (Trinity/Tyranny/Eternity) = SPECIAL NetPs, transform layer; handled separately.
Usage: python gen_netp_career_matrix.py
Output: gamedata/netps/netp_career_matrix.json
"""
import os, json

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CAREERS = os.path.join(REPO, "gamedata", "careers")
OUT = os.path.join(REPO, "gamedata", "netps", "netp_career_matrix.json")

CAT_ELEMENT = {
    "agriculture_biosphere": "Nature", "artificial_intelligence": "Elec", "communications_media": "Sound",
    "construction": "Earth", "cybersecurity": "Dark", "economics_trade": "Time", "education": "Wood",
    "engineering": "Metal", "entertainment_arts": "Plasma", "exploration": "Void", "government_administration": "Crystal",
    "information_technology": "Aqua", "intelligence_agencies": "Null", "law_justice": "Light", "manufacturing": "Fire",
    "medical_biosystem": "Blood", "military_defense": "Wind", "science_research": "Ice", "space_operations": "Gravity",
    "transportation_logistics": "Glitch",
}
CAT_ARCH = {
    "transportation_logistics": ("Trucker", "CyberBellyUnit"),
    "space_operations": ("ATC", "RunwayControlSphere"),
    "medical_biosystem": ("Medical", "MediSynthShell"),
    "construction": ("Construction", "DumpTransformerHull"),
    "cybersecurity": ("Cipher", "ShieldedCipherExoshell"),
    "artificial_intelligence": ("Cognition", "CognitionRig"),
    "information_technology": ("DataCenter", "DataCenterFrame"),
    "manufacturing": ("Factory", "FactoryBotShell"),
    "science_research": ("Lab", "LabAstralRig"),
    "government_administration": ("Civic", "CivicCommandShell"),
    "military_defense": ("Orbital", "OrbitalEnforcerExo"),
}
CAT_FACTION = {
    "transportation_logistics": "EonLogistics", "space_operations": "SkyDirectorate",
    "medical_biosystem": "ClinicOrder", "construction": "InfraDominion", "cybersecurity": "CipherCollective",
    "artificial_intelligence": "CognitionGuild", "information_technology": "DataSovereign",
    "manufacturing": "ForgeSyndicate", "science_research": "AstraLab", "government_administration": "CivicCore",
    "military_defense": "OrbitalEnclave", "agriculture_biosphere": "BiosphereOrder", "communications_media": "SignalChoir",
    "economics_trade": "LedgerConsortium", "education": "ScholaNet", "engineering": "StructurePact",
    "entertainment_arts": "LumenStage", "exploration": "FrontierGuild", "intelligence_agencies": "NullWatch",
    "law_justice": "JustitiaRing",
}
APEX = {"Void", "Light", "Dark", "Plasma"}
UTIL = ["HEADSET HUSH", "PLATE ROLL", "WRENCH HOOK", "SERUM SPARK", "SCAFFOLD GUARD",
        "CALM BREATH", "ROUTE LOCK", "SITE MARKER", "DELIVERY OVERDRIVE"]
SPECIAL_BY_ELEM = {
    "Fire": ["PYRE BURST", "EMBER SLAM"], "Aqua": ["TIDE CRUSH", "DEEP PRESSURE"], "Elec": ["ARC LANCE", "STATIC SURGE"],
    "Ice": ["GLACIER EDGE", "FROST LOCK"], "Wind": ["GALE SLASH", "CYCLONE PULL"], "Earth": ["TERRA SMASH", "STONE WALL"],
    "Nature": ["BLOOM VINE", "THORN SPIKE"], "Sound": ["RESONANCE BOOM", "ECHO STRIKE"], "Gravity": ["MASS CRUSH", "PULL WELL"],
    "Time": ["CHRONO STEP", "REWIND PULSE"], "Blood": ["CRIMSON DRAIN", "VEIN LANCE"], "Poison": ["TOXIC CLOUD", "VENOM BITE"],
    "Crystal": ["PRISM SHARD", "FACET BEAM"], "Metal": ["ALLOY RAM", "SPARK CLAMP"], "Wood": ["BARK GUARD", "ROOT GRAB"],
    "Null": ["ERASURE FIELD", "VOID GRASP"], "Glitch": ["CORRUPT SLICE", "FRAME SKIP"],
    "Void": ["VOID SINGULARITY", "NULL COLLAPSE", "ABYSS DEVOUR"], "Light": ["RADIANCE BLADE", "PRISM NOVA", "HALO BURN"],
    "Dark": ["UMBRA VEIL", "SHADOW REND", "VOID MAW"], "Plasma": ["PLASMA TORRENT", "ION STORM", "FUSION NOVA"],
}
SOUL_BY_CAT = {
    "transportation_logistics": "Surge Delivery", "space_operations": "Approach Ascendant", "medical_biosystem": "Steady Recovery",
    "construction": "Site Mastery", "cybersecurity": "Cipher Lock", "artificial_intelligence": "Logic Surge",
    "information_technology": "Dataflow", "manufacturing": "Forge Pulse", "science_research": "Insight State",
    "government_administration": "Civic Steady", "military_defense": "Combat Ready", "agriculture_biosphere": "Bloom State",
    "communications_media": "Signal Clear", "economics_trade": "Ledger Sync", "education": "Scholar Calm",
    "engineering": "Struct True", "entertainment_arts": "Stage Live", "exploration": "Frontier Ready",
    "intelligence_agencies": "Watch Silent", "law_justice": "Just Order",
}


def decode(fname):
    base = fname[:-3]
    if base.startswith("cat__"):
        return base[5:], None, "cat"
    parts = base.split("__")
    return parts[1], parts[2], "job"


def main():
    files = sorted(f for f in os.listdir(CAREERS) if f.endswith(".js"))
    entries, idx = [], 0
    for f in files:
        cat, role, kind = decode(f)
        base = f[:-3]
        elem = CAT_ELEMENT.get(cat, "Null")
        arch, construct = CAT_ARCH.get(cat, ("Generic", "Standard Unit"))
        faction = CAT_FACTION.get(cat, "NEUTRAL PACT")
        soul = SOUL_BY_CAT.get(cat, "Ready")
        tier = "Delta" if kind == "cat" else "Zeta"
        specials = SPECIAL_BY_ELEM[elem]
        util_needed = 9 - len(specials)
        util = (UTIL * 3)[:util_needed]
        moves = [{"name": s, "type": "special", "iconConcept": elem.lower(), "effectLine": f"{elem} signature strike"} for s in specials]
        moves += [{"name": u, "type": "utility", "iconConcept": "neutral", "effectLine": "archetype utility"} for u in util]
        disp = (role if role else cat).replace("_", " ").title()
        entries.append({
            "id": f"NETP_{idx:04d}", "DisplayName": disp, "Archetype": arch, "Element": elem,
            "Faction": faction, "Construct": construct, "GreekTier": tier, "SoulState": soul,
            "HP": 7000 + idx % 2000, "ATK": 400 + idx % 300, "RAPID": 200 + idx % 200,
            "CHARGE": 500 + idx % 200, "DEF": 700 + idx % 300,
            "moves": moves, "mesh": f"mesh_{cat}_{idx:04d}", "isSpecial": False, "sourceCareer": base,
        })
        idx += 1
    os.makedirs(os.path.dirname(OUT), exist_ok=True)
    with open(OUT, "w", encoding="utf-8") as fh:
        json.dump(entries, fh, indent=2)
    apex3 = [e for e in entries if e["Element"] in APEX]
    norm2 = [e for e in entries if e["Element"] not in APEX]
    assert len(entries) == 272
    assert all(len([m for m in e["moves"] if m["type"] == "special"]) == 3 for e in apex3)
    assert all(len([m for m in e["moves"] if m["type"] == "special"]) == 2 for e in norm2)
    assert all(len(e["moves"]) == 9 for e in entries)
    print(f"AD-HOC VERIFICATION: PASS | {len(entries)} NetP entries | apex(3-special)={len(apex3)} normal(2-special)={len(norm2)} | all 9 moves")


if __name__ == "__main__":
    main()
