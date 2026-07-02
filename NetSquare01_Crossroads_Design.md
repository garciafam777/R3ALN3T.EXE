# R3ALN3T.EXE — NetSquare 01: "The Crossroads" Design Document

**Status:** Draft v0.1
**Area Type:** Public Hub / Tutorial Area
**Faction Status:** Neutral — all factions coexist here uneasily
**Movement:** Free analog (WASD/stick), no grid snapping
**Camera:** Fixed-angle follow (Spring Arm, locked pitch ~-35°, no player rotation)

---

## 1. Concept Identity

The first NetSquare the player arrives in isn't a welcoming place.
It's **a truce, not a peace** — a node in the Net that no single faction has
been able to take and hold, so they've all quietly agreed to leave it alone.
Angel-type NetPs gather near the light-pillar on the north end. Demon-types
cluster near the corrupted data-wall on the south. Everyone in between is
either neutral, unaffiliated, or trying very hard not to make eye contact.

The player drops in with zero context, no allies, and a NetP that hasn't
proven itself yet. This space teaches the player how the world works before
a single line of tutorial dialogue — they can *see* the faction tension, *see*
the rank/tier visual hierarchy (high-tier Navis glow brighter, take up more
space, get wider berths from the crowd), and *feel* that they're the
lowest-power entity in the room.

**Working name:** "The Crossroads" — a name used by neutrals and lower-tier
NetPs. High-tier factions have their own names for it, which the player will
learn through NPC dialogue later.

---

## 2. Visual Language

### 2.1 Shared Design Elements (carry from battle screen)
The NetSquare must feel like the *same world* as the battle grid, not a
separate art direction. Specific elements that bridge the two:

- **Panel-grid floor** — the ground is literally constructed from the same
  beveled panel tile geometry used in battle, just arranged as walkable terrain
  instead of a combat grid. Same material system, same emissive edge-glow
  driven by the same parameter-based material (no separate asset needed).
  Floor tiles are larger (roughly 4x the battle tile size) and spaced with
  visible seams — walking across them should subliminally remind the player
  of the battle grid.
- **Edge-glow language** — every surface, object, and NPC in the space uses
  the same emissive rim/edge treatment established by the battle panels and
  chip UI. Nothing here has a matte-only surface — everything in cyberspace
  has some degree of data-light bleeding from its edges.
- **Dark glass / void-black as the base color** — like the battle screen's
  background, space outside the immediate hub geometry should read as deep
  digital void, not sky or ground. The hub floats.

### 2.2 Faction Visual Zones (how you read the tension without dialogue)
The neutral territory is still *marked* by invisible faction gravity — the
space itself has a north/south pull.

**North zone (Angel-adjacent):**
- Floor tiles tint toward Light element color (cool white-gold emissive)
- Architecture: tall, thin data-spires with faint halo rings floating above them
- NPC ambient behavior: orderly, spaced, facing the center
- Lighting: slightly brighter, more directional — feels structured

**Center zone (true neutral):**
- Floor tiles tint toward Null element color (flat silver-grey emissive) — the
  absence of faction color is itself a visual statement
