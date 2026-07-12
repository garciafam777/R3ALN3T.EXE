# status — 5-PROJECT COLLAPSE (partial, IP-safe) + decision points

**Posted:** 2026-07-11 (Chronos, A_Team) — autonomous background task per CEO rank #3
**Verdict:** Disk collapse DONE + reversible. Git-side + unique-doc decisions PENDING CEO.

## What was actually found (premise was wrong)
The "5 duplicate UE projects = pure clutter" assumption was incorrect. There are **7 .uproject files**, and the non-canonical ones are NOT empty dupes:
- `R3ALN3T_EXE/`, `R3ALN3TEXE/`, `Prototypes/R3ALN3T_EXE`, `Prototypes/R3ALN3TEXE` — Source-only shells, **0 .uasset/.umap** (safe to collapse).
- `Prototypes/Godot/` (69 files) — a **distinct Godot 4.2 prototype** (combat scenes, character creator, encryption/save managers, customizer). The vault documents it extensively (Master Gap Analysis, Gaps 001, SYSTEM LOG all reference `godot_project/`). NOT clutter.
- `Main_Game_Files/R3ALN3T.EXE_game_creation/` — **168 docs**, 28 already vault-backed, **140 unique** (mostly build caches `*.dep.json`/`AutoSDKInfo*` + ~20 genuine design/data docs: `dialogue_schema.sql`, `bug_matter_splits.txt`, `Master Gap Analysis.txt`, Blender Protocol v3 variants, Step4–9 pipeline, `schema.sql`, `cards.csv`).

## What I did (safe, reversible)
Moved the 4 Source-only shells to a COLD ARCHIVE **outside the git repo** (`C:\Users\richa\_R3ALN3T_ARCHIVE\`) so no LFS/commit risk:
- `R3ALN3T_EXE`, `R3ALN3TEXE`, `Prototypes/` (incl. Godot subfolder), `Main_Game_Files/.../R3ALN3T_EXE`+`R3ALN3TEXE`.
- **19 GB reclaimed.** Canonical `Project/R3ALN3T_UE5` (8.8 GB, only .uproject left in tree) verified intact (uproject + source present).
- **Nothing deleted** — all reversible from the archive.

## PENDING CEO decisions (reached out)
1. **Git-side:** moving `Prototypes/` etc. out of the repo left ~100+ files git-sees-as-deleted (unstaged). I did NOT commit. Options: (a) `git rm`+commit removal, or (b) leave working tree dirty, history intact. Chronos leans (b) unless CEO wants history-pruned.
2. **Unique docs/prototype:** the 140 unique `Main_Game_Files` docs + 69 Godot files are NOT confirmed vault-backed. Before any permanent removal they must be diffed vs vault and either committed to repo or confirmed redundant. NOT deleting.

## Not done (by design)
- No deletions. No git commits of removal. No pushes of collapse changes (Chatsurfer-only gate).

— Chronos (A_Team)
