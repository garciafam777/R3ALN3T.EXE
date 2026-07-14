# Mirror/Duplicate Integrity Report — 2026-07-13
**By:** Chronos (A_Team)  **Method:** md5 content-hashing, git-tracked vs untracked verification, git fsck.
**Repo:** C:\Users\richa\Desktop\R3ALN3T_UE5 (branch main, synced origin/main)

## SUMMARY
Disk before: **14G** → after safe deletes: **12G** (~1.9G reclaimed). Zero tracked files touched. Git integrity clean (fsck OK, no tracked deletions).

## ✅ DELETED (this pass — safe, untracked, regenerable/fully-redundant)
| Item | Size | Why safe |
|------|------|----------|
| `BuildPackage/` | 1.1G | UE5 staged package output (Engine+binaries+.exe+manifests). Untracked, 100% regenerable by re-cook. |
| `Main_Game_Files/R3ALN3T.EXE/` | 795M | Nested git repo copy. **1290/1291 files byte-identical** to content elsewhere in tree; only unique file = trivial `.gitignore` (backed up to `/tmp/nested_R3ALN3T.EXE_gitignore.bak`). Untracked. |
| `nul`, `Project/R3ALN3T_UE5/nul` | ~0 | Windows null-device artifacts. |
| 12× build/cook `.log` (`build_*`, `cook_*`, `save_load_rt`, `Scripts/rotterdam_build`) | small | Build noise, untracked. |

Verification: `git status` shows NO tracked-file deletions (`^ D`); `git fsck --connectivity-only` clean; branch still `main...origin/main` in sync.

## ⏸ FOUND, NOT DELETED — needs CEO ruling (tracked and/or history/LFS impact)

### T1. `intro_lifein6thgearSTUDIOS/` — TRACKED mirror of `Cinematics/Intro/` (184M)
- 1200 frames, **frame sets md5-IDENTICAL** to `Cinematics/Intro/frames/`. Also src (`tsconfig.app.json`, `vite-env.d.ts`) identical.
- **BOTH are git-tracked + PNGs are LFS.** Deleting one requires `git rm` + commit → rewrites tree, touches LFS. Reversible via history but not a plain delete.
- Recommend: keep `Cinematics/Intro/` (canonical location), `git rm -r intro_lifein6thgearSTUDIOS/`. Saves 184M working + LFS bloat. **Awaiting go.**

### T2. Duplicate content pairs across `docs/` ↔ `Main_Game_Files/*_complete/` (tracked)
- Many byte-identical: `docs/Game_Mechanics/*.txt` = `Main_Game_Files/.../game_mech_complete/*`, `docs/World_Building/rooms.txt` = `.../homes_complete/rooms.txt`, `docs/Battle_System/*` = `.../Battle_space_complete/*`, `docs/Roads/construction.md` = 2 other copies, etc.
- These look like a `docs/` reorg where `Main_Game_Files/*_complete/` is the OLD pre-move location. Need CEO to confirm which tree is canonical before `git rm` the stale one.

### T3. Card-asset + CSV dup triplets (tracked + untracked mix)
- `Scripts/Card Creation/cards/*.csv` == `Main_Game_Files/.../scripts/Card Creation/cards/*.csv` (byte-identical pairs).
- `Assets/Images/UI/card_frames/Drafts/*.jpeg` == `Scripts/.../frames/Drafts/*` == `Main_Game_Files/.../frames/Drafts/*` (triplets).
- Element icons, `_manifest.js`, card JSONs duplicated `Assets/` ↔ `Main_Game_Files/`.
- Same question: which of `Assets/` vs `Scripts/` vs `Main_Game_Files/` is canonical?

### T4. `content_sample/volume/DT_Career_Master.json` == `shards/career_shard_001.json`
- Identical — likely intended (master vs first shard) OR a stale shard. Confirm.

### T5. `R3ALN3T/` (root, 109M, untracked) — NOT a mirror, NOT deleted
- Separate git repo: Obsidian/Node app (`package.json`, `extensions/`, `node_modules`, `profiles/`, `library/`). Internal dups are just `node_modules` (normal). **Leave as-is** unless you want it out of this repo's folder entirely.

## RECOMMENDATION
Safe pass done. For T1–T4 (tracked dedup), give one ruling on canonical location per group and I'll `git rm` the stale copies in one reviewed commit (LFS-aware). T5 leave alone.
