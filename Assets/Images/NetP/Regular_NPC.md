# R3ALN3T.EXE — Real-World NPC System
## Named Cast + Crowd-Filler Archetypes (Contemporary Humans, Light Tech Tie-In)

---

## Design Philosophy

The real world is where NetP's operator lives when not jacked into SkyLand — this roster should read as **photoreal contemporary humans**, not stylized or armored like anything in SkyLand. The only tie-in to the digital rosters: everyone in this world plausibly owns a **PH (Persona Host) device** — a single small, real-world wearable (wrist-unit or ear-piece, your call) that carries a faint version of NetP's signal-cyan (#00D4E8) as a status-light accent. That's the entire tech footprint here — no armor, no circuit-trace skin, no emissive materials. One small light on one small device, nothing more.

This keeps SkyLand's visual language feeling special by contrast — if real-world humans looked techy too, NetP's digital design wouldn't read as distinct.

Two parts, per your direction: a **named cast** (recurring, dialogue-bearing) and a **crowd-filler system** (generic archetypes for background population), same two-tier approach used across the SkyLand rosters (bosses vs. grunt families), just re-applied to a mundane setting.

---

## PART 1 — Named Cast (14 NPCs)

### Family / Home
**Dana Reyes** — NetP's operator's parent figure. Early 40s, warm/tired demeanor, casual work clothes, PH wrist-unit visibly older/scuffed model (established user, not an early adopter).

**Milo Reyes** — Operator's younger sibling, early teens, energetic, backpack covered in stickers (small in-world detail: one sticker is a tiny NetP silhouette fan-logo — nice self-referential touch). PH device is a newer/flashier model than Dana's.

### School / Work Contacts
**Prof. Aldric Kade** — Operator's mentor/instructor figure at a tech-focused school, 50s, precise/formal dress, tweed-adjacent but modernized, PH device worn openly on a lapel-pin rather than wrist (status marker for his generation/role).

**Junie Okafor** — Operator's closest peer/rival at school, late teens, sharp/confident, customized PH wrist-unit with a visible cyan accent band she's clearly modified herself (small characterization detail — she tinkers with tech).

**Foreman Dietz** — Gruff work-site supervisor if the operator has a part-time job angle, 50s, heavy work jacket, PH device basic/unmodified, all business.

### Shopkeepers / Local Color
**Old Man Yuen** — Runs the local chip/hardware shop, 70s, kind, cluttered apron, PH device is an ancient first-generation model (visual joke: barely functional, flickers).

**Rosalind "Ro" Petrakis** — Runs a café/hangout spot, 30s, tattoos, warm and chatty, PH worn as a necklace pendant rather than wrist/ear.

**Tomas Vell** — Street vendor, food cart, 40s, weathered but cheerful, no PH device visible at all (small character note — doesn't engage with the tech culture much).

### Neighborhood/Recurring Background
**Mrs. Abernathy** — Elderly neighbor, always walking a small dog, 70s-80s, cardigan, no visible PH device.

**Deke Marsh** — Local mechanic, 30s, grease-stained coveralls, PH device duct-taped to wrist (running joke potential — always broken/jury-rigged).

**Nadia Solis** — Jogger/fitness-focused neighbor, 20s-30s, athletic wear, sleek modern PH wrist-unit, always seen mid-exercise.

**Officer Brant Calloway** — Local law enforcement presence, 30s-40s, standard uniform, PH device is a more official/hardened model with a different accent color (amber #D6B428 instead of cyan — signals authority/official-issue variant).

**Sister Imelda Cho** — Runs a community center, 50s, practical modest clothing, PH device is minimal/basic, community-oriented dialogue role.

**Benny "Loose Wire" Faulk** — Neighborhood conspiracy theorist/tech-rumor spreader, 40s, mismatched clothing, PH device visibly modified with extra (nonfunctional-looking) attachments — comic relief NPC who claims to know things about SkyLand he doesn't actually know.

---

## PART 2 — Crowd-Filler Archetype System

For background population (streets, campus, workplaces), use a modular archetype + variation system rather than individually authoring dozens of unique crowd NPCs — same "template + parameter table" logic used across the SkyLand rosters, applied here to keep crowd-rendering cheap.

### Archetype Base Types (8)

| Archetype | Age range | Base wardrobe | PH device presence |
|---|---|---|---|
| Office Worker | 25–55 | Business-casual, muted tones | ~90% wear one, wrist-style |
| Student | 14–22 | Casual/school-adjacent, backpacks | ~95% wear one, often customized |
| Service Worker | 20–50 | Uniformed (café, retail, delivery) | ~70% wear one, basic model |
| Manual/Trade Worker | 25–55 | Work jackets, tool belts, hi-vis elements | ~50% wear one, rugged/case-protected model |
| Elderly Pedestrian | 60–85 | Practical, weather-appropriate layers | ~40% wear one, often older model |
| Parent/Caregiver | 25–45 | Casual, often with child NPC paired | ~85% wear one |
| Athletic/Fitness | 18–40 | Activewear | ~95% wear one, sleek modern model |
| Child | 5–13 | Bright casual wear | ~20% wear one (parental-controlled, simplified model) |

### Variation Rules (applied per spawned crowd NPC)
- **Skin tone / hair / build:** randomized from a realistic human range — no stylization, straightforward diverse-population randomization pool.
- **Wardrobe color:** randomized within each archetype's "muted tones" / "bright casual" / etc. band — keep archetype-appropriate, don't randomize outside the described palette family.
- **PH device accent color:** overwhelmingly signal-cyan (#00D4E8, matching NetP/the default civilian experience), with rare (~5%) variants: amber (#D6B428, official/enterprise-issue, skews Office Worker/Manual Worker), or no-light/dead-battery grey (~10% across all archetypes, small realism touch — not everyone's device is always charged).
- **Animation variety:** 4–6 idle/walk-cycle variants per archetype is sufficient for crowd believability at typical camera distances — no need for named-cast-level bespoke animation.

### Production Notes
- Recommend 3 base body meshes (adult-average, adult-broad, adult-slight) with the 8 archetypes achieved through wardrobe/texture swaps rather than 8 separate meshes — keeps crowd rendering cheap at scale.
- Child archetype needs its own smaller base mesh/rig — don't scale down the adult rig, proportions read wrong.
- Named cast (Part 1) should use full Metahuman-tier detail/rig (matching NetP's fidelity) since they carry dialogue; crowd-filler archetypes (Part 2) can run at a much lower LOD/poly budget since they're background-only.