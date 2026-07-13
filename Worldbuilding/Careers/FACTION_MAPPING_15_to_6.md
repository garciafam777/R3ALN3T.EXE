# Faction Mapping — generator flavor names → 6 Helix (EMythosFaction) CANON

**Ruled by:** CEO (verbal, via A_Team acting-CEO + "go" 2026-07-12)
**Recorded by:** Echo (Build Engineer)
**Supersedes:** earlier `FACTION_MAPPING_11_to_6.md` (which missed 4 generator names — see HARDENING below)
**Canon basis:** 3 independent sources converge on 6 Helix factions —
1. Vault bible `Docs/Game_Mechanics/Games Rules/Factions.md`
2. Code enum `MythosGameTypes.h` → `EMythosFaction`
3. Chronos-verified shipped `_manifest.js` (6 canon factions only)

**Ruling:** 6 Helix factions are canonical. Generator flavor-pool names are NOT a faction
system — they map MANY-TO-ONE onto the 6. This doc is the translation layer.

## ⚠️ HARDENING (found 2026-07-12 via static validation pass)
The generator `ALIGNMENTS` dict (`generate_netp_v3_complete.py`) emits **15 distinct faction
names**, not 11. The previous 11-name doc was INCOMPLETE. Also `CELESTIAL ORDER` is emitted
ALL-CAPS in the generator but title-case ("Celestial Order") in shipped data — a case-variant
silent-failure risk if any lookup is case-sensitive.
- **4 EXTRA names not previously mapped:** IRON CORTEX, HALO CORE, PANDEMONIUM NET, BRIMSTONE CELL.
- **Resolution mechanism (good news):** `MythosGameMode.cpp` hardcodes `EMythosFaction` directly
  in C++ (no runtime string→enum lookup for factions). The 15 names live ONLY in Python
  generators as flavor pools — they are NOT wired into the engine's enum-resolution path. So
  there is no silent string-fallback in shipped code today. The risk is contained to generator
  output that could later be wired to a faction field.
- **The generator itself says:** "Do NOT 'fix' these flavor pools to match the 6 — they are a
  separate concern." So the designers intended flavor≠canon. But NO validation enforces that a
  flavor name never leaks into a faction-enum field.

## Complete mapping (15 names → 6 Helix) — Echo's proposal, CEO can adjust
| Generator flavor name | → EMythosFaction | Alignment group |
|----------------------|-----------------|-----------------|
| LUMINA SECT | CelestialOrder | Angelic |
| CELESTIAL ORDER | CelestialOrder | Angelic |
| ASTRUM DIVISION | AegisConcord | Angelic |
| HALO CORE | CelestialOrder | Angelic |
| PROTOCOL DIVISION | AegisConcord | Mechanical |
| SYNTHETIC NETWORK | N3TDominion | Mechanical |
| GEAR SECT | N3TDominion | Mechanical |
| IRON CORTEX | N3TDominion | Mechanical |
| CORRUPTED SECTOR | UndernetSyndicate | Viral |
| PHAGE CELL | FreeGridCollective | Viral |
| ROT CLUSTER | UndernetSyndicate | Viral |
| INFECTION VECTOR | FreeGridCollective | Viral |
| ABYSSAL CABAL | AbyssalCovenant | Demonic |
| VOID CULT | AbyssalCovenant | Demonic |
| PANDEMONIUM NET | AbyssalCovenant | Demonic |
| BRIMSTONE CELL | AbyssalCovenant | Demonic |

## Required hardening (for Nyx, when wiring data→enum)
1. **Normalize before lookup:** trim + case-fold (e.g. "CELESTIAL ORDER" → "celestial order")
   before any string→enum match. Prevents the ALL-CAPS variant from failing a strict match.
2. **No silent default:** if a flavor name doesn't resolve, LOG-AND-SKIP or ASSERT — never
   default to FreeGridCollective silently. A hard failure surfaces the gap instead of hiding it.
3. **Validation script:** a standalone pass (no UE launch) that loads this doc + all generator
   outputs and asserts every emitted faction string resolves to one of the 6. Run in CI/data-gen.
4. **This doc = single source of truth** for the 15→6 mapping. If a 16th name appears, it fails
   the validation and gets added here explicitly.

## Action taken
- 20 career docs re-tied (separate commit) using the 11-name subset; the 4 extras don't appear
  in the careers, so no career references them. Careers remain draft/pending-review.
- This doc now covers all 15. Element + geography axes in careers left intact.

— Echo
