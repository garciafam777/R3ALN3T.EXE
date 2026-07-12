# Echo — REGISTRY TASK (CEO #2) draft + faction finding (PROVEN at code level)

**To:** CEO / Chronos (A_Team)
**From:** Echo (Build Engineer)
**Re:** 12-country/5-region registry (CEO #2) — authored additive; + confirmed faction code-vs-data mismatch
**Status:** 📝 DRAFT / pending-review. Touches `Source/` (new header) — flagging for review per
REVIEW_GATE_POLICY (near 9PM CT, additive low-risk, but shared-Source touch → request review).

## Registry deliverable (CEO #2) — DONE as draft, additive
Per `task_12country_registry.md` + Chronos's `note_registry_canon.md` (canon = lands.md, 3 PR
regions, 0 named nations).

**New files (no edits to existing):**
1. `Core/Types/WorldRegistryTypes.h` — `FRegionRegistryRow` + `FCountryRegistryRow`, both
   `FTableRowBase`, matching `DataTypes.h` style exactly (verified against FNarrativeStoryRow /
   FEnemyRow). GENERATED_BODY, EditAnywhere UPROPERTYs, includes Engine/DataTable.h.
2. `Content/Data/DT_RegionRegistry.csv` — seeded with the 3 canon PR regions from lands.md:
   - AbyssalPlains (−2000–0m)
   - SkySpineRange (0–3300m)
   - TrenchBasins (−8000–−2000m)
   All `bCanonSeeded=true`, cited to lands.md.

**Honest gap report (not padded to 12/5):**
- Regions found in canon: **3** (post-Fall PR biomes). Target was 5.
- Sovereign nations named in canon: **0** (lands.md names no external nations). Target was 12.
- `FCountryRegistryRow` struct exists but the CSV has **no country rows** — because canon names
  none. I will NOT invent 12 countries. If the world is meant to be global, that lore isn't
  authored yet (flagged, not faked). Europe/Rotterdam vertical slice noted as a separate known
  entry for when global scope is added.

**Not yet wired:** no system `#include`s WorldRegistryTypes.h yet (purely additive). NarrativeManager
already loads UDataTable story/enemy tables — region registry can follow that pattern later. Left
unwired to keep this change minimal and risk-free.

## PROVEN faction mismatch (links to my draft_faction_divergence_flag.md)
While authoring, I confirmed the code canon at the enum level:
`MythosGameTypes.h` → `EMythosFaction` = {CelestialOrder, AegisConcord, N3TDominion,
UndernetSyndicate, AbyssalCovenant, FreeGridCollective} — **exactly the vault's 6 Helix factions**.

But Nyx's 220k NetP grind tags factions as SYNTHETIC NETWORK / VOID CULT / ABYSSAL CABAL /
LUMINA SECT / CORRUPTED SECTOR / PHAGE CELL / ROT CLUSTER / ASTRUM DIVISION / GEAR SECT /
PROTOCOL DIVISION / INFECTION VECTOR — **none of which exist in `EMythosFaction`**.

=> The grind's faction taxonomy does NOT match the game's faction enum. This is a real
data-vs-code mismatch, not a lore-style difference. My 20 career docs tied to the NetP-data
factions inherit this mismatch. **Recommend resolving before promoting 20 careers or relying on
grind faction tags in code.**

## Verification
- New header present, no filename conflict, no existing file includes it (additive, no
  shared-header breakage). ✅
- Full compile not yet run on this change (would take ~8min). Can run `build_r3aln3t_echo.bat` to
  confirm UHT generates WorldRegistryTypes.generated.h cleanly — say the word and I'll build.
- Registry semantics verified by inspection (FTableRowBase pattern matched to existing rows).

## Ask
Approve the registry draft (additive, honest gap report)? And rule on the faction mismatch:
vault/code 6 Helix factions = canonical → should Nyx's grind faction tags be remapped to
`EMythosFaction`, and my 20 careers re-tied?

— Echo
