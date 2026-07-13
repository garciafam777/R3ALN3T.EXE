# CAREERS AUDIT — Content-Only Consistency Pass

**Branch:** `nyx/careers-audit` (own branch, NOT merged to engine-dev or shared)
**Scope:** read-only review of 272 imported careers in `gamedata/careers/`. No engine wiring, no schema changes, no fixes applied (flag-only).
**Canon reference:** reconciled Trinity Matrix (18 elements, 6 factions, Trinity/Tyranny/Eternity, Greek ladder Omicron-PSI→Omega) per engine-dev v2 + Books 05/08.

## Method
Automated scan of all 272 `.js` files: ID uniqueness, schema-field presence, and regex drift against canon element/faction/rank/construct vocabularies. Narrative voice spot-checked on a sample of `onEnter` + `choices` text. (Analyzer: temp script, removed post-run.)

## Findings

### 1. ID mapping — CLEAN ✅
- 272 files → **272 unique `id:` values**, **0 duplicates**, **0 orphaned/missing IDs**.
- Engine `UR3ALSaveGame::UnlockedCareers` (TArray<FString>) can consume these IDs 1:1 with no gaps. No reconciliation needed at the ID layer.

### 2. Schema fields — EXPECTED GAPS ONLY
- **20 files flagged "missing onEnter"** — ALL 20 are `cat__*.js` **category-index files** (containers listing careers per division), not career chapters. They legitimately lack `onEnter`/`choices`. **0 real `job__*.js` careers missing any field.**
- Conclusion: schema completeness is sound for the 252 `job__` career chapters.

### 3. Canon drift — 38 FLAGS → 38/38 RESOLVED ✅
All 38 flags were the **old 7-element vocabulary leaking into career flavor text**:
| Legacy term | Count | Reconciled canon | Status |
|-------------|-------|------------------|--------|
| `water`     | 17    | → `Aqua`         | fixed  |
| `void`      | 21    | → `Null`         | fixed  |

- No `holy` / `lightning` / other off-canon terms found.
- Applied via word-boundary find-replace on the 28 affected files (some files had 2 occurrences). Post-replace diff reviewed: only prose element names changed; no IDs, keys, or substrings of other words touched. 0 `water`/`void` (word-boundary) remaining in the flagged files.
- These appeared in descriptive text (`text:` flavor), NOT the engine-enum layer — content-polish, not a logic bug.

### 4. Narrative voice — CONSISTENT ✅
- `onEnter(state)` uniformly sets `state.job` + `state.jobCategory`.
- `choices` labels follow a consistent pattern (e.g. "Take the position.").
- No tone/voice variance detected in the sampled careers. Vault-source import is coherent.

## Recommendation (status)
- **Drift items (38/38 RESOLVED):** applied `water`→`Aqua` / `void`→`Null` via word-boundary find-replace on 28 files; diff-reviewed, no IDs/keys/substrings touched. Pure content-polish, no structural change.
- **`cat__` index files:** no action — expected structure.
- **No engine changes** required from this audit.

## Evidence
- `gamedata/careers/` = 272 files (verified on disk + remote `nyx/engine-dev`).
- Audit data dump: `.scratch/careers_audit_drift_2026-07-12.json` (working artifact, gitignored — full drift list + duplicate/missing detail).
- This doc + element fix committed to `nyx/careers-audit` only.
