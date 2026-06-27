# NETAdmin.EXE

A Mega Man Battle Network-inspired AI computer governance system where the player navigates a layered digital world, manages NetPs, and builds a growing force of agents, programs, and domains.

---

## Table of Contents

- [Overview](#overview)
- [Core Terminology](#core-terminology)
- [Game Pillars](#game-pillars)
- [Core Loop](#core-loop)
- [World Structure](#world-structure)
- [NetP Hierarchy](#netp-hierarchy)
- [Types and Elements](#types-and-elements)
- [Combat System](#combat-system)
- [Battle Grid System](#battle-grid-system)
- [Battle Actions, Status Effects, and Terrain](#battle-actions-status-effects-and-terrain)
- [Stat System](#stat-system)
- [Programs](#programs)
- [Character Creator](#character-creator)
- [UI and 4K Rules](#ui-and-4k-rules)
- [M.A.N. Token System](#man-token-system)
- [Persona Customizer](#persona-customizer)
- [Project Structure](#project-structure)
- [Data Model](#data-model)
- [Development Workflow](#development-workflow)
- [Technical Requirements](#technical-requirements)
- [Asset Breakdown](#asset-breakdown)
- [Getting Started](#getting-started)
- [Open Questions](#open-questions)

---

## Overview

NETAdmin.EXE is a strategy-combat, customization, and governance game set inside a cyber-networked world. The player controls and manages NetPs, constructs specialized digital entities that vary by rarity, type, element, and role. The experience blends combat, progression, identity customization, and system management into a layered digital fiction.

The game is built around a strong naming system, readable hierarchy, and a data-driven structure so new NetPs, Programs, and content can be added without rewriting the entire framework.

---

## Core Terminology

- **N3T**: The digital network layer where NetPs exist and operate.
- **Encrypting**: Entering the N3T network. This can be represented as a transformation from Hexadecimal streams to Hash algorithm visualization and then upload into N3T.
- **Decrypting**: Exiting the N3T network. This is the reverse sequence: Hash to Hexadecimal to download back to the PED.
- **PED**: Personal Electronic Device, the player's physical device.
- **Kernal**: A premium, clean, simple interface brand. Minimal, elegant, and highly curated.
- **MOD**: A highly customizable, admin-focused interface brand. Open, modular, and power-user oriented.

---

## Game Pillars

- **Readable hierarchy**: Every NetP has a clear place in the world.
- **Meaningful identity**: Names, types, elements, and tiers all matter.
- **Tactical combat**: Stats and Programs create different battle roles.
- **Strong customization**: The creator supports visual and mechanical expression.
- **Data-driven expansion**: New content should be easy to add.

---

## Core Loop

1. Enter the network.
2. Encounter or deploy NetPs.
3. Use Programs and combat actions.
4. Win battles or complete governance tasks.
5. Earn rewards, data, or upgrades.
6. Improve NetPs, unlock content, and expand the roster.
7. Return to hubs, customize, and re-enter the network.

---

## World Structure

### Physical Layer

The real-world side of the game. This includes the player's room, device, terminals, and administrative spaces.

### Network Layer

The N3T side of the game. This includes the Cyber Square, districts, battle zones, and hidden sectors.

### Hub Spaces

Hub areas are used for:

- character management,
- save/load,
- upgrades,
- mission selection,
- lore delivery,
- Program editing.

### Combat Zones

Combat areas are specialized spaces where the player battles hostile entities, tests builds, and interacts with sector-specific hazards.

---

## NetP Hierarchy

NetPs are divided into two major groups:

### OMEGA NetPs

- The absolute top tier of the game.
- Reserved for the strongest, rarest, and most mythic entities.
- The OMEGA block begins at **004** and continues through **040**.

### Regular NetPs

- Begin at **041** and continue downward in the normal progression structure.
- Use Greek rarity tiers as the main progression ladder.

### Greek Rarity Ladder

From highest regular rarity to lowest:

ALPHA, BETA, GAMMA, DELTA, EPSILON, ZETA, ETA, THETA, IOTA, KAPPA, LAMBDA, MU, NU, XI, OMICRON, PI, RHO, SIGMA, TAU, UPSILON, PHI, CHI, PSI

### Naming Rules

- OMEGA units keep singular mythic titles.
- Regular NetPs use singular names below the OMEGA block.
- Tier, type, element, and role should influence the name.

---

## Types and Elements

### Type

Type defines the NetP's identity, alignment, and visual logic.

Example types: Angelic, Demonic, Mechanical, Viral, Abyssal, Celestial, Arcane

### Element

Element defines combat flavor, visual effect, and the style of Programs.

Example elements: Fire, Water, Lightning, Ice, Wind, Earth, Light, Dark, Void, Metal, Nature, Sound, Gravity, Time, Blood, Poison, Crystal, Plasma

### Naming Guidance

- Angelic types should use radiant, holy, and refined naming.
- Demonic types should use dark, harsh, and predatory naming.
- Mechanical types should use engineered, precise, and structured naming.
- Viral types should use glitch, corrupt, or unstable naming.

---

## Combat System

Combat uses a compact stat model for clarity and balance.

### Core Stats

- **HP**: Survivability.
- **ATK**: Raw damage.
- **RAPID**: Tempo, speed, or turn pressure.
- **CHARGE**: Burst buildup or heavy attack scaling.
- **DEF**: Damage resistance.

### Example Apex Stat Line

```text
Trinity OMEGA
HP: 2000 / ATK: 260 / RAPID: 180 / CHARGE: 200 / DEF: 180
```

### Combat Rules

- Higher RAPID should influence turn order or action frequency.
- CHARGE should power stronger skills or enhanced attacks.
- DEF should reduce incoming damage or improve survivability.
- Type and element should alter attack behavior, not just visuals.

### Combat Goals

- Make battles fast to understand.
- Make NetP identity matter in combat.
- Allow rare entities to feel stronger without making normal units useless.

---

## Battle Grid System

Fixed mirrored battlefield: **8 columns × 4 rows** (4×4 player + 4×4 enemy).

| Topic | Detail |
|-------|--------|
| Player side | Columns 0–3 |
| Enemy side | Columns 4–7 |
| Center line | Between columns 3 and 4 |
| Movement | Tile-based with range preview |
| Attack shapes | Line, wide row, cross, cone, full row |
| Guard | Crossed-arm block pose, damage reduction |
| Barrier | Separate HP pool with threshold breaks |
| Large units | 2×1 / 2×2 footprints (planned) |

**Implementation:** `godot_project/scripts/combat/` — `battle_grid.gd`, `attack_shape_resolver.gd`, `barrier_tracker.gd`, `status_effect_system.gd`, `terrain_system.gd`

**Prototype:** `godot_project/scenes/combat/battle_arena.tscn`

Full spec: [docs/Battle_Grid_System.md](docs/Battle_Grid_System.md)

---

## Battle Actions, Status Effects, and Terrain

Attack shapes, defenses, terrain, and status effects for the 4×4 battle grid.

### Attack shape rules

**Sword attacks**
- **Long sword:** 4 tiles straight ahead.
- **Wide sword:** 4 tiles across the row in front.
- Other styles: diagonal, arc, dash, multi-hit.

**Bomb attacks**
- Default bomb lands 4 tiles forward.
- **Locator bombs** target highest-HP enemy directly (no standard travel).

**Ranged attacks**
- Guns, beams, and blasts use a visible tile path or impact zone.

### Guard and barrier rules

- **Guard:** crossed-arm block pose; reduces or blocks damage per move.
- **Barrier:** arms outward; barrier HP shown above; cracks below 50%; breaks at 0.
- Threshold barriers ignore hits below their durability requirement (e.g. 200).

### Special moves

- NetP-specific; described on each character card.
- May affect multiple tiles, one lane, a full row, or a custom shape.

### Status effects

| Terrain | Effect |
|---------|--------|
| Fire | 10 HP/sec while standing |
| Poison | 30 HP per 5 sec |
| Water / Mud | Movement slow |
| Metal | Normal movement |
| Grass / Nature / Earth | Passive or stand heal |
| Void | Ghost spawns (virus-dependent) |
| Wind | Push or pull by strength |
| Light | One-time 100 HP barrier per battle |
| Dark | Strong buffs for dark-tier units |
| Time | Restores broken cells (not direct player effect) |

### Broken cell rules

- Cannot move onto broken tiles.
- Unit on destroyed tile is pushed to nearest valid tile.
- Broken terrain stays visually distinct; restored tiles animate back.

### Design priority

1. Grid movement  
2. Basic attack shapes  
3. Guard and barrier  
4. Terrain damage and healing  
5. Status timers  
6. Broken tile logic  
7. Special move card definitions  
8. Advanced terrain and unique effects  

---

## Stat System

Each type should bias stats differently.

| Type | Bias |
|------|------|
| **Angelic** | High HP, DEF, CHARGE. Moderate ATK and RAPID. |
| **Demonic** | High ATK, RAPID, CHARGE. Lower DEF or HP. |
| **Mechanical** | High DEF, RAPID, stable ATK. |
| **Viral** | High RAPID and ATK. Low DEF. Disruption focus. |
| **Abyssal** | High HP and CHARGE. Moderate ATK. Slower, oppressive. |
| **Celestial** | Balanced HP, DEF, CHARGE. Command-oriented. |

---

## Programs

Programs are the ability system used by NetPs.

### Program Families

Use more than one naming root so the roster does not feel repetitive.

Examples: Volt, Spark, Surge, Arc, Halo, Radiant, Abyss, Void, Grave, Gear, Circuit, Relay, Glitch, Rewrite

### Program Categories

- Attack Programs
- Defense Programs
- Support Programs
- Control Programs
- Ultimate Programs

### Naming Rule

Use `[Family Word] + [Action Word]` — e.g. `Halo Guard`, `Void Rend`, `Circuit Break`, `Glitch Spike`

### Program Limits

- Regular NetPs should have simpler loadouts.
- OMEGA NetPs may have exclusive signature Programs.
- Programs should be restricted by tier, type, or progression.

---

## Character Creator

The character creator is the player's first major personalization system.

### Creator Goals

- Create a valid NetP.
- Preview the NetP instantly.
- Support a 4K-ready UI.
- Export data for gameplay use.

### Creator Sections

Identity · Body · Face · Hair · Colors · Type · Element · Stats · Programs · Preview · Save/Load

### Required Fields

Name, ID, Tier, Faction, Role, Pronouns, Body type, Face details, Hair details, Color palette, Type, Element, Stats, Programs

### 4K Requirements

- Base resolution **3840×2160** with canvas stretch (`project.godot`).
- UI scales via `CreatorTheme` viewport factors.
- **Flashback mode:** `FlashbackManager` autoload — 32-bit retro palette, nearest-neighbor filter, CRT tint overlay. Toggle with `FlashbackManager.toggle_flashback()`.

---

## M.A.N. Token System

M.A.N. currency uses a **helix model** with three strands:

- **Gold** — premium transactions  
- **Blue** — standard balance (maps to save `man_balance`)  
- **Red** — risk / override strand  

**Autoload:** `MANTokenManager` — `credit()`, `debit()`, `transaction_log`, `balance_changed` signal.

Helix icon: `assets/sprites/ui/icon_man_helix.svg`

---

## Persona Customizer

Grid-based NetP synergy builder (distinct from the Character Creator).

| Feature | Status |
|---------|--------|
| Tiered grid 4×4 → 8×8 | ✓ |
| Drag-and-drop cells | ✓ |
| Block library (Core, Support, Hazard, Mutator, Admin) | ✓ |
| Color clash + center line rules | ✓ |
| Bug heat + glitch overlay | ✓ |
| Live NetP preview | ✓ |
| Kernal / MOD device themes | ✓ |

**Scene:** `godot_project/scenes/persona_customizer/persona_customizer.tscn`

---

## UI and 4K Rules

### UI Principles

- Keep hierarchy obvious.
- Put important data near the center or top.
- Use large labels and readable numbers.
- Avoid clutter.
- Prioritize contrast.

### Layout

- Left panel: identity and appearance.
- Center panel: live preview.
- Right panel: stats, type, element, Programs.
- Bottom bar: save, randomize, presets, confirm.

### Accessibility

- High contrast mode.
- Scalable fonts.
- Keyboard navigation.
- Controller support.
- Tooltips for every major field.
- Reduced motion option.

### PED / Narrow Layout

- Load picker uses a narrow, scrollable column (save slots).
- Character creator switches to tabbed layout below 1200px width.
- Kernal = minimal tabs; MOD = expandable detail drawers (`scripts/ui/tabbed_manager.gd`).

---

## Project Structure

```text
NETAdmin_EXE/
├── godot_project/
│   ├── project.godot
│   ├── scenes/
│   │   ├── main/                  # Main menu, load picker
│   │   ├── r34l_room/             # Physical layer
│   │   ├── net_room/              # N3T mirror room
│   │   ├── cyber_square/          # Hub
│   │   └── ui/                    # Character creator, roster picker
│   ├── scripts/
│   │   ├── character_creator/     # Creator panels, validation
│   │   ├── persona_customizer/    # Synergy grid customizer
│   │   ├── combat/                # 8×4 battle grid systems
│   │   ├── core/                  # GameSaveManager, Flashback, M.A.N.
│   │   ├── devices/               # Kernal / MOD theming
│   │   ├── ui/                    # TabbedManager
│   │   └── assets/                # NetPSpriteResolver
│   ├── assets/sprites/            # NetP, player, UI art
│   ├── data/                      # netp_content.json
│   └── export_presets.cfg
├── ai_backend/
│   ├── main.py
│   └── config/
├── docs/
│   ├── 4K_Character_Creator_Spec.md
│   ├── Battle_Grid_System.md
│   └── Game_Creation_README.md
├── assets_source/                 # Raw art (gitignored)
├── exports/
├── saves/
└── README.md
```

---

## Data Model

Characters and NetPs should be stored as structured records.

### Example JSON

```json
{
  "id": "OMEGA-004",
  "name": "Radiant Sentinel",
  "tier": "OMEGA",
  "type": "Angelic",
  "element": "Light",
  "role": "Defender",
  "stats": {
    "hp": 2000,
    "atk": 260,
    "rapid": 180,
    "charge": 200,
    "def": 180
  },
  "programs": {
    "primary": "Halo Guard",
    "secondary": "Prism Break",
    "passive": "Seraph Ward",
    "ultimate": "Radiant Exile"
  }
}
```

### Validation Rules

- ID must be unique.
- Name must fit tier and naming logic.
- Stats must stay within tier limits.
- Type and element must be valid.
- Programs must obey unlock rules.

### Save Slots

- Up to **10 encrypted game saves** (`user://game_saves/`).
- Public metadata preview: name, last played, location, M.A.N. balance, active NetPs.
- Optional thumbnails: `godot_project/assets/sprites/ui/save_slots/slot_01.png` … `slot_10.png`.

---

## Development Workflow

1. Finalize the system rules.
2. Build a combat prototype.
3. Build the creator UI.
4. Add NetP hierarchy and data.
5. Add Programs and element effects.
6. Add progression and save/load.
7. Balance and polish.
8. Expand content.

### Recommended Approach

- Keep this README as a stable reference.
- Put day-to-day tasks in issue tracking once production starts.
- Update `docs/` when mechanics change.

---

## Technical Requirements

| Area | Requirement |
|------|-------------|
| Engine | Godot 4.2+ |
| Backend | Python 3.10+ (AI orchestration) |
| Data | JSON / CSV for roster, stats, Programs |
| Saves | Local encrypted slots + NetP JSON export |
| UI | Resolution-independent, 4K-ready, controller + keyboard |

---

## Asset Breakdown

### Art Assets

Player room · NetP portraits · Full NetP models · Battle FX · UI frames · Icons · Backgrounds · Menu elements · **Save slot thumbnails** (`assets/sprites/ui/save_slots/`)

### Text Assets

Tutorial text · NetP lore · Mission descriptions · System logs · Dialogue

### Sound Assets

UI feedback · Battle impacts · Jack-in / jack-out · BGM · Special attack cues

---

## Getting Started

### Prerequisites

- Godot Engine 4.2+
- Python 3.10+ (for AI backend)
- Ollama (optional, for agent personalities)

### Run the game

1. Open `godot_project/` in Godot.
2. Press Play (main scene: `scenes/main/main.tscn`).
3. The **load picker** opens first — create a save or load an existing slot.

### AI backend

```bash
cd ai_backend
pip install -r requirements.txt   # when available
python main.py
```

### Key scenes

| Scene | Purpose |
|-------|---------|
| `scenes/main/load_picker.tscn` | Save slots + new game |
| `scenes/ui/character_creator/character_creator.tscn` | NetP builder |
| `scenes/persona_customizer/persona_customizer.tscn` | Synergy grid customizer |
| `scenes/combat/battle_arena.tscn` | Battle grid prototype |
| `scenes/cyber_square/` | N3T hub (Plaza Nexus + landmarks) |
| `scenes/r34l_room/` | Physical layer |

---

## Open Questions

- Should NetPs evolve by training, fusion, or story milestones?
- Should all OMEGA units be unlockable or some remain story-only?
- Should Programs be tied to element, type, or both?
- Should the creator support preset sharing?
- Should the N3T and real world have different interface styles?

---

## Notes

This project benefits from documentation that is practical, data-driven, and easy for a small team to maintain. This README describes the game clearly, covers mechanics early, and leaves room for iteration as development continues.
