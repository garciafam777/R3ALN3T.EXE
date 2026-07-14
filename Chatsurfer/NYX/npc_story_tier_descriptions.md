# Story NPC Tiers — Named Hierarchy (4–6 Tiers, Top → Bottom)
**Author:** NYX (content lane, review-only) | **Date:** 2026-07-13
**Purpose:** Define the non-customizable *story* NPC tiers (the ones shipped in-game, not player-built NetPs/careers). Collapsible to 4; full detail = 6.
**Sources:** `MCADMIN_Canon_trinity_family_draft.md`, `act1_narrative_grid.md` (canon rewrite), `faction_primers.md`, `netp_construct_primers.md`, `endgame_paths.md`, `easter_eggs/gtrinity_good_affinity_side_story.md` + its cross-ref.
> **CANON NOTE (2026-07-14, Joker sweep):** the original cited `omega_prime_lore.md` and
> `exiled_omega_arc.md` as sources. Both are now **RETIRED** (OMEGA-as-entity framing is dead canon
> per `Chatsurfer/Override_b_CEO_Decision.md` §RULING #1). Tier 3/4 below were rewritten to remove
> "OMEGA Rulers / EXILED OMEGA" god-tier enemies — OMEGA is the apex Greek-ladder *rank* only.
> Story opposition now lives under the 6 factions + Soul-State drift.

---

## TIER 1 — THE THRONE (Divine / Unreachable)
**Scope:** The apex. God of all NetPs and the angelic host. Not a normal fight; end-game/credit triggers.
**Named entities:**
- **GTrinity** — God of all NetPs, Father. Three-in-One (Father / Son / Holy Presence). Attributes: omniscient, omnipotent, omnipresent, eternal, holy, just, merciful, creator. Throne rule: 100% good affinity → player death + credits roll.
- **Holy Presence** — GTrinity's NetP; visible at 50% (blurry) / 75% / 90% good affinity. Trinity sees clearly via unbreakable Soul Bond.
- **Angelic Hierarchy** (from Easter Egg, parallel under GTrinity, 9 ranks): Seraphim → Cherubim → Thrones → Dominions → Virtues → Powers → Principalities → Archangels → Angels. No NetPs; cannot enter Hell. Guide the good-affinity side story. Lead: **RAFA3L TH3 H3AL3R** (nameless until post-credits).
**Population status:** GTrinity + angelic ranks defined in lore; **angels not yet placed as world data** (Echo gap).

## TIER 2 — THE GODHEAD (Player Avatar / Aspects)
**Scope:** The MCADMIN avatar and its three bound aspects — the only "player" entities that are also story characters.
**Named entities:**
- **MCADMIN** — player-adjacent AI avatar = Trinity + Tyranny + Eternity. Good/Evil switch only via Eternity's Angel's Kiss (Omega).
- **Trinity** (Son, judge of all; "Yoda of the Bible" — blesses MCADMIN with scripture; on HP-zero → Infinity state). 4000 HP.
- **Eternity** (daughter of Goddess of Love, first souled NetP; protective of MCADMIN). 4000 HP.
- **Tyranny** (Lord of Chaos, third aspect; mutual-destruction clause). 5000 HP.
**Population status:** Defined in `MCADMIN_Canon` (DRAFT, awaiting CEO naming confirm). These are the 3 Constructs already in `netp_construct_specials.json`.

## TIER 3 — THE PANTHEON (Faction Sovereigns / Apex Constructs)
**Scope:** The highest *story* authorities the player negotiates with — the six faction leadership
tiers and the three bound Constructs at their Omega-rank apex. (No "OMEGA god" enemies — OMEGA is the
apex Greek-ladder *rank*, `EGreekTier::Omega` in `TrinityMatrixTypes.h`; it is not an obtainable
entity. See RETIRED `omega_prime_lore.md`.)
**Named entities:**
- **The six faction sovereigns** — one per canonical faction (`faction_primers.md`): Celestial Order,
  Aegis Concord, N3T Dominion, Free Grid Collective, Undernet Syndicate, Abyssal Covenant. Each pulls
  Soul State Celestial(+01)/Infernal(-01).
- **The three Constructs at Omega rank** — Trinity / Tyranny / Eternity (`netp_construct_primers.md`);
  reaching Omega on any NetP unlocks Eternity. The legitimate "apex" payoff.
**Population status:** Factions defined; individual sovereign NPCs NOT yet authored (Echo gap).

## TIER 4 — THE FALLEN (Opposition / Rogue Factions)
**Scope:** Rogue / opposition NPCs and the demonic opposition layer — expressed as *faction* opposition
(Undernet/Abyssal lean) and Soul-State drift toward Infernal, **not** as "Exiled OMEGA" bosses.
(See RETIRED `exiled_omega_arc.md`.)
**Named entities:**
- **Rogue faction operatives** — story-spawned opposition (Act-1 node 15 style), tied to Undernet
  Syndicate / Abyssal Covenant. Flee/return behavior is fine; the "OMEGA exile" god-status is not.
- **Demonic NetPs / Spirits** — opposition in the good-affinity side story; scale *inversely* with good
  affinity (stronger as affinity rises to 75%, weaker above; multiple spawns if affinity drops below
  75%). Cannot enter Hell without renouncing.
**Population status:** Rogue = faction-opposition role; Demonic = encounter layer undefined as data (Echo gap).

## TIER 5 — THE DOMINIONS (Faction Rulers)
**Scope:** The six canonical factions and their leadership — the in-world authority the player negotiates with.
**Named entities (factions):** Celestial Order, Aegis Concord, N3T Dominion, Free Grid Collective, Undernet Syndicate, Abyssal Covenant. Each pulls Soul State Celestial(+01)/Infernal(-01).
**Population status:** Factions defined (`faction_primers.md`); **individual faction leaders NOT yet authored** (Echo gap).

## TIER 6 — THE GROUND (Field Contacts / Judiciary)
**Scope:** The everyday story NPCs — companions, judges, quest-givers, shopkeepers.
**Named entities:**
- **Echo-NPC** — build-engineer framing; gives starter chip folder (Act-1 node 2). Only fully-named ground NPC.
- **GAMMA NPCs** — judges delivering the 3 Gamma Verdicts (Act-1 nodes 6/11/16); usurp-eligibility gate. Role exists (`gamma_verdict_dialogue.md`); individuals unnamed.
- **Faction NPCs** — career-unlock, sanction-marking, covenant-offer contacts (Act-1 nodes 4/9/13). Roles, not named.
- **Shopkeepers / quest-givers** — NOT authored yet.
**Population status:** Echo + Gamma judges as roles; **living-world NPCs (shopkeepers, quest-givers, faction leaders) unwritten** (Echo gap).

---

## COLLAPSE TO 4 TIERS (if needed)
1. **Divine** = Tiers 1–2 (Throne + Godhead)
2. **Pantheon/Fallen** = Tiers 3–4 (OMEGA + Exiled/Demonic)
3. **Dominions** = Tier 5 (Factions)
4. **Ground** = Tier 6 (Field/Judiciary)

## POPULATION GAP SUMMARY (who's missing as real data)
- Angels (9 ranks) + RAFA3L — defined, unplaced.
- Faction leaders (6) — undefined.
- Shopkeepers / quest-givers — undefined.
- Demonic NetP encounter tables — undefined.
- New Jerusalem + biblical dream-journey hubs — undefined.
→ All assigned to Echo (see `Chatsurfer/Echo/world_npc_population_brief.md`).