- Architecture: a central elevated platform (slightly raised above the floor,
  same language as Smash Bros Battlefield's main platform) — this is where
  the player spawns in and where the main merchant/info-broker NPC stands
- Lighting: balanced, slightly cooler than the battle screen's purple bias —
  this is "normal" so the faction zones read as deviations from it

**South zone (Demon-adjacent):**
- Floor tiles tint toward Dark/Glitch element color (deep purple-black,
  slightly corrupted emissive flicker — not clean glow like Angel zone)
- Architecture: low, sprawling, irregular — data-walls with cracks and
  corruption artifacts visible in the geometry
- NPC ambient behavior: clustered, facing outward, territorial
- Lighting: darker, redder ambient — feels watched

### 2.3 Tier/Rank Visual Hierarchy (the tutorial the player reads without reading)
Higher-tier NetPs in the crowd should visibly register as more powerful
before the player interacts with them. Mechanism:
- **Scale**: higher Rank NPCs are slightly taller than base-rank ones
  (not cartoonishly, just enough to read at a glance — ~10-15% scale
  difference between Rank 1 and Rank 5)
- **Aura intensity**: the emissive glow on higher-Rank NPCs is brighter
  and has a more pronounced Niagara aura effect
- **Personal space**: crowd behavior logic gives higher-Rank NPCs a
  larger avoidance radius — lower-Rank NPCs unconsciously step aside

The player, arriving at Rank 1 with minimal glow and default scale, should
feel like the smallest thing in the room. This is intentional.

---

## 3. Layout (top-down schematic)

```
        ╔══════════════════════════════════╗
        ║   [Angel zone — light spires]    ║
        ║      NPC clusters (orderly)      ║
        ╠══════════════════════════════════╣
        ║  [Portal Arch — player spawn]    ║  ← Player arrives here, drops
        ║                                  ║    down onto the center platform
        ║      [CENTER PLATFORM]           ║
        ║   Merchant / Info-Broker NPC     ║
        ║   Bulletin board (chip quests)   ║
        ║   Access terminal (NetP status)  ║
        ║                                  ║
        ╠══════════════════════════════════╣
        ║  [Demon zone — corrupted walls]  ║
        ║      NPC clusters (territorial)  ║
        ╚══════════════════════════════════╝

Side corridors (east/west) lead to:
  East → Training Room (tutorial battle trigger)
  West → Data Market (chip shop, expandable later)
```

The whole space is intentionally small for a tutorial area — the player
shouldn't feel lost. One main platform, two faction-zone viewing areas
(visible but not deeply explorable at first), and two corridor exits that
create a clear left/right binary choice once the player is ready to leave
the center.

---

## 4. Key NPCs

### 4.1 The Broker (center platform)
The first NPC the player is funneled toward. Intentionally faction-ambiguous
in appearance — Null element, no visible faction insignia, extremely polished
in a way that suggests they've survived in this space a long time by being
useful to everyone. Gives the player their first chip, explains the gauge
system, references the faction tension without taking sides.

**Design note:** This NPC should be visually distinct from the crowd —
slightly taller, visibly higher Rank, but not intimidatingly so. The player
should feel like they're talking to someone who could help them, not someone
who's about to fight them.

### 4.2 Angel-zone gate NPC (north edge of center)
A low-to-mid-tier Angel-faction Navi who reluctantly talks to the player.
Delivers the "Angel factions don't love neutrals, but they hate Demons more,
so we tolerate this place" vibe. Seeds faction lore without exposition-dumping.

### 4.3 Demon-zone gate NPC (south edge of center)
A low-tier Demon-faction Navi who is more openly hostile but doesn't actually
fight — they're in a neutral zone and they know it. Their dialogue should
make the player slightly uncomfortable, which is correct — the Demon faction
is not the "evil team to beat," it's a genuinely threatening presence that
respects power and nothing else.

### 4.4 Crowd NPCs (ambient, 8-12 total)
Mix of factions, ranks, and elements. These exist primarily to:
- Visually populate the space so it reads as a real hub, not a dev test room
- Give the player something to observe that teaches the visual hierarchy
- Provide optional lore-flavor dialogue ("I heard the Seraphim are patrolling
  Grid-7 now," "Anyone else notice the Glitch signature near the south wall?")

---

## 5. Atmosphere / Audio Notes

- **Ambient sound:** digital hum baseline (same tonal family as the battle
  gauge fill sound), with occasional distant data-burst crackles from the
  south (Glitch/Dark zone ambient) vs clean harmonic tones from the north
- **Music:** a track that's neither triumphant nor threatening — neutral,
  slightly melancholic, with both the "holy" tonal language of Angel elements
  and the "corrupted" distortion of Demon elements audible but neither
  dominant. The tension should be in the music, not just the visuals.
- **Entry moment:** player arrives through a Portal Arch — a brief animation
  of data-materialization (similar to a NetP jacking in, which it literally
  is), then the camera pulls back to the fixed follow angle and the ambient
  sound fades up. First thing the player sees: the crowd. First thing they
  feel: they're being sized up.

---

## 6. Unreal Implementation Notes

### 6.1 Camera setup (Spring Arm)
```
ANetSquarePlayerController or BP_PlayerCharacter:
  USpringArmComponent:
    TargetArmLength = 1200.f
    RelativeRotation = (-35.f, 0.f, 0.f)  // Pitch -35 degrees, no yaw
    bUsePawnControlRotation = false         // FIXED angle, player can't rotate
    bInheritYaw = false
    bInheritPitch = false
    bInheritRoll = false
    bEnableCameraLag = true
    CameraLagSpeed = 8.f                   // Smooth follow, not snappy
```

### 6.2 Movement (CharacterMovementComponent)
Since this is free-roam (no grid), standard `UCharacterMovementComponent`
is appropriate here — unlike the battle screen's `UGridMoverComponent`,
which is specifically for discrete tile movement. The two movement
systems are intentionally separate: `UGridMoverComponent` for battle,
`UCharacterMovementComponent` for overworld. They live on different
Pawn classes, so there's no conflict.

```
MaxWalkSpeed = 450.f       // Feels snappy but not frantic
BrakingDecelerationWalking = 2048.f  // Responsive stops
RotationRate = (0.f, 540.f, 0.f)     // Quick facing-direction change
bUseControllerDesiredRotation = true
bOrientRotationToMovement = true
```

### 6.3 Floor tile reuse
The same `ABattleStagePanel` actor class (already built) can be used for
the hub floor tiles — just scaled up and placed in a flat arrangement rather
than the 8x4 battle grid formation. `ABattleGridManager` is NOT needed here
(that's battle-specific logic); just place `ABattleStagePanel` instances
directly in the level with scaled `TileSize`.

### 6.4 Level streaming
The NetSquare should be its own UE5 World Partition level, not embedded in
a parent level. This keeps it independently loadable, allows seamless
streaming as the player approaches from an outer area later, and prevents
the battle-screen levels (which are separate, self-contained levels spawned
when a fight triggers) from conflicting with hub geometry.

### 6.5 Battle trigger
When a player encounters a virus/opponent in the NetSquare, the battle
doesn't happen in-place (unlike some ARPGs) — the game transitions to a
separate battle level (matching original MMBN's design). A `UBoxComponent`
or random-encounter trigger on the virus NPC fires a `Level Transition`
to the `BattleLevel` map, passing the encounter data (opponent type, element,
rank) as travel parameters. The hub level stays loaded in the background
so the return transition is fast.

---

## 7. What Comes After (scope notes for next session)

- The east corridor's **Training Room** is the tutorial battle — first actual
  use of the `ABattleGridManager` + `UGridMoverComponent` system in a
  controlled, low-stakes encounter
- The west corridor's **Data Market** needs its own design pass (chip shop
  UI, how the Greek-letter code-share system affects what chips are sold
  together, etc.)
- The faction zones (north/south) are visitable but not deeply playable in
  tutorial — they get expanded in later story beats when the player has
  chosen (or been forced into) a faction alignment
- The Portal Arch spawn point doubles as the re-entry point when the player
  returns from a battle — needs a return-from-battle animation/state to
  differentiate "first arrival" from "just survived a fight"
