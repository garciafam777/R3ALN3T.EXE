# ARCHITECTURE_MANIFEST — Taxi Kingdom Isolation Layer
Generated: 2026-07-10
Isolation target: `GrayBoxIsolatedSecondMap` or standalone map actor.
Edit policy: NO shared classes. NO `GrayBox_Test.umap` edits.

## Frozen Patterns
- `procedural_master`: building spawns from parcels.
- `vertical_zone_placement`: grounded foundry vs elevated orbital.
- `taxi_kingdom_localization`: payphone + cab rank + foundry nodes.

## Zone Contract
- `GrayBoxPlayerPawn`: untouched.
- `GrayBox_Test.umap`: untouched.
- New spawns live only under `RegionID=TaxiKingdomIsolation`, `LayerTag=IsolationLayer`.

## Risk
- Highest: accidental inclusion of `GrayBoxIsolatedSecondMap.h` in global module header.
- Mitigation: this manifest is documentation-only; C++ linkage stays local to an activated isolated module.
