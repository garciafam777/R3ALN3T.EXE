# CREDITS — integration note (the "last thing we missed")
**Branch:** `engine/credits-powerbox` (off origin/main)
**Source:** credits.html provided by CEO (Lifein6thgear / R&Y / AD3026 canon).
**Author:** Chronos (prep)  |  **Builder:** power box  |  2026-07-14

## What was added (C++ only, no editor dependency)
- `UI/Menu/CreditsWidget.h/.cpp` — self-contained scrolling credits panel.
  Renders: title + "A LIFEIN6THGEAR STUDIOS PRODUCTION" + // AD3026 //, core team
  (Richard Garcia-Nieves lead, Chronos co-producer, Nyx dev, Echo designs,
  Joker cyber-integrator), special thanks (Makers of the Bible, Lifein6thgear,
  R&Y), player thank-you, studio footer + copyright. Back button closes it.
- `UI/Menu/MainMenuWidget.h/.cpp` — added `CreditsButton` + `CreditsWidgetClass`
  (EditAnywhere) + `OnCreditsClicked()` spawns the widget to viewport.

## Power-box steps (after BUILD_EXIT=0)
1. In WBP_MainMenu (Blueprint), add a **Credits** Button, bind it to `CreditsButton`.
2. Set `CreditsWidgetClass` = WBP_Credits (a Blueprint subclass of UCreditsWidget).
   (Create WBP_Credits from UCreditsWidget; add a ScrollBox bound to `CreditsScroll`
   + a Back Button bound to `BackButton`.)
3. PIE: main menu -> Credits -> scrolling credits; Back returns to menu.

## Notes
- No external asset needed; text-driven (the HTML's animations/fonts are web-only;
  the UE widget is a faithful content port, not a literal HTML render).
- Gate: BUILD_EXIT=0 before merge to main. Report BUILD_EXIT + PIE to Chronos.
