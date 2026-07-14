# R3ALN3T.EXE — NetP Elemental & Rank Variant System
## Generative Spec (18 Elements × 24 Greek Tiers = up to 30 variants each)

---

## How This System Works

Your character-card generator (`NetP_s.md`) procedurally combines a **Tier** (24 Greek-letter ranks, OMEGA at the top, PSI at the bottom) with an **Element** (18 options) and rolls stats/colors randomly per card. A hand-written unique 3D spec for all 540+ possible combinations isn't practical or useful — most of the value is in the *rules*, not in enumerating every roll.

So this doc gives you the same thing your script gives the stat system, translated to visual design:
- **Section 1:** one full material/color/silhouette spec per Element (18 total) — this is what changes across a row.
- **Section 2:** one full scale/detail/emissive-intensity spec per Tier (24 total) — this is what changes across a column.
- **Section 3:** the combination formula — how to generate any specific variant (e.g. "OMEGA Fire NetP" or "PSI Void NetP") from the two tables, plus how the "30 per element" count maps onto the 24 tiers.
- **Section 4:** worked examples (a handful of fully generated variants) so an artist can see the formula produce real output.

All variants share NetP's base proportions doc (height/build/face/rig) from the original spec — this system only overrides material, color, scale multiplier, and VFX intensity.

---

## Section 1 — Element Table (18 entries)

Each element defines: primary color, accent/emissive color, material treatment, and one signature silhouette detail added to NetP's base armor.

| Element | Primary Hex | Accent/Emissive Hex | Material Treatment | Signature Detail |
|---|---|---|---|---|
| Fire | #2A1410 (charred base) | #FF5A1F | High roughness, ember-particle emissive pulsing at seams | Vented shoulder plates (heat-dissipation look) |
| Water | #14232A | #2FC9E8 | Low roughness, subtle refractive rim-shader | Flowing cape-fin trailing from left vambrace |
| Lightning | #1C1A2A | #E8E23F | Sharp specular highlights, crackling emissive branching pattern | Jagged asymmetric shoulder spike |
| Ice | #1A2428 | #B8F0FF | Frosted/translucent plate edges, slow-pulse emissive | Crystalline forearm shard-guard |
| Wind | #1E241C | #CFFFB0 | Matte fabric-like plate finish, faint particle streamers | Trailing ribbon fins at ankles |
| Earth | #241C14 | #C9924A | Rough stone-like normal detail on plate | Heavier boot/gauntlet mass, visibly denser |
| Light | #26241A | #FFF3C4 | Near-white base, soft constant glow (not pulsing) | Halo-ring detail behind head (thin, subtle) |
| Dark | #0F0F12 | #6A28D6 | Matte-black base, glow only visible in shadow/low-light | Cloak-fragment trailing from shoulders |
| Void | #08080A | #9B4FFF | Near-featureless black, edges dissolve into particle static | Missing/incomplete geometry at extremities (intentional) |
| Metal | #303236 | #E8E9ED | High metalness (~0.9), sharp mirror-like reflections | Riveted plate seams, visibly mechanical |
| Nature | #1C2A1A | #6ADB6A | Organic-pattern normal map (bark/leaf-like) on plate | Vine-wrap detail at forearms |
| Sound | #221E2A | #D46AFF | Rippling emissive rings radiating from chest plate | Fin-like ear/temple plating |
| Gravity | #1A1A22 | #4F4FFF | Plate edges appear to bend/warp slightly (shader distortion) | Orbiting small debris-fragments (VFX, non-solid) |
| Time | #2A241A | #E8C24A | Emissive "clock-tick" pulse (discrete steps, not smooth) | Layered afterimage silhouette on fast movement |
| Blood | #2A0F12 | #D6283F | Deep matte red base, wet-look specular on plate edges | Cracked-vein normal detail on exposed suit fabric |
| Poison | #1A241A | #8ADB2A | Bubbling/viscous emissive texture on seams | Drip-particle VFX at gauntlet tips |
| Crystal | #201E2A | #B08AFF | Faceted geometric plate shapes (literal low-poly facets by design) | Prism-shard shoulder cluster |
| Plasma | #241414 | #FF6AC9 | Unstable/flickering emissive (irregular pulse rate) | Arcing energy tendrils between plate segments |

---

## Section 2 — Tier Table (24 entries, OMEGA highest → PSI lowest)

Tiers control **scale multiplier**, **plate coverage/detail density**, and **emissive intensity** — a visual reflection of your script's stat curve (OMEGA = biggest numbers, PSI = smallest).

