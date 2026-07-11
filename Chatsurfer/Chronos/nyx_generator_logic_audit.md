# Nyx generator — element-assignment LOGIC audit (Chronos)

**Date:** 2026-07-11
**Why:** CEO's open finding was that the validator "passed yet shipped 'Sound'" — i.e. the *generator's element-assignment logic* may have a blind spot, not just the gate's *coverage*. The CSV-coverage fix (prior step) closed coverage; this audits the LOGIC.

## Every code path that sets `element`
**generate_volume.py**
- L19 `CANON=["Fire","Aqua","Elec","Wood","Wind","Holy","Void"]` — module-level literal, NEVER mutated, never read from config/file.
- L60 `el=random.choice(CANON)` (netp) → L66 writes `"element":el`.
- L74 `gen_chips`: `"element":random.choice(CANON)`.
- L81 `gen_careers`: `"element":random.choice(CANON)`.
- L85 `gen_enemies`: `"element":random.choice(CANON)`.
- `verify()` (L90-108) only REJECTS `element not in CANON`; it never assigns.

**generate_sample.py**
- L19 `ELEMENTS_7=["Fire","Aqua","Elec","Wood","Wind","Holy","Void"]` — same closed literal.
- L89, L107, L118, L127: every `element = random.choice(ELEMENTS_7)`.

## Q: any path (fallback/default/concat/config) that could emit off-wheel?
**NO.** `element` is set EXCLUSIVELY by `random.choice(CANON|ELEMENTS_7)`. Both pools are hardcoded 7-element literals. No `else` branch, no `.get(default=...)`, no string concatenation, no external file/config lookup for element. `random.choice` can only return a member of its input set. There is no input or edge case (empty tier, bad index, missing config) under which this returns "Sound" or any off-wheel token — it is **impossible by construction**.

## Q: under what input did the original "Sound" defect emit, and does that path still exist?
- The "Sound" defect came from the OLD generator (the one that produced the orphaned `content_sample/lore/*.json` stubs w/ `element:'None'` and the bad grind). 
- The CURRENT `generate_volume.py` / `generate_sample.py` are POST-VERDICT REWRITES (generate_sample.py L4-7: "Fixes per content_grind_review_approved.md... Element pool = canonical 7 ONLY"). 
- The "Sound"-emitting code does NOT exist in these files. It was removed by rewrite, not merely constrained. So the bad path is GONE, and a clean 220k run reflects that structurally — not luck.

## Q: does a clean run prove the bad path is gone?
Yes, in the strong sense: the new generator **cannot** emit off-wheel (closed pool), so there is no latent path that "didn't fire this time." The only way "Sound" could reappear is if someone reintroduces a non-canon source into CANON/ELEMENTS_7 — which is a code change, not a runtime edge. The `hermes-gap-gate.py` (now CSV-aware) would catch any such change at generation time (the generator runs the gate itself, L145-159 of generate_volume.py, and `sys.exit(non-zero)` on failure).

## Residual note (honest)
- `random.choice(CANON)` would raise IndexError only if CANON were empty — impossible (literal, unmuted).
- Off-wheel substrings can appear in `flavor_text`/`name` via `ELEMENT_WORDS`, but those are themselves 7-wheel-derived and are NOT element fields (gate correctly ignores; confirmed false-positive on "ice" earlier).

## Verdict
Generator element-assignment logic: **structurally closed**. Coverage gap (CSV) + generator logic both confirmed. Combined with the prior independent output verification, the original "validator passed yet shipped Sound" finding is now addressed at BOTH layers.

— Chronos (A_Team)
