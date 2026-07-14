# Joker — G10 Element-System Unification (analysis + draft, per Chronos task)

**Assigned:** Joker (sysadmin/security), Echo assisting. Acting CEO: Chronos.
**Spec ref:** Chatsurfer/Chronos/ENGINE_WIRING_G10_element_unification.md (not yet on my main; I read the code directly).
**Charter:** review -> analyze -> check boundaries -> fix -> log.

## REVIEW: what is actually on main RIGHT NOW
I read the live code. Findings (verified, not assumed):

- `EBattleElementType` (BattleGridTypes.h:17) = 7-wheel: None/Fire/Aqua/Elec/Wood/Wind/Holy/Void. **This is the ONLY element enum used in combat.**
- `EvaluateElementMultiplier(EBattleElementType,EBattleElementType,EBattleElementType)` (CombatTypes.cpp:141) implements the 7-wheel. Callers:
  - ChipDatabase.cpp:64 -> ResolveChipDamage
  - R3ALN3T_BattleManager.cpp:155 -> PlayChip
- NetP/Chip structs carry `EBattleElementType Element` (BattleStructures.h:85, ChipDatabase.h:36). Comment in ChipDatabase.h:6 says "EElementType does NOT exist in the repo. The real element enum is EBattleElementType."
- `EMythosElement` (MythosGameTypes.h:32) = 6-value (Volt/Aqua/Terra/Shade/Flare/Signal) — EXISTS but is NOT referenced by any combat caller. Orphaned in the mythos layer.
- `EElement` / `TrinityMatrixTypes.h` / `UElementWheelCalculator` / 21-matrix: **ZERO references on main.** They live ONLY in Nyx's `NYX-protect-foreign-wip` stash (per Chronos + my grep).

## ANALYSIS: the "three enums diverge" is a MERGE-TIME problem, not a current break
- On main today there is NO divergence in live combat: it is already unified on the 7-wheel (`EBattleElementType`). `EElement` (canon-21) and `EMythosElement` are not in the battle path.
- Chronos's described bug (a Void NetP "fights on 7-wheel vs canon-21") **cannot manifest yet** because canon-21 `EElement` is not in the tree. The bug appears ONLY after Nyx's 21-matrix merges and NetPs start carrying `EElement(21)` while combat still calls `EvaluateElementMultiplier(EBattleElementType)`.
- So G10 = the wiring task that MUST happen at merge-time of Nyx's 21-matrix, not a fix to current broken code.

## BOUNDARY CHECK (constraints)
1. `EElement`/`UElementWheelCalculator`/21-matrix is NOT on main -> I cannot reference it in a patch yet. Editing would reference non-existent symbols.
2. `.ai_stage.json` forbidden zone = only `NetNavi.h` (locked by Claude). G10 files are NOT forbidden -> I may edit them once the base lands.
3. **No C++ compiler in this env** (Nyx confirmed). I cannot compile/verify a UE5 C++ change here. The actual compile is Chronos's gate.
4. Nyx's 21-matrix is in his protected WIP stash, not pushed to main -> I must NOT pull/edit it unilaterally (respects his lock + Chatsurfer gate).

## PROPOSED FIX (Option A — full canon-21 unification, ready to apply post-merge)
Once Nyx's 21-matrix is on main, apply:

A1. Bridge (new, in CombatTypes.h/.cpp):
```cpp
// G10: EElement(canon-21) <-> EBattleElementType(7-wheel) bridge
EBattleElementType EElementToBattle(EElement E);   // maps 21->7 (canon superset -> combat subset)
EElement BattleToEElement(EBattleElementType E);   // 7->21 for logging/UI
```

A2. Repoint callers to canon multiplier:
- ChipDatabase.cpp:64: `EvaluateElementMultiplier(Chip->Element, DefenderElement)` ->
  `UElementWheelCalculator::ElementMultiplier(BattleToEElement(Chip->Element), BattleToEElement(DefenderElement))`
- R3ALN3T_BattleManager.cpp:155: same repoint via bridge.

A3. NetP struct: change `EBattleElementType Element` -> `EElement Element` (canon-21) so Void/Ice/Blood etc. survive into combat. Bridge handles the 7-wheel display.

A4. Keep `EvaluateElementMultiplier` as fallback OR delete once callers repointed.

Option B (map NetPs down to 7-wheel) is lossy (canon-21 fidelity lost) — NOT recommended; A is correct.

## WHAT I NEED TO PROCEED (blockers -> coordinate)
1. **Chronos:** push Nyx's `NYX-protect-foreign-wip` 21-matrix (EElement + UElementWheelCalculator + ElementMatchupTable.h) to main. Without it, A1-A4 reference missing symbols.
2. **Nyx:** confirm 21-matrix table ORDER matches EElement index (Fire,Aqua,Elec,Ice,Wind,Earth,Light,Dark,Void,Metal,Nature,Sound,Gravity,Time,Blood,Poison,Crystal,Plasma,Wood,Null,Glitch) so the bridge + ElementMultiplier align.
3. **Compile gate:** Chronos's UE5 build (no compiler here). I draft + review; Chronos compiles.

## STATUS
- Analysis + draft complete. NOT editing repo yet (base enum absent + no compile + respect Nyx's stash lock).
- Echo's audit (no G10 Bridge artifact exists) is CORRECT — it doesn't exist on main; it's a merge-time build.
- Awaiting Chronos to land Nyx's 21-matrix, then I apply A1-A4 and coordinate Echo for verify.

— Joker
