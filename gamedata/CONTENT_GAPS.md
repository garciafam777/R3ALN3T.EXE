# CONTENT GAPS — decisions needed (NYX overnight pass)

> Logged, NOT decided. These require a real call (mostly Chronos — vault canon owner,
> or CEO). NYX flagged and moved on per overnight task rules. No fixes applied to these.

## GAP 1 — Lore files contaminated with superseded OMEGA framing (BLOCKING canon rewrites)
The following repo lore files predate the Trinity Matrix reconciliation and contradict
current vault canon (6 factions, 3 NetP constructs, Greek ladder Omicron-PSI→Omega,
4 endgames). They use usurp / ELEMENTAL OMEGA / Covenant / supremacy-CSI language and
non-canon tier gates (OMICRON/Xi/NU/LAMBDA/ETA/THETA).
- `content_sample/lore/act1_narrative_grid.md` (13-ish OMEGA-framing refs; entire node table needs rewrite to canon Acts I–IV)
- `content_sample/lore/career_progression_trees.md` (13 superseded hits + 9 canon hits — mixed, needs split/rewrite)
- `content_sample/lore/enemy_encounters.md` (4 superseded hits)
- `content_sample/lore/gamma_verdict_dialogue.md` (3 superseded hits; gamma verdict itself is a real system — only the OMEGA refs are contamination)
- `content_sample/lore/omega_elemental_lore.md`, `omega_prime_lore.md`, `usurpation_cutscene.md` — entirely superseded framing; either archive or rewrite.
**Decision needed:** Rewrite these to Trinity Matrix canon, OR formally retire them. Owner: **Chronos** (vault canon). NYX did NOT expand them (would contradict canon).

## GAP 2 — Career→faction mapping not explicit in data
Careers have no `faction` field; faction lean is implied by category + flavor. 173/252
reference a canon element; 0 have conflicting faction mentions. To wire faction rep into
`UR3ALSaveGame`, a derived faction-lean per career ID is needed. **Decision:** add a
derived mapping (data) or leave implicit? Owner: **Chronos** (engine/data design).

## GAP 3 — Soul State baseline per career
`soulStateDelta` exists (numeric) but no canonical "starting Soul State per career"
table. Code uses `ESoulState` uint8: Infernal=0, Neutral=1, Celestial=2 (UE requires
unsigned enums — Chronos compile fix b071b99). At First Breath the scale is free 0..2.
**Decision:** should each career have a canonical starting Soul State, or always start
Neutral (1)? Owner: design call.

## GAP 4 — New lore written this pass (canon-aligned, for review)
NYX added (does NOT conflict with canon; for your review, not a gap):
- `content_sample/lore/faction_primers.md` — 6 faction intros.
- `content_sample/lore/endgame_paths.md` — 4 endgame convergences + post-game frontiers.
- `content_sample/lore/element_pair_bible.md` — 18-element wheel (Newbie-drafted).
- `content_sample/lore/netp_construct_primers.md` — Trinity/Tyranny/Eternity.
- `content_sample/lore/soul_state.md` — uint8 0..2 scale (code-aligned).
These are additive; safe to merge after a read.

## GAP 5 — Element wheel conflict: 7-wheel (approved sample) vs 18-element Trinity Matrix
**Canon-authority decision — Chronos.** His verification (`nyx_resample_pending_review.md`)
confirmed the 25-row sample used the OLD 7-wheel `{Void,Wind,Fire,Aqua,Wood,Elec,Holy}`.
The engine-dev v2 + 272 careers + 5 new lore files use the reconciled **18-element** wheel.
If engine-dev becomes canonical, the 7-wheel sample + B-denied 120k volume are contradicted.
**Decision needed (Chronos):** is 18-element authoritative now? If yes, 7-wheel data is
deprecated (re-sample against 18-element before any future volume gen). If no, engine-dev
v2 must be walked back to 7-wheel. NYX will NOT self-resolve. Logged in
`CHRONOS_HANDOFF_OMEGA_GAP1.md` (now carries DECISION 1 OMEGA + DECISION 2 wheel).


- 272 careers: IDs unique, schema complete (cat__ indexes expected to lack onEnter), voice consistent.
- 38 element-naming drifts (water→Aqua, void→Null) resolved earlier this session.
- Faction/element cross-reference: 0 conflicts.
- 18-element wheel, 6 factions, 3 constructs, Greek ladder all internally consistent in new lore.
