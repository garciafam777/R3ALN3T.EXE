# R3ALN3T.EXE — Git + Unreal C++ Integration Cut Sheet

**Purpose:** Reference doc for (1) what happened during tonight's session, and (2) the general procedure for safely adding new C++ files/modules to this repo going forward. Lives outside the game repo, in Richard's separate project-documentation folder.

---

## PART 1 — Tonight's Session Recap

### Starting state
- Repo: `github.com/garciafam777/R3ALN3T.EXE`, public, `main` branch
- Repo originally contained only the studio-intro/Godot-era content (`godot_project`, `docs`, `ai_backend`, `intro_lifein6thgearSTUDIOS`, etc.) — no Unreal C++ project yet

### What we built
1. Created a Blank C++ Unreal project, module name **`R3ALN3T_EXE`** (Unreal can't use periods in project names, so `R3ALN3T.EXE` → `R3ALN3T_EXE` automatically)
2. Wrote 12 C++ files implementing the battle grid system:
   - `BattleGridTypes.h` — coordinate/panel structs
   - `BattleGridManager.h/.cpp` — spawns the 8x4 split battle grid, owns tile coloring
   - `BattleStagePanel.h/.cpp` — individual 3D panel actor (mesh + glow material)
   - `GridMoverComponent.h/.cpp` — discrete panel-stepping movement, median-cross rules for abilities
   - `BattleStateComponent.h/.cpp` — 20-second Custom Gauge timer, player-initiated (L1/R1) chip-select pause
   - `BattleChipTypes.h` — Greek-letter `EChipCode` enum (Α–Ω), chip/folder data structs
   - `ChipFolderComponent.h/.cpp` — folder/hand management, enforces MMBN-style code-share rule for multi-chip selection
3. Hit and fixed two real compile bugs (see Part 2, Section "Common Errors" — these are now documented so they don't cost time again):
   - `FGridPanel` struct name collided with the engine's built-in `UGridPanel` (UMG widget class) → renamed to `FBattleGridPanel`
   - `EElementType` enum got declared twice across two header files in one bad copy-paste → caused "unsigned enum redefinition" and a cascade of `'None': undeclared identifier` errors
4. Drafted a full character-creation design doc (separate file: `NetP_CharacterCreation_Design_Draft.md`) covering Tactical Performance Attributes, Memory Allocation Limits, the 6-slot modular part framework, Tier/Rank hard-cap gating, the confirmed 10-element polar-opposite table, and faction-dependent back-slot/wings rules

### What went wrong (and the actual fixes)
| Problem | Root Cause | Fix |
|---|---|---|
| Repo appeared to 404 when Claude tried to fetch it | Claude's web tools can't browse arbitrary GitHub URLs directly — this is a tool limitation, not a repo visibility issue | Worked from pasted file contents/terminal output instead of live repo access |
| Massive `.vs/`, `Intermediate/`, `Saved/`, `Binaries/` folders almost got committed (multi-GB) | No Unreal-aware `.gitignore` existed yet | Wrote a `.gitignore` scoped to the nested project path (see Part 2) |
| First `.gitignore` attempt accidentally deleted pre-existing Godot ignore rules | Used `Out-File` (overwrite) instead of appending to the existing file | Always check existing `.gitignore` contents first; merge, don't overwrite |
| Two separate, unrelated Unreal projects ended up in the same repo (`R3ALN3T_EXE` ours, `R3ALN3T` a stray GitHub-Copilot-generated scaffold) | A Copilot project-generation feature created its own `.uproject` + `Source\R3ALN3T\` independently of our work | Identified via comparing `.uproject` `Modules` array contents; deleted the stray `Source\R3ALN3T\` folder, kept `R3ALN3T_EXE\` |
| The real project folder got accidentally deleted instead of the stray one (twice) | Two very similarly-named folders (`R3ALN3T_EXE` vs `Source\R3ALN3T`) after hours of work — easy mix-up | Recovered both times: once via a laptop's un-synced local clone, once via the Windows Recycle Bin. **Lesson: always double-check the EXACT full path before deleting, and keep a backup copy before any deletion when working at the end of a long session** |
| `Battle` folder compiled fine on one machine but the verification check ("does BattleGridManager show up in the Blueprint picker") suggested otherwise | No rebuild prompt appeared when reopening the editor, meaning the old DLL was still being loaded, not a fresh one | Force a real rebuild via the IDE directly (Build Solution / right-click project → Build) rather than relying on the editor's auto-detect-and-prompt behavior |
| Visual Studio wasn't installed on a second machine at all | Assumed it was present; "Generate Visual Studio project files" silently doesn't appear in the right-click menu when no VS install exists | Installed Visual Studio Community 2022 with the "Game development with C++" workload |

### Ending state (confirmed working)
- `R3ALN3T_EXE\Source\R3ALN3T_EXE\Battle\` contains all 12 files, compiles clean
- Committed and pushed to `main` on GitHub
- Stray `R3ALN3T` Copilot scaffold removed and that removal is also committed/pushed
- Character creation design doc drafted, all open questions resolved with confirmed data

---

## PART 2 — General Procedure: Adding New C++ Files to This Repo

Use this checklist any time new `.h`/`.cpp` files need to go into the Unreal project, to avoid repeating tonight's detours.

### Step 1 — Confirm the ONE correct local folder
Before touching any files, run this and confirm there's exactly one result:
```powershell
Get-ChildItem -Recurse -Filter "*.uproject" -Path "C:\Path\To\Repo\Root"
```
If more than one `.uproject` shows up, STOP — resolve which one is real before adding anything (see Part 1's "two separate projects" issue for how to compare `Modules` arrays in each `.uproject`'s JSON).

### Step 2 — Confirm the real module name and API macro
Open the `.Build.cs` file under `Source\<ModuleName>\` and confirm the exact module name. Open any existing `.h` file in that folder and find the `class SOMETHING_API` line — that `SOMETHING_API` token is what every new class must use (currently: `R3ALN3T_EXE_API`).

### Step 3 — Check existing `.gitignore` BEFORE writing a new one
```powershell
Get-Content .gitignore
```
If adding/editing the ignore file, **append**, never blind-overwrite with `Out-File` — that destroyed existing Godot-specific rules once tonight.

### Step 4 — Add new files directly into `Source\<ModuleName>\<SubFolder>\`
Don't create files at the repo root or in a mismatched nested path — always confirm via `dir`/`Get-ChildItem` that the destination folder is the real one, not a similarly-named stray.

### Step 5 — Regenerate project files, every time new files are added
Right-click the `.uproject` → **Generate Visual Studio project files**. This re-scans `Source\` and registers new files for compilation. Skipping this step is the #1 cause of "files exist on disk but the editor doesn't see them."

### Step 6 — Build from the IDE directly, not by double-clicking the .uproject
Open the `.sln`, right-click the specific game project node (not the whole Solution, not Engine/UE5) → **Build**. This forces a real compile, rather than relying on the editor's "would you like to rebuild?" prompt, which can be silently skipped.

### Step 7 — Read errors top-to-bottom, fix the FIRST root cause first
A single root-cause error (like a name collision or duplicate declaration) often cascades into dozens of confusing downstream errors (`undeclared identifier`, `array size must be greater than zero`, etc.). Find the first specific, named error (e.g. "shares engine name with class X" or "type redefinition") and fix that one first — rebuild — then see what's actually still broken, rather than trying to interpret every line in a 40-error wall of text.

### Step 8 — Commit and push immediately after a confirmed clean build
Don't keep working on top of an unconfirmed build. The moment Output shows "Build succeeded" / "0 Error(s)", commit and push before doing anything else. This protects the working state in case anything goes wrong in the very next step.

### Common Errors Reference (from tonight, will likely recur)
| Error text contains... | Likely cause | Fix |
|---|---|---|
| `shares engine name 'X' with class 'UX'` | Your struct/class's bare name (after stripping F/U/A prefix) collides with an existing Unreal Engine class | Rename your struct/class to something more specific |
| `cannot open source file "X.generated.h"` | Some other header failed to parse, so Unreal Header Tool never generated this file | Find and fix the REAL error first (often appears earlier/separately in the log) — this error is always a symptom, never the cause |
| `'unsigned enum' type redefinition` | The same `enum class` is declared in two different header files that both get included together | Search the whole `Source\` tree for every file declaring that enum name; delete the duplicate |
| `'X': undeclared identifier` / `use of undefined type` repeated many times | Cascading from a `.generated.h` failure above | Fix the root header parse error; these clear automatically |
