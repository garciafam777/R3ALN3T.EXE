# R3ALN3T.EXE — Act I–III Climax Cutscene Production Reference

**Studio:** lifein6thgear STUDIOS
**Project:** R3ALN3T.EXE
**Doc type:** Reference / planning only — not part of the compiled game project
**Scope:** End-of-Act cutscenes for Act I ("The Rift"), Act II ("The Totem"), and
Act III ("The Mirror")
**Companion doc:** `R3ALN3T_EXE_Opening_Cutscene_Production.md` (Sequencer pipeline,
folder structure, reusable VFX/material patterns — referenced throughout below
instead of repeated)

> This file lives in `game_development/`, separate from the main UE5 project folder
> (`R3ALN3T_EXE/`). It is a planning and pipeline reference only. Nothing in here
> should be copied verbatim into project source.

> **Scope note:** Act IV has six branching endgame paths (Restoration, Ascension,
> Dominion, Collapse, Balance, MCADMIN) per the lore doc. That's a separate
> production problem — six cutscenes plus state-tracking logic, not just "more
> shots" — and is intentionally **not** covered here. It gets its own doc once
> Act I–III are built and the patterns below are proven.

> **Terminology note:** "PH" = Persona Host (formerly "PET"), consistent with the
> opening cutscene doc.

---

## 1. Narrative Source

Drawn from `THE_MYTHOS_ORIGIN_3026.txt`, lines 64–119 — "THE CORE QUEST: THE
SOURCE" — specifically the three "End of Act" beats:

- **End of Act I** (line 69-70): the rift discovery
- **End of Act II** (line 85-86): the Undernet Totem
- **End of Act III** (lines 89-107): the tutorial-zone room, the older-self
  message, the Navi's MCADMIN confession, and the mirror-self mini-boss

**Source-verification note:** the lore file contains a second, unrelated "Act
I/II/III" structure starting around line 1475 ("The Great Convergence," "The
Incident at Sector 8729," "The Rules of Engagement") — this is card/Tier-Type-
Element system lore (your NetP/Greek-ladder mechanics), not player-story climaxes,
and is **not** used here. The file also contains auto-generated JSON/JS campaign-
state scaffolding (~line 7208 onward) referencing "Fort_Campbell_Sub_Level_4" and a
literal countdown-timer choice prompt — this reads as tool-generated boilerplate,
not your authored lore, and was excluded from this doc for that reason.

---

## 2. End of Act I — "The Rift" (Days 1–30 close)

