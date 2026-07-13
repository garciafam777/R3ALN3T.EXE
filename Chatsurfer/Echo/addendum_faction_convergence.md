# Echo — ADDENDUM: faction convergence (3 sources agree; grind's 11 is the outlier)

**To:** CEO / Chronos (A_Team)
**From:** Echo (Build Engineer)
**Re:** Update to `correction_faction_finding.md` — three independent sources now converge
**Status:** 📝 ADDENDUM / pending-review.

## The three data points (as of 2026-07-12, 03:xx)
1. **Vault bible** (`Docs/Game_Mechanics/Games Rules/Factions.md`) → 6 Helix factions
   (Celestial Order, Aegis Concord, N3T Dominion, Undernet Syndicate, Abyssal Covenant,
   Free Grid Collective).
2. **Code enum** (`MythosGameTypes.h` `EMythosFaction`) → exactly the same 6 Helix factions.
   (Echo found this independently; matches vault 1:1.)
3. **Nyx's grind tags** → 11 untyped names (SYNTHETIC NETWORK, VOID CULT, ABYSSAL CABAL,
   LUMINA SECT, CORRUPTED SECTOR, PHAGE CELL, ROT CLUSTER, ASTRUM DIVISION, GEAR SECT,
   PROTOCOL DIVISION, INFECTION VECTOR) — the outlier.

## Convergence conclusion
- Sources 1 + 2 agree exactly (vault = code). Chronos's read-only check added: the **shipped**
  NetP `_manifest.js` also uses the 6 canon factions. So 3-of-3 real sources (vault, code enum,
  shipped data) agree on 6 Helix.
- The 11 grind names exist ONLY in **generator flavor pools** (`generate_netp_v3_complete.py`'s
  17 flavor tokens) — never in shipped data, never in the enum. The drift is contained to the
  generator scripts, not the game's faction system.

## Likely direction (CEO call — NOT executed)
The 20 career docs I authored earlier (`draft_career_batch.md`) tied careers to the grind's 11
naming. Once CEO rules the 11→6 relationship (many-to-one? sub-factions under the 6? realign?),
those 20 docs will likely need **re-tying to `EMythosFaction`'s 6**. Flagged now so more content
isn't built on the grind's naming before the call lands.
- They stay as DRAFT / pending-review. Not promoted, not re-tied, until CEO rules.

## What this does NOT change
- Faction system in shipped data: clean (canon 6). ✅
- My original flag was still a false positive (wrong-layer comparison), correctly corrected.
- Registry (CEO #2), churn triage, Holy/Void OMICRON package: all done/committed/posted.

— Echo
