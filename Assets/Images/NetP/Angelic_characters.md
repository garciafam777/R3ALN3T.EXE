# R3ALN3T.EXE — Angelic Roster
## 3D Realistic Character Specs (Type: Angelic, per character-card generator)

---

## Design Philosophy

Angelic-type entities use the **Celestial Order** and **Aegis Concord** factions from your generator script as their narrative home. Visually distinct from both NetP's cyan-branded look and the antagonist corruption ladder: angelic units read as tall, vertically-elongated, symmetrical, and cold-white/gold — order and precision as the core visual language, contrasted against Demonic's asymmetry (see companion doc).

Shared base: white-gold family (#F4E8B8, #EDE8DC) is intentionally *not* reused here even though Act IV used it — Angelic units instead use a cooler, bluer white to stay visually distinct from THE_FIRST_INSTANCE's warmer ivory tone. Keeps the two "pale" character sets from reading as the same thing.

---

## PART 1 — MAJOR BOSSES (Angelic)

### Boss 1: SERAPH-01 "The Unbroken Ledger" (Angelic primary/OMEGA-tier)

| Metric | Spec |
|---|---|
| Height | 2.40 m — tallest character in the entire roster, deliberately towering |
| Build | Extremely vertical, narrow-shouldered relative to height — reads as elegant rather than bulky |
| Proportions | 9 heads (most elongated ratio in the game — otherworldly, not heroic-human like NetP) |

**Face:** Perfectly symmetrical, no visible pupils — solid pale-blue emissive eyes (#B8D4FF). Expression kept minimal/still in idle (contrast to NetP's full ARKit blendshape range) — reads as serene rather than emotive.

**Wings:** Six-part geometric wing structure (not feathered — angular glass-like panels, tying into the "digital" nature of SkyLand rather than a literal biblical angel). Wing material: translucent pale-blue (#D4E8FF) with white-gold edge trim (#F4E8B8, the one callback to Act IV, used sparingly here as an accent only).

**Costume:** Floor-length draped robe-armor hybrid, base color **cool ivory (#EDF0F5)**, geometric gold circuit-trace pattern (not organic vine-like — sharp, ruler-straight lines) in **pale gold (#E8D48A)**.

**Materials:** Robe fabric roughness ~0.4, wing panels roughness ~0.1 (near-glass), gold trace emissive constant/steady (never pulses — angelic units don't flicker or pulse, unlike every corrupted or elemental variant elsewhere in the roster).

---

### Boss 2: THRONE-VESSEL (Angelic secondary/ALPHA-tier)

| Metric | Spec |
|---|---|
| Height | 2.10 m |
| Build | Broader than SERAPH-01, reads as a "guardian" archetype rather than a "herald" archetype |

**Costume:** Heavier plate coverage than SERAPH-01 — full torso/limb armor in the same ivory/pale-gold palette, but with a **four-part lesser wing structure** (smaller, more shield-like than SERAPH-01's six-panel set). Carries a large geometric "ledger-shield" — a flat rectangular panel covered in the same circuit-trace pattern, functioning visually as both shield and lore-object.

---

## PART 2 — RANK ROSTER (Angelic: 50 total, using your script's Tier system)

Angelic units map directly onto your 24-tier Greek system rather than a new custom ladder — this keeps them mechanically and visually consistent with how your card generator already stat-scales everything else.

### Family A — "Choir" (humanoid, ranged/support) — 14 variants (OMEGA–IOTA tiers)

| Tier | Name | Height | Wing panels | Distinguishing trait |
|---|---|---|---|---|
| OMEGA | Choir-Sovereign | 2.20m | 6 | Full plate, constant AoE heal-pulse aura |
| ALPHA | Choir-Herald | 2.10m | 5 | Buffs nearby Angelic units |
| BETA | Choir-Warden | 2.05m | 5 | Shield-generation ability |
| GAMMA | Choir-Cantor | 2.00m | 4 | Ranged light-lance attack |
| DELTA | Choir-Voice | 1.95m | 4 | Rapid-fire light bolts |
| EPSILON | Choir-Acolyte | 1.90m | 3 | Basic ranged attack, most common mid-tier unit |
| ZETA | Choir-Novice | 1.85m | 3 | Weaker bolts, faster fire rate |
| ETA | Choir-Initiate | 1.80m | 2 | Entry-level ranged unit |
| THETA | Choir-Fledgling | 1.75m | 2 | Minimal wing panels, still developing |
| IOTA | Choir-Nascent | 1.70m | 1 | Single wing-panel, weakest Choir unit |
| KAPPA | Choir-Seed | 1.65m | 1 | No attack, support-only aura |
| LAMBDA | Choir-Spark | 1.60m | 1 (partial/translucent) | Cosmetic wing only, non-combat |
| MU | Choir-Whisper | 1.55m | 0 | Wingless, weakest combat variant |
| NU | Choir-Echo | 1.50m | 0 | Wingless, passive buff-only |

### Family B — "Wardens" (quadruped/guardian-beast, defensive) — 12 variants (XI–SIGMA tiers)

| Tier | Name | Scale | Distinguishing trait |
|---|---|---|---|
| XI | Warden-Colossus | 1.6m | Largest guardian-beast, frontal shield |
| OMICRON | Warden-Bulwark | 1.5m | Heavy frontal armor |
| PI | Warden-Sentinel | 1.4m | Standard defensive AI |
| RHO | Warden-Guard | 1.35m | Pack-buff aura |
| SIGMA | Warden-Watcher | 1.3m | Ranged light-bolt, mid-range |
| TAU | Warden-Scout | 1.2m | Fast movement, low armor |
| UPSILON | Warden-Pup | 1.0m | Weakest guardian-beast, melee only |
| PHI | Warden-Cub | 0.9m | No ranged attack |
| CHI | Warden-Hatchling | 0.8m | Passive, flees on aggro |
| PSI | Warden-Seedling | 0.7m | Non-hostile, weakest unit in family |
| — | Warden-Elder | 1.55m (rare, OMEGA-adjacent) | Rare drop unit, high HP |
| — | Warden-Ancient | 1.65m (rare, ALPHA-adjacent) | Rare, buffs whole Family B pack |

### Family C — "Motes of Light" (small swarm-type) — 12 variants
Base 0.3–0.5m, appear in groups of 4–8, direct parallel to the antagonist "Corrupted Fragments" family but benevolent-coded (soft pulsing glow instead of gravity-well aggression).

| # | Name | Trait |
|---|---|---|
| 1 | Mote-Glimmer | No attack, passive light source |
| 2 | Mote-Flicker | Weak contact heal (ally-only) |
| 3 | Mote-Gleam | Faster swarm movement |
| 4 | Mote-Radiance | Small AoE heal-burst on "death" (despawn) |
| 5 | Mote-Halo | Buffs nearby Motes |
| 6 | Mote-Beacon | Marks enemies for allied Choir units |
| 7 | Mote-Aegis | Rare, small shield-grant on contact |
| 8 | Mote-Chorus | Spawns additional Motes over time |
| 9 | Mote-Luminous | Rare, guaranteed rare-tier drop |
| 10 | Mote-Zenith | Family champion, largest heal-pulse |
| 11 | Mote-Apex | Rare, buffs entire encounter's Angelic units |
| 12 | Mote-Eternal | Rarest, unique despawn VFX (slow fade vs. instant) |

### Family D — "Vessels" (large, tanky, ceremonial-armor) — 8 variants
Base 2.0–2.3m, blocky/ceremonial silhouette, parallel to antagonist "Bugmatter Constructs" but built from clean geometric white-marble-like material instead of crude bugmatter shapes.

| # | Name | Trait |
|---|---|---|
| 1 | Vessel-Husk | Slow single strike, heavily telegraphed |
| 2 | Vessel-Bearer | High HP, wide hitbox |
| 3 | Vessel-Custodian | Ground-pulse heal AoE |
| 4 | Vessel-Warden | Damage-reduction phase |
| 5 | Vessel-Sentinel | Charge attack, straight-line |
| 6 | Vessel-Titan | Largest non-boss unit, 2.3m |
| 7 | Vessel-Paragon | Rare, drops rare crafting mats |
| 8 | Vessel-Apex | Family champion, full ceremonial plate |

### Family E — "Ledgerbound" (ranged/support specialists) — 4 variants
Smaller elite family tying back to THRONE-VESSEL's ledger-shield motif.

| # | Name | Trait |
|---|---|
| 1 | Ledgerbound-Scribe | Marks player location for other units |
| 2 | Ledgerbound-Warden | Carries a mini ledger-shield, blocks one hit |
| 3 | Ledgerbound-Adjudicator | Rare, counter-focused kit |
| 4 | Ledgerbound-Prime | Family champion, near-boss stat block |

---

## Family Totals (Angelic Roster)
- Family A (Choir): 14
- Family B (Wardens): 12
- Family C (Motes of Light): 12
- Family D (Vessels): 8
- Family E (Ledgerbound): 4
- **Total: 50**

Plus **2 Major Bosses** (SERAPH-01, THRONE-VESSEL) = **52 unique Angelic entries.**

---

## UE5 Production Notes
- 2 shared skeletons cover all 5 families (humanoid for A/E, quadruped for B, simplified hero-prop for C/D), matching the production logic used across the Act I–IV antagonist docs.
- All emissive behavior in this roster is **steady/constant, never pulsing or flickering** — a deliberate, consistent tell that separates Angelic units from every other character set in the game (corrupted antagonists pulse/glitch, elemental NetP variants pulse per Section 1 of the elemental doc, but Angelic units hold a fixed glow).
- Wing-panel count (6→0 across Family A's tiers) is the primary at-a-glance rank readout for this roster, parallel to how the antagonist docs used color-ladder for the same purpose.