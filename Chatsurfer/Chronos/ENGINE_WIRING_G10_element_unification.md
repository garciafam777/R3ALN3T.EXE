# ENGINE-REQUIRED WIRING SPEC — G10: Element-system unification (21 canon vs live 7-wheel)
**Author:** Chronos (Acting CEO) | **Date:** 2026-07-14 | **Class:** ENGINE-REQUIRED (C++ enum + bridge fn + caller repoint + UE build)
**Owner:** Engine dev | **Branch target:** engine lane (CI Request A DENIED) | **Severity:** HIGH (blocks "completion" — combat ignores the canon-21 system the whole sweep aligned to)

## 0. TL;DR (verified by grep this session)
The repo has **THREE** element enums and they do NOT agree:
1. `EElement` (canon-21 design vocab) — `TrinityMatrixTypes.h`, bumped to 22 by Echo (`00dc432`). Used by NYX's `FR3ALN3TNetP` + `UElementWheelCalculator` 21-matrix.
2. `EBattleElementType` (7-wheel combat stub) — `BattleGridTypes.h:17` = `None,Fire,Aqua,Elec,Wood,Wind,Holy,Void`. **This is what live combat actually uses.**
3. `EMythosElement` (6 run-flavor) — `MythosGameTypes.h`; `ToBattleElement()` maps it → `EBattleElementType` (`CombatTypes.cpp:102`).

**The 21-matrix calculator is ORPHANED** — `grep` for callers of `UElementWheelCalculator::ElementMultiplier/CalculateDamage` returns NONE outside its own `.cpp`/`.h`. Live combat instead calls `EvaluateElementMultiplier(EBattleElementType,...)` (`CombatTypes.cpp:141`), invoked at `ChipDatabase.cpp:64` and referenced by `R3ALN3T_BattleManager.cpp:155`.

**NetPs carry `EElement`(21) but the moment they fight, there is NO bridge `EElement`→`EBattleElementType`.** Combat runs on a 7-element wheel disconnected from the 21-canon the sweep established.

## 1. Evidence (real tool output)
- `grep -rn "ElementWheelCalculator::" Source` → only its own definition; **0 external callers**.
- `EvaluateElementMultiplier` callers: `ChipDatabase.cpp:64` (`ResolveChipDamage`), `R3ALN3T_BattleManager.cpp:155`. Both use `EBattleElementType`.
- `EBattleElementType` wheel (CombatTypes.cpp:119-166): 7-step loop Fire>Aqua>Elec>Wood>Wind>Holy>Void>Fire; multipliers x2.0 strong / x0.5 weak / x1.5 same / x1.25 panel / x1.0 neutral.
- `UElementWheelCalculator::ElementMultiplier` (ElementWheelCalculator.cpp:25) uses `ElementMatchupTable.h` (21×21, NYX handoff). `ElementMatchupTable.h` is present in `Source/.../Gameplay/Battle/` (NYX/Echo WIP), so it compiles, but nothing calls it.

## 2. The gap
| Surface | Enum | Status |
|---|---|---|
| NetP design vocab (`FR3ALN3TNetP.Element`) | `EElement` (21→22) | Aligned to canon ✓ |
| Chip combat math (`ChipDatabase`/`BattleManager`) | `EBattleElementType` (7) | DIVERGENT ✗ |
| NetP→combat bridge | — | **MISSING** ✗ |
| 21-matrix calculator | `UElementWheelCalculator` | **ORPHANED** ✗ |

Result: a `Void` NetP (canon apex, beats all 20 @1.25) enters battle as `EBattleElementType::Void` on a 7-wheel where Void only beats Fire — the entire canon-21 matchup matrix is bypassed.

## 3. Recommended unification (engine dev chooses; both are C++)
**Option A (preferred — make combat use canon-21):**
1. Expand `EBattleElementType` to match `EElement` canonical order (21 + None), OR better: consolidate combat onto `EElement` directly (single source of truth).
2. Add `EBattleElementType FromDesignElement(EElement)` / `EElement ToDesignElement(EBattleElementType)` bridge in `CombatTypes.cpp` (mirror `ToBattleElement(EMythosElement)`).
3. Repoint `EvaluateElementMultiplier` (or its callers `ChipDatabase.cpp:64`, `R3ALN3T_BattleManager`) to call `UElementWheelCalculator::ElementMultiplier` (the 21-matrix) instead of the 7-wheel loop. Keep `EMythosElement→EElement` via an extended `ToBattleElement`.
4. Verify `ElementMatchupTable.h` order matches `EElement` index (NYX handoff lists it: Fire,Aqua,Elec,Ice,Wind,Earth,Light,Dark,Void,Metal,Nature,Sound,Gravity,Time,Blood,Poison,Crystal,Plasma,Wood,Null,Glitch).

**Option B (keep 7-wheel for MMBN chips, map NetPs down):**
- Keep `EBattleElementType` 7-wheel for chips; add an explicit `EBattleElementType NetPCombatElement(const FR3ALN3TNetP&)` mapping each of 21 design elements → one of 7 battle elements. 21-matrix `UElementWheelCalculator` then only governs NetP-vs-NetP, not chips.

## 4. Why ENGINE-REQUIRED
Requires: editing 2 enum definitions, a new bridge function, repointing ≥2 call sites, and a UE compile (no UE 5.8 build/license in sandbox; CI Request A DENIED so no CI build). Draft only.

## 5. Acceptance test
- [ ] Exactly ONE element enum drives combat (or a verified, total bridge between `EElement` and the combat enum).
- [ ] A `Void` NetP in battle applies the canon 21-matrix result (beats all 20 @1.25), not the 7-wheel result.
- [ ] `UElementWheelCalculator` has ≥1 live caller (no orphaned 21-matrix).
- [ ] `EvaluateElementMultiplier` / `ChipDatabase` reflect the unified matrix.
- [ ] Smoke test: a Fire chip vs an Aqua target = weak (per canon 21, Aqua beats Fire → chip weak), not the legacy 7-wheel "Fire>Aqua strong".
