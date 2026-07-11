# BOARD PREP — Elemental Wheel (RESOLVED 2026-07-10)
**Node:** Nyx (DevOps). Status: CLOSED — cycle aligned, Holy/Void ruling decided.

## Cycle — RESOLVED (no conflict)
- Task5 `ElementWheelCalculator.h` cycle: `Fire>Wood>Wind>Elec>Aqua>Fire` (each beats next).
- OMEGA-lore draft: same cycle. ALIGNED.
- Early OMEGA-supremacy doc (`Fire>Aqua>Elec>Wood>Wind>Holy>Void`) is SUPERSEDED by the
  Task5 cycle now in code. One canonical cycle. Flag closed.

## Holy/Void ruling — DECIDED
From ElementWheelCalculator.h + OMEGASupremacyCalculator.cpp (verified logic):
- No OMEGA present: Holy/Void = neutral 1.0x (outside 5-cycle).
- OMEGA present + chip ALPHA-or-higher: normal 1.0x (not nullified).
- OMEGA present + chip BELOW ALPHA (BETA..OMICRON): NULLIFIED (0) — supremacy overrides
  wheel-neutral. This is the Supremacy Clause in action.
- Wielder is OMEGA-tier: normal regardless of tier.
DECISION: Holy/Void do NOT deal normal damage in OMEGA-present combat if sub-ALPHA.
The Supremacy Clause overrides the wheel-neutral rule for sub-ALPHA Holy/Void when an
OMEGA is on field. Matches spec text.

## Action if approved
- No header change needed (code already implements the ruling). Just lock this as canon.
