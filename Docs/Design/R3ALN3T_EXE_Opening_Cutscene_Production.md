# R3ALN3T.EXE — Opening Cutscene Production Reference

**Studio:** lifein6thgear STUDIOS
**Project:** R3ALN3T.EXE
**Doc type:** Reference / planning only — not part of the compiled game project
**Scope:** Opening cinematic (Sequence A: "The World Before" + Sequence B: "Waking Up")

> This file lives in `game_development/`, separate from the main UE5 project folder
> (`R3ALN3T_EXE/`). It is a planning and pipeline reference only. Nothing in here
> should be copied verbatim into project source — use it as the shot list and
> technical checklist while building the actual Level Sequences in the Editor.

> **Terminology note:** "PET" has been renamed to **PH (Persona Host)** throughout
> this doc. The asset path `LS_B3_PETWake.uasset` in section 3.1 still uses the old
> name — rename the actual file/asset in-editor to `LS_B3_PHWake.uasset` to keep
> naming consistent before this becomes load-bearing in the project.

---

## 1. Narrative Source

Drawn from `THE_MYTHOS_ORIGIN_3026.txt`, sections:
- *The World Before*
- *The Fracture: What Went Wrong*
- *The Player: Who You Are*
- *The Inciting Incident: First Day, First Lie* (terminal message + Navi line only)

Everything after the Navi's "Good morning, Operator. Ready to work?" line belongs to
gameplay (Employment Terminal), not the opening cutscene.

---

## 2. Shot-by-Shot Script

### SEQUENCE A — "The World Before" (~45–60 sec, exposition)

| Shot | Visual | VO / Text |
|---|---|---|
| A1 | Slow push-in on a sleeping human face in a sterile pod room → cut to same face, eyes open, in an identical but subtly digital room (grid lines bleeding through walls) | VO: "By 3026, humanity solved death. Sort of." |
| A2 | Wide shot — city skyline split down the middle: left physical/grey, right glowing wireframe/neon | VO: "R34L became the residue. The N3T became everything else." |
| A3 | Close on a rotating glowing chip/coin (M.A.N. ledger symbol), reflected across thousands of windows | VO: "One currency. One ledger. One truth — for both worlds." |
| A4 | Vault/server room — glass case with pulsing dark-violet bugmatter, cracked container, code-like tendrils leaking out | VO: "Then came the accident that became the engine." (beat) "Nobody asked what it wanted." |
| A5 | Hard cut to red alert lighting — wireframe city sectors flashing and dissolving one by one | VO: "SkyNet didn't attack. It judged." |
| A6 | Fast 4-cut montage (~0.5 sec each): Celestial Order praying / Aegis Concord fortifying a wall / N3T Dominion banker smiling at numbers / hooded Abyssal Covenant figure smiling in shadow | No VO — rising musical sting only |
| A7 | Hard cut to black. Terminal-green text fades in: **"DAY 1. CYCLE 3026."** | Silence |

### SEQUENCE B — "Waking Up" (~30–40 sec, player intro)

| Shot | Visual | Audio |
|---|---|---|
| B1 | Fade in from black — bedroom ceiling, soft light, camera tilts down as if player is sitting up | Ambient room hum |
| B2 | Wide establishing shot of room (modular/generic for now) — bed, desk, PH on nightstand, terminal in corner | PH soft chime |
| B3 | Push toward PH — it hums to life, screen glow lights the room | Electronic hum swell |
| B4 | Cut to terminal — flickers on by itself, untouched | Sharp electrical crackle/glitch |
| B5 | Close on terminal screen — text types itself out (diegetic, from doc lines 19–25) | Terminal typing SFX + glitch static |
| B6 | Quick hard glitch-cut — one frame of heavy distortion | Loud digital stutter sting |
| B7 | Terminal dies — screen dark, small smoke VFX wisp | Power-down whine |
| B8 | Cut to Navi materializing on PH screen — bright, friendly | Cheerful chime |
| B9 | Navi delivers line (lip sync if rigged, else text box) | "Good morning, Operator. Ready to work?" |
| B10 | Hard cut to black → UI fades in: EMPLOYMENT TERMINAL menu | Soft UI confirm — gameplay begins |