| Tier | Scale Multiplier (vs. base 1.80m) | Plate Coverage | Emissive Intensity | Detail Notes |
|---|---|---|---|---|
| OMEGA | 1.25× (2.25m) | Full — 100% of base armor slots filled, plus 1 unique "crown" accessory | Maximum, constant | Only tier with a unique silhouette add-on (crown/halo-equivalent per element) |
| ALPHA | 1.15× | 95% | Very high | Near-full plating |
| BETA | 1.10× | 88% | High | |
| GAMMA | 1.05× | 80% | High | |
| DELTA | 1.02× | 72% | Medium-high | |
| EPSILON | 1.00× (baseline) | 65% | Medium-high | Matches NetP's exact base proportions |
| ZETA | 0.98× | 58% | Medium | |
| ETA | 0.96× | 52% | Medium | |
| THETA | 0.94× | 47% | Medium | |
| IOTA | 0.92× | 42% | Medium-low | |
| KAPPA | 0.90× | 38% | Medium-low | |
| LAMBDA | 0.88× | 34% | Low-medium | |
| MU | 0.86× | 30% | Low-medium | |
| NU | 0.84× | 27% | Low | |
| XI | 0.82× | 24% | Low | |
| OMICRON | 0.80× | 21% | Low | |
| PI | 0.78× | 18% | Very low | |
| RHO | 0.76× | 16% | Very low | |
| SIGMA | 0.74× | 14% | Very low | |
| TAU | 0.72× | 12% | Minimal | |
| UPSILON | 0.70× | 10% | Minimal | |
| PHI | 0.68× | 8% | Minimal | Suit-only, almost no plate |
| CHI | 0.66× | 5% | Barely visible | Suit-only |
| PSI | 0.64× (1.15m — smallest) | 3% | None (color only, no glow) | Suit-only, no emissive at all — reads as "dormant" |

---

## Section 3 — Combination Formula

**Any variant = Base NetP rig + Element row (Section 1) + Tier row (Section 2).**

- Color: use the Element's primary/accent hex pair, not a new palette.
- Scale: apply the Tier's scale multiplier to NetP's base 1.80m proportions (Section 2 of the original NetP doc) — both gender variants (A/B) scale proportionally, keeping their relative height difference.
- Plate coverage: Tier determines *how much* of NetP's existing armor slot layout (chest/shoulders/vambraces/shins from Section 4.2 of the original doc) is present; Element determines *what it looks like* where present.
- Emissive: Tier sets intensity/pulse behavior; Element sets color and pattern style (particle, crackle, ripple, etc. — see Section 1's Material Treatment column).

### "30 per element" mapping
You have 24 tiers but asked for 30 variants per element. Recommend: the 24 tiers each produce one canonical variant (24), plus **6 "elite" sub-variants** at OMEGA/ALPHA/BETA/GAMMA/DELTA/EPSILON (your top 6 tiers) that add a minor secondary-element accent streak (a thin secondary color line using a *different* element's accent hex) — these represent "hybrid-rank" cards your generator could plausibly roll. That reaches 30 per element (24 base + 6 elite-hybrid) without inventing an arbitrary 25th–30th tier that doesn't exist in your script.

Total generative coverage: **18 elements × 30 = 540 possible NetP variant specs**, fully defined by combining the two tables above — no further writing needed to produce any specific one on request.

---

## Section 4 — Worked Examples

### OMEGA Fire NetP
Height 2.25m, full plate coverage + unique crown (a flame-crest running front-to-back along the helmet-line, element-specific per Section 1's Fire row), charred-base #2A1410 suit, #FF5A1F ember-particle emissive at maximum constant intensity, vented shoulder plates per Fire's signature detail.

### PSI Void NetP
Height 1.15m, suit-only (3% plate — likely just the chest emblem), near-featureless matte black (#08080A), **no emissive at all** (Void + PSI is the one combination where Void's usual particle-static edge effect is suppressed entirely by PSI's "none" emissive rule) — reads as a barely-there whisper of the character, thematically fitting for the lowest-tier void variant.

### EPSILON Metal NetP (baseline example)
Height exactly 1.80m (EPSILON is the tier that maps 1:1 to base proportions), 65% plate coverage, high-metalness brushed finish (#303236/#E8E9ED), riveted seam detail — this is the closest any generated variant gets to "default NetP," useful as a QA reference when building the material system in UE5.

### ALPHA Void NetP with Fire elite-hybrid streak
Height ~2.07m, 95% plate, near-featureless void base — but with a thin #FF5A1F ember-streak accent line down the right vambrace (the elite-hybrid rule from Section 3), representing one of the 6 "elite" rolls per element beyond the 24 base tiers.

---

## UE5 Production Notes
- Single Master Material Instance per element (18 total instances) with a Tier scalar parameter driving scale/coverage/emissive — avoids needing 540 unique material assets.
- Plate coverage percentages (Section 2) map cleanly to mesh-section visibility toggles if NetP's armor is built as separate socketed mesh pieces (recommended over a single skinned mesh, given how much coverage varies by tier).
- The elite-hybrid streak (Section 3) can be a simple secondary emissive mask layer, parameterized by a second color input — cheap to add without a new shader graph.