# GrayBoxIsolatedSecondMap
Second-zone gray-box module scaffold.
Zero shared-file edits. Zero shared C++ class modifications.

## Contents
- `Public/GrayBoxIsolationManifest.h` — frozen zone/patch contract.
- `Public/GrayBoxIsolatedSecondMap.h` — map actor header.
- `Private/GrayBoxIsolatedSecondMap.cpp` — map actor implementation.

## Enable later
When Joker/SSH passes or workstation SSH is ready, add this module to:
`Prototypes/R3ALN3T_EXE/R3ALN3T_EXE.Build.cs`:
```
PublicDependencyModuleNames.AddRange(new string[] { "GrayBoxIsolatedSecondMap" });
```
Do NOT add it now while offline; do not edit shared `.Build.cs` until confirm.

## Region flavor
Taxi Kingdom: payphone, cab rank, magnetic track, foundry perimeter.
Layer tag: `IsolationLayer`, `RegionID=TaxiKingdomIsolation`.
