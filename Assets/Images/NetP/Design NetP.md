# R3ALN3T.EXE — Character Design Spec
## Protagonist: NetP (Default / Neutral Soul State)

---

## 1. Concept Overview

NetP is the player's digital avatar inside SkyLand — not a cartoon mascot, but a **realistic humanoid data-construct**: skin, cloth, and metal rendered with real-world material logic, but with an unmistakable "born of code" tell (seam lines, port access points, faint sub-dermal circuitry that only activates under load). Think grounded sci-fi operator, not superhero.

Base design below represents the **mid-band ("Balanced") Soul State** — the visual midpoint the other six aura bands warp from.

---

## 2. Proportions (Player-Selectable Gender: A/B Split)

NetP is player-selectable at game start (masculine-presenting / feminine-presenting). Both variants share identical rig topology, wardrobe, palette, and Soul State logic from this doc — only body proportions and face-shape defaults differ, so all downstream sections (costume, materials, colors, aura variants) apply equally to both without modification.

| Metric | Variant A (masc-presenting) | Variant B (fem-presenting) |
|---|---|---|
| Height | 1.80 m (5'11") | 1.68 m (5'6") |
| Build | Athletic-lean, swimmer's taper | Athletic-lean, narrower shoulder line |
| Head-to-body ratio | 7.5 heads | 7.5 heads (kept identical for rig/animation parity) |
| Shoulder-to-hip ratio | 1.35:1 | 1.05:1 |
| Torso-to-leg ratio | 45:55 | 44:56 |
| Hands | +5% elongated vs. real-world average | +5% elongated vs. real-world average |
| Face default | Section 3 as written | Softer jaw taper, same cheekbone/nose logic, same iris/hair spec |

**Design intent:** keep the delta to skeletal proportions and face taper only — same M.A.N. Token placement, same gauntlet asymmetry, same armor silhouette, same emissive rules. This keeps both variants reading as clearly "the same character" across cutscenes and keeps your Act I–III climax animation data reusable between them (single blendshape rig, single animation set, just two skeletal scale profiles).

**UE5 rig note:** base both on the UE5 Manny/Metahuman skeleton at their respective ref heights; retarget from a single shared animation set rather than authoring separate mocap per variant — proportion differences are small enough that IK retargeting handles it cleanly.

**Selection UX note:** if you want this exposed as a menu choice rather than a binary toggle, the same A/B skeletal-scale approach supports a height/build slider between the two profiles with minimal extra rig work — flag if you'd rather spec that instead of a hard two-option pick.

---

## 3. Face

- **Structure:** Oval-to-square jaw blend, moderate cheekbone definition, straight nasal bridge — deliberately "unremarkable/handsome" so it reads as an everyman avatar, not an anime lead.
- **Eyes:** Almond, slightly upturned outer corner. Iris color **cyan-white (#B8F4FF core, #2FD9E8 ring)** — the one clearly "non-human" tell up close. Sclera stays human-white (avoid full anime glow-eyes; keep it subtle, like a contact lens, not a light source).
- **Skin material:** Standard subsurface-scattering human skin shader, but with a **secondary emissive mask** baked in along jaw, temple, and collarbone lines — invisible at rest, glows faint cyan when NetP takes damage or executes a chip attack.
- **Brows/expression range:** Full Metahuman-style blendshape set (52+ ARKit-standard morphs) — this character needs full facial animation for cutscenes per your Act I–III climax docs.
- **Hair:** Short-to-mid, textured undercut, matte charcoal black (#1C1C1E) with **single cyan-lit strand streak** at the front-right — small, consistent brand marker across all promotional renders.

---

## 4. Body & Costume

### 4.1 Base Suit (skin-tight under-layer)
- Full bodysuit, matte-finish performance fabric look (not latex-shiny).
- Base color: **Graphite (#2A2D34)**
- Seam lines glow faint cyan when active (same emissive mask logic as face).
- Subtle circuit-line topology (hand-painted normal map, NOT a tiled sci-fi texture) running from wrists up forearms, implying data-flow rather than decoration.

### 4.2 Armor Plating (mid-weight, segmented — not bulky mecha-armor)
Placement: chest plate, shoulder caps, forearm vambraces, shin guards. Hips/knees stay in flexible suit fabric for silhouette and rig-friendliness.

- Plate material: **Brushed titanium-white (#E8E9ED)**, low roughness (~0.25), moderate metalness (~0.8)
- Accent trim: **Signal cyan (#00D4E8)**, emissive, on all plate edges — this is NetP's core "brand color," used consistently through UI, chip icons, and HUD to reinforce identity
- Chest plate bears a **single stamped Greek-letter chip code glyph** (ties directly into your 108 Ghost Data/chip system — recommend Alpha (Α) for the protagonist as the "origin" glyph)

### 4.3 M.A.N. Token Housing
- Worn as a **collar-mounted disc**, ~4cm diameter, recessed into a titanium collar ring at the base of the neck.
- Idle state: dim slate-grey.
- Active/socketed state: token glows according to whichever aura band is currently active (see Section 6) — this is your primary in-world "Soul State" readout, always visible in third-person and in dialogue close-ups.

### 4.4 Gauntlets
- Right forearm gauntlet is asymmetric and slightly larger — houses the primary chip-slot interface (a thin horizontal port line, glows cyan when chip data loads).
- Left gauntlet is the plainer twin, kept clean for silhouette balance.

---

## 5. Color Palette (hex reference sheet)

| Role | Color | Hex |
|---|---|---|
| Base suit | Graphite | #2A2D34 |
| Armor plate | Titanium white | #E8E9ED |
| Brand accent / emissive | Signal cyan | #00D4E8 |
| Iris | Cyan-white core | #B8F4FF |
| Iris ring | Deep cyan | #2FD9E8 |
| Hair | Matte charcoal | #1C1C1E |
| Skin (baseline human) | Neutral warm tan | #C68A66 (adjust per your desired protagonist ethnicity — flag if you want this tied to a specific default) |

---

## 6. Soul State Aura Variants (visual reskin logic)

Rather than redesigning the model per band, drive all seven states off the **same emissive mask + M.A.N. Token color** — cheapest to implement, most readable to the player.

| Band (0–100 scale) | Token / Emissive Color | Material shift |
|---|---|---|
| 1 — Corrupted (lowest) | Blood red (#D6283F) | Armor desaturates toward #3A3A3D, cracked-normal overlay |
| 2 — Fractured | Burnt orange (#D67A28) | Slight static/glitch shader on seams |
| 3 — Wavering | Dull amber (#D6B428) | none beyond color |
| 4 — Balanced (default, this doc) | Signal cyan (#00D4E8) | baseline |
| 5 — Aligned | Cool blue (#2884D6) | +10% plate reflectivity |
| 6 — Ascendant | Violet (#8A28D6) | thin light-rim shader on silhouette |
| 7 — Luminous (highest) | White-gold (#F4E8B8) | full rim light + particle motes at high emotional beats |

This means one geometry/rig, seven material instances — clean for UE5 material parameter collections and cheap to swap at runtime.

---

## 7. Technical Notes (UE5)

- **Target polycount:** 60–80k tris hero-LOD0 (Metahuman-adjacent budget), 3 LOD steps down to ~8k for crowd/cutscene-background use.
- **Texture sets:** 4K base color/normal/ORM on body, 2K on face (Metahuman face texturing pipeline recommended if you're already using Metahuman Creator as a base mesh).
- **Rig:** Metahuman skeleton + 52 ARKit blendshapes minimum for the cutscene pipeline docs you already have (Act I–III climaxes need full facial performance capture compatibility).
- **Material setup:** single Master Material with a Soul-State scalar parameter (0–100) driving emissive color lerp — avoids needing 7 separate material instances if you'd rather do a smooth material-parameter-collection blend instead of the stepped table above.

---

## Open Questions / Assumptions Flagged
- Skin tone left as a placeholder neutral tan — let me know if this should be a fixed default, tied to a specific operator identity, or exposed as a player-customizable slider alongside the gender selection.