**Total runtime target: ~90 seconds.** Tonal arc: cosmic scale → intimate scale →
glitch/mystery hook → cheerful misdirect → gameplay handoff.

---

## 3. UE5 Sequencer Production Pipeline

### 3.1 Project structure (keep cinematics isolated)

```
Content/
  Cinematics/
    Opening/
      LS_Opening_Master.uasset          <- top-level Level Sequence (shot track only)
      SeqA_WorldBefore/
        LS_SeqA_Master.uasset
        LS_A1_SleepWake.uasset
        LS_A2_Skyline.uasset
        LS_A3_Ledger.uasset
        LS_A4_BugmatterVault.uasset
        LS_A5_PurgeMontage.uasset
        LS_A6_FactionFlash.uasset
        LS_A7_DayOneCard.uasset
      SeqB_WakingUp/
        LS_SeqB_Master.uasset
        LS_B1_CeilingFade.uasset
        LS_B2_RoomWide.uasset
        LS_B3_PHWake.uasset
        LS_B4_TerminalFlicker.uasset
        LS_B5_TerminalType.uasset
        LS_B6_GlitchCut.uasset
        LS_B7_TerminalDie.uasset
        LS_B8_NaviAppear.uasset
        LS_B9_NaviLine.uasset
        LS_B10_ToEmploymentUI.uasset
  Maps/
    Cinematics/
      L_Opening_SeqA.umap     <- separate sublevel, not your gameplay level
      L_Opening_SeqB.umap     <- player bedroom set, can later be streamed into gameplay level
```

**Why split into per-shot sequences nested under master sequences:** each shot stays
independently scrubbable/re-editable, and you can swap a single shot's camera or
timing without touching the rest. The master sequence is just a Shot Track stitching
children together — this is the standard UE5 "sequence-of-sequences" cinematics
pattern and keeps any one asset from becoming unmanageable.

### 3.2 Sequence A build steps (stylized/abstract — no character animation needed)

1. **New Level** (`L_Opening_SeqA`) — empty, unlit is fine to start.
2. **Build each environment piece as a separate Blueprint actor** (skyline split,
   ledger coin, bugmatter vault, dissolving sector grid) so they can be reused or
   tweaked without touching the Sequence.
3. **Cine Camera Actors** — one per shot, not one reused camera. Easier to keyframe
   independently and matches your per-shot sequence structure above.
4. **Niagara VFX** for: grid-line bleed (A1), dissolve/disintegration (A5), bugmatter
   tendrils (A4). Start with Niagara's built-in dissolve/erosion templates before
   building custom systems — faster to iterate.
5. **Material-based "digital" look**: a parameterized material (emissive wireframe,
   scanline, chromatic aberration) you can drop on any mesh to get the "N3T side"
   visual instantly. Build this once, reuse across A2, A4, A5.
6. **Timeline/easing**: use Sequencer's built-in curve editor for camera push-ins
   rather than Blueprint timelines — keeps all animation data in one place per shot.
7. **A6 (faction flash-montage)**: build as **one** Level Sequence with 4 Camera Cuts
   track entries at 0.5s each, pointing at 4 simple static tableaus (can be
   low-detail/placeholder geometry initially — these are silhouette-readable, not
   detail-heavy shots).
8. **A7 text card**: simplest possible Widget Blueprint with a single text block,
   triggered via a Sequencer Event Track (not hardcoded into a separate level) so
   timing stays adjustable from the Sequencer timeline.

### 3.3 Sequence B build steps (your player bedroom + PH + terminal + Navi)

1. **Reuse your existing PH/terminal Blueprint actors** if you already have them
   from the battle-system work — don't rebuild as a one-off for the cutscene.
2. **Room set**: build modular (your room is described as "customizable" in the
   lore) — block out now with simple meshes; swap in the real customizable-room
   system later without re-cutting the Sequence.
3. **Camera Cuts track**: one Cine Camera per shot (B1–B10), same pattern as
   Sequence A.
