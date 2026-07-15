# R3ALN3T.EXE — UE 5.8 Project & Content Organization Structure

> CANONICAL STANDARD — adopted 2026-07-15 (CEO letter). Source of truth for folder layout,
> naming, and the non-negotiable redirector/git rules. Pair with Soul.md discipline:
> record + verify, never re-litigate.

## 1. Top-Level Project Structure
```
R3ALN3T/
├── Config/                    # DefaultEngine.ini, DefaultGame.ini, DefaultInput.ini, etc.
├── Content/
│   └── R3ALN3T/                # SINGLE root project namespace — everything lives under this
├── External/                   # Fab / Megascans / Marketplace drops — isolated, never mixed in (UE 5.5+)
├── Plugins/                    # Custom + third-party plugins (own Source + Content)
├── Source/
│   └── R3ALN3T/
│       ├── Public/
│       └── Private/
├── DesignDocs/                 # NOT in Content — kept outside .uproject content tree entirely
├── Saved/                      # Gitignored
├── Intermediate/               # Gitignored
└── R3ALN3T.uproject
```
**Key rule:** everything project-specific lives under one root folder (`/Content/R3ALN3T/`), never
loose at Content root. Matters when migrating assets or reusing R3ALN3T.EXE assets in another R&Y title.

## 2. Content/ — Feature-Based Breakdown
Recommended depth 3-4 levels: `/Content/R3ALN3T/FeatureName/AssetType`.
```
Content/R3ALN3T/
├── Core/ { GameModes/, SaveSystem/, UI/{HUD/,Menus/,Widgets_Shared/}, Audio/{Music/,SFX_Shared/} }
├── SoulState/     { Blueprints/, Data/, VFX/, UI/ }                       # 7-band system
├── Battle/        { Core/, ElementWheel/, NetP/, Encounters/Rotterdam/ }  # grid + NetP-as-enemy + TCG
├── Characters/    { Player/, Antagonists/{Grunts/,Bosses/{MCADMIN/,GTrinity/}}, Rosters/{Angelic/,Demonic/,Mythos/,Cosmos/,Undernet/} }
├── Factions/      { Faction_01_[Name]/ … Faction_06_[Name]/ }             # 6 Helix factions, 1:1 w/ doc
├── Items/         { AngelsKiss/, Consumables/ }
├── TCG/           { Cards/, DataTables/ }
├── Environments/  { Rotterdam/ }
├── Levels/        { Rotterdam_GrayBox.umap, … one folder per named location }
└── VFX_Shared/
```
Naming: type prefix + feature, e.g. `BP_Grunt_Fire_01`, `T_SoulState_Cracked_D`, `DT_ElementWheel`,
`WBP_HUD_SoulMeter`. Standard UE prefixes (`BP_`,`T_`,`M_`,`MI_`,`SM_`,`WBP_`,`DT_`) let Content
Browser filters work instead of folder-diving.

## 3. Source/ — C++ Module Structure
```
Source/R3ALN3T/
├── R3ALN3T.Build.cs
├── Public/  { SoulState/, Battle/, Factions/, Core/ }
└── Private/ { SoulState/, Battle/, Factions/, Core/ }
```
Mirror Content/ feature folders in Source/ (Public+Private per feature). Epic Action-RPG convention;
prevents flat-folder header-path headaches.

## 4. Redirector / Git Workflow — NON-NEGOTIABLE
1. **Never** move/rename assets via Windows Explorer or `git mv` — creates *no* redirector, silently
   breaks every reference (Anchorpoint, 2026).
2. Always move/rename **inside the Content Browser**.
3. Before every commit: right-click folder (or Content root) → **"Update Redirector References"**
   (renamed from "Fix Up Redirectors in Folder" since UE 5.4) (Hyperdense, 2026).
4. Cleanup pass *before* committing — leftover redirectors degrade perf + cause merge conflicts.
5. Gap-gate addendum (Chronos): add a pre-commit check for **orphaned redirectors** as a 4th gate —
   cheap to script, catches the #1 "works on my machine" reference break.

## 5. External / Fab Content (UE 5.5+)
Fab drags assets into Content Browser, polluting namespaces. Route **everything** to `Content/External/`
first, then explicitly move (Content Browser + redirector fixup) anything kept long-term into the proper
`Content/R3ALN3T/...` feature folder (Hyperdense, 2026).

## 6. Design Docs
Stay **outside** the `.uproject` content tree — sibling to `Content/` at `R3ALN3T/DesignDocs/`, or in
Obsidian (current practice). Keeps lore/faction/char spec docs out of binary diffs + Zen Loader asset graph.

## Implementation Status (2026-07-15 audit)
- Content root NOT yet compliant: assets currently loose at `/Content/` + `/Content/UI/` + `/Content/Data/`.
  Migration to `/Content/R3ALN3T/<Feature>/` is a tracked action, NOT yet executed (high reference-risk).
- Code-coupled paths to update on migration: `OpenLevel("MainGameMap")` in MenuGameMode.cpp:41 +
  MainMenuWidget.cpp:114 (only `MainGameMap` is engine-path-referenced; UI widgets referenced by BP/MCP).
- C++ module `R3ALN3TEditorAutomation` is an editor-only extension slot (separate from Source/R3ALN3T/).

## References
Anchorpoint (2026-02-11); Epic Games n.d. (UE 5.8 dir structure); Hyperdense (2026-02-24);
UE Casts n.d.; UhiyamaLab (2025-12-12).
