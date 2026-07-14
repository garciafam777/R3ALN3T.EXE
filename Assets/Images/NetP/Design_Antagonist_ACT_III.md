# R3ALN3T.EXE — Antagonist Roster: ACT III
## 3D Realistic Character Specs

---

## Design Philosophy (Act III Convergence)

Act III closes the corruption arc started in Act I (independent design language) and escalated in Act II (mimicry of NetP's silhouette/rig). The final beat: the antagonist force stops imitating NetP and **steals NetP's own signal cyan (#00D4E8)** outright — the one color that has meant "player identity" across every doc in this project now appears on the final boss, corrupted in *meaning* rather than hue. This is a stronger climax read than inventing a new "evil color," because it directly threatens what the player has visually owned since Section 1 of the NetP spec.

Three closing escalation rules:

1. **Palette convergence:** grunt floor rises to violet (#8A28D6) — Act I's *rare* color is now Act III's *common* color. Signal cyan (#00D4E8) is reserved exclusively for the final boss and a handful of named elite units, making its appearance a genuine "oh no" visual cue.
2. **Fraying becomes structural, not cosmetic:** by Act III, the polygon-fracture VFX from Act I/II is no longer a surface effect — grunt silhouettes are now visibly incomplete/glitching in their base mesh (holes, missing plate segments), communicating that corruption has outpaced the antagonist force's ability to hold coherent form.
3. **M.A.N. Token motif resolves:** where KERN.EXE (Act I) had a cracked empty socket and MIRROR.EXE (Act II) had a cracked dim token, the Act III final boss has a **stolen, fully-lit token** — visually the endpoint of that three-act thread.

---

## PART 1 — MAJOR BOSSES (Act III)

### Boss 1: SOVEREIGN.NULL (Act III final antagonist)

**Concept:** The convergence point of the whole antagonist arc — not a mimicry of NetP like MIRROR.EXE, but a total inversion: has *taken* NetP's token and color rather than copying them. Reads as tragic/parasitic rather than purely monstrous if you want an emotional final-boss beat.

| Metric | Spec |
|---|---|
| Height | 2.20 m — largest humanoid-proportioned entity in the game, but retains readable human posture (not a monster-scale creature, keeps the "this was someone" read) |
| Build | Asymmetric like KERN.EXE (Act I callback), but now the asymmetry is *healing/converging* — right side fully formed and armored, left side still visibly fragmentary, implying transformation-in-progress during the fight |
| Head-to-body ratio | 7.5 heads — matches NetP exactly (final callback to MIRROR.EXE's mimicry, now literalized) |
| Shoulder-to-hip ratio | 1.4:1 |

**Face:** Solid emissive eyes like the Act I/II bosses, but color is **stolen signal cyan (#00D4E8)** — the exact hex from NetP's own iris ring, not a new "villain cyan." This is the single most important color decision in the whole roster: reusing NetP's literal value, not a palette-matched substitute.

**Costume:** Base suit graphite tone shifted darker (#1A1B1F vs NetP's #2A2D34), armor plate goes from titanium-white to **ash-grey (#7A7A7E)** — desaturated version of NetP's plate color, not inverted-to-black like KERN.EXE. This is deliberate: SOVEREIGN.NULL should look like a faded/drained NetP, not an opposite-colored monster.

**M.A.N. Token:** Fully lit, worn at the collar exactly like NetP's — but visually "wrong," pulsing off-rhythm (slightly desynced glow-cycle, easy to build as a simple sine-offset in the material) rather than the steady pulse NetP's token has. Players should recognize the object before they consciously register why it's unsettling.

**Materials:** Plate roughness ~0.35 (between NetP's sleek 0.25 and KERN.EXE's damaged 0.6 — reads as "worn," not destroyed), metalness ~0.75.

**Suggested fight structure note:** left-side fragmentary geometry could be a literal damage-phase trigger (mesh "completes" itself visually as a phase-2 transition) — flagging this since it's a clean hook if your climax cutscene docs want a mid-fight transformation beat.

---

### Boss 2: THE_LAST_ARCHIVE (Act III secondary antagonist)

**Concept:** Final evolution of THE_ARCHIVIST (Act I) → THE_ORACLE_FRAGMENT (Act II) → this. Completes that three-act thread the same way SOVEREIGN.NULL completes the KERN.EXE/MIRROR.EXE thread — gives you two parallel villain arcs resolving in the same act.

| Metric | Spec |
|---|---|
| Height | 2.05 m (fully "grown" from the Act II fragment's 1.95m) |
| Build | Robed silhouette from Acts I–II, but now the calcified-plate side has spread to nearly the whole coat |

**Costume:** Coat material is now almost entirely the calcified plate finish introduced in Act II, color shifted to **cold ash-gold (#B8A25C)** — a desaturated, "dying ember" version of the original fractured-gold trim, signaling this thread is reaching its end rather than escalating in aggression.

**Visor:** Data-glyphs no longer flicker red (Act II's instability tell) — they've stabilized into a **fixed cyan glyph pattern**, tying it into the same stolen-signal-cyan motif as SOVEREIGN.NULL without duplicating the boss's design.

---

## PART 2 — GRUNT ROSTER (Act III: 50 total, final-tier escalated)

### Family A — "Glitch-Grunts" → final 12 variants (floor raised to violet)

| Tier | Name | Height | Accent color | Distinguishing trait |
|---|---|---|---|---|
| 1 | Glitch-Grunt Mk.VI | 1.65m | #8A28D6 (violet — Act III floor) | Visible mesh gaps at shoulder/hip (structural fraying) |
| 2 | Glitch-Grunt Mk.VII | 1.68m | #8A28D6 | Adds second gap point at forearm |
| 3 | Glitch-Reaver III | 1.72m | #2884D6 (blue) | Dual-wield, faster and more erratic movement |
| 4 | Glitch-Warden III | 1.80m | #2884D6 | Adaptive plating now includes leg guards |
| 5 | Glitch-Harrower III | 1.78m | #141416 | Constant particle VFX, larger radius |
| 6 | Glitch-Butcher III | 1.85m | #141416 | Twin oversized blade-arms (both sides, escalated from single-arm Act I/II) |
| 7 | Glitch-Occult III | 1.75m | #7A7A7E (ash-grey — SOVEREIGN.NULL tint) | Homing bolts now split on impact |
| 8 | Glitch-Herald III | 1.83m | #7A7A7E | Summons Mk.VI–VIII on aggro |
| 9 | Glitch-Devourer III | 1.90m | #7A7A7E | Heaviest grunt armor in the game |
| 10 | Glitch-Prime III | 1.95m | #00D4E8 (stolen cyan — rare, elite-only) | Area mini-boss, near-complete adaptive silhouette |
| 11 | Glitch-Ascendant II | 1.93m | #00D4E8 | Rare, drops final-tier crafting mats |
| 12 | Glitch-Sovereign-Echo | 2.00m | #00D4E8 + full rim glow | Family champion, visually smallest step below SOVEREIGN.NULL itself |

---

### Family B — "Firewall Sentries" → final 10 variants

| Tier | Name | Scale | Accent color | Distinguishing trait |
|---|---|---|---|
| 1 | Sentry-Warhound III | 1.25m | #8A28D6 | Structural mesh gaps at haunches |
| 2 | Sentry-Bulwark III | 1.35m | #8A28D6 | Frontal shield now semi-transparent (glitching in/out) |
| 3 | Sentry-Ironhide III | 1.45m | #2884D6 | Full adaptive armor, front and flanks |
| 4 | Sentry-Ravager III | 1.4m | #2884D6 | Pack-buff now affects all families, not just A |
| 5 | Sentry-Wraithhound III | 1.35m | #141416 | Near-permanent stealth uptime |
| 6 | Sentry-Colossus III | 1.7m | #141416 | Largest standard quadruped this act |
| 7 | Sentry-Executioner III | 1.55m | #7A7A7E | Triple homing bolts |
| 8 | Sentry-Alpha III | 1.8m | #7A7A7E | Pack-leader, near-complete plate coverage |
| 9 | Sentry-Archiveborn | 1.65m | #B8A25C (THE_LAST_ARCHIVE tint) | Rare — inherits a data-glyph visor detail |
| 10 | Sentry-Sovereign-Prime | 1.85m | #00D4E8 | Family champion, stolen-cyan rare unit |

---

### Family C — "Data Wraiths" → final 10 variants

| Tier | Name | Accent color | Distinguishing trait |
|---|---|---|---|
| 1 | Wraith-Static III | #8A28D6 | Triple-bolt attack |
| 2 | Wraith-Fray III | #8A28D6 | Near-instant teleport cooldown |
| 3 | Wraith-Howl III | #2884D6 | AoE pulse chains across entire pack |
| 4 | Wraith-Rend III | #2884D6 | Melee claw-plate fully adaptive now |
| 5 | Wraith-Hollow III | #141416 | Damage-reflect near-permanent |
| 6 | Wraith-Keening III | #141416 | Summons 2x Wraith-Static III |
| 7 | Wraith-Sovereign III | #7A7A7E | Elite, quad homing bolts |
| 8 | Wraith-Eclipse III | #7A7A7E | Fastest telegraph-to-strike window in game |
| 9 | Wraith-Archiveborn | #B8A25C | Rare — brief glyph-visor decoy clone |
| 10 | Wraith-Umbra-Prime | #00D4E8 | Family champion, stolen-cyan rare unit |

---

### Family D — "Bugmatter Constructs" → final 10 variants

| Tier | Name | Accent color | Distinguishing trait |
|---|---|---|---|
| 1 | Construct-Cairn III | #8A28D6 | Splits into 3 on death (escalated from 2) |
| 2 | Construct-Monolith III | #8A28D6 | Damage-reduction near-permanent |
| 3 | Construct-Warden III | #2884D6 | Charge attack, full adaptive plate |
| 4 | Construct-Titan III | #2884D6 | 3.5m, largest non-boss unit in the game |
| 5 | Construct-Fracture III | #141416 | Drops final-tier bugmatter |
| 6 | Construct-Obelisk III | #141416 | Fastest projectile in family history |
| 7 | Construct-Apex III | #7A7A7E | Arena mini-boss, near-complete plate |
| 8 | Construct-Sovereign II | #7A7A7E | Rare, permanent damage-reflect |
| 9 | Construct-Archiveshell | #B8A25C | Rare — brief calcified-coat silhouette copy |
| 10 | Construct-Colossus-Sovereign | #00D4E8 | Family champion, stolen-cyan rare unit |

---

### Family E — "Corrupted Fragments" → final 8 variants

| Tier | Name | Accent color | Distinguishing trait |
|---|---|---|---|
| 1 | Fragment-Splinter III | #8A28D6 | Fastest swarm speed in the game |
| 2 | Fragment-Cluster III | #2884D6 | Largest death-explosion radius |
| 3 | Fragment-Swarm-Elite III | #2884D6 | Buffs all nearby families simultaneously |
| 4 | Fragment-Nucleus III | #141416 | Fastest spawn-rate in family history |
| 5 | Fragment-Core III | #141416 | Guaranteed final-tier chip-drop |
| 6 | Fragment-Singularity III | #7A7A7E | Largest gravity-well radius |
| 7 | Fragment-Archiveshard | #B8A25C | Rare — splits into 3 on hit |
| 8 | Fragment-Convergence-Prime | #00D4E8 | Family champion, stolen-cyan rare unit |

---

## Family Totals (Act III Grunt Roster)
- Family A: 12
- Family B: 10
- Family C: 10
- Family D: 10
- Family E: 8
- **Total: 50**

Plus **2 Major Bosses** (SOVEREIGN.NULL, THE_LAST_ARCHIVE) = **52 unique Act III antagonist entries.**

---

## UE5 Production Notes
- Same 2 grunt skeletons from Acts I–II carry forward unchanged across all three acts — the entire 150-unit grunt roster runs on 2 base rigs, which is the real production win of the family-tier system.
- Stolen-cyan (#00D4E8) units are intentionally rare (1 per family, 5 total across the grunt roster) — this preserves the color's shock value when SOVEREIGN.NULL itself appears, rather than diluting it across dozens of units.
- THE_LAST_ARCHIVE's ash-gold (#B8A25C) rare-tint units (1 per family) give players a second "uh oh, elite" visual read distinct from the cyan ones, useful if you want two different alert states in encounter design (e.g., cyan = boss-adjacent threat, gold = archive-thread threat).

---

## Full Trilogy Summary
| Act | Bosses | Grunt Floor Color | Grunt Ceiling (rare) Color | Total Entries |
|---|---|---|---|---|
| I | KERN.EXE, THE_ARCHIVIST | Red #D6283F | Black #141416 | 52 |
| II | MIRROR.EXE, THE_ORACLE_FRAGMENT | Amber #D6B428 | Magenta #D628A0 | 52 |
| III | SOVEREIGN.NULL, THE_LAST_ARCHIVE | Violet #8A28D6 | Stolen Cyan #00D4E8 | 52 |

**Grand total: 156 unique antagonist character specs across the trilogy**, all built on 2 shared grunt skeletons + boss-specific rigs, unified by one continuous corruption-color language that traces directly back to NetP's own palette.