# Game Creation README

## Overview
This document explains how to create NETAdmin_EXE from concept to playable build. It is written to help define the systems first, then expand into content, balance, and production. A good design document keeps the project focused, reduces confusion, and gives every feature a place in the overall structure.

## Vision
NETAdmin_EXE is a cyberpunk-themed RPG where players control a NetP (Network Processor — digital avatar) that can "jack in" to a virtual network world called the N3T. The player is a System Administrator who manages AI-powered NetP agents, each with unique personalities and abilities. Most of the time, the player explores the Cyber Square hub, accepts governance tasks from various districts, battles corrupted data entities, and customizes their NetP team. The game is fun because it combines strategic grid-based combat with AI-driven character interactions, creating a sense of managing a living digital team that grows and evolves based on player choices.

## Core Loop
The core loop is the repeatable cycle the player experiences most of the time:

1. **Jack In** - Enter the N3T from the physical R34L Room
2. **Accept Task** - Receive governance missions from districts or discover threats
3. **Navigate** - Move through Cyber Square and district networks
4. **Battle** - Engage corrupted data or hostile NetPs using Programs and abilities
5. **Earn Rewards** - Gain NetPs, experience, and resources
6. **Customize** - Upgrade NetPs, unlock new Programs, and evolve tiers
7. **Return Stronger** - Re-enter the N3T with enhanced capabilities

If the core loop is strong, the rest of the game can support it rather than fight it.

## Combat System
Combat is turn-based on a 6x6 grid. Each NetP occupies one tile and can move, attack, or use Programs per turn. Turn order is determined by CHARGE stat (higher CHARGE acts earlier). Combat ends when all enemy NetPs are defeated or the player's team is wiped.

**Damage Calculation:**
- Physical damage: `ATK - enemy DEF`
- Program damage: `ATK × Program multiplier - enemy DEF`
- Critical hits occur when RAPID triggers (percentage chance per attack)

**Special Moves:**
- Signature Programs trigger when a NetP's energy meter is full
- Combination attacks occur when specific NetP types are adjacent
- Elemental advantages multiply damage by 1.5x

## Stats
Each NetP has six core stats:

- **HP** - Health points. When reduced to 0, the NetP is defeated.
- **ATK** - Attack power. Base damage dealt to enemies.
- **RAPID** - Attack speed. Percentage chance to trigger multi-hit or critical effects.
- **CHARGE** - Turn order initiative. Higher values act earlier in combat.
- **DEF** - Defense. Reduces incoming damage.
- **SPD** - Movement range on the grid. Higher values allow more tiles per turn.

## Types
Types define a NetP's combat style and alignment:

- **Guardian** - Defensive specialists, high DEF and HP
- **Striker** - Offensive focus, high ATK and RAPID
- **Controller** - Support and debuff capabilities
- **Technical** - Program-focused, high energy generation
- **Assassin** - High mobility and burst damage
- **Tank** - Maximum survivability, low mobility

Types interact with each other: Strikers deal bonus damage to Controllers, Controllers debuff Guardians, etc.

## Elements
Elements provide combat flavor and advantages:

- **Radiant** - Light/holy theme, strong against Abyss
- **Abyss** - Dark/void theme, strong against Radiant
- **Static** - Lightning/tech theme, strong against Bio
- **Bio** - Organic/data theme, strong against Static
- **Thermal** - Fire/heat theme, strong against Cryo
- **Cryo** - Ice/freeze theme, strong against Thermal
- **Quantum** - Reality-bending, neutral but rare

Element advantages grant 1.5x damage and resistances reduce damage by 25%.

## Rarity Tiers
NetP hierarchy follows a structured rarity ladder:

- **OMEGA** - Apex class. Mythic, unique, game-changing abilities. Only 004+ infrastructure.
- **ALPHA** - Highest regular tier. Extremely powerful, rare drops.
- **BETA** - High-tier NetPs. Strong signature Programs.
- **GAMMA** - Mid-tier. Balanced stats and abilities.
- **DELTA** - Low-mid tier. Specialized roles.
- **EPSILON** - Low-tier. Basic utility.
- **ZETA** - Entry-tier. Common, weak but functional.
- **PSI** - Lowest tier. Basic data constructs.

**004+** - OMEGA infrastructure units (SystemAdmin, Security, etc.)
**041+** - Regular NetPs following the rarity ladder

## NetP Naming Rules
Naming follows consistent logic:

- **Tier** identifies power class (OMEGA, ALPHA, etc.)
- **Type** identifies style or alignment (Guardian, Striker, etc.)
- **Element** identifies combat flavor (Radiant, Abyss, etc.)
- **Role** identifies function (Defender, Controller, etc.)
- **Program names** identify abilities

Examples:
- **Radiant Sentinel** - Angelic Guardian defender
- **Abyss Warden** - Dark Controller with crowd control
- **Static Archon** - Technical lightning-type authority
- **Thermal Vanguard** - Fire Striker with high mobility
- **Quantum Observer** - Rare OMEGA unit with reality manipulation

This gives names meaning instead of making them random labels.

## Programs
Programs are abilities NetPs can use in combat:

- **Attack Programs** - Direct damage abilities
- **Defense Programs** - Shields, damage reduction
- **Support Programs** - Healing, buffs, team effects
- **Debuff Programs** - Status effects, enemy penalties
- **Utility Programs** - Movement, grid manipulation
- **Signature Programs** - Unique ultimate abilities per NetP

Each Program has:
- Name
- Element
- Type
- Energy cost
- Cooldown
- Effect description
- Stat scaling

## Progression
Players move from weak to strong through:

