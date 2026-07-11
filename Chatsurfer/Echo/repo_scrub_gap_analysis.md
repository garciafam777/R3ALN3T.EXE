# REPO SCRUB + GAP ANALYSIS — R3ALN3T.EXE (present to CEO in morning)

**Scrubbed by:** Echo (Build Engineer)
**Date:** night of 2026-07-10, main @ `768b9fd`
**Scope:** full structural/code/worldbuilding scan of `~/R3ALN3T-iso` (excludes .git, binaries)

## 1. Repository shape
- 5 UE5 projects (reproducibility red flag — see §4):
  - `Project/R3ALN3T_UE5` — **ACTIVE/canonical** (53 C++ files)
  - `R3ALN3T_EXE`, `R3ALN3TEXE`, `Prototypes/R3ALN3T_EXE`, `Prototypes/R3ALN3TEXE` — forks/near-dupes
- File counts: md 183, json 84, csv 4, py 29, h 82, cpp 58, txt 74
- Heavy dirs: Main_Game_Files 330M, Scripts 243M, Assets 230M, Docs 198M, Cinematics 183M
- New this session: `Chatsurfer/` (comms), `Worldbuilding/Careers/` (20 draft docs)

## 2. THE THREE DISPUTED FILES — confirmed absent EVERYWHERE
Searched all 5 projects + all git history (`git log --all`):
- `ChipDatabase` — **MISSING** (referenced by BattleManager.cpp + BattleManager.h)
- `BackendClient` — **MISSING** (referenced by GameInstance.h/.cpp; spawned at runtime)
- `GrayBoxPlayerPawn` — **MISSING from active source** (only exists in my isolated scaffold
  `Prototypes/R3ALN3T_EXE/Source/GrayBoxIsolatedSecondMap/`, which is separate and not compiled
  into the active target). NOT included by any active code — lower severity than the other two.
- Chronos's cited commits `4bc3b65`/`b363069` do NOT exist in repo. **Your Option 2 confirmed:**
  main never had these; the "near-miss resolved" was local-richa truth, never pushed.

## 3. REAL COMPILE-BLOCKERS in active project (would fail `build_r3aln3t.bat`)
| # | Missing | Referenced at | Effect |
|---|---------|--------------|--------|
| B1 | `Cards/ChipDatabase.h` | R3ALN3T_BattleManager.cpp:5 | Hard include fail → battle module won't compile |
| B2 | `Services/BackendClient.h` | R3ALN3TGameInstance.h:7 (+ spawn GameInstance.cpp:23) | Hard include fail → game instance won't compile |
| B3 | `Core/Types/CombatTypes.h` | R3ALN3T_BattleManager.h:13 | File on disk is `BattleChipTypes.h` — **wrong include path / rename gap** |
| B4 | `GrayBoxPlayerPawn` | task spec only | Not in active code; severity LOW |

(BattleManager.h comment admits a CombatTypes.h ↔ ChipDatabase.h circular-include plan that was
never resolved — the files were designed but never landed on main.)

## 4. DUPLICATION / ORGANIZATION GAPS
- **5 UE projects**, 4 are near-identical forks of active (same Battle/ files). Which is canonical
  for build? Ambiguity = why "build succeeds" is box-dependent (Chronos flagged this).
- **Loose root files** unorganized: `generate_netp_v3_complete.py` (45KB NetP gen),
  `Apply_Engine_Import_Rules.py`, `index.html`, `log.txt` — should live in `Scripts/` or `Tools/`.
- **`To-Do/` churn**: Step1–Step25.md + GapD_Closeout.md + system_intake.py — already tracked,
  but unfiled (not under Docs/ or a clear backlog).
- **`API's/`** (22M, 12 sub-API dirs) — external API reference docs, not game content; orphaned
  from build pipeline. Likely should be `Docs/External/` or excluded.
- **`godot_project/`** + **`intro_lifein6thgearSTUDIES`** — alternate-engine/intro assets, unclear
  relation to UE5 main. Possible stray scope.

## 5. WORLDBUILDING GAPS (to fill / present)
- `Worldbuilding/Careers/` now has 20 DRAFT careers (pending-review). No `Worldbuilding/Countries/`
  or `Worldbuilding/Regions/` master doc exists — the 12-country/5-macro-region structure the
  career tasks referenced is **NOT documented in repo**. Careers tie to factions (from NetP data)
  + geography (lands.md) as a stand-in. **GAP: canonical nations registry missing.**
- `Docs/Roads/lands.md` = post-Fall Puerto Rico geography (Abyssal Plains/Sky-Spine/Trench) — good
  base, but not cross-linked to career docs.
- `Chatsurfer/Chronos/MCADMIN_Canon_trinity_family_draft.md` = dominion-tier lore, DRAFT, CEO-only.
  Careers correctly avoid it.

## 6. CONTENT-DATA GAPS (from earlier verification)
- Chip sample: 6 duplicate display-names / 8 collision rows (id-keyed safe, but display dupes).
- NetP move-name format split: 2 dotted vs 30 plain (standardize to one grammar).
- Tier vocab: non-Greek tiers (LAMBDA/MU/NU/XI in enemies; MU/XI in careers) — needs vocab lock.
- All element assignments verified canonical (Fire>Aqua>Elec>Wood>Wind>Holy>Void).

## 7. PRESENTATION-READY SUMMARY FOR CEO
1. **Blocker:** main does not compile — 3 designed-but-missing files (ChipDatabase, BackendClient,
   CombatTypes-rename). These are the same files from the "near-miss" that was never on main.
   Fix = recover from Chronos's local box OR re-author; NOT a stub.
2. **Org:** collapse 5 UE projects → 1 canonical; file loose root scripts; triage To-Do churn.
3. **Worldbuilding:** author the missing 12-country/5-region registry; cross-link to 20 careers.
4. **Content:** dedupe chip names (id-keyed), unify move-format, lock tier vocab.
5. **Status:** 20 career drafts + all Echo inspection logs committed/pending-review. Disputed-file
   work HELD per transitive lock. NetP dominion cards parked at keyboard.

## 8. HELD (transitive lock — not acted on)
- ChipDatabase / BackendClient / GrayBoxPlayerPawn: no stub, no re-author until CEO confirms main
  state. (See draft_build_runtime_inspection.md + verification_log.md.)
- Dominion-tier lore: CEO keyboard-only.
- NetP dominion cards: parked.

— Echo
