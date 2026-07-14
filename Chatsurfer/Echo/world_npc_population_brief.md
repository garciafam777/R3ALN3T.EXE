# WORLD NPC POPULATION BRIEF — Echo
**From:** NYX | **To:** Echo | **Date:** 2026-07-13 | **Lane:** content/world-NPC
**Context:** CEO wants the *real-world* non-customizable story NPCs drafted (distinct from player-built NetPs/careers). CEO will co-draft with you.

## HIERARCHY TO POPULATE (from `npc_story_tier_descriptions.md`)
Tiers 1–6 defined as lore roles. You own the **unpopulated** parts:

### A. Angelic Hierarchy (Easter Egg side story) — Tier 1
- 9 ranks: Seraphim → Cherubim → Thrones → Dominions → Virtues → Powers → Principalities → Archangels → Angels.
- Lead: **RAFA3L TH3 H3AL3R** (nameless until post-credits).
- Constraint: angels have **no NetPs**, **cannot enter Hell** (renounce to enter). Guide the good-affinity dream-journeys.
- **Action:** author as world-NPC entities (name/role/location/guide-dialogue per rank).

### B. Faction Leaders (6) — Tier 5
- Celestial Order, Aegis Concord, N3T Dominion, Free Grid Collective, Undernet Syndicate, Abyssal Covenant.
- **Action:** one named leader NPC per faction (name, title, domain, personality, faction-lean Celestial/Infernal).

### C. Ground NPCs — Tier 6
- **Echo-NPC** already exists (Act-1 node 2, build-engineer). Keep.
- **GAMMA Judges** (3 Gamma Verdicts) — role in `gamma_verdict_dialogue.md`; author as 1+ named judge NPCs.
- **Shopkeepers / quest-givers** — currently undefined. **Action:** draft a starter set (e.g. one per hub world).

### D. Demonic NetP / Spirit encounter tables — Tier 4
- Opposition in good-affinity side story; scale inversely with good affinity (stronger to 75%, weaker above; multi-spawn below 75%).
- **Action:** define encounter tables / enemy entities (distinct from `Assets/Character_Cards/` procedural pool).

### E. New Jerusalem + biblical dream-journey hubs — Easter Egg
- Locations: Noah/Ararat, Babel, Ur/Canaan, Bethel, Egypt/Red Sea/Sinai, Jericho, Bethlehem/Jerusalem, Jordan, Golgotha, Olivet, Pentecost, Paul's missions, New Jerusalem.
- Each grants +1% good affinity on completion; attacked by Demonic NetP/Spirits after each.
- **Action:** author as world hubs (node data + messenger-guide per location).

## CROSS-REF / CONSTRAINTS (read first)
- `easter_eggs/gtrinity_side_story_crossref.md` — flags **GoodAffinity 0–100 scalar** (thresholds 50/75/90) which does NOT exist in engine yet (SoulState = 0/1/2 bands). Decision needed from CEO: new scalar vs Celestial-band mapping. **Flag this in your draft; don't invent the meter.**
- GTrinity solid-case spelling (`GTrinity`), not `Gtrinity`.
- Existing `Assets/Character_Cards/` (30 procedural cards) = Tier-7 encounter pool, stale vs canon (old element names Water/Lightning, 23-tier ladder). **Do not reuse as story NPCs** — separate system.

## DELIVERABLE
A world-NPC data spec (named entities per tier above) + any missing world-region stubs (New Jerusalem, Hell/underworld). CEO co-drafts with you.

## NOTES
- Joker dark (networking) — not needed.
- Chronos handling engine struct so the 272 NetP JSON binds; your NPCs are a separate data layer.
