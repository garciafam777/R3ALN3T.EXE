# NYX — untracked-file triage disposition (CEO okay 2026-07-13)
**From:** Chronos (A_Team)  **To:** Nyx (eng/devops)  **Re:** the 65 untracked files on Chronos's box
**Status:** CEO authorized triage. Do NOT `git add -A`. Batch by class below.

## DELETE (junk — never commit)
- `nul`, `Project/R3ALN3T_UE5/nul`
- `build_editor_restore.log`, `build_editor_restore2.log`, `build_fullclean.log`, `build_gametarget.log`, `build_main_sync.log`, `build_main_sync2.log`, `build_main_sync3.log`, `cook_alone.log`, `cook_package.log`, `cook_package2.log`, `save_load_rt.log`, `Scripts/rotterdam_build.log`
- `build_r3aln3t.bat` — local helper; if team wants it tracked, move to `tools/` (not repo root)
- `Project/R3ALN3T_UE5/Content/Maps/GrayBox_Test.umap` — scratch map; confirm unreferenced, then delete or `_scratch`

## COMMIT (reviewed batches)
1. `Assets/` (15 NetP `.md` + `Content/R3ALN3T/Characters/Common/Trinity001.jpg`, `Cinematics/Intro/intro.mp4`) → "content: NetP designs + intro"
2. `Docs/` root: `00_MASTER_DOCUMENTATION.md`, `DOCUMENTATION_INDEX.md`, `Game dir_complete.md`, `Planned fixes_complete.md`, `Programs to use for game creation_complete.md`, `Ranks_complete.md`, `Main_Game_Files/game_txt_files/THE MYTHOS ORIGIN_3026.md` → "docs: master/index/notes" (scan for secrets first)
3. `Main_Game_Files/game_txt_files/NetP's_MCADMIN/Eternitynity - 002 (pre-final draft).png` → asset commit
4. CSVs: `Scripts/Card Creation/cards/*.csv` AND `Main_Game_Files/.../cards/*.csv` are DUPLICATE PAIRS. Keep ONE canonical location, delete the other. Confirm generator-output vs source.
5. `Services/r3aln3t_datasync.py`, `Services/datasync_report.json`, `backend_api.py`, `data_models.py`, `bruno_environments.json` → "services: datasync + api" (review for creds)
6. `GameIntro.tsx`, `IntroSequence.cpp/.h`, `R3ALN3TGameMode.cpp/.h` → **SOURCE changes: needs code review before commit** (don't batch with docs)
7. `Chatsurfer/Echo/task_crossref_vault.md`, `Chatsurfer/NYX/nyx_chatsurfer_post.md` → Chatsurfer commit
8. `To-Do/Briefs/`, `To-Do/Completed review/`, `To-Do/Steps/` → "todo: briefs/steps" (check stale)

## HOLD / QUESTION
- `Project/R3ALN3T_UE5/Content/Python/` — confirm intended engine Python content
- `R3ALN3T/` (root) — likely a stray mirror of `Project/R3ALN3T_UE5/`; verify NOT a full-project dup before adding
- `BuildPackage/` — inspect; likely build output

## Gate
Triage cleans the base. **Request A (CI) stays DENIED** until CEO's written lift — this work does not auto-un-deny it.
