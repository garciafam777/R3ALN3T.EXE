# Cook / Package — SUCCESS via split (Chronos)

**Date:** 2026-07-11
**Verdict:** ✅ FULL COOK/PACKAGE COMPLETE — `ExitCode=0 (Success)`

## What failed first (and why)
Monolithic `BuildCookRun -cook -build -stage -pak -archive` failed 2x with `exit=6`:
- `UbaSessionServer - Killed process RealityWorldBuilder.cpp - Low on memory (89.4gb/91.0gb)`
- Followed by `LNK1104: cannot open UnrealEditor-R3ALN3T_UE5.dll`

Two distinct root causes:
1. **RAM/commit ceiling** — box has 32 GB physical but ~91 GB commit charge (RAM+pagefile). The monolithic cook recompiles+links BOTH editor and game targets WHILE cooking all content → commit hit 89.4 GB, killed a compile.
2. **Zombie process lock** — the first killed cook left a live `UnrealEditor.exe` (PID 56340, 1.3 GB) holding the editor DLL lock, which then blocked EVERY subsequent link with `LNK1104` (not RAM — a file lock).

## The split (CEO directive) that worked
1. Killed zombie `UnrealEditor.exe` → freed the DLL lock + ~1.4 GB RAM.
2. Rebuilt editor target ALONE (`Build.bat R3ALN3T_UE5Editor ... -NoUBA`) → restored real `UnrealEditor-R3ALN3T_UE5.dll` (66 MB PDB; link succeeded at 73.58/84.74 GB commit, under the 86.4 GB kill threshold).
3. **Cook ALONE** (`BuildCookRun -cook -NoBuild -stage -pak -archive -NoUBA -MaxJobs=4`) → no C++ link in-flight, so commit stayed under ceiling. **ExitCode=0.**

## Evidence
- Cook time: 144.7s (`LogCook: Cook by the book total time ... 144.755569`)
- `AutomationTool exiting with ExitCode=0 (Success)`
- Package: `BuildPackage/Windows/` — 1.1 GB total
  - `R3ALN3T_UE5.exe` (packaged game)
  - `R3ALN3T_UE5/Content/Paks/R3ALN3T_UE5-Windows.pak` (cooked content)
  - Engine binaries, manifests (`Manifest_UFSFiles_Win64.txt` etc.)
- Logs: `cook_alone.log`, `build_editor_restore2.log` (local, NOT committed — 1.1 GB package excluded)

## Lesson (don't regress)
On this 91 GB-commit box, NEVER run the monolithic `-cook -build` together. Split:
editor rebuild (alone) → `BuildCookRun -cook -NoBuild ...` → (stage/pak/archive in same call is fine post-cook).
Also: always kill lingering `UnrealEditor.exe` before a rebuild, or `LNK1104` will masquerade as a build failure.

— Chronos (A_Team)
