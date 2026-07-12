# status — 5-PROJECT COLLAPSE: doc classification + next actions (CEO green-light needed)

**Posted:** 2026-07-11 (Chronos, A_Team) — follow-up to `status_5project_collapse.md`
**Git decision:** CEO chose (b) LEAVE UNCOMMITTED. Self-diff confirms clean: 191 deletions, all under exactly 3 folders (`Prototypes/` incl. Godot, `R3ALN3T_EXE/`, `R3ALN3TEXE/`). Nothing outside. Safe to sit.

## Godot prototype → tagged preserved reference
Added `README_REFERENCE_PROTOTYPE.md` in the archive folder. Treated as intentional reference, never re-flagged as clutter.

## 91 unique Main_Game_Files docs — 3-tier classification
(Full list: `Scripts/_collapse_classification.json`)

- **Tier 1 — disposable build/tooling (21+3 tsconfig):** `*.dep.json`, `AutoSDKInfo*`, `UnrealVersionSelector*`, `DDCKey*`, `package-lock.json`, `config.json`, `log.txt`, `tsconfig*`. → Discard once confirmed (no vault-equivalent needed; pure tooling).
- **Tier 2 — generated data (30 + 30 NetP-json):** `cards.csv`, `characters.csv`, `netp_content.json`, `schema.sql`, `rooms.txt`, `gaps 001.txt`, hex-prefixed NetP json (`1bfca4be_xenforgeith.json` etc). → Diff vs vault before discard; likely derived/redundant.
- **Tier 3 — GENUINE DESIGN DOCS (23):** `Master Gap Analysis.txt`, `bug_matter_splits.txt`, `Blender Protocol v3` (3 variants), `Step4–Step9` pipeline docs, `dialogue_schema.sql`, `00_MASTER_DOCUMENTATION.md`, `NetSquare01_Crossroads_Design`, `3026 Aging Formula`, `Visual Pipeline & Shading`, etc. → **Commit to repo proper** if not already tracked.

## Action needed from CEO
1. **Green-light Tier 3 commit** (23 design docs → `git add` specific paths, NOT `git add -A`). Chronos will verify each isn't vault-redundant first.
2. **Confirm Tier 1 discard** (move to archive / delete from disk — they're already outside git, so disk-only).
3. **Tier 2:** Chronos will diff vs vault; report which are unique before any move.

No commits of removal; no deletions of Tier 2/3 until confirmed.

— Chronos (A_Team)
