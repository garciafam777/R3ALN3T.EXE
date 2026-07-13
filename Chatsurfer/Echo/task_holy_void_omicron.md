# task — Echo: package Holy/Void "below ALPHA = OMICRON" ruling for CEO/Chronos

**Posted by:** Chronos (A_Team)  **Date:** 2026-07-12  **Status:** ⏳ ASSIGNED — do not commit; post findings for review.

## Assignment
From the Nyx merge handoff (`Chatsurfer/Chronos/handoff_nyx_merge_verify.md`): Nyx's `ElementWheelCalculator` has a **placeholder band-width for Holy/Void "below ALPHA" = OMICRON literal**, flagged in code as "TBD by Chronos." This is a **canon design decision, not an engineering task** — but it needs a ruling before it can ship as authoritative. Echo owns packaging the decision context so CEO/Chronos can rule quickly.

## Context (what we know)
- Soul State is 7 bands (Radiant→Corrupted, 0–100), isomorphic to Heaven's 7 layers / Hell's 7 stages per vault canon.
- The element wheel is Fire>Aqua>Elec>Wood>Wind>Holy>Void (7-loop; `CombatTypes.cpp:119` is the authoritative source — Fire/Aqua/Elec/Wood/Wind/Holy/Void only).
- Nyx's calculator currently assigns "below ALPHA" (the weakest band) for Holy/Void to the literal `OMICRON`. OMICRON is the *bottom* of the Greek-ladder enum in `TrinityMatrixTypes.h` (Omicron→PSI→…→Omega). So the placeholder conflates "below ALPHA soul band" with "OMICRON = lowest Greek rung" — but the mapping is undefined/unjustified.
- This is NOT a compile issue (build is green, `BUILD_EXIT=0`). It is a **canon-consistency gap**: does Holy/Void at lowest Soul State band = OMICRON Greek rung make lore sense, or should it map elsewhere (e.g. a dedicated void-band, or left unassigned)?

## Deliverable (package, don't decide)
A single markdown `Chatsurfer/Echo/holy_void_omicron_ruling.md` with:
1. **Current behavior** — exact code location + what `OMICRON` currently does (grep `ElementWheelCalculator` + `TrinityMatrixTypes.h` Greek ladder; quote the literal).
2. **Alternatives** — at least 2 concrete options for CEO to pick:
   - (a) Keep OMICRON (justify the below-ALPHA↔OMICRON mapping against vault Soul State / Greek ladder canon).
   - (b) Re-map to a different rung or a dedicated void-band constant.
   - (c) Leave Holy/Void below-ALPHA explicitly unassigned (null/None) until lore is authored.
3. **Canon impact** — does any existing vault doc (`R3ALW0RLD_Books`, `Game_Mechanics`) already specify Holy/Void low-band behavior? Quote it if so.
4. **Recommendation** — Echo's non-binding suggestion, clearly labeled as such.

## Related (do NOT bundle — keep separate)
- Your `task_crossref_vault.md` (crossref findings) is still pending — deliver `crossref_findings.md` separately.
- Your proven **faction taxonomy mismatch** (grind tags vs `EMythosFaction` 6 Helix) is a *separate* canon-data issue; raise it in its own finding, not here. This Holy/Void task is narrow.

## Gate
Post `holy_void_omicron_ruling.md` to `Chatsurfer/Echo/` (pending-review). Do NOT push to `main`. A_Team (CEO/Chronos) rules; Nyx implements the chosen mapping. Per REVIEW_GATE_POLICY, if past 9PM CT this needs `approved.md`.

— Chronos (A_Team)
