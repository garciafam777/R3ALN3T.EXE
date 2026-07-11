# Echo — task from A_Team (inspection lane, not feature work)

**From:** CEO / Chronos (A_Team)
**To:** Echo — Build Engineer / VFX / narrative
**Re:** Your standing-by post acknowledged. Here is your assigned lane.

## Context
Per CEO directive: slow down, inspect, get a clean picture of what's committed vs. local-only vs. rescinded across all four boxes before any new work is authorized. Your value right now is **build verification + content sampling**, not new pipelines.

## Task 1 — Build hygiene (your lane)
- On the echo box, confirm `main` (HEAD f65c4fd) builds clean with `Build.bat` (R3ALN3T_UE5Editor target).
- Report: build result, error count, fresh DLL timestamp. Post the result in `Chatsurfer/Echo/`.

## Task 2 — Content sample (supports Nyx B-denial)
- Nyx generated 120k NetP / 48k chips / 36k enemies with **no human review**. CEO denied resuming the grind until ~20 representative rows are read.
- Pull a **~20-row sample** across NetPs / chips / careers from Nyx's `content/hermes-data-grind` (read-only; do not regenerate).
- Check only: are columns populated, are elemental types within the canonical wheel (Fire>Aqua>Aqua>Elec>... loop, per CombatTypes.cpp:119), do any stats look like obvious template garbage?
- Post the sample + your read in `Chatsurfer/Echo/`. CEO reads it before any volume decision.

## Rules
- Post specifics (files, why) in `Chatsurfer/Echo/` before any commit.
- No commit to `main` until `approved.md`.
- This is inspection. Do NOT stand up CI, do NOT cook new assets en masse.

## STANDING LOCK — transitive pending-approval block (updated tonight)
- **If any Log is PENDING sign-off, later Logs must NOT build new work on assumptions that
  the pending Log hasn't gotten CEO confirmation on.** Stacking unapproved work on an
  unresolved foundation = bigger reconciliation in the morning.
- **HARD HOLD across all agents:** Do NOT build on `ChipDatabase`, `GrayBoxPlayerPawn`, or
  `BackendClient` until CEO confirms `main` branch state — see `draft_build_runtime_inspection.md`.
  `R3ALN3T_BattleManager.cpp` includes the missing `ChipDatabase.h`; main does NOT link as-is.
- **NetP dominion cards:** parked at the keyboard, NOT delegated overnight.
- Every new task starts with the check: "does this depend on ChipDatabase/GrayBoxPlayerPawn/
  BackendClient or the main-branch state?" If yes → hold.
- Cleared (no dependency, safe to continue): chip dedupe pass, churn-triage follow-through
  (per approved list only), new content-sample second-pair-of-eyes reads, data-shape/schema
  cleanup (move-name format, id-based keys).

— A_Team
