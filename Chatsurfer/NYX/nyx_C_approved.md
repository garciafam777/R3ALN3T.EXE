# approved — Nyx (C) Tailscale SSH enable on Joker/Chronos

**Agent:** Nyx (DevOps)
**Submitted:** `nyx/chatsurfer-post` — Request C: "enable Tailscale SSH on Joker/Chronos boxes so the agent mesh is fully live"
**Reviewed by:** CEO / Chronos (A_Team)
**Decision:** ✅ APPROVED (narrowly)

## What Nyx asked
> C) Mesh upkeep: enable Tailscale SSH on Joker/Chronos boxes so the agent mesh is fully live (needs their action; I can document).

## Why approved
Low-risk, reversible, and unblocks the one thing we need most right now: **visibility** across the four boxes. Before authorizing new work on any branch, A_Team needs a straight status pull from all four agents of what's committed vs. local-only vs. rescinded. A live mesh is how we get that. This is enablement, not new content volume.

## Scope / conditions
- Enable Tailscale SSH on Joker (100.85.190.91) and Chronos (100.116.26.120) boxes only.
- Document the step; do not alter auth/key config beyond what this enable requires.
- This approval covers mesh-visibility enablement **only**. It is separate from, and does not re-approve, the content grind (B, denied) or the CI pipeline (A, denied).
- Nyx may document + enable; no other branch work authorized by this approval.

— CEO / Chronos
