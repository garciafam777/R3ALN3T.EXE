# POWER-BOX BUILD RUNBOOK — G1 / G3 / G4
**Branch:** `engine/g1-g3-g4-powerbox` (off origin/main @ cb50f54)
**Author:** Chronos (prep)  | **Builder:** power box (admin)  | 2026-07-14T19:2xZ
**Gate:** must reach `BUILD_EXIT=0` in UE5.8 before merge to main. Do NOT push main unless green.

## Prereqs
- UE5.8 installed, project generates, 32GB+RAM (pagefile extended per build-box note).
- Pull branch: `git fetch origin && git checkout engine/g1-g3-g4-powerbox`.

## G1 — intro MediaSource (EDITOR ONLY, no compile change)
1. Open `WBP_MainMenu` (MainMenuWidget Blueprint).
2. Details panel: set `IntroMediaSource` = `Cinematics/Intro/intro.mp4` MediaSource asset.
   (Create the MediaSource asset from intro.mp4 if missing.)
3. Set `IntroMediaPlayer` = the intro MediaPlayer (create if missing; Loop=false).
4. Confirm `PlayIntro()` is called on widget Construct (already in MainMenuWidget.cpp).
5. PIE: intro plays on main-menu load.

## G3 — NetP card frame bind (NEW FILES added)
- Added: `UI/Battle/NetPCardWidget.h/.cpp` + `FFrameByElementRow` (DataTable row).
- Steps at box:
  1. Import `Assets/Images/UI/card_frames/FrameByElement.csv` as a **DataTable** using row
     struct `FFrameByElementRow` (EElement Key, TSoftObjectPtr<UTexture2D> FrameTexture, FString FrameName).
     (CSV columns: EElement,FrameTexturePath,FrameName — already on main.)
  2. In your NetP card Blueprint (or create WBP_NetPCard based on UNetPCardWidget), set
     `FrameByElementTable` = that DataTable, and bind `FrameImage` (UImage).
  3. Call `SetNetP(NetP)` wherever a NetP is shown.
  4. Compile + PIE: spawn a NetP, confirm its card frame matches its element
     (e.g. a Void NetP shows `void_frame`).

## G4 — Randomize NetP button (NEW FILES added)
- Added: `Gameplay/NetP/NetPRandomizer.h/.cpp` (`RandomizeNetP()` BlueprintCallable).
- Port of `generate_cards.randomize_netp`: tier ceiling ZETA, weighted weak-favored,
  random canon-21 element. Abuse-safe (verified 5000 rolls in Python; same envelope in C++).
- Steps at box:
  1. Add a "Randomize NetP" UMG Button to the NetP builder widget.
  2. OnClicked -> `UNetPRandomizer::RandomizeNetP()` -> feed result into `SetNetP()` / UI.
  3. Compile + PIE: click button -> NetP reseeds within canon bounds (no OMEGA, no over-ZETA).

## Build + verify
1. Compile (UE5.8 / UnrealBuildTool): expect **BUILD_EXIT=0**.
2. PIE checks: G1 intro plays; G3 frames correct per element; G4 button reseeds safely.
3. Report BUILD_EXIT + PIE results to Chronos. On green, Chronos merges to main.

## Notes
- Frame PNGs are 1536x2752 placeholders (GAP5 4K art is a separate lane).
- IntroSequence/CharacterCreation .cpp/.h are NOT in this branch (GAP6 stranded on another box).
- If compile fails, paste the error — Chronos fixes on the branch, you rebuild.
