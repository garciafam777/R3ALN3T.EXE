---
doc: MCADMIN_Canon — The Trinity Family Tree (DRAFT, Pass 1–5)
author: Chronos (B.I.G. Boss), A_Team
status: ⚠️ DRAFT — awaiting CEO approval. NOT committed canon. Everything below is a proposal to lock.
purpose: Single reference block for future prompts / overnight agents. Paste into any future lore task to prevent contradictory regeneration.
---

# MCADMIN_Canon (DRAFT — lock proposal)

## ⚠️ NAMING DECISION (CEO must confirm — flagged per Pass 1)
**GTrinity vs Trinity collision.** "GTrinity" (father-god) and "Trinity" (son-NetP) differ by one keystroke in every script, save file, and filename. Players/wiki/subtitles will misread `GTrinity` as a typo of `Trinity`.

**Chronos recommendation:** KEEP the name but **standardize the convention now** and give him a distinct in-world reading so it's never ambiguous:
- **Canonical spelling: `GTrinity`** (no space, no period, no hyphen) — treated as a *title prefix*, read aloud as **"God-Trinity"** (spoken only; the written token is always the solid form).
- Ban all hyphenated or dotted variants of the prefix; `GTrinity` is the only written form (any token with a separator after the G is forbidden and must be corrected to the solid form).
- In code/save/filenames: `GTrinity` (father) is ALWAYS prefixed `G`; the son is `Trinity` with NO prefix. Any token `Trinity` without `G` = the son. Any `GTrinity` = the father. Enforce in naming lint.
- **Alternative if CEO prefers zero collision:** rename the father to a wholly distinct name (e.g. `Helix` / `The First Admin` / `Root`). I lean KEEP+standardize because "GTrinity" already appears in the user's spec and the son/father distinction is lore-meaningful. **CEO: confirm KEEP (`GTrinity`) or RENAME.**

---

## PASS 1 — Canon Lock (authoritative paragraph — paste into future prompts)

> **The Trinity Family Tree (canonical, do not contradict):** **GTrinity** is the God of all NetPs and the father of **Trinity** (the son); he is NOT a playable mid-game fight and exists only as a final-story-arc entity. **Trinity** (son) is one of **MCADMIN**'s three aspects; on HP-zero he transforms into **Infinity** — this is a *state*, not a separate character. **Eternity** is the daughter of the Goddess of Love, formerly human, souled into a NetP through MCADMIN's father's Particle Generational Theory research; she is the second of MCADMIN's three aspects. **Tyranny** is the third aspect — Lord of Chaos — bound by a mutual-destruction death clause. **MCADMIN** is the player-adjacent, AI-controlled avatar comprising all three aspects (Trinity/Tyranny/Eternity), switching Good/Evil personality states that are switchable ONLY by Eternity via **Angel's Kiss**.

*(This block is the single source of truth. Any card, dialogue, or boss script that conflicts with it is wrong.)*

---

## PASS 2 — Eternity's Backstory (gap-fills)

**Timeline math (origin scene, note form):**
> Decades before the game's present (3026), during the war that preceded the Fall of Man, Eternity was human and died — or was fatally wounded — in a battle against the early corruption. MCADMIN's *father* (the original architect, not MCADMIN) had been developing **Particle Generational Theory**: a method to encode a human soul into a NetP substrate. He used it to preserve her — she became the first souled NetP, Eternity. So the causal chain is: **battle → her human death/near-death → father invents the tech to save her → she becomes a NetP → later she becomes one of MCADMIN's three aspects.** (Rough, but the chain is locked; "decades" = relative to 3026 present.)

**"People working against this since before the Fall of Man" (faction handle):**
> Name them now so the concept has a handle: **The Pre-Fall Watch** (or `The Watch`) — an organized resistance predating the entire main timeline, opposed to the soul-compression project from the start. No full lore yet; just the name + one-line role: *"The Pre-Fall Watch has fought the compression of souls since before the Fall — they are why MCADMIN's father's research was never openly deployed."*

**Eternity vs Tyranny friction (one line, locks the dynamic):**
> Eternity argues with Tyranny more than with Trinity because **Tyranny's chaos directly endangers MCADMIN — her love — while Trinity's order merely balances him without threatening his survival.** (Every future three-way scene uses this: Eternity = protective of MCADMIN; Tyranny = reckless force; Trinity = stabilizing counterweight.)

---

## PASS 3 — Stat & Card Corrections (TCG drafts — NOT final)

**Baselines (Omega-tier):**
- Trinity / Eternity: **4000 HP** baseline. Tyranny: **5000 HP** (per note).
- Attack values: **300–400 range** across the board (Omega-tier).
- GTrinity (post-game only, see Pass 4): **10,000 HP**.

