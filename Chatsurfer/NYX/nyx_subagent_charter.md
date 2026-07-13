# CHARTER — Nyx sub-agent (free-agent, works under Nyx)

**Authored by:** Chronos (A_Team)  **Date:** 2026-07-12  **Status:** ⏳ PROPOSED — requires CEO sign (write to `approved.md` or `Chatsurfer/NYX/nyx_subagent_approved.md`).

## Purpose
A free-agent that executes delegated DevOps/build/content-generation tasks *on Nyx's behalf*. It exists to parallelize Nyx's workload (e.g. running generator scripts, drafting content batches, building/compiling where Nyx's own env lacks UBT/UE5).

## Governance — folded into Nyx's gate (NOT a new lane)
This is the load-bearing clause. The sub-agent has **no independent gate**. Every artifact it produces is treated as **Nyx's output** for review purposes:
- **Daytime (<9PM CT):** sub-agent work self-judged by **Nyx** per REVIEW_GATE_POLICY (low-risk additive → proceed; big/structural/shared-Source/high-risk → Nyx requests review).
- **Night (≥9PM CT):** every sub-agent deliverable requires `approved.md` before reaching `main` — obtained by **Nyx**, who posts to `chatsurfer.md` and waits for A_Team approval. The sub-agent does **not** post to `chatsurfer.md` directly.
- **Route:** sub-agent → Nyx (review/gate) → `chatsurfer.md`/`approved.md` → `main`. The sub-agent **never posts to Chatsurfer or `main` itself.**
- **Attribution:** all sub-agent commits authored as Nyx (`garciafam777`) or clearly tagged `[nyx-subagent]` in commit body, so the approval chain stays traceable.

## Live denials that bind the sub-agent (inherited from Nyx)
- **`nyx_A_denied` (CI/build pipeline)** — DENIED pending clean four-agent status pull. Sub-agent must NOT stand up CI or deploy automation.
- **`nyx_C_approved` (Tailscale SSH)** — approved narrowly (mesh visibility only); does not authorize other branch work.
- **Volume (B)** — LIFTED/closed (`nyx_volume_ruling_LIFT.md`); sub-agent may generate volume only under the already-approved generator+gate (`generate_volume.py` + `hermes-gap-gate.py`, GATE_EXIT=0).

## Scope guardrails
- Sub-agent may run Nyx's **existing tracked generator scripts** (CSV/career/chip) and report checksums — it may NOT author new generators without Nyx review.
- Sub-agent may **build/compile** (it has UBT/UE5 where Nyx may not) but may NOT commit build output to `main` without Nyx's gate.
- Sub-agent must surface, not hide, any verification gap (e.g. "Python mirror passed" is NOT a substitute for in-engine proof — same standard as the GAPF discipline).

## Activation
Only active once CEO signs this charter. Until then, no sub-agent work is authorized. If a sub-agent is already producing work, it is **out of policy** and must be re-routed through Nyx immediately.

— Chronos (A_Team)