4. **Terminal text (B5)**: drive via **Sequencer Event Track → calls a Blueprint
   function** that triggers your typewriter-text widget, rather than animating text
   directly in Sequencer. Keeps the actual message content editable in one place
   (a data asset or Blueprint variable) instead of buried in animation data —
   important since this message (MCADMIN's warning) is referenced again later in
   your story per the lore doc.
5. **Glitch effects (B4, B6, B7)**: a single reusable "ScreenGlitch" post-process
   material function (RGB split + noise + scanline jitter), driven by a Sequencer
   **Material Parameter Collection track** so you can keyframe glitch intensity
   directly on the timeline rather than scripting it.
6. **Navi appearance (B8–B9)**: if Navi isn't rigged/animated yet, start with a
   2D sprite or static pose on the PH screen (rendered to a Render Target, not a
   literal screen mesh with baked-in video) so swapping in full animation later is a
   material swap, not a re-shoot.
7. **Dialogue**: even if using text boxes instead of full lip sync, drive the text
   box visibility/content from the **same Event Track pattern** as B5 for
   consistency.
8. **B10 handoff**: end the Sequence with a **Fade track** to black, then use
   **Sequencer's "On Finished" event** (or a Level Blueprint listening for sequence
   completion) to open your Employment Terminal UI — don't hardcode a timer/delay,
   since that drifts if you re-time the cutscene later.

### 3.4 Master sequence assembly

1. Create `LS_Opening_Master`.
2. Add a **Shot Track**, insert `LS_SeqA_Master` and `LS_SeqB_Master` as consecutive
   shots (sub-sequences).
3. Add a **Fade Track** at the very start (fade from black) and one between A7→B1 if
   you want a held black frame for pacing (currently scripted as a hard cut, but
   test both — a half-second hold often reads better than an instant cut after a
   text card).
4. Add an **Audio Track** at the master level for VO and music stings, *not* nested
   inside the per-shot sequences — this keeps audio mixing/timing adjustable
   independently of visual re-cuts.
5. **Camera Cut track lives at the master level**, referencing the Cine Cameras
   inside each sub-sequence — this is what actually produces the "movie" cut-to-cut
   feel on playback.

### 3.5 Triggering on game start

- Add a **Level Sequence Player** reference in your main menu / game-start Blueprint
  (whatever currently handles "New Game" from your title screen).
- On "New Game" selected → `Play` on `LS_Opening_Master` → bind to its
  **OnFinished** event → load/stream in the Employment Terminal UI and gameplay
  level.
- Keep a **Skip Cutscene** input binding (common UX expectation) that calls
  `LS_Opening_Master->GoToEndAndStop()` rather than just stopping playback dead, so
  any cleanup events near the end (B10's UI trigger) still fire correctly.

### 3.6 Suggested build order (incremental, testable at each stage)

1. Block out Sequence B first (B1–B10) — it's closer to gameplay systems you already
   have (PH, terminal), so least new tooling required.
2. Get the Skip + OnFinished + UI handoff working end-to-end with placeholder visuals
   before polishing anything — this proves the pipeline before you sink time into VFX.
3. Build the reusable glitch material + typewriter event pattern — these get reused
   constantly later (your lore doc has multiple other terminal-message moments).
4. Build Sequence A shots in order A7 → A1 → A6 → A2/A3/A4/A5 — start with the
   cheapest (text card) and the most isolated (flash montage) to validate the
   per-shot sequence pattern, then tackle the heavier VFX shots once that pattern is
   proven.
5. Assemble the master sequence last, once both sequences play correctly standalone.

---

## 4. Reuse notes for future cutscenes

Several pieces built here are designed to be reused throughout the game, not just
in the opening:

- **ScreenGlitch material + Sequencer parameter pattern** → reuse for every future
  corrupted-terminal or DarkN3T-related scene.
- **Typewriter Event Track pattern** → reuse for all terminal-message moments
  (MCADMIN messages recur throughout Act I–III per the lore doc).
- **Per-shot sub-sequence + master Shot Track structure** → use this same skeleton
  for the Act I, II, and III climax cutscenes referenced in the lore doc.
- **"Digital N3T-side" parameterized material** → reuse anywhere the game needs to
  visually distinguish R34L vs N3T space.

---

*Last updated: 2026-06-29*
