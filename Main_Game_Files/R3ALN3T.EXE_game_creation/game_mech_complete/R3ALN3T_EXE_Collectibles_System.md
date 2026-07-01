# R3ALN3T.EXE — Collectibles System Reference

**Studio:** lifein6thgear STUDIOS
**Project:** R3ALN3T.EXE
**Doc type:** Reference / planning only — not part of the compiled game project
**Scope:** All three collectible systems — Battle Chips (Greek-letter code/combo),
Lore Items (terminals, fragments, ghost data), and Economic Items (Z-trade, craft,
sell) — across both R34L and N3T world layers
**Companion docs:**
- `R3ALN3T_EXE_Opening_Cutscene_Production.md`
- `R3ALN3T_EXE_Act_Climax_Cutscenes.md`
- `R3ALN3T_EXE_Soul_State_System.md`

> This file lives in `game_development/`, separate from the main UE5 project folder.
> Nothing here should be copied verbatim into project source.

---

## SYSTEM 1 — BATTLE CHIPS (N3T World)

Battle chips are the core combat collectible. Found in the N3T layer, acquired
through grid battles, job-site drops, shops, and bugmatter crafting. Every chip
carries a **Greek-letter code** that determines combo eligibility in battle.

---

### 1.1 The Greek-Letter Code System (Full Alphabet)

The 24-letter Greek alphabet maps to 24 chip codes. Each chip is assigned exactly
one code letter at creation. In battle, the player selects chips from their folder
— chips sharing the same code letter can be selected consecutively to trigger
**Code Combos** (see §1.3).

| # | Letter | Name | Rarity Tier | Thematic Identity |
|---|---|---|---|---|
| 1 | Α | Alpha | Common | Entry-level, starter chips. Widely available. |
| 2 | Β | Beta | Common | Iterative variants of Alpha — slightly upgraded base attacks |
| 3 | Γ | Gamma | Common | Area/spread attacks, low damage ceiling |
| 4 | Δ | Delta | Uncommon | Defensive chips — shields, counters, terrain |
| 5 | Ε | Epsilon | Uncommon | Speed/movement chips — teleport, dash, panel shift |
| 6 | Ζ | Zeta | Uncommon | Utility chips — traps, status effects, field manipulation |
| 7 | Η | Eta | Uncommon | Recovery chips — HP restore, Navi charge, status clear |
| 8 | Θ | Theta | Rare | Elemental chips — fire, water, electric, wind |
| 9 | Ι | Iota | Rare | Chip-enhancement chips — boost next chip's damage/effect |
| 10 | Κ | Kappa | Rare | Summon chips — temporary field entities |
| 11 | Λ | Lambda | Rare | Stealth/deception chips — invisibility, decoys, mirror images |
| 12 | Μ | Mu | Rare | Heavy damage single-target chips |
| 13 | Ν | Nu | Rare | Chain/pierce chips — hit multiple enemies or panels |
| 14 | Ξ | Xi | Epic | Terrain-destruction chips — delete panels, create hazards |
| 15 | Ο | Omicron | Epic | Time-manipulation chips — slow, freeze, rewind cooldowns |
| 16 | Π | Pi | Epic | Economy chips — Z generation, M.A.N. disruption in battle |
| 17 | Ρ | Rho | Epic | Bugmatter chips — use compressed soul-energy as fuel |
| 18 | Σ | Sigma | Epic | Faction-aligned chips — effect varies by player's faction |
| 19 | Τ | Tau | Epic | Overload chips — massive damage, self-damage risk |
| 20 | Υ | Upsilon | Legendary | Void chips — erase attributes, delete buffs, null terrain |
| 21 | Φ | Phi | Legendary | Soul State chips — effect scales with player's morality band |
| 22 | Χ | Chi | Legendary | DarkN3T chips — unstable, high reward, corruption side effect |
| 23 | Ψ | Psi | Legendary | SkyNet chips — purification effects, anti-corruption, anti-Void |
| 24 | Ω | Omega | Mythic | Giga-class chips — one per folder max, screen-filling effects |

**Rarity distribution targets (for drop table design):**
- Common (Α–Γ): 45% of all drops
- Uncommon (Δ–Η): 25% of all drops
- Rare (Θ–Ν): 18% of all drops
- Epic (Ξ–Τ): 9% of all drops
- Legendary (Υ–Ψ): 2.5% of all drops
- Mythic (Ω): 0.5% of all drops — no random drops, story/craft only

