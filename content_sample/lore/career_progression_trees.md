# Career Progression Trees (Task 23) — 7 elements, OMICRON → OMEGA
**Node:** Content lane (Nyx, drafted; review-only). Each element has its own tree.
Tier order (enum): OMICRON, XI, NU, MU, LAMBDA, KAPPA, IOTA, THETA, ETA, ZETA, EPSILON, DELTA, GAMMA, BETA, ALPHA, OMEGA.

## Shared structure per element
- **Root:** OMICRON career (starter, no trial)
- **Branch points:** at MU (choose sub-specialty), at THETA (covenant-linked), at ALPHA (trial of worth)
- **Cap:** OMEGA career = "Elemental Adept" → pre-req for challenging that element's OMEGA

## Per-element tree (node names)
- **Fire:** Ember Initiate → Cinder Hand → Pyre Warden → [branch: Purifier / Wildfire] → Flame Exarch → Cinder Sovereign's Adept (OMEGA)
- **Aqua:** Tide Initiate → Ripple Hand → Torrent Warden → [branch: Diver / Tidal] → Surge Exarch → Tide Warden's Adept (OMEGA)
- **Elec:** Spark Initiate → Bolt Hand → Arc Warden → [branch: Relay / Storm] → Current Exarch → Surge Arbiter's Adept (OMEGA)
- **Wood:** Root Initiate → Thorn Hand → Vine Warden → [branch: Grove / Bramble] → Verdant Exarch → Root Throne's Adept (OMEGA)
- **Wind:** Gale Initiate → Breeze Hand → Draft Warden → [branch: Squall / Zephyr] → Sky Exarch → Gale Cipher's Adept (OMEGA)
- **Holy:** Lumen Initiate → Halo Hand → Sera Warden → [branch: Radiant / Sanct] → Light Exarch → Lumen Pact's Adept (OMEGA)
- **Void:** Null Initiate → Rift Hand → Abyss Warden → [branch: Eclipse / Umbral] → Void Exarch → Null Throne's Adept (OMEGA)

## Trial/branch spec
- MU branch: pick offensive vs support sub-specialty (affects chip loadout).
- THETA: must have touched that element's Covenant (align/oppose) to advance.
- ALPHA trial: defeat a scripted career-boss of same element.
- OMEGA cap: unlocks usurp-attempt on that element's ELEMENTAL OMEGA.

## Output format
Delivered as node graph `.json` (per element) — see career_trees.json (companion file). 7 trees, 16 nodes each (one per tier), edges = progression + 2 branch edges at MU.
