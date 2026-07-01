# R3ALN3T.EXE: Automated System Script & Execution Architecture
## Pipeline Reference Document for Pinokio Automation Controller

This document serves as a direct file system interface for Pinokio. It contains structural pipeline definitions, precise execution terminal strings, and configuration rules to fix engine halts and stabilize repository staging.

---

## 1. System Automation & Tool Matrix

The local high-density orchestration stack interfaces natively via the following layout parameters:

| Component | Target File / Vector | Execution / Automation Mandate |
| :--- | :--- | :--- |
| **Unreal Engine 5** | `/R3ALN3T.uproject` | Primary runtime environment, physics simulation, and binary execution layer. |
| **Cursor & VS Code** | `/.vscode/`, `/*.sln` | Header analysis, C++ compilation loops, and data structural schema validation. |
| **Git + LFS** | `/.gitattributes` | Pointer interception for binary layers to prevent asset staging bloating. |
| **Docker Desktop** | `localhost` Local Container | Asynchronous backend database/state management execution loops. |
| **Bruno** | `/*.json` Collection | Automated REST endpoint execution profiling without locking game threads. |
| **Blender 5.1 & Krita**| `/Content/R3ALN3T/` | Target directories for structured `.fbx` models and high-fidelity `.png` menus. |
| **Audacity** | `/Content/Audio/` | Audio payload rendering path target (`16-bit / 44.1kHz .wav`). |
| **Inno Setup** | `/Saved/StagedBuilds/`| Final local staging package compiler for client distribution. |

---

## 2. Diagnostics: The "Zero Execution" Editor Bug

### Root Cause Analysis
When the editor viewport "Play" trigger yields zero action or locks execution, Pinokio has modified source headers (`.h`) or code implementation arrays (`.cpp`) on disk without triggering an active MSVC/UBT engine compilation pass. The editor runtime is executing an empty or uninitialized memory address loop.

### Automation Rectification Chain
Pinokio must execute the following sequence via local CLI terminals to compile changes before triggering the editor workspace loop:

1. **Kill Stray Editor Threads:**
   ```bash
   taskkill /F /IM UnrealEditor.exe /T
   ```

2. **Generate Native Solution Projects:**
   Execute against the local engine installation path (Update path arguments to match physical disk mapping):
   ```bash
   "C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.dll" -projectfiles -project="[PATH_TO_YOUR_PROJECT]\R3ALN3T.uproject" -game -engine -progress
   ```

3. **Execute Headless Binary Compilation Pass:**
   ```bash
   "C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.dll" R3ALN3TEditor Development Win64 -Project="[PATH_TO_YOUR_PROJECT]\R3ALN3T.uproject" -NoHotReload -WaitMutex
   ```

---

## 3. Structural Architectural Gaps to Resolve

Pinokio must construct files matching the following structural layouts to stabilize game loops before integrating script layouts or narrative text streams:

### Gap A: Separation of UI Runtime from Character Mechanics
* **Vulnerability:** Wiring intro screens, splash screens, or start choices into normal game modes causes circular header execution faults.
* **Architecture Fix:** Create an isolated `AMenuGameMode` and an independent `AMenuPlayerController`. This controller forces mouse visibility, instantiates the master viewport user widget, and prevents character entity initialization until a clean level streaming swap occurs.

### Gap B: Data-Driven Narrative Engine
* **Vulnerability:** Hardcoding story descriptions or dialogues inside standard blueprint arrays creates massive stack footprints.
* **Architecture Fix:** Define structs inheriting from `FTableRowBase`. Store game story layouts, text elements, and cinematic cues within native **Data Tables** (`UDataTable`), pulling metadata dynamically via **Soft Object References** (`TSoftObjectPtr`).

### Gap C: Persistent State Management
* **Vulnerability:** Storing critical parameters (like graphic toggles, system data, or game progress flags) inside individual level instances causes data wipes on map transitions.
* **Architecture Fix:** Subclass `UGameInstance`. Implement master save/load interfaces here, since this object initializes at launch and stays resident until process termination.

---

## 4. Local Integration Files (Target Configurations)

Pinokio must output the following files to the project root folder exactly as defined below to preserve repository stability:

### Target File: `[PROJECT_ROOT]/.gitattributes`
```text
# R3ALN3T.EXE Binary Interception Matrix
*.uasset filter=lfs diff=lfs merge=lfs -text
*.umap filter=lfs diff=lfs merge=lfs -text
*.fbx filter=lfs diff=lfs merge=lfs -text
*.png filter=lfs diff=lfs merge=lfs -text
*.jpg filter=lfs diff=lfs merge=lfs -text
*.wav filter=lfs diff=lfs merge=lfs -text
*.mp3 filter=lfs diff=lfs merge=lfs -text
*.blend filter=lfs diff=lfs merge=lfs -text
*.kra filter=lfs diff=lfs merge=lfs -text
*.exe filter=lfs diff=lfs merge=lfs -text
*.dll filter=lfs diff=lfs merge=lfs -text
*.pdb filter=lfs diff=lfs merge=lfs -text

*.cpp text
*.h text
*.cs text
*.md text
*.json text
```

### Target File: `[PROJECT_ROOT]/.gitignore`
```text
# Local Intermediate File Filters
Binaries/
Build/
DerivedDataCache/
Intermediate/
Saved/
Script/
.idea/
.vscode/
*.sln
*.suo
*.opensdf
*.sdf
*.VC.db
*.VC.opendb

# Telemetry & Environment Caches
.DS_Store
*.log
Docker/data/
node_modules/
__pycache__/
```