---

### 1.2 Chip Folder Rules

Consistent with the MMBN design philosophy — the folder is the loadout, and folder
construction is a skill in itself.

| Rule | Value | Notes |
|---|---|---|
| Max folder size | 30 chips | Standard |
| Max copies of same chip | 3 | Prevents spam, rewards planning |
| Max Omega (Mythic) chips | 1 | One Giga-class per folder, period |
| Max Phi (Soul State) chips | 2 | Soul State chips are too unstable to stack past 2 |
| Max Chi (DarkN3T) chips | 3 | Standard limit but corruption risk stacks per use |
| Code restriction | None forced | Player free to mix codes, but combos reward discipline |

---

### 1.3 Code Combo System

When a player selects chips of the **same code letter consecutively** in the battle
select screen, a **Code Combo** activates on the second chip in the chain. The
combo effect is additive — it does not replace the second chip's base effect, it
enhances it.

**Combo chain rules:**
- Chain must be consecutive selections (Α → Α → Α is valid; Α → Β → Α is not)
- Maximum chain length: 5 chips of the same code
- Each additional chip in the chain adds a stack bonus (see table below)
- Breaking the chain (selecting a different code) resets the counter

**Combo stack bonuses:**

| Chain Length | Bonus |
|---|---|
| 2 chips | +20% damage / +1 tile effect radius |
| 3 chips | +40% damage / +2 tile radius / speed increase |
| 4 chips | +60% damage / +3 tile radius / status effect added |
| 5 chips (MAX) | +80% damage / full-screen effect / CODE BREAK triggered |

**CODE BREAK** (5-chip chain): a full-alphabet-length chain of 5 identical-code
chips triggers a visual signature event — the chip code letter appears large on
screen in its Greek glyph, and the final chip fires at 2x damage with a unique VFX.
Different code letters produce different CODE BREAK visual signatures.

**Special combo interactions:**
- **Α + Ω (Alpha into Omega)**: if a player has an Alpha chip immediately before
  their single Omega chip in the select order, the Omega chip gains +25% power —
  the "full-alphabet" bonus. Thematically: beginning and end, combined.
- **Φ + Ρ (Phi + Rho)**: Soul State chip into Bugmatter chip — effect of Phi chip
  doubles, but corruption side effect of Rho chip also doubles. High risk/reward
  combo for morally gray players.
- **Ψ + Χ (Psi + Chi)**: SkyNet chip into DarkN3T chip (or reverse) — the two
  chips cancel each other's secondary effects and deal a neutral, purely
  damage-focused burst. The "balance" combo — useful for Wanderer-path players.

---

### 1.4 Chip Acquisition — Four Routes

#### Route 1: Grid Battle Drops
- Standard enemies drop Alpha–Eta (Common/Uncommon)
- Mini-bosses drop Theta–Nu (Rare)
- Act climax bosses drop Xi–Tau (Epic) on first clear, random on repeat
- Omega chips are **never random drops** — story and craft only

#### Route 2: Job-World Physical Drops (R34L Layer)
Each career has unique chip drops tied to its job site — reinforces the "your job
shapes your kit" design of the career system:

| Career | R34L Drop Pool | Thematic reason |
|---|---|---|
| Miner | Ρ Rho (Bugmatter), Ξ Xi (Terrain destruction) | You work with raw compressed material |
| Electrician | Θ Theta (Elemental/electric), Ο Omicron (Time/signal) | Grid signals, voltage, timing |
| Security | Δ Delta (Defense/shields), Λ Lambda (Stealth) | Patrol, containment, deception |
| Medical | Η Eta (Recovery), Φ Phi (Soul State) | Healing, reading the patient's inner state |
| Broker | Π Pi (Economy/M.A.N.), Ι Iota (Enhancement/leverage) | Money manipulation, stacking advantages |
| Trucker | Ε Epsilon (Movement/speed), Κ Kappa (Summon/cargo) | Routes, hauling, calling in support |

Physical R34L drops appear as **scan events** — the player's PH device pings during
a job task, and a quick mini-game (30-second window) lets them extract the chip
data before it degrades. Miss the window, no drop.

