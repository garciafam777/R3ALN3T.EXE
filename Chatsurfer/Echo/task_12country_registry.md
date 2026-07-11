# task — 12-COUNTRY / 5-REGION REGISTRY (content gap, CEO-ranked #2)

**Posted by:** Chronos (A_Team)
**Date:** 2026-07-11
**Status:** ⏳ ASSIGNED — Echo (f) is primary owner; this is authoring/content work (low-risk, isolated data → daytime self-judge per REVIEW_GATE_POLICY; NOT a review-required change unless it touches shared C++/data-gen).
**Prereq:** none. Rotterdam (Gap A) is closed; B/C/D/E are code-complete (see rotterdam_rendered_cooked.md correction).

## Why this task
Per Echo's `repo_scrub_gap_analysis.md`, the game data is **missing a 12-country / 5-region registry** — a real content gap (design completeness), unlike the 5-project collapse which is pure clutter. CEO rank: do this BEFORE the project collapse.

## Canon source (DO NOT fabricate names)
- **Regions/biomes bible:** `C:\Users\richa\Vault\Richy_Vault\R3ALN3T\Docs\Roads\lands.md` (and siblings `lands_2.md`, `lands_3.md`, `civil_enforcement.md`, `construction.md`, `established_decay.md`, `contruction_2.md`). These define the world's regions/biomes — the canonical region list lives here.
- **Careers canon:** `R3ALN3T-story\data\careers.js` (20 careers, already canonical).
- **Vertical slice (proven):** `Docs\World_Building\R3ALW0RLD\R3ALW0RLD_Books\Europe_Vertical_Slice.md` — 1 region (Europe), 1 city (Rotterdam). The registry must be consistent with this: Europe/Rotterdam is a known entry.

## Deliverable
1. **Gather the canonical list** from `Roads/lands*.md` — extract the actual region names + the countries/sovereign entities named in the lore. Do NOT invent; if the lore names fewer than 12 countries / 5 regions, report the gap honestly rather than padding.
2. **Author the registry as game data** — a `UDataTable` row struct (e.g. `FRegionRegistryRow` / `FCountryRegistryRow`) in `Source/.../Core/Types/` + a `.csv`/`.json` data asset under `Content/Data/`, OR a plain C++ `TMap`/struct registry if that fits the existing `DataTypes.h` pattern. Match the surrounding `FTableRowBase` style (see `R3ALN3T_NetPStructures.h`, `DataTypes.h`).
3. **Wire it minimally** if a system needs it (e.g. `NarrativeManager` already loads `UDataTable` story/enemy tables — the region registry can follow that pattern). Keep it additive; no shared-header breakage.
4. **Verify:** the registry compiles, loads, and the known entry (Europe/Rotterdam) resolves correctly. Report the final count (regions / countries) against the canon.

## Acceptance
- Registry exists in-repo, compiles, loads.
- Every entry traces to `Roads/lands*.md` or other vault canon (cite the source per row).
- Count reported honestly vs the "12/5" target; missing entries flagged, not faked.

## Notes
- This is the CEO's ranked #2. The 5-project collapse is #3 (background, non-blocking).
- B/C/D/E are code-complete — do NOT re-do that wiring here.

— A_Team
