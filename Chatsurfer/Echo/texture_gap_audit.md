# TEXTURE GAP AUDIT — for Echo (current work: textures)
**From:** NYX | **Date:** 2026-07-13 | **Scope:** texture coverage vs locked canon 21 + NetP/card art
**Repo:** 2760 image files total. Audit of `Assets/Images/`.

## 1. CARD FRAMES (Drafts) — vs canon 21
36 draft frames in `Assets/Images/UI/card_frames/Drafts/`. Coverage:

**PRESENT (with old-name duplicates to rename):**
| Canonical | Drafts | Issue |
|---|---|---|
| Fire | 2 | ok |
| Wind | 2 | ok |
| Ice | 2 | ok |
| Earth | 1 | ok |
| Light | 3 | ok |
| Dark | 1 | ok |
| Void | 3 | ok |
| Metal | 3 | ok |
| Nature | 3 | ok |
| Sound | 2 | ok |
| Gravity | 2 | ok |
| Time | 1 | ok |
| Blood | 2 | ok |
| Poison | 2 | ok |
| Crystal | 2 | ok |
| Plasma | 2 | ok |

**MISSING (canon 21, zero drafts):**
- **Aqua** — 0 (only `water_horizontal_frame.jpeg` exists → rename Water→Aqua)
- **Elec** — 0 (only `lightning_frame.jpeg` + `thunder_horizontal_frame.jpeg` → rename to Elec)
- **Wood** — 0 ❌
- **Null** — 0 ❌
- **Glitch** — 0 ❌

**OLD-NAME FILES TO RENAME:**
- `water_horizontal_frame.jpeg` → `aqua_horizontal_frame.jpeg`
- `lightning_frame.jpeg` → `elec_frame.jpeg`
- `thunder_horizontal_frame.jpeg` → `elec_horizontal_frame.jpeg` (thunder was a variant spelling of Elec)

**EXTRA (non-element, leave or move):** `angelic_frame.jpeg` (type-alignment frame, not element — keep if type-frames are a thing).

**GAP:** 16/21 elements have frames; **Wood/Null/Glitch entirely missing**. Aqua/Elec exist only under old names.

## 2. NETP ART (`Assets/Images/NetP/`)
- `Eternity.png`, `Tyranny.png` — the 2 Constructs with art. **Trinity.png MISSING** ❌ (3 Constructs defined; only 2 have art).
- 3 `ChatGPT Image...` + 1 `gemini...battle_stage` — unsorted/battle-stage concepts, not named per construct.
- **No per-element NetP art** (the 272 career NetPs have no textures yet — mesh refs are data-only, no image assets).

## 3. CHARACTER CARDS (`Assets/Character_Cards/`)
- **0 PNGs.** Generator writes JSON only — no card portraits generated. ❌ GAP (cards are stat-blocks with no visuals).

## 4. SUMMARY OF GAPS (for Echo)
1. **Card frames:** add Wood, Null, Glitch (3 new). Rename Water→Aqua, Lightning/Thunder→Elec (3 files).
2. **NetP art:** add Trinity.png (missing 3rd Construct). Optionally name the 3 stray battle-stage images.
3. **NetP per-element art:** none exists for the 272 career NetPs (data has `Mesh` ref but no texture). Decide: generate per-element skin textures or reuse frames?
4. **Character card portraits:** generator produces no PNGs — either wire PNG gen into `generate_cards.py` or assign placeholder frames.
5. **`Agent-Profiles/.../assets/textures`** — empty.

## NOTE (consistency with my card regen)
I already fixed the **card DATA** (`generate_cards.py`) to canon-21 (Aqua/Elec/Wood/Null/Glitch). The **textures** lag — Echo's lane. This audit is the punch-list.
