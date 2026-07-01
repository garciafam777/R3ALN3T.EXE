# R3ALN3T.EXE — Player NetP Character Creation: Design Draft

**Status:** Draft v0.2 — all 5 open questions from v0.1 resolved with confirmed data. Ready to move into technical (C++/Mutable) implementation.

---

## 1. Scope

This system applies **only to player-created NetPs**. The 3 premade MC Admin characters (Trinity Ascendant + 2 others) are fixed, hand-authored Skeletal Meshes with no runtime customization — they are out of scope for this document.

Player character creation produces a NetP defined by:
- **Tier** (visual/power category)
- **Rank** (progression level within Tier)
- **Element** (one of 10, see Section 3)
- **Category 4: Tactical Performance Attributes (TPA)** — HP, ATK, DEF, SPD
- **Category 5: Memory Allocation Limits (MAL)** — Memory Capacity, Slot Availability, Bandwidth Throttle Rate

These 5 categories drive both **stat/mechanical identity** (battle stats, chip access) and **visual identity** (modular part availability, color/material theming on the battle grid — tying back into `ABattleGridManager`'s `TierColor` system already built).

---

## 2. Customization Model: Modular Parts

Player NetPs are built from **swappable modular parts**, not sliders/morphs. This maps directly onto Unreal's **Customizable Object (Mutable)** plugin, already present in the project.

### 2.1 Part Categories — Confirmed 6-Slot Framework

| Slot | Function | Mechanical Effect |
|---|---|---|
| **Core** (Processor/Frame) | Baseline chassis | Dictates HP/DEF multipliers (Category 4) |
| **Left Arm** (Weapon System/Buster) | Primary offense | Houses ranged/melee offensive code |
| **Right Arm** (Utility/Shield/Aux Weapon) | Defense/utility | Block rates, secondary tactical tools |
| **Legs** (Locomotion/Drive System) | Movement | Grid movement patterns, speed, tile-hazard immunity |
| **Head** (Sensors/OS Targeter) | Targeting | Critical hit chance, lock-on range, status resistance |
| **Expansion** (Auxiliary Subroutine/Mod Chip) | Free utility | Passive perks, custom script overrides |

All 6 slots are always present on every NetNavi chassis — none are Tier-gated into existence; what's gated is *which parts* can be installed into each slot (see 2.2).

Each slot's part directly affects gameplay stats, not just cosmetics — this is a meaningful difference from a purely cosmetic customizer. The `UCustomizableObject` graph needs parameter outputs feeding into the NetP's actual stat block (likely a future `FNetPStatBlock` struct), not just mesh/material swaps.

### 2.2 Part Unlocking by Tier/Rank — Hard-Cap Allocation Protocol

**The Rule:** A part's Tier/Rank cannot exceed the NetNavi's current operational Rank.

This is a **hard lock**, not soft statistical scaling — deliberately, to avoid balance issues from partial scaling. Mechanism:
- Check the Navi's base Rank code at part-selection time
- A Rank 2 (Common/Uncommon) Navi has the UI **hard-lock** any Rank 3+ (Rare/Epic/Legendary) part from being selectable at all — not greyed-out-but-clickable, fully inaccessible
- Progression path: player must evolve/upgrade the **core Navi framework** itself (raising Category 5 — Memory Allocation Limits) before higher-tier parts become installable

This maps cleanly to a `GetLegalPartsForSlot(EPartSlot Slot, int32 CurrentRank)` style query function in the eventual character-creator backend — same design pattern already used in `UChipFolderComponent::GetLegalNextSelections()` for the chip-code system, which is a nice consistency win across the codebase.

### 2.3 Part Coloring by Element
Each equipped part's material should expose an **Element-driven color parameter**, consistent with the panel/HUD color language already established (`ABattleGridManager::TierColor`, the per-side glow system). A single mesh (e.g., one gauntlet model) can visually read as Fire, Aqua, Elec, etc. via material parameter swap rather than needing 10 separate gauntlet meshes — a major asset-production time-saver.

---

## 3. Elements (10 total) — CONFIRMED: Strict 1:1 Polar Opposition

**Relationship rule (confirmed, supersedes v0.1's many-to-many assumption):** each element has **exactly one** true hard-counter/opposite. This is a clean Polar Opposition matrix — no logic loops, no many-to-many complexity. This is simpler to implement than v0.1 anticipated: `EElementType` just needs one `Opposite` field per entry, not a list.

| Primary Element | Polar Opposite | Mechanical Interaction |
|---|---|---|
| Fire (Thermal) | Aqua (Coolant) | Heat melts/evaporates; coolant douses thermal spikes |
| Elec (Voltage) | Wood (Bio-Data) | Voltage overloads circuits; bio-data grounds electrical charge |
| Wind (Aero) | Earth (Geo) | Wind erodes/bypasses structures; earth anchors against kinetic air |
| Light (Holy) | Dark (Shadow) | Light purges corrupt files, breaks stealth; shadow dampens visibility, leeches vitality |
| Null (Raw Code) | Glitch (Chaos/Void) | Null is stable/predictable baseline data; Glitch is unstable, causes status anomalies |

**Note:** This is 10 elements as 5 opposite *pairs* (Fire/Aqua, Elec/Wood, Wind/Earth, Light/Dark, Null/Glitch) — cleaner than v0.1's draft list, which included some non-matching names (Plasma, Time, Aether, Blood, Bloom, Poison, Photon, Sound, Metal, Crystal, Nature, Void, Holy, Lightning, Water, Ice). **This confirmed table replaces the v0.1 list entirely** — the earlier names were either early brainstorming that didn't make the final cut, or this list is the authoritative one going forward. Flagging this explicitly since it's a meaningful change, not just a refinement.

This directly replaces the placeholder `EElementType` enum (`None, Fire, Aqua, Elec, Wood, Wind, Holy, Void`) — the placeholder actually already had 4 of the 5 correct pairs partially represented (Fire, Aqua, Elec, Wood, Wind all appear), just missing Earth, Light/Holy rename, Dark, Null, Glitch, and the explicit pairing logic.

---

## 4. Back-Slot / Wings: Faction-Dependent Visual Rules

**Confirmed:** Back-slot attachments (including wings) are player-accessible — **not** MC-Admin-exclusive. However, what's visually available depends on the NetNavi's **faction/entity sub-class**, not just Tier/Rank alone. This is a meaningful branch in the customization logic — back-slot options are filtered by faction first, then by Tier within that faction.

### 4.1 Angel Factions
- **Seraphim** (and similar high entities): multi-layered, radiant wing profiles that visually scale up with Tier upgrades
- **Cherubim / lower-tier celestial entities**: smaller, compact structural wings, or wing-like energy binders (a lighter-weight visual than full Seraphim wings)

### 4.2 Demon Factions
- Highly variable by specific entity type
- High-tier demonic Navis may have classic leather/bat wings, or "digital skeletal" wing variants
- No single consistent demon-wing rule the way Angel factions have one — this implies demon back-slot parts are likely a larger, more varied asset set rather than a simple tier-scaling chain

### 4.3 The "Cut-Off" Sub-Class
A distinct lore category: rogue or corrupted entities with permanently clipped, scarred, or fully severed wing roots. This is a deliberate visual storytelling choice, not a missing-asset placeholder — these entities trade flight-data functionality for **erratic, high-damage ground-burst capabilities**. This suggests the back-slot system needs at least one option that's mechanically active (grants a ground-burst ability) while being visually "wingless/damaged," which is a different design shape than a normal cosmetic-only slot.

### 4.4 Non-Winged Entities
Humanoid, beast-type, or purely mechanical Navis (both angelic and demonic variants) commonly have **no wings at all** — their back-slot is used instead for booster arrays, weapon holsters, or processing exhaust ports. This means the back-slot's available part *list* is fundamentally different depending on the chassis archetype, not just visually retextured.

**Implication for the Customizable Object graph:** back-slot part availability needs at least two upstream filters before Tier/Rank gating even applies: (1) Faction (Angel/Demon/Other), and (2) Entity sub-class within that faction. This is more branching than a flat "6 slots, filter by Rank" model — worth designing the Mutable graph's parameter hierarchy with Faction as a top-level switch.

---

## 5. Updated Technical Roadmap

With all design questions resolved, the implementation order is:

1. **Rebuild `EElementType`** with the confirmed 10 elements (Fire, Aqua, Elec, Wood, Wind, Earth, Light, Dark, Null, Glitch) and a single `Opposite` field per value (1:1, not array — simpler than v0.1 anticipated)
2. **Add `FNetPStatBlock`** struct for Category 4 (HP/ATK/DEF/SPD) and Category 5 (Memory Capacity/Slot Availability/Bandwidth Throttle)
3. **Define `EPartSlot` enum**: Core, LeftArm, RightArm, Legs, Head, Expansion (6 values, confirmed)
4. **Define `EFaction` / entity sub-class enums** for the back-slot filtering logic (Angel: Seraphim/Cherubim/etc.; Demon: variable; CutOff; NonWinged)
5. **Port the Hard-Cap Allocation Protocol** into a `GetLegalPartsForSlot()`-style function, mirroring `UChipFolderComponent::GetLegalNextSelections()`'s existing pattern for consistency
6. **Scope the actual `UCustomizableObject` asset graph** in Unreal — Faction switch → Slot → Tier/Rank-gated part list → Element-driven material parameter
7. **Build the in-game character creator UMG UI** that queries the above in the right order (Faction first, then slot-by-slot with live legality filtering)
