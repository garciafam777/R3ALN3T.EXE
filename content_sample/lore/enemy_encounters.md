# Enemy Encounter Scripting (Task 22) — 5 scripted encounters using sample enemies
**Node:** Content lane (Nyx, drafted; review-only). Grounded in enemy_sample.json (canon-7, named).
Each: terrain, AI behavior, win/lose.

## E1 — "Corrupted Spawn" (OMICRON, Void)
- **Terrain:** corrupted sector alley; erasure floors (Void theme).
- **AI:** rushes, uses Void chip below-ALPHA (nullified if OMEGA present — none here, so lands).
- **Win:** reduce CSI to 0. **Lose:** player CSI hits 0 first.
- **Ties to:** Act-1 node 3.

## E2 — "Tide Patrol" (NU, Aqua)
- **Terrain:** flooded corridor; pressure gates.
- **AI:** kites behind water; punishes melee approach.
- **Win:** flush it to dry tile + burst. **Lose:** drown timer expires.

## E3 — "Surge Node" (MU, Elec)
- **Terrain:** conductive grid; chain-risk.
- **AI:** chains damage across metal; isolates player.
- **Win:** break 2 relays. **Lose:** chained to 0.

## E4 — "Root Warden" (LAMBDA, Wood)
- **Terrain:** overgrowth; re-seals.
- **AI:** regenerates during lulls; punishes dawdling.
- **Win:** sever root in regen-phase. **Lose:** overrun by sprouts.

## E5 — "Cinder Flare" (ETA, Fire) — OMEGA-adjacent teaser
- **Terrain:** lava floor (pre-Throne).
- **AI:** applies -50% CSI to player's Fire NPCs (supremacy demo); not a true OMEGA, a herald.
- **Win:** survive + extinguish anchors. **Lose:** CSI attrition.
- **Ties to:** Act-1 node 12 (Fire OMEGA pressure).

## Output
Delivered as 5 encounter `.json` specs (companion file enemy_encounters.json). Each: terrain, ai_behavior, win_condition, lose_condition, tier, element.
