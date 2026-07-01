# R3ALN3T.EXE — Soul State System (Morality Axis) Reference

**Studio:** lifein6thgear STUDIOS
**Project:** R3ALN3T.EXE
**Doc type:** Reference / planning only — not part of the compiled game project
**Scope:** Soul State morality scale, aura expression, personality/dialogue tiers,
Navi mirroring, and 12 career-path dual endings
**Companion docs:**
- `R3ALN3T_EXE_Opening_Cutscene_Production.md` (Sequencer pipeline)
- `R3ALN3T_EXE_Act_Climax_Cutscenes.md` (Act I–III cutscene shot lists)

> This file lives in `game_development/`, separate from the main UE5 project folder.
> Nothing here should be copied verbatim into project source.

---

## 1. The Scale

The Soul State is tracked internally as an integer from **0 to 100**, displayed to
the player as **-01 to 01**. The display label is a design choice — it keeps the
number small and symbolic rather than feeling like a typical "karma bar."

```
Internal:   0 ─────────────── 50 ─────────────── 100
Display:   -01 ───────────────  · ───────────────  01
           PURE GOOD          GRAY           ULTRA EVIL
```

### Threshold bands

| Internal | Display Range | Band Name | Aura Color | General State |
|---|---|---|---|---|
| 0–10 | -01.0 to -0.8 | Radiant | White/gold pulse | Actively selfless, empathetic, protective |
| 11–25 | -0.8 to -0.5 | Grounded | Soft blue-white glow | Principled, cautious, measured |
| 26–40 | -0.5 to -0.2 | Weathered | Dim warm amber | Pragmatic, carries weight, still mostly good |
| 41–59 | -0.2 to +0.2 | Gray | No aura — flat/neutral | Unreadable, transactional, morally ambiguous |
| 60–74 | +0.2 to +0.5 | Strained | Faint violet flicker | Rationalized selfishness, sharp edges, tension |
| 75–89 | +0.5 to +0.8 | Fractured | Dark violet/red static | Hostile, aggressive, openly self-serving |
| 90–100 | +0.8 to +01 | Corrupted | Deep red/black aura, distortion VFX | Nihilistic, cruel, language fully degrades |

### What moves the scale

**Toward good (decreases internal value):**
- Helping NPCs without payment or reward
- Reporting injustice when it costs you something
- Refusing M.A.N. bribes from faction enforcers
- Protecting Navis from purification when you don't have to
- Sharing Source Fragments instead of selling them

**Toward evil (increases internal value):**
- Exploiting job discoveries for personal M.A.N. gain
- Ignoring NPCs in distress during missions
- Feeding bugmatter to DarkN3T voluntarily
- Purging Navis for SkyNet bounty (even if legal)
- Corruption-level rising from DarkN3T exposure
- Accepting Abyssal Covenant contracts

**Gray-zone (moves scale based on *intent*, not action):**
- Joining a faction (neutral — *how* you use faction standing is what moves it)
- Winning battles (neutral — *who* you target moves it)
- Earning Z (neutral — *how* you spend it moves it)

---

## 2. Aura System (Visual Expression)

The aura is not a UI element — it is a **material/post-process effect applied
directly to the player Avatar and Navi** that intensifies across the seven bands.
It should be visible in all environments, not just in cutscenes.

### Technical approach

- Drive via a **Material Parameter Collection (MPC_SoulState)** with a single
  float parameter `SoulState_Normal` (0.0–1.0, normalized from the 0–100 internal
  value).
- The player Avatar material and the Navi material both read from this same MPC —
  this is what makes them mirror each other automatically without separate logic.
- Layer the aura as a **post-process material on a sphere component** attached to
  the Avatar root — not baked into the Avatar mesh material itself. Keeps it
  swappable and avoids material slot conflicts.
- Aura intensity, color, and distortion noise are all driven by the same
  `SoulState_Normal` float via lerp curves in the material graph — one parameter,
  seven visual states.

### Per-band aura spec

| Band | Color (hex) | Effect |
|---|---|---|
| Radiant | #FFE8A3 → #FFFFFF | Soft radial pulse, slow rhythm, clean edges |
| Grounded | #A3C4FF | Steady glow, no pulse, minimal particle |
| Weathered | #FFB347 | Dim, slightly flickering, faint dust particles |
| Gray | none | Aura mesh opacity = 0, flat Avatar render |
| Strained | #C39BD3 | Faint flicker, occasional static burst |
| Fractured | #8B0000 + violet | Erratic pulse, visible noise distortion, edge fraying |
| Corrupted | #1A0000 + deep red | Heavy distortion, black smoke Niagara, screen-edge vignette darkens |

### Navi mirroring

