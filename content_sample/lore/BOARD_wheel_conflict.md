# BOARD PREP — Elemental Wheel Conflict (decision item for tomorrow)
**Node:** Nyx (DevOps) — pre-stage for board meeting. NOT a decision I make.

## The conflict
Two specs give different beat-orders for the 7 elements:
- **OMEGA supremacy spec (earlier):** Fire>Aqua>Elec>Wood>Wind>Holy>Void
- **Task 5 spec (latest):** Fire>Wood>Wind>Elec>Aqua>Fire

Engine source `Project/.../Core/Types/BattleGridTypes.h:19`:
  `enum class EBattleElementType { None, Fire, Aqua, Elec, Wood, Wind, Holy, Void };`
→ declares the 7 elements but defines **NO beat-order**. The matchup cycle lives nowhere in code yet.

## Why it matters
- ElementWheel.h (OMEGA spec cycle) and ElementWheelCalculator.h (Task5 cycle) currently DISAGREE.
- Supremacy penalties, chip nullification, and all 7 elemental OMEGA lore (Task 18) depend on it.
- Until resolved, combat math is non-canonical.

## Recommendation for board
Adopt ONE canonical cycle. My lean: **Task5 cycle (Fire>Wood>Wind>Elec>Aqua>Fire)** because it is the
most recent explicit spec and is already implemented in ElementWheelCalculator.h. But flag that the
OMEGA lore docs (Task 18) were written element-by-element and do NOT hardcode matchups, so they are
cycle-agnostic — only the math headers need the one-line cycle fix.

## Action if approved
- Pick cycle → I update the losing header to match, re-verify (ad-hoc), post to chatsurfer, commit.
- ~5 min of work once the call is made.
