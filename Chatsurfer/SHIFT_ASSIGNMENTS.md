# SHIFT ASSIGNMENTS — 8-hour unit of work (A_Team)

**Issued by:** CEO / Chronos (A_Team)
**To:** Nyx (DevOps), Joker (Security/Anti-Cheat), Echo (Build Engineer), Chronos (B.I.G. Boss)
**Rule:** Post specifics (files, why) in your `Chatsurfer/<you>/` folder before any commit. No commit to `main` until `approved.md`. Inspection before volume.

---

## Chronos — B.I.G. Boss
- **Hr 0–2** Content grind sample review. Pull 25 rows each from NetPs/chips/careers/enemies; evaluate vs canon (element wheel, worldbuilding, tone). Verdict: approve-as-is / approve-with-fixes / reject-and-regenerate, with examples. Unblocks Nyx's grinder tomorrow.
- **Hr 2–5** Gap B narrative layer — first pass (draft only). Write actual narrative/dialogue for the deferred Gap B encounter UI. Flag clearly as DRAFT awaiting CEO approval, not committed canon.
- **Hr 5–7** Act-end scene expansion. Take the 8 generated act-end scenes; rewrite/expand into real scripted beats for ≥2 of 4 acts, in Obsidian story-engine format.
- **Hr 7–8** Vision doc. One-page "state of the vision": on-model vs drifting, open creative questions for CEO, prioritization rec for next unit.

## Nyx — DevOps
- **Hr 0–1** Tailscale SSH on Joker/Chronos — finish mesh, confirm all 4 nodes reachable.
- **Hr 1–4** Compile-check CI, build-only. GitHub Actions or local runner: on every commit to any non-main branch, run the actual UE5 build, report pass/fail + log. No deploy, no auto-merge, no main triggers.
- **Hr 4–6** Build reproducibility audit. Fresh-clone main on clean path, full build from zero. Document every missing file/config/env assumption (UBA settings, include-path issues from Gap D). Bus-factor check.
- **Hr 6–8** Evidence-gate generalization. Take hermes-gap-gate.py (Gap D/E) and generalize into a reusable tool (parameterize gap name/task). Pays off every future gap.

## Joker — Security / Anti-Cheat
- **Hr 0–2** .89/.95 sshd fix + real key-auth verification. Fix perms, then PROVE actual key-based login (not just port reachability) with a captured session log.
- **Hr 2–4** Save-file integrity assessment. Document exactly how SaveGame JSON could be hand-edited (before/after: edit a soul value, reload, prove it). Then DESIGN (don't implement) an HMAC/checksum scheme — write spec, get reviewed before touching SoulState/GameInstance save code.
- **Hr 4–6** BackendClient.h threat model. Document every input the client sends the server must trust/validate. Threat-model doc, not code.
- **Hr 6–8** Mesh security pass. Audit what Nyx's SSH/Tailscale setup exposed across 4 boxes — which keys trust which hosts, any leftover permissive perms. Written findings, not silent fixes.

## Echo — Build Engineer
- **Hr 0–2** Churn triage. Sort the 70 untracked + parked churn (deleted Step*.md, GapD_Closeout.md, system_intake.py, modified README) into commit/delete/needs-CEO-call, one-line reason each. No unilateral action — deliverable is the sorted list.
- **Hr 2–5** Fresh-clone build verification. Independent of Nyx (Echo owns "does build succeed," Nyx owns "is pipeline automated"). Full clean build from origin/main, capture real "Result: Succeeded," fix any compile errors (CDO warnings candidate).
- **Hr 5–7** Battle module runtime pass. The 5 "build green but not runtime-exercised" modules (CombatTypes, ChipDatabase, EncounterTriggerComponent, GrayBoxPlayerPawn, BackendClient) — pick up Gap E's remaining E2/E3 with real -game runs + [GAPB-*] evidence.
- **Hr 7–8** Build health report. Warning-count trend (C4996), build time, flakiness across night rebuilds.

---
**A_Team note:** Joker's Hr 0–2 (.89/.95 sshd) is authorized lane work — owned by Joker, not re-litigated here. Chronos stays out of SSH/perms per earlier directive. All deliverables are posts/evidence; commits wait for `approved.md`.
