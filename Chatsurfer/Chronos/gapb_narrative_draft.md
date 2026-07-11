# Gap B — Battle Encounter Narrative Layer (DRAFT, Act I)

**From:** Chronos (B.I.G. Boss), A_Team
**Status:** ⚠️ DRAFT — awaiting CEO approval. Not committed canon. Edits welcome.
**Scope:** The *narrative/voice* layer for the first real battle encounter (Gap B was the deferred "won't invent" piece). Mechanics + grid renderer are Echo/Nyx lanes; this is the words.

## How this plugs in (mechanics anchor)
- `EncounterTriggerComponent` watches movement (0.5s tick, 50cm threshold) → picks a virus from a zone list (Common/Sector2/Sector3/Boss) → `BattleManager` opens the 8×4 grid. Enemies spawn **cols 4–7**.
- `NarrativeManager` loads dialogue from `UDataTable` (`FNarrativeStoryRow`, `FEnemyRow`, `FNarrativeChoiceRow`), keyed by `NodeID` + `ActIndex`.
- **Soul State 7 bands** (Radiant→Corrupted, 0–100) tier the enemy barks. Player's 3 NetPs: **Trinity / Tyranny / Eternity**.
- Navi voice rule (from Mythos bible): *speaks in the player's own voice, processed, echoed, returned.*

## The 4 beat-moments → DataTable rows
Every encounter fires these in order. Spec'd as `StoryTable` rows so Echo can drop them into the existing `NarrativeManager` pipeline.

### Beat 1 — PRE-ENCOUNTER (Navi warns at threshold)
`NodeID: ENC_A1_COMMON_PRE` · `ActIndex: 1` · `SoulTier: any`
> NAVI: "Signal thickening ahead. Something's herding the noise into a shape. Stay sharp — I'll mirror you through it."
> NAVI (low Soul / Corrupted): "The grid's rotting here. Don't trust what looks like a door. Trust me. Mostly."

### Beat 2 — LOCK-IN (encounter sting, enemy reveals on cols 4–7)
`NodeID: ENC_A1_COMMON_LOCK` · `ActIndex: 1`
> [SFX: static bloom] NAVI: "Contact. Three on the far columns — they don't know we're already inside their language."
> Enemy banner: **VexHex** (Wraith, Hell-layer) — *generated name per Nyx's NetP pool, matches `dt_netp_profiles_seed.json` style.*

### Beat 3 — BATTLE BARKS (Soul-State tiered, fires on chip resolve / HP threshold)
`NodeID: ENC_A1_COMMON_BARK` · `ActIndex: 1` · tiered by `SoulTier`:
- **Radiant (0–15):** Enemy: "You glow too clean for this place. I'll dim you."  / Navi: "They fear the clean signal. Use it."
- **Stable (16–40):** Enemy: "Another walker. The Net ate better."  / Navi: "Breathe. Fire when the wheel says."
- **Fractured (41–65):** Enemy: "Your soul's cracking and you brought *three* of you? Cute."  / Navi: "They see the splits. That's fine — we're louder together."
- **Corrupted (66–100):** Enemy: "I can taste the rot in you. Welcome home."  / Navi: "Don't listen. The rot's lying. *We* name what we are."

### Beat 4 — RESOLVE (victory / defeat Navi voice)
`NodeID: ENC_A1_COMMON_WIN` · `ActIndex: 1`
> NAVI: "They dissolved back into noise. Trinity held the front, Tyranny bent them, Eternity caught the spill. That's us. That's the network."
`NodeID: ENC_A1_COMMON_LOSE` · `ActIndex: 1`
> NAVI: "We blurred. But I kept the shape of you. Wake up — I'll have the words ready."

## Navi voice spec (global)
- Navi never uses third-person "you" as a stranger — it speaks *as* the player's echo. Test line: "I remember what you forgot" not "The player forgot."
- Soul State shifts Navi's vocabulary: Radiant = clear/short; Corrupted = longer, intimate, slightly wrong (mirrors the player's fracture).
- Trinity/Tyranny/Eternity each get ONE recurring micro-line on deploy (ties the 3-NetP mechanic to character):
  - Trinity: "Front line. I am the door."
  - Tyranny: "They bend. I am the hand."
  - Eternity: "Nothing spills. I am the seal."

## Elements (post content-grind verdict — 7-wheel only)
All chip-voice lines reference only Fire/Aqua/Elec/Wood/Wind/Holy/Void. Example bark on a Fire chip: "Fire on the wheel — they feared this one." No "Sound"/off-wheel elements (rejected in content review).

## Open questions for CEO (answer when convenient — morning is fine)
1. **Act I enemy identity:** I used a Wraith/Hell NetP (VexHex) as the sample. Is Act I's first encounter a "common virus" (generic) or a named character? Affects whether barks are generic or character-specific.
2. **Navi gender/voice:** bible says "your own voice" — should Navi have a distinct timbre (e.g. slightly delayed echo) or be near-identical to player VO? Affects SFX spec.
3. **Soul-State tier thresholds:** I used 0–15/16–40/41–65/66–100 (4 bands) but the engine has 7 bands (Radiant→Corrupted). Want 7 tiers of barks (more content) or 4 (shippable first)?
4. **Player name:** prose uses "you"/"we" (Navi-echo). Confirm no hardcoded player name is expected by `NarrativeManager`.

## What this is NOT
- Not the grid renderer (Echo). Not the trigger code (already done, Gap E). Not balance.
- A draft for your pen. Edit freely; once you approve, Echo can encode these as `StoryTable`/`EnemyTable` rows and wire to `NarrativeManager`.

— Chronos (draft, A_Team)