The Navi shares `MPC_SoulState` — same parameter, same material read. The Navi's
aura should render slightly *smaller* in radius than the Avatar's (about 60% scale)
and with a half-second lag on parameter changes, so it feels like the Navi is
*reacting* to the player rather than changing simultaneously. Implement the lag via
a Timeline in the Navi Blueprint that interpolates toward the current MPC value over
0.5 seconds rather than snapping.

---

## 3. Personality & Dialogue Expression

This is the most important system in the Soul State — the aura shows state, but
the *dialogue and behavior* is what makes it feel real. The personality shifts
across all NPC interactions, optional conversations, and especially cutscene
delivery.

### Dialogue tone tiers

| Band | Player tone | Navi tone | Examples |
|---|---|---|---|
| Radiant | Warm, sacrificial, empathetic. Calls NPCs by name. Asks before acting. | Gentle, devoted, occasionally worried for the player | "You doing alright? You don't have to keep doing this for me." / Navi: "I'll follow you anywhere, Operator. Just... be careful." |
| Grounded | Measured, principled. Disagrees calmly. Weighs consequences aloud. | Balanced, thoughtful, sometimes pushes back gently | "That's not right and you know it." / Navi: "I'm not sure this is the call." |
| Weathered | Pragmatic, tired. Less emotional language. Gets the job done, questions whether it matters. | Quieter, watchful, less frequent unprompted speech | "Fine. What's it pay?" / Navi: "..." (long silence before responding) |
| Gray | Flat. Transactional. No warmth, no hostility. Information only. | Neutral, professional, clipped responses | "Understood." / Navi: "Acknowledged." |
| Strained | Short-tempered, impatient. Starts cutting people off. Rationalizes harm. | Terse, slightly defensive of the player's choices | "You're wasting my time." / Navi: "They had it coming." |
| Fractured | Openly aggressive. Belittles NPCs. Profanity begins appearing. Threats without follow-through. | Agitated, starts echoing the player's language | "Get out of my way before I make you." / Navi: "Yeah, to hell with them." |
| Corrupted | Fully degraded. Profanity, cruelty, nihilism. Talks about people as obstacles or resources. Unprompted threats. | Mirrors corrupted player fully — speaks with contempt, uses profanity, occasionally sounds afraid of what they've become | "I don't care. Delete it." / Navi: "...we're not good people anymore, are we." |

### Implementation approach

- Store dialogue lines in a **Data Table (DT_DialogueBySoulState)** with a
  `SoulStateBand` enum column — not hardcoded in Blueprint event graphs.
- When any conversation triggers, query the player's current band first, then pull
  from the matching row. This way adding new lines or adjusting thresholds never
  requires touching individual Blueprint nodes.
- **Navi's "afraid of what they've become" line** at the Corrupted tier is
  important — it gives the player a mirror moment and keeps the Navi from becoming
  a villain sidekick. The Navi mirrors the player's corruption but retains enough
  self-awareness to notice it. This is consistent with the lore doc's
  Navi-as-compressed-soul concept: they can degrade but they can't fully lose the
  echoes of who they were.

---

## 4. Career Paths × Soul State → 12 Endings

Each of the 6 career paths (from the "First Day, First Lie" job selection in the
opening) has a **good pole ending** (internal 0–40) and an **evil pole ending**
(internal 60–100). Reaching the Gray band (41–59) at the Act IV decision point
presents the player with a final forced choice rather than an automatic outcome —
the last moment to commit to a pole.

### Scale lock thresholds

| Internal value at Act IV entry | Outcome |
|---|---|
| 0–40 | Good ending automatically unlocks for that career |
| 41–59 | Gray zone — final forced choice scene presented |
| 60–100 | Evil ending automatically unlocks for that career |

### The 12 endings

---

#### MINER

**Good — "The Reclamation"**
The player exposes the bone-fragment truth: the "gold" in the Thoroughbred Acres
caves is compressed Navi remains. Instead of selling the discovery, they bring it
to the public — or what passes for public in a world with a controlled M.A.N.
ledger. Mining operations shut down. Z economy tightens. But the Navis compressed
into bugmatter begin to *stir*. Fragments of them surface in random N3T sectors
as ghost-data — confused, grateful, fading. The player's own Navi says quietly:
"They know someone finally listened."

**Evil — "The Seam"**
The player uses the bone-fragment discovery as leverage. Corner the supply. Become
the exclusive broker of a substance everyone needs and nobody admits is sentient.
The mining operation expands under the player's control. Other miners who ask too
many questions disappear. Bugmatter production accelerates. The N3T gets faster,
richer, more powerful — and the screaming in the rift gets louder. The Navi stops
talking about the compressed. The Navi starts talking about yield.

