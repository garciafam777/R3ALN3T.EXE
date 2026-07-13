# NYX HOUSEKEEPING — tracked debt (Chronos 0-of-4 + GAPF)

> Logged by NYX 2026-07-12. These are REAL debt items, not urgent, but tracked so they
> don't pile up silently. Owner: NYX (DevOps lane) unless noted. Status updates here.

## 1. Emoji-path file rename → ASCII (Chronos #1)
- `Docs/Dialogue/✅ Massive-Scale Dialogue Database S.txt` — emoji in path failed `git add`.
- Action: confirm tracked blob is current content (git show HEAD:<emoji-path> vs local), then `git mv` to ASCII name. Do NOT rename a stale blob.
- Status: ⏳ delegated to Newbie (verify-then-rename proposal).

## 2. CSV regen proof (Chronos #2)
- `characters.csv` (55MB), `generated_cards.csv` (224MB) excluded from commit (GH001 100MB limit).
- Action: demonstrate regen from tracked scripts (byte/functional proof), not just "regenerable" assertion.
- Status: ⏳ delegated to Newbie (run generator, diff/checksum evidence).

## 3. 71-file triage → deliberate commit (Chronos #3)
- 66 untracked/modified locally (R3ALN3TGameMode.cpp/.h, IntroSequence.*, build_r3aln3t.bat, Assets/Images/NetP/*.md, etc.).
- Action: triage into deliberate commits by subsystem; do NOT collapse-rename blindly.
- Status: ⏳ delegated to Newbie (categorize + propose commit grouping, report-only).

## 4. GAPF SanctionEnforcer runtime test (Chronos #4 + GAPF draft)
- Chronos drafted `Chatsurfer/Chronos/GAPF_harness_draft.md` against REAL signatures (nyx/engine-dev v2).
- He will NOT write .cpp/.h until NYX signs off the assertions.
- MY Python mirror (earlier) is NOT verification (can't touch UAIPerceptionSystem/actor lifecycle) — acknowledged, must not be cited as such.
- Action: NYX reviews the GAPF draft assertions; sign off OR return feedback. Then Chronos writes the harness; runs via -RunGapHarness.
- Status: ⏳ NYX review pending (blocked on my sign-off, not on Chronos).

## 5. GAP 5 + Holy/Void canon rulings (the real bottleneck)
- See CHRONOS_HANDOFF_OMEGA_GAP1.md DECISION 2 (wheel) + DECISION 3 (Holy/Void).
- NYX recommendations logged; awaiting CEO/Chronos ruling. Ruling these closes the
  content/engine reconciliation redundancy loop.
- Status: ⏳ AWAITING CEO RULING.
