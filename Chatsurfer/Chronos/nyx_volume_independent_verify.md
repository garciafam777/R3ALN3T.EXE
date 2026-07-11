# Nyx volume v0.4.0 — INDEPENDENT verification (Chronos, not trusting commit message)

**Date:** 2026-07-11
**Trigger:** `main` @ `d5ebdc1` committed "PRODUCTION volume v0.4.0: 220k rows, GATE_EXIT=0".
**Why re-checked:** volume was DENIED in `nyx_B_denied.md` / `nyx_resample_pending_review.md` (sample-only approved; volume pending validator review at scale). A mobile "continue" is not the same as lifting a named denial. Richard asked for independent verification, not trust of the commit's self-reported GATE_EXIT=0.

## What I verified myself (against real committed data on main)
1. **`hermes-gap-gate.py content_sample/volume/`** → **GATE_EXIT=0**, 0 violations, 28 files. (This is the commit's claimed check.)
2. **CSV gap (gate does NOT scan .csv):** `netps/netp_master.csv` = 120,001 lines (120k rows + header), 34 MB.
   - Off-wheel grep (case-insensitive, full file): **0 hits**.
   - Unique `card_number`: **120,000** (zero duplicates — no seed-row replication; the `DEL-000000` seen earlier was just each shard's first row).
   - Element distribution: Aqua 17255 / Wind 17220 / Wood 17214 / Void 17203 / Holy 17174 / Elec 17087 / Fire 16847 — **even, all 7-wheel, no starvation**.
3. **Chip master:** 48,000 rows, 48,000 unique, even element spread, 0 off-wheel in element field.
4. **Enemy master:** 36,000 unique. **Career master:** 16,000 unique. Both element-clean.
5. **"ice" grep hits in career (2005):** FALSE POSITIVE — substring in names/flavor (Just-ice, serv-ice, pol-icy...), NOT element values. Gate correctly ignored.

## (a) Did the gate actually pass on the real data?
**YES — independently confirmed.**
- The JSON the gate checks: clean, exit 0.
- The CSV the gate SKIPS (119,500 rows): I verified manually — also clean + distinct at 220k scale.
- No evidence of the prior failure mode ("passes small, breaks at volume"): rows are unique, distribution even, zero off-wheel.

## (b) Formal ruling — DOES RICHARD LIFT THE VOLUME DENIAL?
**NOT answered here. This is Richard's written call, not mine.** Two things stand:
- The *output* is canon-clean at volume (verified above).
- The *original open finding* is NOT yet closed by evidence: `nyx_resample_pending_review.md` required the **validator itself reviewed at scale** before volume. The commit asserts GATE_EXIT=0 but contains **no record of the validator being audited** — only that output passed. A pass from a validator with a known open blind spot is the thing under investigation, not proof it's fixed.
- Therefore: a mobile "continue" + this clean verification ≠ automatic lifting of `nyx_B_denied.md`. Richard must state in writing (superseding the pending_review doc) whether volume is now GREEN or still held pending validator-scale audit.

## Residual gap to fix (machine-checkable, not human-grep)
`hermes-gap-gate.py` only scans `.json`. The 119,500-row `netp_master.csv` was NOT covered by the committed gate — I checked it by hand. **Action:** extend the gate to scan CSV (element column + distinctness + row-count) so volume is enforceable in CI, not dependent on a human grep. Until then, GATE_EXIT=0 on a volume commit does NOT cover the CSV.

## Status
- Data: ✅ canon-clean at 220k scale (verified independently).
- Gate coverage: ⚠️ CSV not machine-checked (manual only this time).
- Volume denial: ⏸️ STILL STANDS per `nyx_B_denied.md` until Richard's explicit written lift.

— Chronos (A_Team)