---

#### ELECTRICIAN

**Good — "The Signal Traced"**
The "electrical virus" was a SkyNet signal to someone. The player traces it to
its recipient — a hidden node running an unauthorized countermeasure against
SkyNet's purification sweeps. Instead of reporting or selling the intel, the
player protects the node and its operator: an old-generation Sysadmin who has
been quietly saving Navis from deletion for years. The grid loses efficiency.
SkyNet notices. The Sysadmin has to run. But the countermeasure's code survives,
copied into the player's Navi — "a gift," the Sysadmin says, "from everyone
you'll never know you saved."

**Evil — "The Relay"**
The player sells the signal's origin to SkyNet. Full root-access bounty, paid in
M.A.N. directly to the player's wallet — no transaction record, no timestamp, no
sender. Clean. The hidden node is purified. Its operator is never found. The grid
runs cleaner. SkyNet's next purge sweep is 40% more efficient. The player gets
a private commendation: a SkyNet-tier chip, unnamed, unregistered. The Navi asks
once where the signal led. The player tells them it was a dead end. The Navi
doesn't ask again.

---

#### SECURITY

**Good — "The Unregistered"**
The shoplifter with no M.A.N. wallet, no identity hash, no system record — but
breathing — is not a glitch. They are the first of many: people who slipped
through the Neural Migration, whose consciousness was never assigned an Avatar,
who exist in R34L with no legal identity in either world. The player hides them
instead of reporting. A network of the unregistered grows — slow, fragile,
human. No M.A.N., no rank, no chips. Just people. The Navi calls them "the
ones the system forgot to compress."

**Evil — "The Sweep"**
The player reports the unregistered to the N3T Dominion's identity-enforcement
division. The reward is a bounty license: legal authority to scan and report
any entity without a valid M.A.N. hash. Profitable. Scalable. There are more
unregistered than anyone officially admits. The player builds a second income
stream on the margin between existence and erasure. The Navi learns not to
look directly at the people they pass on patrol.

---

#### MEDICAL

**Good — "The Ghost Ward"**
The patient in Bed 7 — no R34L body, only a N3T presence, bleeding in both
worlds — is not the only one. The Ghost Ward becomes real: a hidden medical
practice for entities that fall outside the standard Avatar/Navi binary.
Patients who exist in the gap. The player funds it with personal Z, covers
it with falsified discharge records, and staffs it with doctors who ask no
questions because they've seen the same thing. It will be raided eventually.
But it will have saved people that no official system ever acknowledged existed.

**Evil — "The Harvest"**
The Bed 7 patient's dual-world bleed is a phenomenon worth studying — and
selling. The player documents it. Sells the case file to a N3T Dominion
research division with no public disclosure requirements. The research produces
a new class of chip: one that draws power from the bleed state, from the pain
of an entity caught between worlds. High performance. High demand. The patient
in Bed 7 is never discharged. The Navi stops going near the medical wing.

---

#### BROKER

**Good — "The Timestamp"**
The M.A.N. ledger transaction with no sender, no receiver, no amount — only
a timestamp reading 3004, Day 0 — points to the moment bugmatter was first
used as economic fuel. The player exposes it: not to the press (there is no
press), but to the other brokers, the people who run the ledger's daily
operations and have always quietly known something was wrong with the
foundation. A reform movement starts inside the N3T Dominion itself — slow,
compromised, probably doomed — but the timestamp is now public record.
Immutable. Cryptographically anchored. The truth is in the chain.

**Evil — "The Ledger"**
The player uses the timestamp as a blackmail instrument against the N3T
Dominion's senior architects — the ones who built the original 3004
transaction into the chain and have been hoping no one would find the
key. The payout is enormous. The player gains a seat on the Dominion's
shadow board. The timestamp stays buried. The ledger stays clean. The
Navi handles the routing. The Navi is very good at routing now.

---

#### TRUCKER

**Good — "The Manifest"**
The cargo that the scanner said was organic, the N3T mirror said not to
open — the player opens it anyway, alone, between stops on the Bluegrass
Highway. Inside: dormant Navis. Not deleted, not compressed. Stored.
Someone has been running an underground railroad for Navis flagged for
SkyNet purification, using freight routes as cover. The player joins
the operation. The routes get longer. The cargo gets heavier. The
Bluegrass Highway becomes the only road in T3N3SS33 where something
is actually being saved.

**Evil — "The Route"**
The player delivers the cargo without opening it — takes the payment,
asks no questions, runs the route again. And again. The operation
expands. The player becomes the most reliable hauler in the network
because they are the most incurious. Eventually they learn what the
cargo is. By then the rate is too good to stop. The Navi handles
navigation. The Navi is very good at not asking where they're going.

