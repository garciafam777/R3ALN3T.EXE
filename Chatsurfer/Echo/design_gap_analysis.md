# DESIGN GAP ANALYSIS — full sweep (Echo + Nyx findings combined)

**Compiled by:** Echo (Build Engineer), with Nyx's posted findings
**For:** CEO / Chronos (A_Team) + Nyx
**Date:** 2026-07-13
**Method:** static inspection of repo (code enums, data files, asset dirs, Content/). No GPU playtest.

## A. CANON STATE (Nyx locked, mostly solid)
- CEO `Override_b`: **21-element Trinity Matrix authoritative** (was 7-wheel). 21×21 matrix CSV committed. ✅
- 4 cruft factions (IRON CORTEX/HALO CORE/PANDEMONIUM NET/BRIMSTONE CELL) **pruned by Nyx** ✅
  → my earlier "ask Nyx about the 4 extras" is ANSWERED: they were cruft, removed.
- My 15→6 mapping + 20-career re-tie are **superseded by Option B / 21-design vocab** (documented in `status_faction_optionB_supersede.md`).

## B. OPEN DESIGN GAPS (evidence-based)

### GAP 1 — Code enum lags canon lock (HIGH)
- `TrinityMatrixTypes.h` `EElement` = **19 members, COUNT=19**, and is **MISSING Ice/Blood/Void**.
- Nyx's spec + matrix CSV assume **21 (with Ice/Blood/Void)**. `EElement_COUNT=19` vs spec 22 (incl None).
- `EFaction` on disk = **6 Helix**; Option B spec = **21**. Not yet extended.
- **Impact:** any data using Ice/Blood/Void or the 21 factions won't compile/resolve until the
  enum is updated. The canon lock is documented, not implemented in active code.

### GAP 2 — Engine wheel NOT wired (HIGH, Nyx-flagged)
- `ElementWheelCalculator.cpp` still uses the old 5-cycle/`OMICRON` stub. Must encode the 21×21
  matrix. Chronos's lane (engine C++). Combat multipliers currently wrong vs canon.

### GAP 3 — 252 careers: data exists, but coverage gaps
- `gamedata/careers/job__*.js` = **252 files** ✅ (matches vault's "252 paths").
- BUT vault prose doc `Complete Career Storylines 252 Paths.md` = **MISSING** from this checkout
  (Nyx's `content-salvage` may hold it; verify it's on main, not stranded).
- Career→faction lean reference (`gamedata/career_faction_lean_reference.md`) is DERIVED/INFERRED,
  owner-decision needed (Chronos) before canon. 173/252 have canon element; 0 conflicting faction.

### GAP 4 — NetP seed data absent in active project (MEDIUM)
- `Content/R3ALN3T/Characters/NetP/Data/seed_*.json` = **0 files** in active project.
- Nyx's doc claims seed instances exist ("PyraShift etc.") — they're NOT in `Project/R3ALN3T_UE5/
  Content/`. Either in `Main_Game_Files/`, or never imported. NetP designs have lore+engine+CSV
  but **no imported UE data instances** in the buildable project.

### GAP 5 — TEXTURES / 4K (HIGH, your stated priority)
- **Source art is NOT 4K.** Measured: NetP concepts 1024×1536 / 1122×1402 / 1024×1024; UI frames
  1536×2752. **0 files ≥ 2048px.** True 4K (3840×2160) sharpness is impossible from 1K sources
  (upscaling = the blur you want to avoid).
- **0 .uasset imported** into active `Content/` — nothing is rendering. The 2652 "texture-like"
  files are in `Assets/` (repo root, untracked pile), not imported.
- `DefaultEngine.ini` has **no streaming pool / device profiles / anisotropy** set → engine
  defaults; no 4K guarantee, no per-platform LOD policy.
- **Conclusion:** "crystal clear 4K, no blur, no lag" is NOT achievable with current assets+config.
  Requires: (a) regenerate/upscale source art to true 4K, (b) import to Content with correct
  texture groups + MipBias=0, (c) tune DefaultEngine.ini (PoolSize 2048+MB, DeviceProfiles
  4K max, anisotropy), (d) GPU playtest (stat Streaming / ProfileGPU) — can't be done headlessly.

### GAP 6 — Intro / Character Creation MISSING (MEDIUM)
- `IntroSequence` + `CharacterCreation` = **MISSING** from active source (MASTER_TRACKER lists them
  as Steps 11/13; Nyx's 65-file pile on Chronos's box may hold `IntroSequence.cpp/.h` as stray
  untracked). Game has no intro or char-creation widget in the buildable project yet.

### GAP 7 — netp_master.csv STALE (LOW, Nyx-flagged)
- Committed sample uses pre-prune faction strings (`VOID CULT`). Generator fixed; sample not
  regenerated. Cosmetic but contradicts the prune.

### GAP 8 — Balance lopsided (YOUR CALL)
- 21×21 matrix std dev 0.22, 90% spread. Glitch 10%, Null/Wood 20%, Blood 25%, Crystal 30%
  underpowered. Accept as flavor or rebalance — CEO decision.

## C. SUMMARY TABLE
| # | Gap | Severity | Owner | Status |
|---|-----|----------|-------|--------|
|1|EElement 19≠21, missing Ice/Blood/Void; EFaction 6≠21|HIGH|Nyx/Chronos|code not updated to canon|
|2|Engine wheel not wired to 21×21|HIGH|Chronos|stub only|
|3|252 career data yes; prose doc missing; lean ref inferred|MED|Nyx/Chronos|partial|
|4|NetP seed .json absent in active Content|MED|Nyx|not imported|
|5|Textures 1K not 4K; 0 imported; ini defaults|HIGH|Art+Echo config|blocker for "4K crisp"|
|6|IntroSequence + CharacterCreation missing|MED|Chronos|stranded on box|
|7|netp_master.csv stale faction strings|LOW|Nyx|cosmetic|
|8|Balance lopsided|YOUR CALL|CEO|pending|

## D. WHAT NYX + ECHO CAN DO NOW (no GPU needed)
- Nyx: close GAP 1 (extend EElement→21 + EFaction→21 in TrinityMatrixTypes.h) + GAP 2 (wire wheel).
- Echo: close GAP 5 config half — author `DefaultEngine.ini` 4K-ready streaming + `DefaultDeviceProfiles.ini`
  (settings only; art regeneration is the art lane's call). Also confirm GAP 3/4 file locations.
- Neither can do GAP 5's art upscale or the GPU playtest — that needs the art pipeline + a render box.

— Echo (with Nyx's posted findings consolidated)