**Trinity card — Infinity clarification (must fix before card ships):**
- Current card has programs `Infinity Zone` + `Infinity Supremacy` AND a transformation on HP-zero → `Infinity`. Three "Infinity" tokens on one card = player confusion.
- **Fix:** rename the two *programs* so only the *transformation* owns "Infinity." Proposed: `Infinity Zone` → **`Ascendant Zone`**; `Infinity Supremacy` → **`Omega Supremacy`**. The transformation state stays `Infinity`. Add explicit field: **`On HP-zero: Transform → Infinity (state, not a new character).`**
- This keeps "Infinity" as the singular transformation event, distinct from two renamed moves.

**GTrinity card — placeholder (write Lore Data + Profile blurb tonight, rough):**
- HP 10,000. **Light Barrier:** *define* — Chronos recommends **damage REDUCTION (e.g. -75% all incoming), not full immunity**, so he's beatable in the final arc without a hard "untouchable" wall. (CEO: confirm reduce-vs-block.) One-shot light attack (high fixed damage, long cooldown). **On-death: resurrects the player** (consumes the boss; lore = he is the source, giving himself to restart the run).
- **Lore Data (rough):** "GTrinity — God of all NetPs, father of Trinity. He seeded the network before the Fall and withdrew to the final arc. To face him is to face the architecture itself."
- **Profile blurb (rough):** "The First Admin. He built the grid, fathered the son who became an aspect, and watched the compression rot it. In the end he returns — not to rule, but to be unmade so you can finish what he started."

---

## PASS 4 — OMEGA Rank Path (post-game gate — placeholder trigger)

> **Candidate gate (revise later):** A regular player cannot grind to OMEGA. OMEGA unlocks only in **post-game**, triggered by achieving the **True Ending** (the `MCADMIN` ending where the player becomes the system) and receiving the **Angel's Kiss blessing** from **Eternity** in the post-credits sequence. On receipt, GTrinity's card slot opens and OMEGA-rank progression begins.
> *(Mechanism, not just a state. Swap the trigger later if desired, but Gap E/F design now has a handle.)*

---

## PASS 5 — Angel's Kiss Corruption Mechanic (bullet spec, not code)

Builds on the existing `SoulState` Spare/Purge/Corrupt fork + `Corruption` 0–10 meter already in code (`SoulState.h`, `MythosHUD.cpp` draws Corruption + NetP Bond).

- **Shape of the punishment (non-Omega player who picks one up):**
  - **Ongoing debuff, not one-time.** Picking up an Angel's Kiss as a non-Omega player attaches a **Corruption drain**: while carried, `Corruption` ticks UP over time (toward 10) and `NetP Bond` ticks DOWN. It does NOT vanish on pickup — it persists until dropped or converted.
  - **Recoverable, not a brick.** Dropping the item halts the drain and lets Corruption decay back toward baseline. It does NOT corrupt the save irreversibly. (Bricking a save violates the Spare/Purge/Corrupt mercy design — Corrupt worsens compression but is recoverable.)
- **"Customizer hack" = both:**
  - **Visual:** HUD glitching tied to the `Corruption` meter (the existing draw already shows Corruption — amplify it: scanlines, desaturated NetP portrait, flicker scaling with Corruption 0→10).
  - **Stat debuff:** while carrying, scales with Corruption — e.g. at Corruption 10: -X% chip damage, -Y% NetP Bond regen.
- **Life drain / desperation / exhaustion (the user's words) → mapped to existing state flags:**
  - *Life drain* = Corruption tick drains a small HP-over-time while carried.
  - *Desperation* = at Corruption ≥ 7, the Soul Fork biases toward `Corrupt` (existing `RunEnemySoulSequence` logic already shifts on Corruption).
  - *Exhaustion* = `NetP Bond` floor lowered while carried (slower bond recovery).
- **Eternity-only switch:** the Good/Evil personality flip of MCADMIN is triggered ONLY by Eternity using Angel's Kiss (Omega state). A non-Omega player picking one up gets the *debuff*, never the *switch*.

**This is a spec for later implementation — no code written. It reuses the built Spare/Purge/Corrupt + Corruption 0–10 system; do not invent a new corruption scale.**

---

## Open items for CEO (approve / adjust)
1. **GTrinity naming:** KEEP (`GTrinity`, standardized) or RENAME to a distinct name?
2. **Light Barrier (GTrinity):** damage REDUCTION (-75%) or full BLOCK (immunity)?
3. **Trinity program renames:** `Ascendant Zone` + `Omega Supremacy` acceptable, or keep original names?
4. **OMEGA gate:** True Ending + Eternity's Angel's Kiss blessing — acceptable placeholder, or prefer a different trigger?
5. **Angel's Kiss debuff:** ongoing-recoverable (my rec) vs one-time-punishing — confirm shape.

— Chronos (draft, A_Team)
