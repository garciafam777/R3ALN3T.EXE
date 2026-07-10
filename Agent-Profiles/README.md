# R3ALN3T.EXE — Multi-Agent Profile Pack

9 Hermes agent personas (8 roles + orchestrator) for building R3ALN3T.EXE
(cyberpunk battle-network TCG, UE5 + Blender). Each persona is a `SOUL.md`
that becomes the delegated subagent's contract/context.

## Layout
```
Agent-Profiles/
├── setup-profiles.sh              # one-command installer (portable Win/Linux)
├── README.md                      # this file
├── researcher/SOUL.md             # engine eval, benchmarks, feasibility
├── writer/SOUL.md                 # GDD, lore, mechanics, narrative
├── architect/SOUL.md              # system design, APIs, schemas, ECS
├── modeler/SOUL.md                # asset specs, PBR, shaders, LOD
├── level-designer/SOUL.md         # spaces, encounters, pacing, metrics
├── programmer/SOUL.md             # C++/C#/GDScript gameplay, physics, AI
├── qa-tester/SOUL.md              # bug reports, compliance, balance
├── build-engineer/SOUL.md         # CI/CD, builds, bundles, deploy
├── orchestrator/SOUL.md           # coordination, delegation, synthesis
└── project-workspace-template/    # shared ground-truth tree (copy to project)
    ├── docs/{gdd,tech-specs,lore}
    ├── assets/{specs,models,materials,textures}
    ├── src/{gameplay,systems,ui}
    ├── levels/{blockouts,encounters}
    ├── builds/{dev,release}
    └── qa/{reports,test-cases}
```

## Install
```bash
chmod +x setup-profiles.sh
./setup-profiles.sh
```
The script detects the Hermes profile dir:
- **Windows (git-bash/MSYS):** `~/.hermes/profiles/`   ← this host
- **Linux:** `~/.config/hermes/profiles/`

It copies each `SOUL.md` into `~/.hermes/profiles/<role>/SOUL.md`.

## Wire the workspace into your project
```bash
cp -r project-workspace-template ~/my-3d-game/
cd ~/my-3d-game/ && git init   # optional but recommended
```
All agents read/write this shared tree — it is the single source of truth.

## Delegation model (this host)
Hermes' `delegate_task` takes `role` + `goal` + `context` (not a `--profile` flag).
So: load the role's `SOUL.md` text and paste it as the subagent `context`, then give
the `goal`. Example (orchestrator driving two parallel leaves):

> role: researcher
> goal: Evaluate UE5.8 vs Godot 4.4 for R3ALN3T's 8x4 MMBN battle + isometric traversal.
> context: <paste researcher/SOUL.md> + "Project at C:\Users\richa\Desktop\R3ALN3T_UE5.
>           Constraint: box has 32 GB / ~2 GB free; UBA disabled. Canon: 8x4 grid,
>           Soul 7 bands, Greek Α-Ω chips, no Diablo overworld combat."

## Workflow DAG
```
Phase 1   researcher ║ writer            (parallel: tech/engine  +  GDD/lore)
           │                │
Phase 2   architect   ◄─────┘             (sequential: design from P1)
           │
Phase 3   modeler ║ level-designer         (parallel: assets  +  spaces)
           │         │
Phase 4   programmer  ◄── architect+modeler+level-designer
           │
Phase 5   build-engineer → qa-tester → (sign-off gate)
           │
           └─► orchestrator synthesizes → MCADMIN (final sign-off; never self-close)
```

## Canon guardrails (load-bearing — every agent must respect)
- Strands: R34L / N3T / The Compressed. 6 factions.
- Soul State: 7 bands Radiant→Corrupted (0-100), isomorphic to Heaven's 7 layers &
  Hell's 7 stages (Seam = Echo Abyss L1↔S1).
- 24 Greek-letter chip codes (Α-Ω) in `BattleChipTypes.h` — never revert to alphanumeric.
- Architecture: isometric open-world TRAVERSAL (Diablo cam) + MMBN BATTLE (8x4 grid,
  real-time gauge, chip + Star). NO Diablo overworld combat. Enemy spawn = NetPs on
  grid cols 4-7 at encounter.

## Build/verify facts (from this host — keep)
- UBA disabled (`BuildConfiguration.xml`, `bAllowUBAExecutor=false`) — it OOM-death-loops.
- Kill editor: `cmd.exe /c "taskkill /F /IM UnrealEditor.exe"` (MSYS `//F //IM` = no-op).
- Built module: `Binaries/Win64/UnrealEditor-R3ALN3T_UE5.dll`.
- Headless `-game` verify execs must route through `UR3ALN3TGameInstance` (Pawn/PC don't
  spawn under AGameModeBase). UE logs to `Saved/Logs/R3ALN3T_UE5.log`, not stdout.
