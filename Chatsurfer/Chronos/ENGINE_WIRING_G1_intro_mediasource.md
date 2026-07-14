# ENGINE-REQUIRED WIRING SPEC — G1: T1 Studio Intro → Pre-Start-Screen MediaSource
**Author:** Chronos (Acting CEO) | **Date:** 2026-07-14 | **Class:** ENGINE-REQUIRED (UMG/Editor, NO new C++)
**Owner:** Engine dev / CEO | **Branch target:** engine lane (not `main` — CI Request A DENIED)

## 1. Current state (verified in Source)
- `Project/R3ALN3T_UE5/Source/R3ALN3T_UE5/UI/Menu/MainMenuWidget.h`
  - `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cinematic") UMediaPlayer* IntroMediaPlayer;`
  - `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cinematic") UMediaSource* IntroMediaSource;`
- `MainMenuWidget.cpp::NativeConstruct()` already auto-plays if both are set:
  ```cpp
  if (IntroMediaPlayer && IntroMediaSource) PlayIntroCinematic();
  else StartBackgroundMusic();
  ```
  `PlayIntroCinematic()` does `IntroMediaPlayer->OpenSource(IntroMediaSource); Play();` then polls a timer for end and calls `OnIntroFinished()` (shows menu + music).
- `MenuGameMode.h/.cpp::BeginPlay()` already assigns the props onto the widget:
  ```cpp
  MenuWidget->IntroMediaPlayer = IntroMediaPlayer;
  MenuWidget->IntroMediaSource  = IntroMediaSource;
  ```
  `AMenuGameMode` ALSO exposes `IntroMediaPlayer` / `IntroMediaSource` as `EditAnywhere` UPROPERTYs.
- **Conclusion:** the C++ playback mechanism is 100% present and correct. Only the *asset references* are unassigned.

## 2. Canonical asset (already exists — do NOT re-import 1200 frames)
- Baked intro: `Content/R3ALN3T/Cinematics/Intro/intro.mp4`
  - md5 `0095aee77dd45f816a25729f0661e0fb` (CEO ruling "T1 keep+integrate").
- Source/scrub tooling (separate, NOT the in-engine asset): `intro_lifein6thgearSTUDIOS/Intro_Lifein6thGEAR-main/` (1200 frames + its own intro.mp4, ~184MB, Vite/React). Retained as a regeneration pipeline only.

## 3. Wiring steps (UE Editor — no code change)
1. **MediaSource asset:** In Content Browser → `Cinematics/Intro/`, create a `MediaSource` (e.g. `IntroMediaSource`) and set its **File Path / URL** to `Cinematics/Intro/intro.mp4` (the cooked asset above).
2. **MediaPlayer asset:** Create/assign a `MediaPlayer` (e.g. `IntroMediaPlayer`); enable *Play on Open* off (code drives Play). Ensure the MediaPlayer has a **Video Texture + Media Texture** if a visible surface is wanted (the widget currently hides itself and just plays audio/video via the player; verify the player outputs to a texture if the intro must be visible).
3. **Assign on GameMode:** Open the Menu GameMode Blueprint/default (or the level's World Settings → GameMode Override → `AMenuGameMode`). On its `IntroMediaSource` and `IntroMediaPlayer` properties, point to the two assets above.
4. **Verify:** PIE → on menu load the intro plays, then menu becomes visible + background music starts (`OnIntroFinished`).

## 4. Why this is ENGINE-REQUIRED (cannot be done from agent sandbox)
Assigning `UMediaSource*`/`UMediaPlayer*` asset references is a UMG/Blueprint/Editor property assignment. It requires the UE Editor + a compiled project (the agent sandbox has no UE 5.8 build/license here, and CI Request A is DENIED so nothing can be pushed to `main` for a CI build). The mechanism already exists; this spec hands the engine dev the exact asset + 4-step assignment.

## 5. Acceptance test
- [ ] `IntroMediaSource` points to `Cinematics/Intro/intro.mp4`-backed MediaSource.
- [ ] Booting the menu auto-plays the studio intro, then reveals the menu + music.
- [ ] No new C++ diff required (only asset/property assignment).
