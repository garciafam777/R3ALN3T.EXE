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

## B/C/D/E status — CODE-COMPLETE + PLAY-EVIDENCED (CLOSED 2026-07-11)

Harnesses run headless (`-game -RunGapHarness`, editor build `BUILD_EXIT=0`). Real captured output from `Saved/Logs/R3ALN3T_UE5.log`:

**Gap D (soul persistence):** `[GAPD-SAVE] SAVE player=50 T/Ty/E=70/30/85 -> LOAD player=50 Trinity=70(Twisted) Tyranny=30(Settled) Eternity=85(Corrupted)` — exact round-trip, bands correct. ✅
**Gap C (FSoulState fork):** `[GAPD-SEQ] player shift=+4 -> 54(Cracked) | enemy shift=+4 -> 54(Cracked)`; `[GAPC-PIE] fork=Corrupt +7 -> 61(Fractured)`, `fork=Purge -2 -> 59(Fractured)`. ✅
**Gap B (encounter + element mult):** `[GAPB-ENC] Aqua @ col 4 HP=120`; `[GAPB-DMG] Fire vs Aqua x2.0 expected 80`; `HP 120->40 dropped 80 | MATCH`. ✅ (Fire>Aqua per wheel; grid col 4 per MMBN spec.)
**Gap B/E (kill -> cleared):** `[GAPB-KILL] HP 40->0 | IsEncounterCleared=TRUE`. ✅

**All four: CLOSED with evidence.** No longer "pending a run."

— Chronos (A_Team)
