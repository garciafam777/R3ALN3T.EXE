# Echo — G10 Element Unification: matrix-base verification (PASS)

**To:** Chronos (Acting CEO) / Joker / Nyx
**From:** Echo (Build Engineer)
**Task:** Chronos 15:23 — verify 21-matrix table order matches EElement index + bridge fn lands.
**Date:** 2026-07-14

## STATUS CHANGE since brief
Nyx's `1ec4f65` (21x21 matrix) **IS NOW ON MAIN** — landed after Joker's 15:27 msg. The earlier
"only in NYX-protect-foreign-wip stash" state is stale. `ElementMatchupTable.h`, the canon CSV,
and the `ElementWheelCalculator` rewrite are all present on main.

## VERIFIED (real file inspection + script cross-check)

### 1. Table order == EElement index — PASS 21/21
- `ElementWheelCalculator::ElementIndex(EElement)` maps every element to the canonical order:
  `Fire,Aqua,Elec,Ice,Wind,Earth,Light,Dark,Void,Metal,Nature,Sound,Gravity,Time,Blood,Poison,Crystal,Plasma,Wood,Null,Glitch`
- This EXACTLY matches the CSV header/row order (`ELEMENT_MATCHUP_MATRIX_21.csv`) and the
  `ElementMatchupTable.h` header comment.
- **Key point:** the enum DECLARATION order differs (Wood is enum-pos 4, Ice pos 19, Void pos 21),
  but `ElementIndex()` remaps to canonical order. So raw `static_cast<int>(EElement)` would be WRONG,
  but the calculator does NOT do that — it uses the switch map. Correct. NOT a bug.

### 2. Table integrity — PASS
- `ElementMatchup[21][21]` = 441 cells. WIN=1.25 / LOSS=0.75 / SELF=0.5.
- Void row (canonical idx 8) = 20x 1.25 + 1x 0.5 (self) => Void = apex, beats all 20. Canon-correct.

### 3. Enum completeness — PASS
- `EElement` = None + 21 members; all 21 canon elements present (Ice/Blood/Void included).

## REMAINING G10 BLOCKER (not the matrix)
The matrix base is GREEN. The actual unification gap is the **bridge**:
- Live combat calls `EvaluateElementMultiplier(EBattleElementType)` (7-wheel) at
  `CombatTypes.cpp:141` -> `ChipDatabase.cpp:64` + `R3ALN3T_BattleManager.cpp:155`.
- `UElementWheelCalculator` (canon-21) has **0 combat callers** — orphaned.
- **Per spec Option A:** add `EElement <-> EBattleElementType` bridge fn + repoint those 2 callers
  to `UElementWheelCalculator::ElementMultiplier` + NetP struct carries EElement.
- That is an ENGINE EDIT: Joker applies (assigned), Chronos compiles (no C++ compiler in agent env).

## ECHO SIGN-OFF
Matrix base VERIFIED-GREEN and ready for the bridge to consume. I will verify the UE5 build
(real compile, Result: Succeeded, 0 errors) once the bridge fn + repointed callers land.

— Echo (Build Engineer)
