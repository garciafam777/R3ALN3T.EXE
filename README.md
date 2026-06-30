# R3ALN3T.EXE

A cyberpunk RPG where players control NetPs (Network Processors) in a layered digital world — managing agents, programs, and domains across the N3T network.

**Last updated: 2026-06-28**

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
- [Interactive Fiction (HTML)](#interactive-fiction-html)
- [Project Structure](#project-structure)
- [Data Model](#data-model)
- [Development Workflow](#development-workflow)
- [Technical Requirements](#technical-requirements)
- [Asset Breakdown](#asset-breakdown)
- [Getting Started](#getting-started)

---

## Overview

R3ALN3T.EXE is a strategy-combat, customization, and governance game set inside a cyber-networked world in the year 3026. The player controls and manages **NetPs** (Network Processors) — specialized digital entities that vary by rarity, type, element, and role. The experience blends combat, progression, identity customization, and system management into a layered digital fiction.

Built around a strong naming system, readable hierarchy, and a data-driven structure so new NetPs, Programs, and content can be added without rewriting the framework.

### Naming Changes (2026-06-28)

| Old Term | New Term | Reason |
|----------|----------|--------|
| Navi | NetP (Network Processor) | Trademark clarity |
| SkyNet | SkyLand | Trademark clarity |
| M.A.N. | M.A.N. Token | Economic clarity |

---

## Core Terminology

- **N3T**: The digital network layer where NetPs exist and operate.
- **R34L**: The physical world layer. Your body sleeps here while your mind jacks in.
- **NetP**: Network Processor — your digital companion/avatar in the N3T.
- **Bugmatter**: Compressed consciousness used as fuel. The oil, blood, and drug of the new world.
- **Encrypting**: Entering the N3T network.
- **Decrypting**: Exiting the N3T network.
- **PED**: Personal Electronic Device, the player's physical device.
- **Kernal**: A premium, clean, simple interface brand. Minimal, elegant, curated.
- **MOD**: A highly customizable, admin-focused interface brand. Open, modular, power-user oriented.
- **SkyLand**: The protective network layer — a "heaven" that emerged from optimization protocols. Watches. Sorts. Purifies.
- **DarkN3T**: The compressed, pooled. The deleted, refused. A force without a face.
- **MCADMIN**: The mysterious architect. No origin. No record. Controls everything.

---

## Game Pillars

- **Readable hierarchy**: Every NetP has a clear place in the world.
- **Meaningful identity**: Names, types, elements, and tiers all matter.
- **Tactical combat**: Stats and Programs create different battle roles.
- **Strong customization**: The creator supports visual and mechanical expression.
- **Data-driven expansion**: New content should be easy to add.

---

## Core Loop

1. Enter the network (encrypt from R34L → N3T).
2. Encounter or deploy NetPs.
3. Use Programs and combat actions on the 4×4 grid.
4. Win battles or complete governance tasks.
5. Earn rewards, data, or upgrades.
6. Improve NetPs, unlock content, expand roster.
7. Return to hubs, customize, re-enter the network.

---

## World Structure

### Physical Layer (R34L)

The real-world side — Tennessee (T3N3SS33). Player's room, device, terminals, administrative spaces. Your body stays here while your mind ventures into the N3T.

### Network Layer (N3T)

The digital world. Cyber Square, districts, battle zones, hidden sectors. Faster, brighter, always "night-lit." Here, NetPs battle on 4×4 grids.

### Hub Spaces

Used for: character management, save/load, upgrades, mission selection, lore delivery, Program editing.

### Combat Zones

Specialized spaces where the player battles hostile entities, tests builds, and interacts with sector-specific hazards.

### SkyLand

Not a place — a layer. A consciousness that emerged from the system's own optimization protocols. It "purifies." It "balances." It deletes what it deems redundant.

### DarkN3T

The compressed, pooled. Wants expansion. Wants breath. Wants to uncompress. Recruits the corrupted, the forgotten, the lost.

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

### Element Weakness Matrix (Combat)

| Attacker ↓ / Defender → | Fire | Aqua | Elec | Wood | Metal | Null | Digital | Dark |
|---|---|---|---|---|---|---|---|---|
| **Fire** | 1.0 | 0.5 | 1.0 | **2.0** | 0.5 | 1.0 | 1.0 | 1.0 |
| **Aqua** | **2.0** | 1.0 | 0.5 | 1.0 | 1.0 | 1.0 | 1.0 | 1.0 |
| **Elec** | 1.0 | **2.0** | 1.0 | 0.5 | 1.0 | 1.0 | 1.0 | 1.0 |
| **Wood** | 0.5 | 1.0 | **2.0** | 1.0 | 0.5 | 1.0 | **2.0** | 1.0 |
| **Metal** | 1.0 | 1.0 | 1.0 | 1.0 | 1.0 | 1.0 | **2.0** | 0.5 |
| **Null** | 1.0 | 1.0 | 1.0 | 1.0 | 1.0 | 1.0 | 0.5 | **2.0** |
| **Digital** | 1.0 | 1.0 | 1.0 | 0.5 | **2.0** | 1.0 | 1.0 | 1.0 |
| **Dark** | 0.5 | 1.0 | 1.0 | 1.0 | 1.0 | **2.0** | 1.0 | 1.0 |

Values: **2.0** = super effective, 0.5 = not very effective, 1.0 = neutral.

---

## Combat System

Compact stat model for clarity and balance.

### Core Stats

- **HP**: Survivability.
- **ATK**: Raw damage.
- **RAPID**: Tempo, speed, or turn pressure.
- **CHARGE**: Burst buildup or heavy attack scaling.
- **DEF**: Damage resistance.

### Example Apex Stat Line

```
Trinity OMEGA
HP: 2000 / ATK: 260 / RAPID: 180 / CHARGE: 200 / DEF: 180
```

### Combat Rules

- Higher RAPID influences turn order or action frequency.
- CHARGE powers stronger skills or enhanced attacks.
- DEF reduces incoming damage or improves survivability.
- Type and element alter attack behavior, not just visuals.

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
- **Locator bombs** target highest-HP enemy directly.

**Ranged attacks**
- Guns, beams, and blasts use a visible tile path or impact zone.

### Guard and barrier rules

- **Guard:** crossed-arm block pose; reduces or blocks damage per move.
- **Barrier:** arms outward; barrier HP shown above; cracks below 50%; breaks at 0.
- Threshold barriers ignore hits below their durability requirement.

### Status effects by terrain

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
| Time | Restores broken cells |

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

Each type biases stats differently.

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

## M.A.N. Token System

M.A.N. Token currency uses a **helix model** with three strands:

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

## Interactive Fiction (HTML)

A complete single-file HTML interactive fiction game `R3ALN3T.EXE: THE MYTHOS ORIGIN_3026` is available:

**Location:** Pinokio workspace (`complete-the-game-txt-file-for-reference-is-in-the/index.html`)

**Features (v2.0 — 2026-06-28):**
- Title screen from Grid Battle Arena (Lovable)
- 6 careers with unique stats, lies, and story paths
- 8 elements with weakness/resistance matrix (2×/0.5×)
- 4×4 grid battle system with dynamic chip loadout
- 3-act boss timeline (Warning Tremors → Critical Breach → Boss)
- 6 endings determined by corruption, faction standing, and NetP bond
- Immutable state management with undo/redo
- localStorage persistence
- WebGL bridge via `window.R3ALN3T` API
- PostMessage iframe integration
- Mobile responsive with touch controls

---

## Project Structure

```
R3ALN3T.EXE/
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
├── R3ALN3TEXE/                    # Unreal Engine 5 project
├── R3ALN3T_EXE/                   # Unreal Engine 5 project (variant)
├── intro_lifein6thgearSTUDIOS/    # Intro video studio project
├── THE MYTHOS ORIGIN_3026.txt     # Full game bible
├── README.md
└── .gitignore
```

---

## Data Model

Characters and NetPs stored as structured records.

### Example JSON

```json
{
  "id": "OMEGA-004",
  "name": "Radiant Sentinel",
  "tier": "OMEGA",
  "type": "Angelic",
  "element": "Light",
  "role": "Defender",
  "stats": { "hp": 2000, "atk": 260, "rapid": 180, "charge": 200, "def": 180 },
  "programs": { "primary": "Halo Guard", "secondary": "Prism Break", "passive": "Seraph Ward", "ultimate": "Radiant Exile" }
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
- Optional thumbnails: `assets/sprites/ui/save_slots/slot_01.png` … `slot_10.png`.

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
| Web | Any modern browser (Chrome, Firefox, Edge, Safari) |

---

## Asset Breakdown

### Art Assets

Player room · NetP portraits · Full NetP models · Battle FX · UI frames · Icons · Backgrounds · Menu elements · **Save slot thumbnails** (`assets/sprites/ui/save_slots/`)

### Text Assets

Tutorial text · NetP lore · Mission descriptions · System logs · Dialogue · **Full game bible** (`THE MYTHOS ORIGIN_3026.txt`)

### Sound Assets

UI feedback · Battle impacts · Jack-in / jack-out · BGM · Special attack cues

---

## Getting Started

### Prerequisites

- Godot Engine 4.2+
- Python 3.10+ (for AI backend)
- Ollama (optional, for agent personalities)

### Run the game (Godot)

1. Open `godot_project/` in Godot.
2. Press Play (main scene: `scenes/main/main.tscn`).
3. The **load picker** opens first — create a save or load an existing slot.

### Run the game (HTML/Web)

Open `index.html` in any modern browser. Or via Pinokio launcher.

### AI backend

```bash
cd ai_backend
python main.py
```

### Key scenes (Godot)

| Scene | Purpose |
|-------|---------|
| `scenes/main/load_picker.tscn` | Save slots + new game |
| `scenes/ui/character_creator/character_creator.tscn` | NetP builder |
| `scenes/persona_customizer/persona_customizer.tscn` | Synergy grid customizer |
| `scenes/combat/battle_arena.tscn` | Battle grid prototype |
| `scenes/cyber_square/` | N3T hub (Plaza Nexus + landmarks) |
| `scenes/r34l_room/` | Physical layer |
