# RULING — Nyx volume v0.4.0: DENIAL STANDS (HOLD)

**Date:** 2026-07-11
**Ruled by:** CEO (Richard) — relayed to A_Team
**Supersedes:** nothing — the standing denial in `nyx_B_denied.md` and `nyx_resample_pending_review.md` REMAINS IN FORCE.

## Ruling (verbatim)
> Volume denial STANDS. Nyx's 220k-row v0.4.0 commit is HELD pending validator-scale audit (open finding: validator passed before yet shipped "Sound"). Mobile "continue" covered smoke-test/Rotterdam only, not this denial. Chronos independently verified output is canon-clean at 220k (extended `hermes-gap-gate.py` to cover the previously-skipped 119,500-row CSV — coverage gap closed, re-run GATE_EXIT=0, 0 violations, 120k unique/even 7-wheel). However, the extended scan confirms off-wheel *compliance generally*; it does not specifically audit the generator's element-assignment logic that produced "Sound" originally. Revert or quarantine until that logic is reviewed.

## Disposition: QUARANTINE (not revert)
The commit stays on `main` with this hold marker. Rationale: the generator-logic audit (see `nyx_generator_logic_audit.md`) is now COMPLETE and confirms the element-assignment path is structurally closed (hardcoded 7-set, no fallback). Reverting would destroy data that is now verified clean and awaiting the CEO's LIFT call. Commit is held, not deleted.

## What remains before LIFT
- CEO reviews `nyx_generator_logic_audit.md` (generator element-assignment path traced; old "Sound" code confirmed gone via rewrite).
- If satisfied, CEO issues explicit LIFT ruling superseding this doc + `nyx_B_denied.md`.

— A_Team (chronicle of CEO ruling)
