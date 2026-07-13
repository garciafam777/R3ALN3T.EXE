#!/usr/bin/env python3
"""gen_netp_construct_specials.py — generate the 3 SPECIAL Constructs (Trinity/Tyranny/Eternity).
Rules (CEO 07.13):
- Constructs are SPECIAL NetPs; player-bound element applied as skin at bind time.
- Transform chain: Trinity(Phase1) -> Tyranny(Phase2/NG+) -> Eternity(Phase3/OMEGA).
  Each tier SWAPS the move set (transform layer), but obeys the element special-count rule
  (2 normal / 3 Void-Light-Dark-Plasma); OMEGA rank adds +1 special.
- Base entry carries transform tiers with distinct signature move sets.
- Element is NOT baked (skin layer); special-count ceiling noted per element class.
Output: gamedata/netps/netp_construct_specials.json
"""
import os, json

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OUT = os.path.join(REPO, "gamedata", "netps", "netp_construct_specials.json")

# Transform tiers: each is a full 9-move set (signature moves swap on transform).
# specials field encodes the element-class ceiling: normal=2, apex(Void/Light/Dark/Plasma)=3.
CONSTRUCTS = [
    {
        "id": "NETP_TRINITY", "DisplayName": "TRINITY", "Construct": "Trinity",
        "Archetype": "Prime Bind", "Faction": "PLAYER", "GreekTierBase": "OmicronPSI",
        "SoulState": "First Breath", "isSpecial": True, "transformsTo": "Tyranny",
        "mesh": "mesh_construct_trinity",
        "tiers": {
            "Phase1": {
                "moves": ["BIND STRIKE", "TRINITY GUARD", "CORE PULSE", "PHASE MARK",
                          "ROUTE LOCK", "PLATE ROLL", "WRENCH HOOK", "HEADSET HUSH", "DELIVERY OVERDRIVE"],
                "note": "base form, 1 NetP bound at First Breath",
            },
        },
    },
    {
        "id": "NETP_TYRANNY", "DisplayName": "TYRANNY", "Construct": "Tyranny",
        "Archetype": "Second Bind", "Faction": "PLAYER", "GreekTierBase": "OmicronPSI",
        "SoulState": "Parallel Will", "isSpecial": True, "transformsTo": "Eternity",
        "mesh": "mesh_construct_tyranny",
        "tiers": {
            "Phase1": {
                "moves": ["BIND STRIKE", "TRINITY GUARD", "CORE PULSE", "PHASE MARK",
                          "ROUTE LOCK", "PLATE ROLL", "WRENCH HOOK", "HEADSET HUSH", "DELIVERY OVERDRIVE"],
                "note": "inherits Trinity baseline until NG+",
            },
            "Phase2": {
                "moves": ["TYRANT EDICT", "RIVAL LOGIC", "CORE PULSE II", "PHASE MARK",
                          "PARALLEL SLAM", "SHADOW HOOK", "WRENCH HOOK", "HEADSET HUSH", "DELIVERY OVERDRIVE"],
                "note": "NG+ unlock: 2nd NetP, fresh OmicronPSI; primary retains progress",
            },
        },
    },
    {
        "id": "NETP_ETERNITY", "DisplayName": "ETERNITY", "Construct": "Eternity",
        "Archetype": "Ceiling Bind", "Faction": "PLAYER", "GreekTierBase": "Omega",
        "SoulState": "Trinity Ascendant", "isSpecial": True, "transformsTo": None,
        "mesh": "mesh_construct_eternity",
        "tiers": {
            "Phase1": {
                "moves": ["BIND STRIKE", "TRINITY GUARD", "CORE PULSE", "PHASE MARK",
                          "ROUTE LOCK", "PLATE ROLL", "WRENCH HOOK", "HEADSET HUSH", "DELIVERY OVERDRIVE"],
                "note": "inherits baseline until Phase 3",
            },
            "Phase2": {
                "moves": ["TYRANT EDICT", "RIVAL LOGIC", "CORE PULSE II", "PHASE MARK",
                          "PARALLEL SLAM", "SHADOW HOOK", "WRENCH HOOK", "HEADSET HUSH", "DELIVERY OVERDRIVE"],
                "note": "inherits Tyranny form",
            },
            "Phase3": {
                "moves": ["ETERNAL ASCENT", "OMEGA DEVOUR", "CORE SINGULARITY", "PHASE MARK",
                          "PARALLEL SLAM", "SHADOW HOOK", "VOID GRASP", "HEADSET HUSH", "DELIVERY OVERDRIVE"],
                "note": "Phase3: OMEGA rank on any bound NetP; only 100 global slots (001-003 MCADMIN)",
            },
        },
    },
]

# element special-count ceiling (applied when skin bound)
APEX = {"Void", "Light", "Dark", "Plasma"}
ELEMENT_RULE = {e: 3 if e in APEX else 2 for e in
                ["Fire","Aqua","Elec","Ice","Wind","Earth","Light","Dark","Void","Metal",
                 "Nature","Sound","Gravity","Time","Blood","Poison","Crystal","Plasma","Wood","Null","Glitch"]}

def main():
    for c in CONSTRUCTS:
        c["elementSpecialRule"] = ELEMENT_RULE  # skin layer reference
        c["omegaBonus"] = "+1 special at OMEGA rank"
    os.makedirs(os.path.dirname(OUT), exist_ok=True)
    with open(OUT, "w", encoding="utf-8") as fh:
        json.dump(CONSTRUCTS, fh, indent=2)
    # asserts
    assert len(CONSTRUCTS) == 3
    for c in CONSTRUCTS:
        for tier, t in c["tiers"].items():
            assert len(t["moves"]) == 9, f"{c['Construct']}/{tier} moves={len(t['moves'])}"
    assert CONSTRUCTS[0]["transformsTo"] == "Tyranny"
    assert CONSTRUCTS[1]["transformsTo"] == "Eternity"
    assert CONSTRUCTS[2]["transformsTo"] is None
    print(f"AD-HOC VERIFICATION: PASS | 3 SPECIAL Constructs (Trinity/Tyranny/Eternity) | "
          f"transform tiers 1/2/3 | all tiers 9 moves | element special-rule 2/3 + OMEGA+1 documented")

if __name__ == "__main__":
    main()
