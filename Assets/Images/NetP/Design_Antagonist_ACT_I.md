# R3ALN3T.EXE — Antagonist Roster: ACT I
## 3D Realistic Character Specs

---

## Design Philosophy

Antagonists are visually coded as **corruption of NetP's own design language** — same material logic (bodysuit + segmented plating + emissive circuitry), but inverted palette, degraded geometry, and asymmetric silhouettes. Where NetP reads clean/vertical/balanced, antagonists read jagged/off-axis/fraying — literal "bad data."

Roster splits into two tiers:
- **Major Bosses** (1–2 per act): full unique narrative-driven specs, boss-fight-grade detail.
- **Grunt Roster** (50 per act): organized into **Families** — a shared base template per family with tiered variants (escalating corruption/rank). Each variant still carries a complete, distinct spec (proportions, palette, material, trait) — this mirrors the aura-band system from NetP's doc, just applied to enemy design instead of morality state.

---

## PART 1 — MAJOR BOSSES (Act I)

### Boss 1: KERN.EXE (Act I primary antagonist)

**Concept:** A corrupted kernel-process given humanoid form — the "anti-NetP," same base rig, inverted everything.

| Metric | Spec |
|---|---|
| Height | 2.05 m (6'9") — deliberately taller than either NetP variant, reads as looming in cutscenes |
| Build | Broad-shouldered, asymmetric — right side over-armored, left side exposed/frayed data-mesh |
| Head-to-body ratio | 7 heads (slightly stockier than NetP's 7.5 — reads heavier, less agile) |
| Shoulder-to-hip ratio | 1.5:1 |
| Hands | Right hand normal proportion; left hand elongated, claw-tipped (visual "instability" tell) |

**Face:** Angular, gaunt cheek hollows, no visible pupils — just solid emissive iris (no sclera at all, unlike NetP's human-white sclera). Reads as "not fully rendered."

**Skin/base layer:** Same subsurface-scatter logic as NetP but desaturated to near-grey (#4A4A4E), with **visible seam-splitting** on the left arm/torso — geometry literally shows polygon-edge fraying as a stylized "corruption" VFX built into the mesh, not just a texture.

**Armor:** Fractured obsidian-black plating (#141416), asymmetric coverage (heavy right pauldron/vambrace, minimal left side). Trim color: **Corrupted red (#D6283F)** — matches your Soul State "Corrupted" band exactly, reinforcing that KERN.EXE sits at the bottom of the same morality scale NetP's aura system tracks.

**Signature element:** No M.A.N. Token — instead, a **cracked token socket**, empty, at the collar. Visual shorthand: this is what NetP becomes without one. Strong thematic hook for Act I climax if you want it.

**Materials:** Plate roughness ~0.6 (duller than NetP's 0.25 — "corrupted" reads as matte/damaged rather than sleek), metalness ~0.7.

---

### Boss 2: THE_ARCHIVIST (Act I secondary/mid-act antagonist)

**Concept:** A rogue data-librarian entity — quieter, less physical threat, more "corrupting information" theme. Good foil if KERN.EXE is the brute-force boss.

| Metric | Spec |
|---|---|
| Height | 1.90 m (6'3") |
| Build | Thin, elongated, robed silhouette (reads as least "combat" of your bosses — good visual variety) |
| Head-to-body ratio | 8 heads (deliberately stretched, unsettling) |

**Face:** Obscured — visor-mask made of shifting data-glyph fragments (procedural texture scroll, cheap VFX trick, high visual payoff).

**Costume:** Long draped "coat" built from layered data-fragment plates (not solid cloth — reads as thousands of thin overlapping shards, like a feather coat but digital). Base color: **deep violet-black (#1A1226)**, trim in **fractured gold (#C9A227)** — signals "corrupted knowledge/currency" theme, distinct from KERN.EXE's red so players read them as separate threats immediately.

**Materials:** No metalness on the coat — matte fabric-like shader on the shard layers, each shard has a subtle independent sway (cloth-sim or bone-chain rig) for a "restless" idle animation.

---

## PART 2 — GRUNT ROSTER (Act I: 50 total)

### Shared Base Template (all Act I grunt families)
- Rig: shared humanoid/quadruped base skeletons (2 base skeletons cover all 5 families below — keeps animation cost sane)
- Material logic: same "corrupted NetP" language as bosses — desaturated base + emissive fracture lines
- All families tie to a Greek chip-code glyph family for loot/data-drop consistency with your 108 Ghost Data system

---

### Family A — "Glitch-Grunts" (humanoid, melee) — 12 variants
Base: 1.6m humanoid, hunched posture, matte-grey suit (#5C5C60), no full armor — cheapest unit to render, appears in largest numbers.

| Tier | Name | Height | Accent color | Distinguishing trait |
|---|---|---|---|---|
| 1 | Glitch-Grunt Mk.I | 1.55m | #D6283F (red) | Bare-fisted, single cracked shoulder plate |
| 2 | Glitch-Grunt Mk.II | 1.60m | #D6283F | Adds forearm blade fragment |
| 3 | Glitch-Grunt Mk.III | 1.65m | #D67A28 (orange) | Both arms bladed |
| 4 | Glitch-Sentinel | 1.70m | #D67A28 | Chest plate added, slower/tankier |
| 5 | Glitch-Reaver | 1.68m | #D6B428 (amber) | Dual-wield, faster attack anim |
| 6 | Glitch-Warden | 1.75m | #D6B428 | Full torso armor, shield-arm |
| 7 | Glitch-Harrower | 1.72m | #8A28D6 (violet — rare/elite tinting) | Emissive crack pattern intensifies, minor particle VFX |
| 8 | Glitch-Butcher | 1.80m | #8A28D6 | Oversized single blade-arm |
| 9 | Glitch-Occult | 1.66m | #2884D6 (blue — "inverted" rare tint) | Ranged data-bolt variant, no melee |
| 10 | Glitch-Herald | 1.78m | #2884D6 | Mini-boss tier, summons Mk.I–III on aggro |
| 11 | Glitch-Devourer | 1.85m | #141416 (near-black, top corruption) | Armor near-total, slow but heavy damage |
| 12 | Glitch-Prime | 1.90m | #141416 + full emissive red rim | Family "champion," guaranteed rare drop, functions as area mini-boss |

---

### Family B — "Firewall Sentries" (quadruped, defensive/turret-like) — 10 variants
Base: 1.2m at shoulder, 2.0m long, low quadruped stance, heavy plating concentrated on front/head — reads as a guard-dog/turret hybrid.

| Tier | Name | Scale | Accent color | Distinguishing trait |
|---|---|---|---|---|
| 1 | Sentry-Pup | 0.9m | #D6283F | No ranged attack, melee-only, weakest unit in game |
| 2 | Sentry-Hound | 1.1m | #D6283F | Adds short-range data-bolt |
| 3 | Sentry-Warhound | 1.2m | #D67A28 | Faster movement speed |
| 4 | Sentry-Bulwark | 1.3m | #D67A28 | Frontal shield plate, must flank to damage |
| 5 | Sentry-Ironhide | 1.4m | #D6B428 | Full front-quarter armor |
| 6 | Sentry-Ravager | 1.35m | #D6B428 | Pack-buff aura (buffs nearby Family A units) |
| 7 | Sentry-Wraithhound | 1.3m | #8A28D6 | Brief cloak/stealth ability |
| 8 | Sentry-Colossus | 1.6m | #8A28D6 | Largest standard unit, knockback melee |
| 9 | Sentry-Executioner | 1.45m | #2884D6 | Rare ranged-only variant, sniper-role |
| 10 | Sentry-Alpha | 1.7m | #141416 | Family champion, pack-leader mini-boss |

---

### Family C — "Data Wraiths" (flying/hovering, ranged) — 10 variants
Base: no legs — floating torso/cloak silhouette, 1.4m "height" (hover height), thin and fast.

| Tier | Name | Accent color | Distinguishing trait |
|---|---|---|---|
| 1 | Wraith-Flicker | #D6283F | Single weak data-bolt |
| 2 | Wraith-Drift | #D6283F | Adds erratic hover-strafe movement |
| 3 | Wraith-Static | #D67A28 | Dual-bolt attack |
| 4 | Wraith-Fray | #D67A28 | Short teleport-blink ability |
| 5 | Wraith-Howl | #D6B428 | AoE pulse attack |
| 6 | Wraith-Rend | #D6B428 | Melee-capable (rare for family) |
| 7 | Wraith-Hollow | #8A28D6 | Damage-reflect shield phase |
| 8 | Wraith-Keening | #8A28D6 | Summons 2x Wraith-Flicker |
| 9 | Wraith-Sovereign | #2884D6 | Elite ranged, homing bolts |
| 10 | Wraith-Eclipse | #141416 | Family champion, screen-wide telegraph attack |

---

### Family D — "Bugmatter Constructs" (large, slow, tanky) — 10 variants
Base: 2.2m, blocky/geometric silhouette — built from visibly cruder polygon shapes than other families (intentional low-fi "raw bugmatter" aesthetic tying into your crafting system).

| Tier | Name | Accent color | Distinguishing trait |
|---|---|---|---|
| 1 | Construct-Husk | #D6283F | Slow single-slam attack |
| 2 | Construct-Bulk | #D67A28 | Wider hitbox, more HP |
| 3 | Construct-Slab | #D67A28 | Adds ground-slam AoE |
| 4 | Construct-Cairn | #D6B428 | Splits into 2 smaller units on death |
| 5 | Construct-Monolith | #D6B428 | Damage-reduction armor phase |
| 6 | Construct-Warden | #8A28D6 | Adds charge attack |
| 7 | Construct-Titan | #8A28D6 | Largest non-boss unit, 3.0m |
| 8 | Construct-Fracture | #2884D6 | Rare, drops crafting-tier bugmatter on death |
| 9 | Construct-Obelisk | #2884D6 | Stationary, ranged bugmatter projectile |
| 10 | Construct-Apex | #141416 | Family champion, arena-style mini-boss |

---

### Family E — "Corrupted Fragments" (small, swarm-type) — 8 variants
Base: 0.4m, simple geometric shard-form, appear in groups of 4–8 — cheapest unit in the game, fills out swarm encounters.

| Tier | Name | Accent color | Distinguishing trait |
|---|---|---|---|
| 1 | Fragment-Mote | #D6283F | No attack, contact damage only |
| 2 | Fragment-Shard | #D67A28 | Adds weak melee jab |
| 3 | Fragment-Splinter | #D6B428 | Faster swarm movement |
| 4 | Fragment-Cluster | #8A28D6 | Explodes on death (small AoE) |
| 5 | Fragment-Swarm-Elite | #2884D6 | Buffs nearby fragments |
| 6 | Fragment-Nucleus | #2884D6 | Spawns additional fragments over time |
| 7 | Fragment-Core | #141416 | Rare, guaranteed chip-drop |
| 8 | Fragment-Singularity | #141416 + full rim glow | Family champion, pulls player toward it (gravity-well gimmick) |

---

## Family Totals (Act I Grunt Roster)
- Family A (Glitch-Grunts): 12
- Family B (Firewall Sentries): 10
- Family C (Data Wraiths): 10
- Family D (Bugmatter Constructs): 10
- Family E (Corrupted Fragments): 8
- **Total: 50**

Plus **2 Major Bosses** (KERN.EXE, THE_ARCHIVIST) = **52 unique Act I antagonist entries.**

---

## UE5 Production Notes
- 2 grunt skeletons cover all 5 families (humanoid for A/C, quadruped for B, simplified/no-rig-hero-prop for D/E) — keeps animation budget realistic for 50 units.
- Palette progression (red → orange → amber → violet → blue → black) doubles as an at-a-glance difficulty/rank readout for players, and reuses the exact hex values from NetP's Soul State table — antagonists and protagonist share one unified corruption-color language across the whole game.
- Recommend LOD0 grunt budget ~15–20k tris (well under boss/hero budget), LOD2 swarm-ready ~3k tris for Family E.

---

## Next Steps
Acts II and III will follow the same Major Boss + 5-Family/50-unit structure. Let me know if you want the same 5 family archetypes carried through all three acts (reskinned/escalated), or distinct new families per act for visual variety.