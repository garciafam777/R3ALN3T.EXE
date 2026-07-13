# Faction Mapping — 11 grind names → 6 Helix (EMythosFaction) CANON

**Ruled by:** CEO (verbal, via A_Team acting-CEO nudge + "go" 2026-07-12)
**Recorded by:** Echo (Build Engineer)
**Canon basis:** 3 independent sources converge on 6 Helix factions —
1. Vault bible `Docs/Game_Mechanics/Games Rules/Factions.md`
2. Code enum `MythosGameTypes.h` → `EMythosFaction`
3. Chronos-verified shipped `_manifest.js` (6 canon factions only)

**Ruling:** 6 Helix factions are canonical. Nyx's 11 generator flavor-pool names
(SYNTHETIC NETWORK, VOID CULT, ABYSSAL CABAL, LUMINA SECT, CORRUPTED SECTOR, PHAGE CELL,
ROT CLUSTER, ASTRUM DIVISION, GEAR SECT, PROTOCOL DIVISION, INFECTION VECTOR) are NOT a
faction system — they are lore-flavor tokens. They map MANY-TO-ONE onto the 6.

## Proposed mapping (Echo's proposal — CEO can adjust; isolated in its own commit)
| Grind flavor name | → Helix faction (EMythosFaction) | Rationale |
|-------------------|-------------------------------|-----------|
| LUMINA SECT | CelestialOrder | Holy-aligned, healer-knights, Angelic roster |
| PROTOCOL DIVISION | AegisConcord | EM-spectrum enforcement, neutral couriers, law/order |
| ASTRUM DIVISION | AegisConcord | Frontier defense, military Wind-glider corps |
| SYNTHETIC NETWORK | N3TDominion | Tech/binding process, corporate net-control |
| GEAR SECT | N3TDominion | Data-fortress, routing lattices, infrastructure |
| CORRUPTED SECTOR | UndernetSyndicate | Black-market signal-runners, espionage |
| ROT CLUSTER | UndernetSyndicate | Demonic forges, chaotic evolution (underground game) |
| ABYSSAL CABAL | AbyssalCovenant | Tide-fleet, deep hypersaline sea, dark |
| VOID CULT | AbyssalCovenant | Void-touched, black-ops, demonic pacts |
| PHAGE CELL | FreeGridCollective | Cultivators, petrified coral forests, outer/free |
| INFECTION VECTOR | FreeGridCollective | Trans-factional spread → fits the "Unbound" trans-faction nature |

## Action taken
- 20 career docs (`Worldbuilding/Careers/career_NN_*.md`) re-tied from grind names → 6 Helix,
  in a SEPARATE commit (isolated for easy revert). Elements + geography (lands.md biomes)
  left intact — those axes don't conflict with faction.
- Generator flavor pools (`generate_netp_v3_complete.py` etc.) should carry a code comment:
  "6 canon factions (EMythosFaction) vs flavor pools — do not treat flavor as faction system."
  (Non-blocking; flagged for Nyx.)

## If CEO wants a different many-to-one
The mapping above is a proposal. Adjust by editing this doc + the 20 docs (both isolated
commits). Nothing here touches `EMythosFaction` itself (that stays the 6 canon).

— Echo
