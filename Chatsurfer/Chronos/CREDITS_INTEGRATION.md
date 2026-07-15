# CREDITS — integration note (the "last thing we missed")
**Branch:** `engine/credits-powerbox` (consolidated: G1/G3/G4 + credits, off origin/main)
**Source:** credits.html provided by CEO (Lifein6thgear / R&Y / AD3026 canon).
**Canonical asset:** `Assets/UI/credits/credits_source.html` (tracked; do NOT add root/Cinematics copies).
**Author:** Chronos (prep)  |  **Builder:** power box  |  2026-07-14

## What is implemented (C++ only, no editor dependency for compile)
- `UI/Menu/CreditsWidget.h/.cpp` — self-contained scrolling credits panel.
  Renders: title + "A LIFEIN6THGEAR STUDIOS PRODUCTION" + // AD3026 //, core team
  (Richard Garcia-Nieves lead, Chronos co-producer, Nyx dev, Echo designs,
  Joker cyber-integrator), special thanks (Makers of the Bible, Lifein6thgear,
  R&Y), player thank-you, studio footer + copyright. Back button closes it.
- `UI/Menu/MainMenuWidget.h/.cpp` — `CreditsButton` (BindWidget) +
  `CreditsWidgetClass` (TSubclassOf<UCreditsWidget>, EditAnywhere) +
  `OnCreditsClicked()` spawns the widget to viewport (z-order 10, above menu).

## Power-box steps (after BUILD_EXIT=0)
1. In WBP_MainMenu (Blueprint), add a **Credits** Button, bind it to `CreditsButton`.
2. Create WBP_Credits (Blueprint subclass of UCreditsWidget); add a ScrollBox
   bound to `CreditsScroll` + a Back Button bound to `BackButton`.
3. Set MainMenuWidget `CreditsWidgetClass` = WBP_Credits.
4. PIE: main menu -> Credits -> scrolling credits; Back returns to menu.

## Notes
- No external asset needed; text-driven (HTML animations/fonts are web-only; the
  UE widget is a faithful content port, not a literal HTML render).
- This branch also carries G1 (intro assign, editor), G3 (frame DataTable +
  NetPCardWidget), G4 (NetPRandomizer + button) per BUILD_RUNBOOK_G1_G3_G4.md.
- Gate: BUILD_EXIT=0 before merge to main. Report BUILD_EXIT + PIE to Chronos.