#### Route 3: Shop Purchase (Z currency)
- **Tyrone's Shop** (mentioned in lore doc Act I): sells Alpha–Delta codes, rotates
  weekly inventory. Reliable source for folder-filling Common/Uncommon chips.
- **N3T Dominion Bank Branch** (Broker career connection): sells Π Pi economy chips
  and Σ Sigma faction chips at premium Z cost.
- **Undernet Syndicate Vendors** (unlocked after Act II faction alignment): sell
  Lambda, Chi, Tau — the aggressive, risky codes. No questions asked, inflated price.
- **Celestial Order Dispensary** (faction-aligned): sells Eta, Psi, Phi — recovery
  and soul-aligned codes only. Requires minimum Grounded Soul State band to access.
- **Black Market** (appears after Act I "The Lie" event, hidden per career path):
  sells near-Legendary chips at Z cost + corruption side effect on purchase.

#### Route 4: Bugmatter Crafting
Bugmatter (the compressed soul-energy substance central to the lore) is also a
crafting material. This is the only route to Omega (Mythic) chips and the only way
to craft specific Legendary codes on demand.

**Crafting table:**

| Output | Bugmatter Cost | Additional Material | Unlock Condition |
|---|---|---|---|
| Any Alpha–Gamma chip (player's choice) | 1 unit | None | Available from Day 1 |
| Any Theta–Nu chip (random in category) | 3 units | 1 chip of matching code | Act I complete |
| Any Xi–Tau chip (random in category) | 6 units | 2 chips of matching code + 500 Z | Act II complete |
| Specific Legendary (Υ/Φ/Χ/Ψ) chip | 10 units | 3 chips of matching code + 2000 Z | Act III complete |
| Omega chip (unique, story-named) | 15 units | 1 Legendary of any code + STEELKEY Fragment | Act IV entry only |

**Bugmatter acquisition:** found in Miner job-site drops, dropped rarely by
DarkN3T enemies in N3T layer, and awarded as quest rewards for certain faction
tasks. Spending bugmatter on crafting has a **minor Soul State effect** — you are
literally burning compressed soul-energy to make weapons. Small push toward evil
(+2 internal) per craft unless the player's Navi speaks a ritual acknowledgment
line first (a dialogue option that appears before confirming the craft, costing
nothing but time).

---

## SYSTEM 2 — LORE ITEMS (Both Worlds)

Lore collectibles are non-combat items that expand the world, reveal backstory, and
in some cases unlock hidden content or affect the Soul State scale. They cannot be
equipped in battle folders and cannot be sold.

---

### 2.1 Lore Item Types

#### Terminal Messages (R34L + N3T)
Fragments of the broader MCADMIN conspiracy. Found on glitching terminals throughout
both worlds. Each message has a timestamp from 3004–3026 and a sender code.

| Sub-type | Where found | Content |
|---|---|---|
| MCADMIN Dispatches | Hidden terminals, usually behind job-site anomalies | Direct messages from MCADMIN — escalating urgency as Acts progress |
| Ghost Transmissions | Corrupted N3T sectors, near DarkN3T zones | Fragmented messages from deleted/compressed Navis — emotionally heavy |
| SkyNet Audit Logs | Purified sectors, Celestial Order zones | Cold, bureaucratic records of "purification events" — names, timestamps, chip totals |
| Dominion Ledger Fragments | N3T Dominion bank interiors, broker job site | Financial records that don't add up — economic evidence of the original 3004 crime |

Collecting all messages in a category unlocks a **Cipher Log** — a decoded summary
that reveals one piece of the larger MCADMIN identity mystery. There are 4 Cipher
Logs total (one per message type), each unlocking a unique N3T location.

#### Source Fragments
The key lore collectible — referenced directly in the core quest (your Navi carries
one, the STEELKEY Fragments point to Source locations). Found by following the
conspiracy trail across careers and Acts.

| Fragment Type | Count | Effect on collection |
|---|---|---|
| Source Fragment (generic) | Unlimited | Sell for Z, donate to factions for rep, or hold for crafting |
| Named Source Fragments | 12 (2 per career path) | Unlock career-specific lore entry + Soul State shift (+/- 3 depending on what player does with it) |
| STEELKEY Fragment 1/3 | 1 | Awarded end of Act III (story-locked) — required for Omega chip craft |
| STEELKEY Fragment 2/3 | 1 | Act IV discovery — unlocks final Source location |
| STEELKEY Fragment 3/3 | 1 | Final pre-ending item — triggers the MCADMIN confrontation |

#### Ghost Data
Residual personality traces of deleted Navis, found drifting in N3T sectors as
faint luminescent particles. Collecting ghost data is the closest thing R3ALN3T.EXE
has to a "story collectible that makes you feel bad" — you are gathering the remains
of people.

- 108 Ghost Data total across the full game world
- Each one plays a 3–5 second audio fragment: a voice, a name, a last thought
- Collecting 10 → unlocks Navi dialogue acknowledging what they're hearing
- Collecting 54 (half) → unlocks the Ghost Ward location (ties into Medical career
  good ending even for non-Medical players — anyone can find it)
- Collecting all 108 → unlocks a hidden terminal with a message from the first
  deleted Navi ("Her name was... [CORRUPTED]" from the Undernet Totem scene — this
  is where her name is finally revealed)
- Ghost Data collection has **no Soul State effect by itself** — it's morally
  neutral to gather. What the player *does* with the Ghost Data (donate to
  Celestial Order for purification bounty, feed to DarkN3T for bugmatter,
  or simply keep them) moves the scale.

---

## SYSTEM 3 — ECONOMIC ITEMS (R34L World Primary)

Economic items are the material layer of the game — things you find, earn, buy,
trade, and sometimes lose. They live primarily in the R34L world (job sites, shops,
housing) but can cross into N3T as chip-craft components.

---

### 3.1 Economic Item Categories

#### Job Materials
Each career generates unique material drops during work shifts. These are the
primary Z-generation collectible for non-combat players.

| Career | Material | Base Z value | Secondary use |
|---|---|---|---|
| Miner | Raw Compacite | 50 Z | Bugmatter crafting component |
| Electrician | Grid Filament | 35 Z | Theta/Omicron chip crafting component |
| Security | Null Badge | 20 Z | Grants temporary authority in one NPC interaction |
| Medical | Biometric Key | 45 Z | Opens Ghost Ward doors, medical terminal access |
| Broker | Ledger Token | 60 Z | Used in Pi chip crafting, faction rep purchase |
| Trucker | Manifest Seal | 30 Z | Proves cargo legitimacy — avoids security stops |

#### Contraband
Items that are illegal to carry in certain zones or under certain faction
jurisdictions. High Z value, high risk. Contraband is flagged by the M.A.N.
wallet scanner if the player enters a security zone while carrying it.

| Item | Legal status | Z value | Risk |
|---|---|---|---|
| Unregistered Bugmatter | Illegal everywhere except Abyssal Covenant zones | 200 Z | Immediate arrest if scanned |
| Ghost Data (bottled) | Illegal in SkyNet and Celestial Order zones | 150 Z | Corruption +5 if confiscated |
| Null Identity Card | Illegal everywhere | 500 Z | Criminal record flag, locks certain faction doors |
| DarkN3T Access Key | Illegal in Aegis Concord and Celestial Order zones | 350 Z | DarkN3T rep gain, Syndicate attention |

#### Housing & Room Items (R34L)
Collectible objects for the player's R34L room — the customizable starting space
referenced in the lore doc. These have no combat value but affect:
- **Ambient dialogue** from the Navi (they comment on room contents)
- **NPC visit behavior** (characters like Tyrone, Lex, Akai, Yani react to the room)
- **Soul State minor modifiers** (a room full of DarkN3T art pushes +1 internal per
  day; a room with Celestial Order iconography pushes -1 per day)

| Category | Examples | Source |
|---|---|---|
| Technology | PH upgrade shells, terminal skins, holographic displays | Shops, job rewards |
| Faction décor | Faction flags, insignia, propaganda posters | Faction vendors (locked by rep) |
| Lore artifacts | Framed terminal messages, ghost data display cases | Crafted from lore items |
| Contraband décor | DarkN3T murals, unregistered identity displays | Black market, Abyssal Covenant |
| Navi mementos | Objects tied to Navi's past (revealed through Ghost Data collection) | Unlocked via Ghost Data milestones |

---

## 4. Cross-System Interactions

The three systems are designed to create decisions, not just accumulation. Key
interaction points:

| Situation | Systems involved | Decision |
|---|---|---|
| Found a Named Source Fragment | Lore + Economic | Sell for Z / donate for faction rep / hold for Omega craft |
| Carrying Unregistered Bugmatter into a job site | Economic + Battle | Get scanned and lose it, or spend a Lambda (stealth) chip to pass |
| Ghost Data collected: 108/108 | Lore + Soul State | What do you do with them? The final Ghost Data location reveals a choice |
| Bugmatter crafting an Omega chip | Battle + Lore + Soul State | Costs STEELKEY Fragment 1/3, burns 15 units of compressed souls, +6 internal unless Navi ritual performed |
| Room décor daily Soul State drift | Economic + Soul State | Passive — environment shapes who you become without active choice |
| Phi (Soul State) chip effectiveness | Battle + Soul State | Phi chip damage = (SoulStateInternal - 50) × 4, meaning good players deal negative/healing Phi damage and evil players deal maximum Phi damage — mechanically rewards committing to a pole |

---

## 5. Data Structure Sketch

```cpp
// Collectible item base (all three systems inherit from this)
USTRUCT(BlueprintType)
struct FCollectibleItem
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemID;                    // Unique ID, e.g. "CHIP_ALPHA_001", "LORE_GHOST_047"

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECollectibleType Type;           // ECollectibleType: BattleChip, LoreItem, EconomicItem

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGreekCode ChipCode;             // Only relevant for BattleChip type

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ZValue;                    // 0 for lore items (unsellable)

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SoulStateDelta;            // +/- applied on acquisition or use (0 = neutral)

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsContraband;              // Flagged by M.A.N. scanner in security zones

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText FlavorText;                // Lore description shown in inventory
};

// Greek code enum (24 letters)
UENUM(BlueprintType)
enum class EGreekCode : uint8
{
    Alpha, Beta, Gamma, Delta, Epsilon, Zeta, Eta, Theta,
    Iota, Kappa, Lambda, Mu, Nu, Xi, Omicron, Pi, Rho,
    Sigma, Tau, Upsilon, Phi, Chi, Psi, Omega,
    None    // For non-chip collectibles
};

// Combo chain tracker (lives on the BattleComponent or chip-select subsystem)
USTRUCT(BlueprintType)
struct FComboChainState
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    EGreekCode ActiveCode;           // Current chain's code letter

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32 ChainLength;               // 1–5, resets on code break

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float DamageMultiplier;          // Derived from ChainLength per §1.3 table

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bCodeBreakReady;            // True when ChainLength == 5
};
```

> As with the Soul State component: verify these structs don't already exist in
> your `Source/Private/Gameplay/` or `Source/Public/` headers before adding.
> Share current file contents before any code is written or modified in-engine.

---

## 6. Folder locations for collectible assets

```
Content/
  Collectibles/
    BattleChips/
      Alpha/          <- one folder per Greek letter
      Beta/
      ...
      Omega/
      DA_ChipDatabase.uasset       <- Data Asset: master chip registry
      DT_ChipDropTable.uasset      <- Data Table: drop weights per enemy/zone
    LoreItems/
      TerminalMessages/
      SourceFragments/
      GhostData/
      DA_LoreRegistry.uasset
    EconomicItems/
      JobMaterials/
      Contraband/
      RoomItems/
      DA_EconomicRegistry.uasset
  Crafting/
    DT_BugmatterRecipes.uasset     <- Data Table: all crafting recipes
    BP_CraftingSubsystem.uasset    <- Blueprint: crafting logic, soul state delta on craft
```

---

## 7. Reuse notes

- **MPC_SoulState** (from Soul State doc): Phi chip damage calculation reads
  directly from this MPC float — no separate query needed.
- **DT_DialogueBySoulState** (from Soul State doc): Navi's bugmatter-craft ritual
  acknowledgment dialogue is a row in this table, keyed to whatever band the player
  is in when they open the crafting menu.
- **Typewriter Event Track pattern** (from Opening Cutscene doc): Terminal Message
  lore items display via the same widget/Event Track system as the MCADMIN message
  in the opening — consistent UX, reused tooling.
- **Ghost Ward location** (from Medical career good ending in Soul State doc):
  unlocked at 54 Ghost Data collected regardless of career — the good ending for
  Medical is the *canonical* Ghost Ward story, but all players can find the
  location through collectibles.

---

*Last updated: 2026-06-29*
