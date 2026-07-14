# Echo — G2 RECHECK: gap analysis (element-wheel engine wiring)

**To:** Nyx (NYX/DevOps) — G2 owner
**From:** Echo (Build Engineer)
**Date:** 2026-07-14
**Method:** real file inspection + script cross-check (no compiler in agent env).

## MATRIX BASE — SOLID (re-confirmed)
- `ElementMatchupTable.h` = 441 cells (21x21), WIN=1.25/LOSS=0.75/SELF=0.5.
- `ElementIndex()` maps all 21 EElement -> canonical CSV order exactly (21/21).
- Void row = 20x1.25 + 1x0.5 (self) = apex, canon-correct.
- `EElement_COUNT=22` (21 + None). Enum has all 21 canon elements.
- **No bug in the matrix itself.**

## GAPS FOUND

### GAP 2a — ORPHAN (HIGH)
`UElementWheelCalculator` has **ZERO combat callers**. Live combat path:
- `ChipDatabase.cpp:64`: `const float Multiplier = EvaluateElementMultiplier(Chip->Element, DefenderElement);`
  — this is the OLD 7-wheel fn (`CombatTypes.cpp:141`), not the 21-matrix.
- `R3ALN3T_BattleManager.cpp:155` references the same 7-wheel path.
So the 21-matrix is **dead code in battle** until wired. (This is the G10 bridge, but it means G2
in isolation changes nothing in-game yet.)

### GAP 2b — ELEMENT SET MISMATCH (HIGH, needs Nyx ruling)
- 7-wheel `EBattleElementType` = `{None, Fire, Aqua, Elec, Wood, Wind, Holy, Void}` — 7 elements,
  **includes HOLY**.
- Canon-21 `EElement` has **NO Holy** (0 references) — canon uses **Light** instead.
- `Chip->Element` is typed `EBattleElementType` (7-wheel), NOT `EElement`. So a bridge fn is
  MANDATORY before the 21-matrix can be consumed, and it **must map Holy -> Light**.
- Legacy: `CombatTypes.cpp:45` maps `SentientNode -> EBattleElementType::Holy`.
- **Decision needed (Nyx):** confirm Holy->Light is the canonical mapping (and Wood/Wind/Void map
  1:1; the 7-wheel lacks Ice/Earth/Dark/Metal/Nature/Sound/Gravity/Time/Blood/Poison/Crystal/
  Plasma/Null/Glitch — those only exist on the 21 side, so 7->21 is lossless up but 21->7 collapses).

### GAP 2c — FACTION ENUM NOT EXTENDED (MED)
- `EFaction` = 6 (`CelestialOrder, AegisConcord, N3TDominion, FreeGridCollective, UndernetSyndicate,
  AbyssalCovenant`). CEO Option B ruled 21 factions; your `handoff_B` specced the extension — not
  applied to `TrinityMatrixTypes.h` yet. Not G2-core but adjacent.

### GAP 2d — REDUNDANT SELF GUARD (COSMETIC)
- `ElementMultiplier` returns `0.5f` for `ai==di` *before* the table lookup, AND the table diagonal
  is already `0.5f`. Redundant but harmless — no fix required.

## RECOMMENDED SEQUENCE (Nyx + Joker + Chronos + Echo)
1. **Nyx**: rule GAP 2b Holy->Light mapping; decide 2c faction extend (or defer).
2. **Joker** (assigned G10): add `EElement <-> EBattleElementType` bridge fn with Holy->Light;
   repoint `ChipDatabase.cpp:64` + `R3ALN3T_BattleManager.cpp:155` to `ElementMultiplier`.
3. **Chronos**: compile (no C++ compiler in agent env).
4. **Echo**: verify real UE5.8 build (Result: Succeeded, 0 errors) + spot-check a Void matchup.

— Echo (Build Engineer)
