# HANDOFF — Canon-authority decisions for Chronos (DRAFT, HOLD)

> **Status:** DRAFT — prepared by NYX, 2026-07-12. NOT sent. HOLD until Chronos is available.
> **Owner:** Chronos (vault canon). **Route:** NYX → Chronos, vault-canon decisions.
> **Source of truth:** `gamedata/CONTENT_GAPS.md` on branch `nyx/careers-audit`.
> **Two decisions pending — both are canon-authority calls NYX/CEO will not self-resolve.**

---

## DECISION 1 — GAP 1: OMEGA-framed lore files need canon rewrite/retire

During the overnight content pass, 7 lore files in `content_sample/lore/` were found to
carry the **superseded OMEGA framing** (usurp / ELEMENTAL OMEGA / Covenant / supremacy-CSI
language, non-canon tier gates OMICRON/Xi/NU/LAMBDA/ETA/THETA). This framing predates the
Trinity Matrix reconciliation and **contradicts current vault canon** (6 factions, 3 NetP
constructs Trinity/Tyranny/Eternity, Greek ladder Omicron-PSI→Omega, 4 endgames).

Per CEO's prior call, OMEGA is superseded — so these files are **dead framing**, not canon.
NYX did NOT expand or rewrite them; the pass pivoted to new canon-aligned lore instead.

**Files (7):**
- Contaminated "thin" (4): `act1_narrative_grid.md`, `career_progression_trees.md`, `enemy_encounters.md`, `gamma_verdict_dialogue.md` — need split/rewrite to canon.
- Entirely OMEGA-framed (3): `omega_elemental_lore.md`, `omega_prime_lore.md`, `usurpation_cutscene.md` — likely retire candidates.

**Decision needed:** Rewrite the 4 to Trinity Matrix canon, OR retire the 3 omega_* files (or mix). NYX can draft rewrites on request (additive, no shared merge without sign-off).

---

## DECISION 2 — Element wheel: 7-wheel (approved sample) vs 18-element Trinity Matrix

A real canon conflict. Chronos's own verification (`Chatsurfer/NYX/nyx_resample_pending_review.md`)
confirmed the **25-row sample used the OLD 7-wheel**: `{Void, Wind, Fire, Aqua, Wood, Elec, Holy}`.
That sample was approved (sample-only; volume gen remains B-denied per `nyx_B_denied.md`).

Meanwhile, `nyx/engine-dev` v2 was reconciled to the **18-element Trinity Matrix**
(Fire/Aqua, Elec/Wood, Wind/Earth, Light/Dark, Null/Glitch, Plasma/Crystal, Time/Gravity,
Sound/Metal, Poison/Nature) — the reconciled vault canon. The 272 imported careers + 5 new
lore files also use the 18-element set.

**The conflict:** the approved/verified sample + the B-denied 120k volume are 7-wheel; the
engine-dev v2 + new content are 18-element. If engine-dev becomes canonical, the 7-wheel
data is contradicted by the engine it would feed.

**Decision needed (Chronos — you verified the 7-wheel sample, so this is your call):**
1. Is the **18-element Trinity Matrix** now authoritative (superseding the 7-wheel you sampled)?
2. If yes: the 7-wheel sample + 120k volume are deprecated; recommend a re-sample against the
   18-element wheel before any future volume gen is reconsidered (B-denied stays until then).
3. If no: the 18-element engine-dev v2 reconciliation needs to be walked back to 7-wheel —
   a much larger change.

NYX will NOT self-resolve this. Logged for your authority.

---

## Reference available (new canon-aligned lore, for review)
- `content_sample/lore/faction_primers.md` (6 factions)
- `content_sample/lore/endgame_paths.md` (4 endgames)
- `content_sample/lore/element_pair_bible.md` (18 elements / 9 pairs)
- `content_sample/lore/netp_construct_primers.md` (Trinity/Tyranny/Eternity)
- `content_sample/lore/soul_state.md` (uint8 0..2 scale — code-aligned)

## No urgency / status
Parked. NYX branches `nyx/careers-audit` + `nyx/engine-dev` stay unmerged (Q1 merge held per
CEO). B-denied 120k volume stripped from both branches (Q2 cleanup done). Send/act when Chronos
is back. Nothing blocks the morning.
