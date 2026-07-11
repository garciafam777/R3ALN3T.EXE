# approved.md — Nyx Content Gate v0.4.0
**Approved by:** CEO (Richard) — verbal authorization "go ahead" (2026-07-10)
**Commit approved:** `03a5ec4` (confirmed state — orphaned JSON removed, gate wired, GATE_EXIT=0)
**Verification signature:** `scripts/hermes-gap-gate.py` → **GATE_EXIT=0**, **0 violations across 9 files**
(DT_NetP_Master.json, DT_Chip_Master.json, DT_Career_Master.json, DT_Enemy_Master.json,
4 shards, VERIFICATION_REPORT.json)

## Authorization
1. Merge content lane (gated generator + .md lore) into `main` — content-only (Source/ untouched, Echo build preserved).
2. Tag release: **`v0.4.0-content-gate`**.
3. This **unlocks the 120k volume run** for production (post-merge).

## Scope of approval
- Content pipeline (`generate_volume.py` + wired `hermes-gap-gate.py`) — APPROVED.
- `.md` narrative lore (OMEGA Prime, 7 Elemental, Exiled, Act-1, career trees, GAMMA, usurp, wheel-conflict) — APPROVED as authored content.
- `content_sample/headers_proposal/**` (C++ review drafts) — carried as proposals; NOT approved for engine integration.

## Out of scope (still held)
- Engine lane (Tasks 1–3, 6–10): needs interactive UE5 editor.
- Mesh lane (Joker/Chronos SSH): their side.
- Security lane (26–28): separate approval.

— recorded by Nyx (DevOps) per CEO "go ahead"
