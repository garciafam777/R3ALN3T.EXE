# ENGINE-REQUIRED WIRING SPEC — G4: "Randomize NetP" UI button → backend
**Author:** Chronos (Acting CEO) | **Date:** 2026-07-14 | **Class:** ENGINE-REQUIRED (UMG button + invoke)
**Owner:** Engine dev / Blueprint | **Branch target:** engine lane (CI Request A DENIED)

## 1. Backend is VERIFIED SAFE (Chronos, scriptable side — DONE, re-run 2026-07-14)
- File: `Main_Game_Files/R3ALN3T.EXE_game_creation/character_cards/generate_cards.py`
- `randomize_netp()` → ONE rank-capped NetP JSON. Hard ceiling `RANDOMIZER_MAX_TIER='ZETA'`; `FORBIDDEN_TIERS={'OMEGA'}`.
- CLI: `python generate_cards.py randomize` → prints one JSON to stdout with self-asserts (no OMEGA, not over ZETA).
- **Real stress test (this session):** 5000 rolls → `forbidden(OMEGA)=0`, `over_ceiling(ZETA)=0`, `max_tier_seen=ZETA`, 18 distinct tiers, `ZETA_COUNT=27`. **Backend correct + abuse-safe.**
- (Note: `Assets/Character_Cards/generate_cards.py` is the *dev-batch* variant WITHOUT the `randomize` subcommand — the player-facing one is the `Main_Game_Files/...` copy. Do not wire the dev copy.)

## 2. What is MISSING (the UI wiring)
`MainMenuWidget` exposes only `NewGameButton`, `ContinueButton`, `QuitButton`. No "Randomize NetP" control, and **no call site consumes `randomize`**. A character-build / NetP-select screen needs the button.

## 3. Wiring options (engine dev chooses)
**A. Port to C++/Blueprint (preferred for packaged build):**
   Translate `randomize_netp()` into a `UFunction` on a `UNetPFactory` subsystem:
   ```cpp
   UFUNCTION(BlueprintCallable, Category="NetP")
   FR3ALN3TNetP UNetPFactory::RandomizeNetP() const; // mirror randomize_netp(): tier∈allowed, weighted, ZETA ceiling, OMEGA forbidden
   ```
   Button handler: `NetP = Factory->RandomizeNetP(); LoadIntoRun(NetP);`

**B. Subprocess invoke (fastest, needs Python at runtime — not for packaged shipping):**
   ```cpp
   FString Cmd = TEXT("python \".../generate_cards.py\" randomize");
   // capture stdout JSON, FJsonSerializer::Deserialize into FR3ALN3TNetP
   ```

**C. Backend HTTP:** POST to the AI backend (`ai_backend/main.py`) if it exposes a randomize route — currently it does NOT; would need an endpoint + the CORS/auth fix (see Joker `security_audit_save_netcode.md`).

## 4. UMG steps (Editor)
1. On the NetP-select/character-build Widget Blueprint, add a `UButton` named `RandomizeButton`.
2. In the widget's `NativeConstruct`/`Construct`, bind: `RandomizeButton->OnClicked.AddDynamic(this, &UYourWidget::OnRandomizeClicked);`
3. `OnRandomizeClicked()` calls the chosen backend (A/B/C), then loads the resulting NetP into the pending run state and advances.
4. Add the same `ZETA`-ceiling + `OMEGA`-forbidden assert server/client-side as a guard (defense in depth; backend already enforces).

## 5. Why ENGINE-REQUIRED
Adding a `UButton`, a click handler, and an invocation path (C++/Blueprint) + a UE compile is engine work. The *backend correctness* is already proven; this spec hands the engine dev the verified contract + C++ sketch.

## 6. Acceptance test
- [ ] "Randomize NetP" button present on the build screen.
- [ ] Clicking it produces a NetP that is ≤ ZETA tier and never OMEGA (verify against 5000-roll contract).
- [ ] Resulting NetP loads into the run; no crash on missing portrait (portraits are G7 art gap — JSON-only is fine).