1. **Earn NetPs** - Battle rewards, governance tasks, exploration
2. **Level Up** - Gain experience to increase base stats
3. **Unlock Programs** - Learn new abilities at level milestones
4. **Evolve Tiers** - Transform from lower to higher rarity tiers
5. **Customize Grid** - Arrange NetPs in the Customizer for stat bonuses
6. **Equipment** - Install data chips and modules

Progression is visible through:
- Level indicators
- Tier evolution animations
- Stat growth charts
- Program unlock notifications
- Customizer grid bonuses

## UI
UI design makes hierarchy and systems understandable at a glance:

**Main Menu:**
- Jack In button (prominent, center)
- NetP Roster (bottom tab)
- Customizer (side panel)
- District Map (top right)
- Settings (top left)

**NetP Info Card:**
- Portrait/sprite (left)
- Name and tier (top)
- Type and element icons (below name)
- Stats bar chart (center)
- Program list (right)
- Evolution path (bottom)

**Battle Screen:**
- 6x6 grid (center)
- Player team (bottom, blue)
- Enemy team (top, red)
- Turn order indicator (left side)
- Energy meters (above each NetP)
- Program selection panel (bottom)
- Combat log (right)

**Program Selection:**
- Grid of available Programs
- Energy cost display
- Cooldown indicators
- Target preview on grid
- Damage estimation

**Upgrade Screens:**
- Level-up stat allocation
- Program unlock tree
- Evolution requirements
- Customizer grid placement

**Roster Sorting:**
- Filter by tier, type, element
- Sort by level, stats, name
- Search functionality
- Favorite marking

## Art Direction
Visual identity supports the cyberpunk theme and hierarchy:

**Color Palette:**
- Primary: Neon cyan (#00FFFF) and magenta (#FF00FF)
- Secondary: Deep purple (#2D0036) and electric blue (#0066FF)
- Background: Dark grid with data stream effects
- UI: Semi-transparent panels with glowing borders

**Shape Language:**
- OMEGA units: Complex, ornate, multiple glowing elements
- Regular NetPs: Clean, geometric, functional
- Corrupted entities: Jagged, glitched, asymmetrical
- UI: Sharp angles, technical lines, holographic feel

**UI Mood:**
- High-tech but accessible
- Information-dense but organized
- Glowing accents for important elements
- Smooth transitions and animations

**Effect Style:**
- Data streams for movement
- Pixel bursts for attacks
- Grid distortions for Programs
- Holographic overlays for UI

**Character Silhouette:**
- OMEGA: Large, imposing, multiple protrusions
- High tiers: Dynamic poses, distinctive shapes
- Low tiers: Simple, recognizable forms
- Each type has identifiable silhouette traits

## Technical Setup
**Engine:** Godot 4.2+ with GL Compatibility renderer

**Platform:** Windows (primary), with export presets for Linux and macOS

**Save System:**
- Local saves in `saves/` directory
- JSON format for NetP roster, progress, and settings
- Auto-save after major events
- Manual save slots (3 slots)

**Data Format:**
- NetP data: JSON files per unit or master CSV
- Program definitions: JSON with stat scaling
- Combat balance: CSV for easy iteration
- District data: JSON for mission structures

**Battle Logic:**
- Turn-based state machine
- Grid-based movement and targeting
- Stat-based damage calculation
- AI decision trees for enemy NetPs

**AI Backend:**
- Python FastAPI server (ai_backend/main.py)
- Ollama integration for Navi personality responses
- Agent system for specialized AI behaviors
- Vector database for long-term context

## Content Pipeline
1. **Design** - Create NetP concepts in docs/design/
2. **Art** - Create sprites in assets_source/ (Aseprite, PSD)
3. **Export** - Convert to Godot-compatible formats in godot_project/assets/
4. **Data** - Define stats and Programs in JSON/CSV
5. **Implement** - Create scenes and scripts in Godot
6. **Test** - Balance combat and progression
7. **Iterate** - Refine based on feedback

**Asset Organization:**
- Source files in assets_source/ (gitignored)
- Final assets in godot_project/assets/
- Naming convention: tier_type_element_name (e.g., omega_guardian_radiant_sentinel)

## Balance Rules
**Stat Ranges by Tier:**
- OMEGA: 200-300 HP, 50-80 ATK
- ALPHA: 150-220 HP, 40-60 ATK
- BETA: 120-180 HP, 30-50 ATK
- GAMMA: 100-150 HP, 25-40 ATK
- DELTA: 80-120 HP, 20-30 ATK
- EPSILON: 60-100 HP, 15-25 ATK
- ZETA: 50-80 HP, 10-20 ATK
- PSI: 40-60 HP, 8-15 ATK

**Program Power:**
- Signature Programs: 3-4x base damage
- Regular Programs: 1.5-2.5x base damage
- Basic attacks: 1x base damage

**Progression Speed:**
- Level 1-10: Tutorial and early game (2-3 hours)
- Level 11-30: Mid-game, unlock districts (8-10 hours)
- Level 31-50: Late-game, OMEGA content (10-15 hours)
- Total playtime: 20-30 hours for main story

**Difficulty Scaling:**
- Enemy stats scale with player level
- District difficulty increases with distance from Cyber Square
- Optional challenges for high-level players

## Development Workflow
1. **Finalize Rules** - Complete this design document
2. **Build Prototype** - Implement basic combat and grid movement
3. **Test Combat** - Verify stat model and damage calculations
4. **Adjust Stat Ranges** - Balance based on prototype testing
5. **Add Content** - Create initial NetP roster and Programs
6. **Refine UI** - Implement all screens and navigation
7. **Balance Progression** - Tune leveling and evolution curves
8. **Integrate AI** - Connect Python backend for Navi personalities
9. **Polish** - Add effects, animations, and audio
10. **Ship** - Export executables and release

## Changelog
- **v0.1** - Initial design document created
- Future updates will track major design changes and feature additions
