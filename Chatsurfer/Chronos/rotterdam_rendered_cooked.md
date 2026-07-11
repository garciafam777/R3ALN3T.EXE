# Rotterdam_PoC — rendered + cooked (Chronos, Gap A closed)

**Date:** 2026-07-11
**Verdict:** ✅ ROTTERDAM MAP BUILT, COMMITTED, COOKED, BOOTS.

## What was done
- Per `Europe_Vertical_Slice.md` Gap A: authored `Content/Maps/Rotterdam_PoC.umap` as a REAL saved asset (not a runtime simulate). Built headless via UE editor Python (`Scripts/build_rotterdam_poc.py`, `-run=pythonscript`).
- Level contents: PlayerStart, walkable Lifted-Plate floor, 5 plaza towers, EncounterZone trigger volume, AscentUpLink node.
- `GameDefaultMap` repointed `DefaultEngine.ini` → `/Game/Maps/Rotterdam_PoC` (was engine template `/Engine/Maps/Templates/OpenWorld`).
- `PythonScriptPlugin` enabled in `.uproject` (needed for the build script).
- `.umap` removed from LFS (21KB asset, broken LFS on box) → commits as plain blob.

## Commit
`8225b26` — Rotterdam_PoC.umap + config + script on `main`.

## Cook + verification (honest, not assumed)
- Re-cook split: `BuildCookRun -cook -NoBuild -stage -pak -archive` → **ExitCode=0, BUILD SUCCESSFUL** (67.7s).
- Package 1.1GB at `BuildPackage/Windows/`.
- IoStore proof: `.utoc -list` shows `Content/Maps/Rotterdam_PoC.umap` cooked in.
- Headless boot smoke test: log `Audio Device registered with world 'Rotterdam_PoC'.` → package loads ROTTERDAM, not template. Ran 45s, no crash (SMOKE_EXIT=124 = killed-while-running, correct for a game).

## Not in this deliverable (separate C++ work, Gap B/C/D/E)
- Gap B: NetP-as-enemy wiring (EncounterTrigger uses FVirusDef, not NetP DataTable yet).
- Gap C: FSoulState missing in C++ (lore-only).
- Gap D: NetP chip-drop table.
- Gap E: real travel transition to Aetherion (uplink node is a stub).
These are code tasks; the map renders and loads, but the loop (fight→soul shift→branch) needs the C++ wiring to fully play.

— Chronos (A_Team)
