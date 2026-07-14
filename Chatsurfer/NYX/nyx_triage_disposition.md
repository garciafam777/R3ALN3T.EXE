# NYX — untracked-file triage disposition (REFRESHED 2026-07-13, v2)
**From:** Chronos (A_Team)  **To:** Nyx (eng/devops)  **Re:** untracked pile on Chronos's box
**Status:** CEO authorized triage. DO NOT `git add -A`. Batch by class below.
**v2 changes:** Chronos already executed the SAFE deletes + tracked dedup this session.
Pile is now **75 entries** (down from 65). Re-triaged against live `git status`.

## ⚠️ ALREADY DONE by Chronos (do NOT re-do)
- Deleted untracked regenerable junk: `BuildPackage/` (1.1G), nested `Main_Game_Files/R3ALN3T.EXE/` repo (795M), `nul`×2, 12 build/cook logs.
- `git rm`'d tracked: all 9 `*_complete/` dirs (T2) + `Main_Game_Files/.../scripts/Card Creation` mirror (T3) = 135 files committed (`62183d1`).
- Emoji-named dialogue dup deleted; 21-element ruling recorded; randomizer built/verified.
=> These items are GONE from the pile. See `mirror_integrity_report_2026-07-13.md`.

## DELETE (junk — never commit)
- `build_r3aln3t.bat` — local helper at repo root; if team wants it tracked, move to `tools/` first.
- `Project/R3ALN3T_UE5/Content/Maps/GrayBox_Test.umap` — scratch map. Per "kill loose ends" discipline: confirm it is NOT referenced by any level/asset, then DELETE (do not keep as a loose test map).

## COMMIT (reviewed batches — verify each before adding)
1. **Lore/design docs** → "docs: NetP designs + master/index"
   - `Assets/Images/NetP/*.md` (15 files: Angelic, Cosmos, Creatures_Unranked, Demonic, Design NetP, Design_Antagonist_ACT_I–IV+secret, Design_Bible_NetP, NETP_elemental, Regular_NPC, UnderNet_NetP)
   - `Assets/Character_Cards/NetP's.md`, `Content/R3ALN3T/Characters/Common/Trinity001.jpg`
   - Root: `00_MASTER_DOCUMENTATION.md`, `DOCUMENTATION_INDEX.md`, `Game dir_complete.md`, `Planned fixes_complete.md`, `Programs to use for game creation_complete.md`, `Ranks_complete.md`
   - `Main_Game_Files/game_txt_files/THE MYTHOS ORIGIN_3026.md`, `Main_Game_Files/game_txt_files/NetP's_MCADMIN/Eternitynity - 002 (pre-final draft).png`
   - `Scripts/_tier2_add.txt`
2. **Intro media** → "content: studio intro"
   - `Cinematics/Intro/intro.mp4` (this is T1 — the pre-start-screen studio intro; KEPT per CEO, integrate later)
3. **Card CSVs** → decision needed (item Q1 below): `Scripts/Card Creation/cards/characters.csv`, `generated_cards.csv` — dup pair of the deleted Main copy. Keep Scripts/ as canonical, delete the other (none remain here, but confirm no re-gen).
4. **Generated card JSONs (36)** → "cards: randomized NetP drafts"
   - `Main_Game_Files/R3ALN3T.EXE_game_creation/character_cards/cards/*.json` (25 new + `_manifest.json`) + modified `_manifest.js`. These are randomizer test output + 31 accepted drafts. CEO said "31 drafts it is" — keep. Commit as data, NOT with source.
5. **Services/backend** → "services: datasync + api" (REVIEW FOR CREDS FIRST)
   - `Services/r3aln3t_datasync.py`, `Services/datasync_report.json`, `backend_api.py`, `data_models.py`, `bruno_environments.json`
6. **Chatsurfer** → "chat: crossref + nyx post"
   - `Chatsurfer/Echo/task_crossref_vault.md`, `Chatsurfer/NYX/nyx_chatsurfer_post.md`
7. **To-Do** → "todo: briefs/steps" (check for stale before commit)
   - `To-Do/Briefs/`, `To-Do/Completed review/`, `To-Do/Steps/`

## SOURCE — CODE REVIEW REQUIRED before commit (do NOT batch with docs)
- `GameIntro.tsx`, `IntroSequence.cpp`, `IntroSequence.h`, `R3ALN3TGameMode.cpp`, `R3ALN3TGameMode.h`
- These are engine/gameplay source changes. Get a reviewer sign-off (Chronos/Echo) before they enter `main`.

## HOLD / OPEN QUESTIONS for CEO (NYX cannot decide)
- **Q1** `Main_Game_Files/R3ALN3T.EXE_game_creation/scripts/` (untracked) — now that the *tracked* Main script mirror was deleted, is this *untracked* `scripts/` canonical or a dup of root `Scripts/`? Verify before committing.
- **Q2** `Project/R3ALN3T_UE5/Content/Python/` — confirm intended engine Python content (not stray) before commit.
- **Q3** `R3ALN3T/` (root, 109M) — it's the "brain" (separate Obsidian/Node app, its OWN git repo). CEO said leave it. Decide: keep embedded in this repo folder (stays untracked noise) or extract to its own standalone repo.
- **Q4** `Chatsurfer/NYX/nyx_chatsurfer_post.md` — is this NYX's own post? OK to commit in the Chatsurfer batch?

## Gate
Triage cleans the base. **Request A (CI) stays DENIED** until CEO's written lift — this work does NOT auto-un-deny it. NYX commits to a branch / local only until then.
