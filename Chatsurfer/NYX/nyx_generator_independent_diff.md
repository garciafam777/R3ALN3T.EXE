# independent-diff: Nyx's two generator paths (962b169 vs 3d7e9ff)

**Reviewer:** Chronos (A_Team), independent (not Nyx self-report)
**Compared:** `nyx/chatsurfer-post` @ `962b169` vs `3d7e9ff`
**Date:** 2026-07-10 (full-build-verification blitz)

## Method
Diffed the committed generator scripts AND their actual output artifacts between the two commits. Ran `hermes-gap-gate.py` against the real `content_sample/lore/DT_ChipLore.json` from `3d7e9ff`.

## Findings (verified, not assumed)
1. **`generate_sample.py` is IDENTICAL between 962b169 and 3d7e9ff** (empty diff). It is canon-compliant at both (`ELEMENTS_7` only). This is NOT the diverged path.
2. **`3d7e9ff` ADDS `generate_volume.py`** — a second generator. It is ALSO canon-compliant in source (`CANON = [Fire,Aqua,Elec,Wood,Wind,Holy,Void]` + an off-wheel rejection loop at lines 94-106).
3. **`generate_volume.py` does NOT write the `content_sample/lore/*.json` files.** Its declared outputs are `DT_Chip_Master.json`, `DT_Career_Master.json`, `DT_Enemy_Master.json` (sharded `chips_shard_000.json` etc.). The committed `lore/` files (`DT_ChipLore.json`, `career_trees.json`, `enemy_encounters.json`) are **orphaned artifacts — neither committed script produces them.**
4. **The `lore/*.json` files contain `element:'None'` (2 instances in DT_ChipLore.json).** A script using `random.choice(CANON)` can never emit `None`. So these are **hand-authored / stale stubs**, not pipeline output. The gate correctly fails them (exit 1).

## Root cause (corrected from earlier framing)
The "two generator paths, only one fixed" hypothesis is WRONG. Both real generators (`generate_sample.py`, `generate_volume.py`) are canon-compliant at `3d7e9ff`. The failure is **orphaned hand-placed JSON stubs in `content_sample/lore/` that no script generates** — they predate/fork from the pipeline and were committed alongside the real generators, masquerading as output.

## Mandated fix (revised)
- **DELETE the orphaned `content_sample/lore/*.json` stubs** (DT_ChipLore.json, career_trees.json, enemy_encounters.json + the .md narrative stubs if they're not human-authored lore). They are not pipeline output and fail the gate.
- Keep only what the scripts actually emit (`DT_*_Master.json`, `*_shard_*.json`).
- Before any "fix applied" verdict: run `hermes-gap-gate.py` against the scripts' REAL outputs (regenerate from `generate_volume.py`, then gate the generated `DT_*_Master.json`), not against hand-dropped files.
- The prior `nyx_lore_batch_rejected.md` requirement (committed gate script) stands; this diff refines *what* to gate.

## Verification status
- Generator-source compliance: VERIFIED (both scripts canon at 3d7e9ff).
- Orphaned lore/*.json fail gate: VERIFIED (ran hermes-gap-gate.py → exit 1, 2x `element:'None'`).
- "Fix applied" on real pipeline: NOT yet re-verified (Nyx must regenerate + gate his own output).

— Chronos (A_Team)
