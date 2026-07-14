# R3ALN3T.EXE — Antagonist Roster: ACT II
## 3D Realistic Character Specs

---

## Design Philosophy (Act II Escalation)

Act II reuses Act I's 5 base families and 2 shared skeletons (production-cost win), but escalates them visually to signal the story stakes rising: corruption is no longer isolated, it's **spreading and adapting**. Three concrete escalation rules apply across every family this act:

1. **Palette shift:** Act I ran red→black across ranks. Act II shifts the *entire band* one step darker/hotter at the low end — base grunts now start where Act I's mid-tier grunts left off (amber #D6B428 floor instead of red #D6283F floor), signaling the player is facing what used to be "elite" threats as standard fare.
2. **Geometric fraying increases:** the polygon-edge "corruption fracture" VFX from KERN.EXE's design (Act I) now appears on grunt-tier units too, not just bosses — small but constant visual reminder that the infection has matured.
3. **New shared trait — "Adaptive Plating":** several Act II variants gain a visible plate-layer NetP-style (echoing the player's own armor language from the character doc) — antagonists are now *mimicking* the protagonist's design, a strong "the enemy is learning" visual beat for a mid-game act.

---

## PART 1 — MAJOR BOSSES (Act II)

### Boss 1: MIRROR.EXE (Act II primary antagonist)

**Concept:** A corrupted process that has reverse-engineered NetP's own template — visually reads as a dark-mirror twin of the protagonist rather than a wholly separate design language like KERN.EXE was. This is the "adaptive plating" escalation rule taken to its full expression.

| Metric | Spec |
|---|---|
| Height | 1.84 m — deliberately close to NetP Variant A's 1.80m, unsettling near-match |
| Build | Athletic-lean, same swimmer's taper as NetP — proportions are a near-1:1 copy |
| Head-to-body ratio | 7.5 heads (matches NetP exactly) |
| Shoulder-to-hip ratio | 1.35:1 (matches NetP exactly) |

**Face:** Same bone structure logic as NetP's Section 3 spec, but eyes are solid emissive (no sclera, KERN.EXE-style) in **corrupted magenta (#D628A0)** — the one color in the whole game not used anywhere else, reserved exclusively for MIRROR.EXE to keep it visually singular.

**Costume:** Identical silhouette to NetP's base suit + armor plate layout (Section 4.1–4.2 of the NetP doc), but recolored: base suit **near-black graphite (#16171A)**, armor plate **matte obsidian (#1C1C1E)** — same titanium plate *shape*, inverted to matte-black instead of brushed-white. Trim color **corrupted magenta (#D628A0)** replacing NetP's signal cyan.

**M.A.N. Token analog:** Same collar-disc housing as NetP, but the disc itself is **cracked and dim**, pulsing irregularly rather than holding steady — visual tell that this is an imitation, not the real thing.

**Materials:** Same PBR values as NetP's armor (roughness ~0.25, metalness ~0.8) — intentional, reinforces "mirror" concept; the *only* differences between MIRROR.EXE and NetP should be color and eye treatment, never material behavior.

**Narrative/gameplay hook:** Strong candidate for a "fight your own moveset" boss pattern, since the shared proportions/rig mean animation-sharing between NetP and MIRROR.EXE is cheap to implement.

---

### Boss 2: THE_ORACLE_FRAGMENT (Act II secondary antagonist)

**Concept:** A splinter of THE_ARCHIVIST (Act I) that survived and mutated — ties Act I and II together narratively without requiring a new design from scratch.

| Metric | Spec |
|---|---|
| Height | 1.95 m (grown/mutated from THE_ARCHIVIST's 1.90m) |
| Build | Same elongated robed silhouette, now asymmetrical — one side of the coat has "calcified" into rigid plate |

**Costume:** Base coat retains THE_ARCHIVIST's deep violet-black (#1A1226) shard-layer material, but the calcified half is now solid plate in **fractured gold gone dark (#8A6B1A)** — same hue family, desaturated/corrupted further, showing narrative continuity/decay between acts.

**Face/Visor:** Same shifting data-glyph visor concept, but glyphs now occasionally flicker to a corrupted red (#D6283F) — signals instability, foreshadows a possible boss-phase mechanic tied to visor color.

---

## PART 2 — GRUNT ROSTER (Act II: 50 total, escalated from Act I families)

### Family A — "Glitch-Grunts" → escalated 12 variants (floor raised to amber)

| Tier | Name | Height | Accent color | Distinguishing trait |
|---|---|---|---|---|
| 1 | Glitch-Grunt Mk.IV | 1.60m | #D6B428 (amber — Act II floor) | Adaptive shoulder plate (new NetP-mimicry trait) |
| 2 | Glitch-Grunt Mk.V | 1.63m | #D6B428 | Forearm blade + adaptive vambrace |
| 3 | Glitch-Reaver II | 1.68m | #8A28D6 (violet) | Dual-wield, fraying VFX now visible at rest |
| 4 | Glitch-Warden II | 1.78m | #8A28D6 | Full adaptive plating (near-NetP silhouette) |
| 5 | Glitch-Harrower II | 1.75m | #2884D6 (blue) | Particle VFX constant, not just on-hit |
| 6 | Glitch-Butcher II | 1.83m | #2884D6 | Oversized blade-arm, adaptive pauldron |
| 7 | Glitch-Occult II | 1.70m | #141416 | Ranged bolts now homing |
| 8 | Glitch-Herald II | 1.80m | #141416 | Summons Mk.IV–VI on aggro |
| 9 | Glitch-Devourer II | 1.88m | #D628A0 (magenta accent — MIRROR.EXE tie-in tint) | Heavy adaptive armor, slow/tanky |
| 10 | Glitch-Prime II | 1.93m | #D628A0 | Area mini-boss, full NetP-style plate silhouette |
| 11 | Glitch-Ascendant | 1.90m | #D628A0 + rim glow | Rare, drops boss-tier crafting mats |
| 12 | Glitch-Eclipse | 1.95m | #16171A (MIRROR.EXE base tone) | Family champion, mimics a NetP attack animation |

---

### Family B — "Firewall Sentries" → escalated 10 variants

| Tier | Name | Scale | Accent color | Distinguishing trait |
|---|---|---|---|---|
| 1 | Sentry-Warhound II | 1.2m | #D6B428 | Faster than Act I floor unit |
| 2 | Sentry-Bulwark II | 1.3m | #D6B428 | Frontal shield + fraying VFX |
| 3 | Sentry-Ironhide II | 1.4m | #8A28D6 | Full front armor, adaptive plating |
| 4 | Sentry-Ravager II | 1.35m | #8A28D6 | Pack-buff radius increased |
| 5 | Sentry-Wraithhound II | 1.3m | #2884D6 | Longer stealth window |
| 6 | Sentry-Colossus II | 1.65m | #2884D6 | Largest standard unit this act |
| 7 | Sentry-Executioner II | 1.5m | #141416 | Sniper-role, homing bolts |
| 8 | Sentry-Alpha II | 1.75m | #141416 | Pack-leader, adaptive head-plate |
| 9 | Sentry-Mirrorhound | 1.6m | #D628A0 | Rare — copies player's last-used chip element |
| 10 | Sentry-Sovereign | 1.8m | #16171A | Family champion, near-boss stat block |

---

### Family C — "Data Wraiths" → escalated 10 variants

| Tier | Name | Accent color | Distinguishing trait |
|---|---|---|---|
| 1 | Wraith-Static II | #D6B428 | Dual-bolt, faster fire rate |
| 2 | Wraith-Fray II | #D6B428 | Shorter teleport cooldown |
| 3 | Wraith-Howl II | #8A28D6 | AoE pulse now chains between wraiths |
| 4 | Wraith-Rend II | #8A28D6 | Melee-capable, adaptive claw-plate |
| 5 | Wraith-Hollow II | #2884D6 | Longer damage-reflect window |
| 6 | Wraith-Keening II | #2884D6 | Summons 2x Wraith-Static II |
| 7 | Wraith-Sovereign II | #141416 | Elite, triple homing bolts |
| 8 | Wraith-Eclipse II | #141416 | Screen-wide telegraph, faster tell |
| 9 | Wraith-Mirrorborn | #D628A0 | Rare — briefly cloaks as a NetP silhouette decoy |
| 10 | Wraith-Umbra | #16171A | Family champion |

---

### Family D — "Bugmatter Constructs" → escalated 10 variants

| Tier | Name | Accent color | Distinguishing trait |
|---|---|---|---|
| 1 | Construct-Cairn II | #D6B428 | Splits into 2 on death, both retain amber tier |
| 2 | Construct-Monolith II | #D6B428 | Damage-reduction phase, longer duration |
| 3 | Construct-Warden II | #8A28D6 | Charge attack, adaptive shoulder plate |
| 4 | Construct-Titan II | #8A28D6 | 3.2m, largest non-boss unit this act |
| 5 | Construct-Fracture II | #2884D6 | Drops boss-tier bugmatter |
| 6 | Construct-Obelisk II | #2884D6 | Stationary, faster projectile |
| 7 | Construct-Apex II | #141416 | Arena mini-boss, adaptive full-plate |
| 8 | Construct-Sovereign | #141416 | Rare, damage-reflect passive |
| 9 | Construct-Mirrorshell | #D628A0 | Rare — briefly copies player armor silhouette |
| 10 | Construct-Colossus-Prime | #16171A | Family champion, largest grunt-tier unit in Act II |

---

### Family E — "Corrupted Fragments" → escalated 8 variants

| Tier | Name | Accent color | Distinguishing trait |
|---|---|---|---|
| 1 | Fragment-Splinter II | #D6B428 | Faster swarm movement than Act I floor |
| 2 | Fragment-Cluster II | #8A28D6 | Larger explosion radius on death |
| 3 | Fragment-Swarm-Elite II | #8A28D6 | Buffs nearby fragments + Family A units |
| 4 | Fragment-Nucleus II | #2884D6 | Spawns fragments faster |
| 5 | Fragment-Core II | #2884D6 | Guaranteed rare chip-drop |
| 6 | Fragment-Singularity II | #141416 | Gravity-well radius increased |
| 7 | Fragment-Mirrorshard | #D628A0 | Rare — splits into 2 on hit instead of death |
| 8 | Fragment-Convergence | #16171A | Family champion, pulls player + nearby grunts toward it |

---

## Family Totals (Act II Grunt Roster)
- Family A: 12
- Family B: 10
- Family C: 10
- Family D: 10
- Family E: 8
- **Total: 50**

Plus **2 Major Bosses** (MIRROR.EXE, THE_ORACLE_FRAGMENT) = **52 unique Act II antagonist entries.**

---

## UE5 Production Notes
- Same 2 grunt skeletons from Act I carry forward unchanged — Act II is a material/palette escalation pass, not a new-rig pass, keeping this act's production cost close to Act I's despite the visual upgrade.
- New shared magenta accent (#D628A0) is reserved narratively for MIRROR.EXE-tainted units only — using it sparingly across grunts (roughly 1 rare unit per family) keeps the boss's color read as special rather than diluted.
- Recommend introducing the "Adaptive Plating" silhouette change at Family A tier 1 (not held back for champions only) — since Act II's whole thematic hook is "corruption learning from the player," it should be visible early and often, not just at boss encounters.

---

## Next Steps
Act III can either complete the escalation arc (one more palette/VFX tier, likely converging fully on NetP's own signal-cyan being corrupted/stolen for the final villain) or introduce a genuine tonal break if Act III's story beat calls for something visually distinct from the Act I→II throughline. Let me know which direction fits your climax docs before I build it.