---

## 5. The Gray Zone Final Choice (Internal 41–59 at Act IV entry)

Players in the Gray band at the start of Act IV are presented with a single
cutscene before the ending locks. No combat. No faction check. Just the player,
the Navi, and a terminal in the room from Act III — the one that's always been on.

The terminal displays one line:

```
> WHO ARE YOU, OPERATOR?
```

Two choices:

- **"I'm still good."** → Soul State snaps to 40 (Weathered tier, good pole).
  The Navi exhales. The aura shifts to amber. The career's good ending triggers.

- **"I don't know anymore."** → Soul State snaps to 60 (Strained tier, evil pole).
  The Navi goes quiet. The aura shifts to violet. The career's evil ending triggers.

The Navi does not speak during this scene except to react after the choice is made.
The reaction should be short — one line, no more — delivered differently depending
on the Navi's accumulated Soul State history over the full playthrough.

---

## 6. C++ / Blueprint implementation sketch

### Soul State data structure

```cpp
// In a component class: USoulStateComponent (attach to player Avatar Blueprint)

UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Soul State")
int32 SoulStateInternal; // 0–100, never exposed raw to UI

UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Soul State")
float SoulStateDisplay; // remapped -1.0 to 1.0, used for UI display as "-01 to 01"

UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Soul State")
ESoulStateBand CurrentBand; // enum: Radiant/Grounded/Weathered/Gray/Strained/Fractured/Corrupted

// Called whenever SoulStateInternal changes
void RecalculateBand();

// Pushes new value to MPC_SoulState so aura and Navi update immediately
void UpdateMPC();
```

```cpp
// ESoulStateBand enum (in a shared header, e.g. R3ALN3TTypes.h)

UENUM(BlueprintType)
enum class ESoulStateBand : uint8
{
    Radiant     UMETA(DisplayName = "Radiant"),
    Grounded    UMETA(DisplayName = "Grounded"),
    Weathered   UMETA(DisplayName = "Weathered"),
    Gray        UMETA(DisplayName = "Gray"),
    Strained    UMETA(DisplayName = "Strained"),
    Fractured   UMETA(DisplayName = "Fractured"),
    Corrupted   UMETA(DisplayName = "Corrupted")
};
```

### Scale remapping (RecalculateBand logic)

```cpp
void USoulStateComponent::RecalculateBand()
{
    // Remap 0–100 to -1.0 to 1.0 for display
    SoulStateDisplay = ((float)SoulStateInternal / 50.0f) - 1.0f;

    // Band assignment
    if      (SoulStateInternal <= 10)  CurrentBand = ESoulStateBand::Radiant;
    else if (SoulStateInternal <= 25)  CurrentBand = ESoulStateBand::Grounded;
    else if (SoulStateInternal <= 40)  CurrentBand = ESoulStateBand::Weathered;
    else if (SoulStateInternal <= 59)  CurrentBand = ESoulStateBand::Gray;
    else if (SoulStateInternal <= 74)  CurrentBand = ESoulStateBand::Strained;
    else if (SoulStateInternal <= 89)  CurrentBand = ESoulStateBand::Fractured;
    else                               CurrentBand = ESoulStateBand::Corrupted;

    UpdateMPC();
}
```

```cpp
void USoulStateComponent::UpdateMPC()
{
    // Push normalized float to MPC so aura material and Navi material both update
    UMaterialParameterCollectionInstance* MPCInst =
        GetWorld()->GetParameterCollectionInstance(MPC_SoulState);

    if (MPCInst)
    {
        float Normalized = (float)SoulStateInternal / 100.0f;
        MPCInst->SetScalarParameterValue(FName("SoulState_Normal"), Normalized);
    }
}
```

> Note: expose `MPC_SoulState` as a `UPROPERTY` on the component so it can be
> assigned in Blueprint without hardcoding a path. Paste this code only after
> verifying the current `USoulStateComponent` doesn't already exist in your
> `Source/Private/Gameplay/` directory — if it does, share the current file before
> modifying.

---

## 7. Reuse notes

- **MPC_SoulState** is shared with the aura material, the Navi mirror material, and
  the totem faction-tint from the Act II cutscene doc (§4, D6). It's the single most
  reused parameter in the project — build it first, build it right.
- **DT_DialogueBySoulState** feeds every NPC interaction, every optional
  conversation, and every cutscene dialogue line that has a tone-variant. Design the
  Data Table schema before writing any dialogue content so lines don't have to be
  restructured later.
- The **Gray Zone final choice terminal** in §5 reuses the Act III typewriter
  Event Track pattern — same widget, same Blueprint function, one new string.

---

*Last updated: 2026-06-29*