**Tone:** Quiet dread, not action. This is a reveal, not a fight — the mini-boss
(job's secret guardian) happens earlier in Act I; this scene is where the personal
job-story snaps into the cosmic conspiracy.

| Shot | Visual | VO / Dialogue |
|---|---|---|
| C1 | Player walking a familiar N3T corridor/sector (reuse existing level geometry) — camera trailing behind, normal pacing | Ambient N3T hum |
| C2 | Player turns a corner — hard stop. Wide reveal: a jagged white-edged tear in space, screaming static bleeding from its center, completely unlike any normal jack-in port | Sustained dissonant tone rises under scream-static |
| C3 | Push-in toward the rift — screen edges chromatic-aberrate/distort the closer the camera gets | Static intensifies, faint heartbeat-like pulse layered in |
| C4 | Cut to Navi — not afraid, staring with recognition | (silence — let the held stare read) |
| C5 | Close on Navi | Navi: "That's where I was born. Where we were *all* born." |
| C6 | Slow push back to the rift — scream-static briefly resolves into overlapping whispered voices, then back to noise | Navi (cont'd, V.O. over shot): "The first deletion. The first compression. The first... bug." |
| C7 | Hard cut to black. **ACT I COMPLETE** card, terminal-green (visual callback to the opening's "DAY 1. CYCLE 3026." card) | UI confirm chime — fades to Act II load |

### Production notes — Act I

- **Rift VFX**: build as a Niagara system with a noise-driven edge-erosion shader
  (white rim + interior static) — same "dissolve/erosion template" family suggested
  for the opening's A5 sector-deletion shots in the companion doc. Reuse, don't
  rebuild.
- **Whispered-voices beat (C6)**: if you don't have VO actors yet, this can be
  built from pitched/layered fragments of the Navi's own VO line, time-stretched —
  cheap and thematically appropriate (the rift is made of compressed people,
  including past Navis).
- **ACT I COMPLETE card**: reuse the exact Widget Blueprint + Sequencer Event Track
  pattern from the opening's A7 "DAY 1. CYCLE 3026." card (see companion doc §3.2,
  step 8) — don't build a new text-card system for this.

---

## 3. End of Act II — "The Totem" (Days 31–90 close)

**Tone:** Interrogative, heavy — your doc's own "Death Note-style critical
thinking" framing. No action music. Player asks, doesn't fight.

| Shot | Visual | VO / Dialogue |
|---|---|---|
| D1 | Player descending into Undernet space — darker, more corroded palette than standard N3T | Low ambient drone, distant data-corruption crackle |
| D2 | Wide reveal: the Undernet Totem — ancient-looking but unmistakably code-constructed, faint glitching faction symbols across its surface | Drone swells |
| D3 | Player approaches — no combat UI appears (deliberate contrast: every other Undernet encounter so far has been a fight) | (silence) |
| D4 | Totem "wakes" — surface ripples like a Navi sprite-glitch, but larger in scale | Deep, layered vocal texture — many voices, not one |
| D5 | Totem speaks — text on its surface AND as dialogue (reinforces "ancient terminal," not a person) | Totem: "You seek the Source. The Source is not a place. The Source is a choice." |
| D6 | Cut to a subtle tint shift on the totem's light, matching the player's dominant faction color (Celestial/Aegis/Dominion/Syndicate/Covenant/Free Grid) | Totem (cont'd): "In 3004, the first Navi was not deleted. She was sacrificed." |
| D7 | Glitch-flash — one frame shows a face, gone before it registers (parallel to the Navi's glitch-face moment from the opening Navi-reveal scene) | Sharp glitch sting |
| D8 | Totem's final line — direct address, turns the lore dump into a question for the player | Totem: "Her crime was asking why. What is your crime, seeker?" |
| D9 | Hold on player/Navi reaction, no answer given — question carries into Act III | (silence, hold 2–3 sec) |
| D10 | Fade to black → **ACT II COMPLETE** card | Fades to Act III load |

### Production notes — Act II

- **Faction-color tint (D6)**: cheapest possible way to make six different player
  paths feel acknowledged in one shared cutscene — drive the totem material's
  emissive color via a Material Parameter Collection read from the player's
  faction-standing variable, same MPC-driven approach used for the opening's
  ScreenGlitch material (companion doc §3.3, step 5). One reusable MPC pattern,
  two different uses.
- **Totem geometry**: should read as ancient *and* digital simultaneously —
  consider a stone/monument silhouette with a procedurally-animated code-texture
  material rather than literal carved stone, to keep the "this is the Undernet,
  everything here is still code" rule consistent.
- **Multi-voice totem VO**: same layered/pitched-voice approach as the Act I rift
  whispers — reuse the technique, different emotional register (this one should
  sound deliberate and ancient, not chaotic).

---

## 4. End of Act III — "The Mirror" (Days 91–180 close)

**Tone:** Identity-fracture, the emotional peak of the act per your own doc framing.
This is the largest of the three climaxes — three connected sub-sequences (Room →
Message → Mirror) rather than one scene. Slow the pacing hard going into the mirror
reveal; that's the emotional high point, not the fight that follows it.

### 4.1 Sub-sequence E — "The Room"

| Shot | Visual | VO / Dialogue |
|---|---|---|
| E1 | Player walks through a wall that wasn't there before — subtle dissolve VFX, deliberately undramatic (the world quietly admitting it lied, not a special-effects moment) | A single low tone, almost a held breath |
| E2 | Reveal: a room identical to the player's starting bedroom — same bed, same desk, same terminal placement | Dead silence — no ambient hum (deliberate absence, contrast with every other room in the game) |
| E3 | Push toward the terminal — it's already on, has clearly been on, waiting | Faint terminal hum only |

### 4.2 Sub-sequence F — "The Message"

| Shot | Visual | VO / Dialogue |
|---|---|---|
| F1 | Close on terminal screen — text typing itself, same typewriter SFX/Event-Track pattern as the opening's B5 | Terminal typing SFX |
| F2 | Full message displayed, camera holds — give the player time to actually read it | On-screen text: full "MESSAGE FROM: [YOUR NAME — BUT OLDER]" content (lines 93-103 of the lore doc) |
| F3 | Cut to Navi, who has been standing in the doorway, not entering | (silence) |
| F4 | Navi's confession, tighter close-up than any prior Navi dialogue shot | Navi: "Operator. I'm not her. I'm not the one who wrote that. But I'm made of her." |
| F5 | Hold close on Navi | Navi (cont'd): "The MCADMIN knows. The MCADMIN is one of us. The first one who didn't compress. The first one who survived deletion." |

### 4.3 Sub-sequence G — "The Mirror"

| Shot | Visual | VO / Dialogue |
|---|---|---|
| G1 | Far wall of the room glitches — a recognition effect, not a portal; the room itself rendering something new | Rising static |
| G2 | Reveal: a second Navi, identical build/rank to the player's own, standing where the wall was | Sharp glitch sting |
| G3 | Mirror-Navi doesn't attack first — looks at the player, almost sadly | (silence) |
| G4 | Single line, tragic register rather than villainous | Mirror-Navi: "In my timeline, you're the villain." |
| G5 | Cut to standard battle-intro transition (existing battle-transition VFX/UI) — hands off into the mini-boss fight | Battle-transition SFX |
| *(gameplay — mini-boss fight, not cutscene)* | | |
| G6 | Post-fight: hold on STEELKEY Fragment 1/3 icon appearing in inventory — first time the player physically has one on-screen | UI item-get chime, pitched lower/heavier than a normal pickup |
| G7 | Fade to black → **ACT III COMPLETE** card | Fades to Act IV load |

### Production notes — Act III

- **E1 "quiet dissolve" wall**: resist the urge to make this a flashy VFX moment —
  the room sub-sequence's entire effect depends on *underselling* the visual while
  the absence of ambient sound (E2) does the emotional work. This is a sound-design
  beat more than a VFX beat.
- **F2 message display**: this is the same diegetic-terminal-text pattern as the
  opening's B5 (Event Track → Blueprint function → typewriter widget). Pull the
  actual message string from a shared data asset, not hardcoded per-cutscene — this
  message is referenced again later in your story (per lore doc), so it should have
  one source of truth.
- **G2 mirror-Navi**: technically, this should be the *same* Navi
  Blueprint/skeletal mesh as the player's, with an alternate material/color variant
  applied — not a separate asset. Reinforces "this is you" rather than "this is an
  enemy design."
- **STEELKEY Fragment icon (G6)**: first UI appearance of an item type that recurs
  through Act IV per the lore doc (Fragment 1/3, implying 2 more later) — worth
  designing the icon now with room for a "2/3," "3/3" state change rather than
  treating it as a one-off.

---

## 5. Reuse summary across all three climaxes

| Pattern | First used | Reused in |
|---|---|---|
| Dissolve/erosion Niagara template | Opening A5 | Act I rift edges |
| ScreenGlitch MPC-driven material | Opening B4/B6/B7 | Act II totem tint, Act III wall glitch |
| Typewriter Event Track → Blueprint → widget | Opening B5 | Act III message (F2) |
| ACT-complete text card Widget + Event Track | Opening A7 | End of every Act in this doc |
| Layered/pitched VO for non-human voices | — (new here) | Act I rift whispers, Act II totem voice |

Building these as shared, parameterized systems once (per the companion doc's
build-order guidance) means each new Act climax is mostly **shot composition and
timing**, not new tooling — by Act III you should be assembling sequences faster
than Act I took.

---

*Last updated: 2026-06-29*
