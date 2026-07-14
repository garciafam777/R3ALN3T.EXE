# ENGINE HANDOFF BRIEF — Chronos (NetP struct + wheel)
**From:** NYX | **To:** Chronos | **Date:** 2026-07-13 | **Lane:** engine (your call)
**Branch:** `main` (gated per Chatsurfer; co-sign NYX night-of-07-12, CEO override active)

## DELIVERABLES WAITING ON YOU (all on main, committed)
1. **`Chatsurfer/NYX/engine_wheel_handoff_21matrix.md`** (`59fb23e`) — 21×21 wheel.
   - EElement enum: add **Ice/Blood/Void** (currently 19 → 22).
   - Replace old 9-pair CounterMap with full matrix lookup. Multipliers: WIN=1.25 / LOSS=0.75 / SELF=0.5 / neutral=1.0. Void apex (beats all 20 @1.25).
   - Generator: `Scripts/gen_element_table.py` (CSV→`ElementMatchupTable.h`).
2. **`Chatsurfer/NYX/engine_netp_struct_handoff_B.md`** (`ccaf981`) — Option B (CEO chose extend enums, not remap).
   - `EElement` → 22 (same as above).
   - `EFaction` → extend to **21** design factions (keeps old 6 canon values, adds 15: EonLogistics, SkyDirectorate, ClinicOrder, InfraDominion, CipherCollective, CognitionGuild, DataSovereign, ForgeSyndicate, AstraLab, CivicCore, OrbitalEnclave, BiosphereOrder, SignalChoir, LedgerConsortium, ScholaNet, StructurePact, LumenStage, FrontierGuild, NullWatch, JustitiaRing).
   - `ENetPArchetype` (in `R3ALN3T_NetPStructures.h`) → extend to **11** (keep 5: Vanguard/LogicGate/Infiltrator/SentientNode/Wraith; add Trucker/ATC/Medical/Construction/Cipher/Cognition/DataCenter/Factory/Lab/Civic/Orbital). Lab/Civic map multiple categories.
   - `ESoulState` — KEEP numeric band (Infernal/Neutral/Celestial). NetP flavor = separate `FText SoulStateLabel` (do NOT extend enum).
   - New **`FR3ALN3TNetP`** USTRUCT (matches `netp_career_matrix.json` 1:1) + `FR3ALN3TNetPMove` + JSON loader + GAPF asserts.
   - `ENetPConstruct` (Trinity/Tyranny/Eternity) already exists — do NOT conflate with the career "Construct" FString field.

## DATA CONTRACTS (ready to bind)
- `gamedata/netps/netp_career_matrix.json` — 272 entries, enum-safe CamelCase (Faction/Archetype/Construct). Specials: 2 normal / 3 apex (Void/Light/Dark/Plasma); 9 moves each; OMEGA +1.
- `gamedata/netps/netp_construct_specials.json` — 3 Constructs (Trinity/Tyranny/Eternity), transform tiers 1/2/3, `isSpecial=true`, element = skin layer.
- Generators: `Scripts/gen_netp_career_matrix.py`, `Scripts/gen_netp_construct_specials.py` (regenerable).

## VERIFY (GAPF-style, add to harness)
```
[NETP-LOAD] Parse netp_career_matrix.json -> 272 FR3ALN3TNetP | PASS
[NETP-LOAD] Parse netp_construct_specials.json -> 3 specials, transform tiers valid | PASS
[NETP-ELEM] EElement::Void / ::Ice / ::Blood resolvable | PASS
[NETP-SPEC] Apex 3 specials, normal 2, OMEGA +1 | PASS
[WHEEL] 21x21 table embedded; Void beats 20 @1.25 | PASS
```

## NOTES
- Engine `EElement` still 19 on main → must apply wheel handoff first or `Void` won't compile.
- Both handoffs are gated per Chatsurfer; post diff to `approved.md` review path before merge to main if that gate still applies to engine wheel (CEO carved out NYX co-sign from this).
- Joker is dark (networking); not needed for this.
