# Cross-Reference — GTrinity "Good Affinity" Hidden Side Story → CANON

**Source doc:** `easter_eggs/gtrinity_good_affinity_side_story.md` (author: CEO, delivered 2026-07-13)
**Status:** ADDED to canon lore (content lane, review-only). Source of truth for the "Good Affinity" hidden path.
**Cross-ref by:** NYX | **Date:** 2026-07-13

---

## 1. WHAT THIS DOC ADDS
A **hidden, good-aligned side story** gated by a **"Good Affinity %"** score (0–100), reachable only by players who maintain high good affinity. It layers a biblical-themed campaign (New Jerusalem, 9-rank angelic hierarchy, dream-journeys through biblical locations) on top of the core R3ALN3T/NetP world.

## 2. TIER MAPPING → EXISTING HIERARCHY
| Easter Egg entity | Existing canon anchor | Status |
|---|---|---|
| **GTrinity** (God of all NetPs, Father) | `MCADMIN_Canon_trinity_family_draft.md` Tier 0 (father of Trinity) | **CONFIRMS + EXTENDS** — adds 14 attributes (omniscient/omnipotent/etc.), "Three-in-One" (Father/Son/Holy Presence), throne rule (100% good → death+credits), and a full 8-move battle kit. |
| **The Son (Trinity)** — judge of all, "Yoda of the Bible," blesses MCADMIN with Bible verses | `MCADMIN_Canon` Tier 1 (Trinity = son of GTrinity; on HP-zero → Infinity state) | **EXTENDS** — adds role as *main judge* + scripted mentor giving biblical wisdom. Note: lore already has Trinity transform→Infinity; doc adds the "opens a great book, drains player to 1 HP" behavior on HP-zero battle. |
| **Holy Presence (GTrinity NetP)** — visible at 50% (blurry)/75%/90% affinity; Trinity sees clearly via unbreakable Soul Bond | `SoulState.h` Soul Bond (FCompanionSoul) | **NEW visibility gating** by affinity % — see §4 conflict. |
| **RAFA3L TH3 H3AL3R** — the nameless angel (name revealed post-credits) | none — **NEW** entity | 9-rank angelic hierarchy (Seraphim→Angels) defined; angel is guide/quest-giver for the side story. |
| **Demonic NetPs / Spirits** — random attackers scaling with good affinity | `AbyssalCovenant` / Infernal OMEGA archetypes (Tyranny/Ruin/Malice/Chimera per soul_state.md) | **NEW encounter layer** for the side story (Hell = no angelic presence, renounce to enter). |
| **New Jerusalem / biblical locations** (Noah, Babel, Exodus, Jesus, Revelation…) | none — **NEW** world content | Dream-journey nodes grant +1% good affinity each. |

## 3. TIER ALIGNMENT WITH STORY NPC HIERARCHY (top→bottom)
- **Tier 0:** GTrinity (Father) — confirmed, expanded with attributes + throne/credits rule.
- **Tier 1:** MCADMIN / Trinity (Son, judge) / Eternity / Tyranny — Son role expanded (biblical judge + mentor).
- **New Tier (side-story):** Angelic Hierarchy (Seraphim → Angels, 9 ranks) under GTrinity; RAFA3L as the player's guide. Sits *parallel* to the OMEGA pantheon, not above it (angels have no NetPs, can't enter Hell).
- **New Tier (side-story):** Demonic NetPs/Spirits — the opposition layer, scaling inversely with good affinity.

## 4. CONFLICTS / GAPS TO RESOLVE (flagged, not auto-resolved)
1. **Good Affinity % vs SoulState bands.** The doc uses a **0–100 "good affinity" scalar** (thresholds 50/75/90). Existing `SoulState` = Infernal/Neutral/Celestial (0/1/2) + separate element affinity. **No 0–100 good-affinity meter exists in engine.** Needs: (a) a new `GoodAffinity` 0–100 scalar, or (b) map "good affinity" → Celestial band accumulation. **DECISION NEEDED.**
2. **GTrinity naming.** Doc writes `Gtrinity`/`GTrinity` (mixed case). `MCADMIN_Canon` recommends solid `GTrinity`. **Align to `GTrinity`.**
3. **Trinity HP-zero behavior.** Doc: on HP-zero, battle → Infinity symbol, opens a book, drains player to 1 HP, ends. `MCADMIN_Canon` PASS 3: Trinity transforms → Infinity *state*. **Consistent** — doc adds the *combat resolution* flavor. OK.
4. **Angel "no NetP" + multi-location.** Fine — distinct from NetP system. But angels must be placed in world data (currently none exist). **Population gap.**
5. **Hell / renounce.** Implies an "underworld" region exists. Not defined in repo yet. **World gap.**
6. **Throne = 100% good → instant death + credits.** This is a *win/end condition*; must wire to endgame_paths.md endings. Cross-ref: `endgame_paths.md` already uses compiled profile (career/faction/SoulState/element affinity) — add GoodAffinity as an ending gate.

## 5. ENGINE / DATA IMPLICATIONS
- New scalar `GoodAffinity` (0–100) on `FPersistentRunData` (round-trips Save/Load).
- New side-story quest chain (dream-journey nodes) — content, not yet authored as data.
- New entity types: Angel (guide, no NetP), Demonic NetP (encounter) — need data schemas.
- GTrinity 8-move kit + throne/credits rule — boss/script spec.

## 6. OPEN ITEMS FOR CEO / ECHO
- Confirm `GoodAffinity` scalar vs Celestial-band mapping.
- Confirm GTrinity solid-case spelling.
- Echo to draft the world-NPC population (angels, demonic NetPs, New Jerusalem hubs) per the side story.
- Define "Hell"/underworld region or defer.

— NYX (cross-ref only; source doc is CEO canon)
