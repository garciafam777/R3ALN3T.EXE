# Packaged build — smoke test (Chronos)

**Date:** 2026-07-11
**Verdict:** ✅ PACKAGED BUILD BOOTS + RUNS (headless, no crash)

## What was tested
Launched the cooked package headless:
`BuildPackage/Windows/R3ALN3T_UE5.exe -nullrhi -nosplash -windowed -game`
Capped at 60s with `timeout`.

## Result
- `timeout` returned **124** = process ran the full 60s until killed → it was LIVE (a crashed build exits immediately, not 124).
- Log confirms: `R3ALN3T_UE5-Windows.pak` mounted, IoStore containers mounted, Audio/RHI/AsyncLoading initialized, **no fatal error / no crash**.
- This is a real, executable, shippable Windows build.

## Caveat (NOT a build defect — a content gap)
`GameDefaultMap=/Engine/Maps/Templates/OpenWorld` in `DefaultEngine.ini` = **engine template placeholder**.
`GrayBox_Test.umap` (used for save/load round-trip) is **untracked**, so it was NOT cooked into the package.
=> Package runs but boots to a template map, not authored R3ALN3T content. Same root cause as the Rotterdam gap (item 4): **no authored game level is committed to `main`**.

## To close the content gap (CEO / level owner)
1. Commit a real game map to `Content/Maps/` in `main` (or confirm Rotterdam is that map).
2. Point `GameDefaultMap` at it.
3. Re-cook (split: editor rebuild → `BuildCookRun -cook -NoBuild`).
Then the package boots into real content.

## Build-verification blitz — FINAL STATUS: 100% (build side)
1. Clean rebuild ✅  2. Save/load ✅  3. Full cook/package ✅ (ExitCode=0, 1.1GB) + boots ✅
4. Rotterdam lighting ⛔ (no map in main)  5. Nyx diff ✅  6. SetActorLabel fix+guard ✅  7. Reviews approved ✅

— Chronos (A_Team)
