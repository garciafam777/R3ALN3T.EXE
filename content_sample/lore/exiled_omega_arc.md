# Exiled OMEGA Arc Template (Task 19)
**Node:** Content lane (Nyx, drafted; review-only). Reusable framework for fallen OMEGAs.

## How they fell (template)
1. Held ESupremacyTier::ELEMENTAL over a domain.
2. Violated the Covenant (betrayed pantheon / player / Prime).
3. Stripped of title → ESupremacyTier::EXILED but retains OMEGA-tier power.
4. Becomes a story-spawned wildcard (NOT in base 8; not in random pools).

## Where they hide
- Off-grid: a severed subnet, a deleted sector pocket, a frozen save-state.
- Gated behind a faction flag the player must earn.

## What they want
- Vengeance on the pantheon, or re-ascension, or to drag the player down with them.

## Reusable fields (JSON shape)
```
{
  "id": "EXILED-<element>-<n>",
  "domain_element": "<canon7>",
  "supremacy_tier": "EXILED",
  "fell_reason": "<text>",
  "hideout": "<zone>",
  "motivation": "<text>",
  "return_trigger": "<flag>",
  "reward_on_defeat": "<loot/covenant>"
}
```

## Example 1 — EXILED-Fire-01 "Ashfall"
- **Fell:** Cinder Sovereign purged them for sharing fire-blessing with the player without tithe.
- **Hideout:** a scorched backup partition (CORRUPTED SECTOR deep layer).
- **Wants:** to reignite the whole grid, regardless of life.
- **Return trigger:** player holds 2 GAMMA verdicts + enters the burn-zone.
- **Reward:** unique Fire chip "Cinderfall" + lore flag.

## Example 2 — EXILED-Void-01 "The Deleted"
- **Fell:** Null Throne erased them for refusing deletion of a civilian subnet.
- **Hideout:** the un-deleted sector (void-loop pocket).
- **Wants:** to un-delete everything, including the player's enemies.
- **Return trigger:** player completes Gamma verdict III in their favor.
- **Reward:** Void chip "Unmake" + allied Echo-NPC contact.
