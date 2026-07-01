# R3ALN3T_UE5

A cyberpunk NetP-battler built in Unreal Engine 5.8 — inspired by Mega Man Battle Network, set in the world of 3026.

## Repository Structure

```
R3ALN3T_UE5/
├── Project/
│   └── R3ALN3T_UE5/          # ★ Active UE5 project (C++ source, Content, Config)
├── Prototypes/
│   ├── R3ALN3TEXE/            # Legacy UE5 prototype (R3ALN3TEXE module name)
│   ├── R3ALN3T_EXE/           # Legacy UE5 prototype (R3ALN3T_EXE module name)
│   └── Godot/                 # Godot engine prototype
├── Cinematics/
│   └── Intro/                 # Intro cinematic (Vite + TS ++ frames)
├── Services/
│   └── AI_Backend/            # Python FastAPI + Ollama AI agent backend
├── Assets/
│   ├── Character_Cards/       # JSON character card data + generator
│   ├── Images/
│   │   ├── Battle/            # Battle system concept art & screenshots
│   │   ├── UI/                # UI frames, element icons, font assets
│   │   └── NetP/              # NetP / MCADMIN reference images
│   └── Sprites/               # Character / entity sprites
├── Docs/
│   ├── Design/                # Spec docs, design drafts, text archives
│   ├── Game_Mechanics/        # Combat, inventory, collectibles, pipeline docs
│   ├── Battle_System/         # Grid, chip state, 4x4 dual-grid definitions
│   ├── Dialogue/              # Dialogue database schema & architecture
│   ├── World_Building/        # Rooms, lands, world lore
│   ├── Roads/                 # World road tree, construction, decay
│   ├── Vehicles/              # Vehicle & fuel system
│   ├── Buildings/             # Building / location documentation
│   ├── People_NPCs/           # NPC, aging formula, AI bot design
│   └── MCADMIN/               # Masked Admin lore & data structure
├── Scripts/
│   ├── Card Creation/         # Card renderer, asset generators
│   └── setup_ue5.ps1          # Orchestrated setup script
├── ArtSource/                 # Original art source files (Krita, textures)
├── Builds/                    # Packaged builds output
├── index.html                 # Pinokio web entry point
├── pinokio.json               # Pinokio metadata
├── README.md
└── .gitignore
```

## Development Setup

### Prerequisites
- Unreal Engine 5.8
- Visual Studio 2022 with Game Development workload
- (Optional) Python 3.12+ for AI backend & card generation

### Build the Project

```powershell
# Generate Visual Studio solution files
dotnet "C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.dll" ^
  -projectfiles -project="C:\path\to\R3ALN3T_UE5\Project\R3ALN3T_UE5\R3ALN3T_UE5.uproject" ^
  -game -engine

# Build
dotnet "C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.dll" ^
  Development Win64 ^
  -Project="C:\path\to\R3ALN3T_UE5\Project\R3ALN3T_UE5\R3ALN3T_UE5.uproject" ^
  -TargetType=Editor -Progress
```

### AI Backend (optional)
```bash
cd Services/AI_Backend
uv pip install -r requirements.txt
python main.py
```

### Intro Cinematic (optional)
```bash
cd Cinematics/Intro
npm install
npm run dev
```

## Project Map

| Area | Path | Tech |
|------|------|------|
| Active UE5 Project | `Project/R3ALN3T_UE5/` | C++ / UE 5.8 |
| Godot Prototype | `Prototypes/Godot/` | GDScript |
| AI Agents | `Services/AI_Backend/` | Python FastAPI |
| Intro Video | `Cinematics/Intro/` | Vite + TS |
| Card Data | `Assets/Character_Cards/` | JSON |
| Concepts | `Docs/Images/` | PNG / JPG |

## Game Features

- **Career System** — 6 careers with unique stats, faction lean, and hidden lies
- **Element System** — 6 Navi elements granting combat and progression perks
- **Faction Alignment** — 6 dynamic factions determining ending paths
- **Battle Grid** — 8×4 split grid (4×4 player + 4×4 enemy) with panel mechanics
- **Chip Folder System** — 30-chip folders with Greek-letter code-share rules
- **Branching Narrative** — Day progression, corruption tracking, 6 endings

## License

See LICENSE file.
