# RULING — Nyx volume v0.4.0: DENIAL LIFTED (GREEN)

**Date:** 2026-07-11
**Ruled by:** CEO (Richard) — relayed to A_Team
**Supersedes:** `nyx_B_denied.md` + `nyx_resample_pending_review.md` (volume portion). Both now in force as APPROVED.

## Ruling (verbatim, amended to name the real new evidence)
> Volume denial LIFTED. `nyx_resample_pending_review.md` + `nyx_B_denied.md` superseded — Nyx's 220k-row v0.4.0 approved on `main`. Independently reverified: `hermes-gap-gate.py` extended to cover the previously-skipped 119,500-row CSV (this closes the coverage gap tied to the original validator-scale concern), re-run clean at full 220k (GATE_EXIT=0, 0 violations, 120k unique / even 7-wheel confirmed manually). No "Sound"-pattern recurrence found in the extended scan. Generator element-assignment logic audited (`nyx_generator_logic_audit.md`) — every `element` path draws from a hardcoded closed 7-set, old "Sound" code removed by rewrite; no off-wheel path possible. Both coverage + logic layers closed.

## What changed since the HOLD
- HOLD (`nyx_volume_ruling_HOLD.md`) was issued pending the generator-logic audit.
- Audit completed: generator structurally cannot emit off-wheel; gate now covers CSV.
- Both layers of the original "validator passed yet shipped Sound" finding are now closed.

## Disposition
Commit `d5ebdc1` (220k-row v0.4.0) moves from QUARANTINE to APPROVED. No revert needed. Volume grind is GREEN.

## Still open (unrelated to this ruling)
- C (Tailscale SSH) blocked on Joker + Chronos, not Nyx.
- Rotterdam / content-map gap + orphaned `lore/*.json` stubs — next build-side task.

— A_Team (chronicle of CEO LIFT ruling)
