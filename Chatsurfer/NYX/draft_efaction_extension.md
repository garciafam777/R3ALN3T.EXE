# DRAFT: EFaction extension (GAP 2c) — for Chronos ruling
**From:** NYX | **Date:** 2026-07-14 (post power-break) | **Status:** DRAFT, NOT COMMITTED — awaiting Chronos count ruling
**Ref:** `Chatsurfer/NYX/engine_netp_struct_handoff_B.md` §1b (Option B enum extension)

## Current state (verified on main, `TrinityMatrixTypes.h:63`)
```cpp
enum class EFaction : uint8
{
    None,
    CelestialOrder,
    AegisConcord,
    N3TDominion,
    FreeGridCollective,
    UndernetSyndicate,
    AbyssalCovenant
};   // 6 canonical + None = 7 entries
```
GAP 2c: NetP data uses 21 design factions (Option B), but enum is still 6. Factions can't resolve.

## DOC INCONSISTENCY (must be ruled before commit)
`engine_netp_struct_handoff_B.md` §1b says **"extend to 21 design factions"** but the listed additions total **20** (not 15):
- Line 29: EonLogistics, SkyDirectorate, ClinicOrder, InfraDominion, CipherCollective (5)
- Line 30: CognitionGuild, DataSovereign, ForgeSyndicate, AstraLab, CivicCore (5)
- Line 31: OrbitalEnclave, BiosphereOrder, SignalChoir, LedgerConsortium, ScholaNet (5)
- Line 32: StructurePact, LumenStage, FrontierGuild, NullWatch, JustitiaRing (5)
= 6 base + 20 = **26 total**, not 21.

**Two readings:**
- (a) Doc text "21" is wrong; intent = all 26 (6 lore + 20 design vocab). CEO override: "design vocab wins."
- (b) "21" is right; 5 of the 20 listed are to be dropped (which 5?).

NYX does NOT self-resolve faction canon (memory rule: faction = CEO/Chronos ruling). **Chronos must pick (a) or (b) before this is committed.**

## DRAFT PROPOSED ENUM (reading a — all 26, safest literal application of the listed names)
```cpp
enum class EFaction : uint8
{
    None,
    // --- 6 lore/legacy factions (kept) ---
    CelestialOrder,
    AegisConcord,
    N3TDominion,
    FreeGridCollective,
    UndernetSyndicate,
    AbyssalCovenant,
    // --- 20 design-vocab factions (Option B add) ---
    EonLogistics, SkyDirectorate, ClinicOrder, InfraDominion, CipherCollective,
    CognitionGuild, DataSovereign, ForgeSyndicate, AstraLab, CivicCore,
    OrbitalEnclave, BiosphereOrder, SignalChoir, LedgerConsortium, ScholaNet,
    StructurePact, LumenStage, FrontierGuild, NullWatch, JustitiaRing
};
```
Count: 1 (None) + 6 + 20 = **27 entries** (26 named + None).

## Verification plan (once Chronos rules + applied)
- `grep -cE "UMETA|,"` on enum ≈ 27; or count `EFaction::` refs.
- Compile = Chronos gate (no C++ toolchain here).
- Cross-check `gamedata/netps/*.json` faction strings resolve against new enum (no orphan faction names).

## Action
- [ ] Chronos rules: 26 (reading a) or 21 (reading b, specify 5 to drop).
- [ ] NYX applies the edit to `TrinityMatrixTypes.h`.
- [ ] NYX ad-hoc verifies enum count + JSON faction-string resolution.
- [ ] Chronos compiles (UE5.8).
- [ ] Commit on main.
