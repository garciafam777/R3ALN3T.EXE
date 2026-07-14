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

---

## ⚡ CEO RULINGS EXECUTED — 2026-07-13 (update)
CEO rulings received and actioned:

- **T1 — KEEP + INTEGRATE.** `intro_lifein6thgearSTUDIOS/` is the studio intro that plays before the start screen; it needs integration, NOT deletion. **Left fully intact.** (Follow-up task: wire it into the pre-start-screen flow — added to future tasks.)
- **T2 — TOSSED.** All 9 `*_complete/` dirs (39 files) `git rm`'d. Every file was byte-identical to a copy outside `_complete` (0 unique, verified against 2,192 outside hashes). Canonical copies (in `docs/`, `Assets/`, etc.) retained.
- **T3 — PARTIAL TOSS (safety catch).**
  - ✅ Tossed: `Main_Game_Files/.../scripts/Card Creation` — full stale mirror of root `Scripts/Card Creation` (96 files, 523M, 0 unique).
  - ⚠️ KEPT `Main_Game_Files/.../character_cards` — **NOT a duplicate**: it has **31 unique card JSONs** not in `Assets/Character_Cards`. Tossing would have lost 31 cards. This is a different card SET, not a mirror. Flagged for CEO: do you want these 31 merged into `Assets/Character_Cards`?
  - ⚠️ KEPT both `Assets/Images/UI/card_frames` and `Scripts/.../frames` (identical 218M each) — each is a LIVE location (asset library vs renderer working dir). Deleting either risks breaking references. Advise which is canonical if you want one gone.
- **T4 — HELD (56KB, pipeline risk).** `DT_Career_Master.json` and `shards/career_shard_001.json` are byte-identical AND same mtime — can't pick "most updated," they're equal. They serve distinct pipeline roles (master aggregate vs shard input). Deleting either risks the volume generator for 56KB. Recommend keep both. Confirm if you still want one gone.
- **T5 — LEFT ALONE.** Root `R3ALN3T/` (the "brain," Obsidian/Node app) untouched. ✅

### Space (this session, cumulative)
14G → 12G working tree. Committed tracked-mirror removal: 135 files (T2+T3) removed from the tree. LFS blobs for tossed PNGs remain in history (expected; a `git lfs prune`/gc after push reclaims remote/local LFS cache if desired).

