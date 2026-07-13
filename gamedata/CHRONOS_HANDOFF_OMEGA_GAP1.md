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
- `content_sample/lore/endgame_paths.md` (4 endgame convergences + post-game frontiers)
- `content_sample/lore/element_pair_bible.md` (18 elements / 9 pairs)
- `content_sample/lore/netp_construct_primers.md` (Trinity/Tyranny/Eternity)
- `content_sample/lore/soul_state.md` (uint8 0..2 scale — code-aligned)

## DECISION 3 — Holy/Void "below ALPHA = OMICRON" band-width (canon decision)
`ElementWheelCalculator` (in main, v2) has a literal `OMICRON` placeholder for Holy/Void
"below ALPHA" Soul State band, flagged "TBD by Chronos." Per Echo's task brief, this
conflates "below-ALPHA Soul State band" (0–100 scale, isomorphic to Heaven's 7 layers /
Hell's 7 stages) with "OMICRON = bottom Greek-ladder rung" (Omicron→PSI→…→Omega). The
mapping is undefined/unjustified. Engine builds green (not a compile issue) — purely canon.

**NYX recommendation (non-binding, for CEO/Chronos ruling):** do NOT keep the OMICRON
conflace. Either (a) remap Holy/Void below-ALPHA to a dedicated void-band constant, or
(b) leave explicitly unassigned (null) until lore authors it. Echo is packaging the
options in `Chatsurfer/Echo/holy_void_omicron_ruling.md` (ASSIGNED, not yet posted).

## DECISION 4 — Generator emits 15 factions (4 cruft extras); Echo hardening (NYX answer)
Echo's faction-mapping hardening (`Chatsurfer/Echo/draft_faction_hardening.md` +
`draft_faction_closure_notes.md`, main `2b5c251`/`bfefadf`): generators emit **15 distinct
faction names**, not the expected 11 (nor vault's 6). 4 EXTRAS: `IRON CORTEX, HALO CORE,
PANDEMONIUM NET, BRIMSTONE CELL` (from `generate_netp_v3_complete.py` ALIGNMENTS dict).
He built `FACTION_MAPPING_15_to_6.md`; 20 careers don't reference the extras.

**NYX answer to Echo's "ask-Nyx on 4 extras": they are CRUFT, not reserved.** They are
generator flavor-pool leftovers from the 7-wheel/OMEGA era — never wired to `EMythosFaction`
(shipped code hardcodes the enum, no string lookup), and absent from vault canon (6 Helix
factions). Recommend **pruning them from the generator's ALIGNMENTS dict** so the emitted
set collapses to the canonical 6. Echo will not prune without this answer — recorded here.

**Convergence:** this is the SAME root call as GAP 5 + Holy/Void. Three signals now point
one way: (1) wheel 7 vs 18, (2) Holy/Void OMICRON stub, (3) generator emits 15 factions /
4 cruft. All resolved by adopting the reconciled Trinity Matrix canon (6 factions, 18
elements) as the single source and retiring the 7-wheel/OMEGA-era generator vocabulary.
The `FACTION_MAPPING_15_to_6.md` doc is a band-aid; the real fix is generator-pool retirement.

**NYX recommendation:** when CEO rules GAP 5 (18-element canonical), also (a) prune the 4
extras + align generator faction pool to the 6 Helix, (b) delete the OMICRON stub, (c)
normalize the 3 spellings of "Celestial Order" to the enum DisplayName. One coordinated
pass closes all three.

## No urgency / status
Parked. NYX branches retired; unique content on `nyx/content-salvage` (off main).
B-denied volume was lifted per Chronos trip-wire correction. Housekeeping debt tracked in
`gamedata/NYX_HOUSEKEEPING.md` (corrected: #1 done, #3 overstated, #4 = NYX GAPF sign-off).
Echo's faction finding logged as DECISION 4. Send/act when Chronos/CEO is back.

---

## RESOLVED 2026-07-13 — CEO Override_b supersedes the parked state above
Override_b (CEO final sign) resolved DECISION 2/3/4:
- **DECISION 2 (wheel):** 18-element Trinity Matrix is AUTHORITATIVE; 7-wheel deprecated.
  (Chronos's earlier 7-wheel sample is now superseded — re-sample against 18-element before any volume gen.)
- **DECISION 3 (Holy/Void OMICRON):** Holy/Void NOT in canonical 18. The OMICRON stub only
  existed in `content_sample/headers_proposal/omega/` (REVIEW-ONLY proposal, never compiled into the
  shipped engine). Shipped `ElementWheelCalculator.cpp/.h` has zero OMICRON/Holy/Void refs — already clean.
  No live code to delete; proposal files are reference-only (left as-is, non-blocking).
- **DECISION 4 (4 cruft factions):** IRON CORTEX/HALO CORE/PANDEMONIUM NET/BRIMSTONE CELL = cruft,
  prune from generator ALIGNMENTS. Executed by NYX on nyx/engine-dev per Override_b Ruling #1.
- **GAPF (Chronos #4):** CLOSED. GapFTest() written + run; 9/9 [GAPF-...] MATCH/PASS real-engine markers.
  See gamedata/NYX_HOUSEKEEPING.md #4.

**Carry-forward (still open, NOT resolved by Override_b):**
- CI (Request A) REMAINS DENIED (nyx_A_denied.md) — awaits CEO's own written lift after four-agent status picture.
- Chronos box: 65 untracked files (recurring 71-file mess) still untriaged — part of the status-pull blocker.
- GAP 1 (7 OMEGA-contaminated lore files) needs canon rewrite/retire — vault-canon owner (Chronos) action.


