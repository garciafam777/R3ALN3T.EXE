# Joker — task from A_Team (mesh visibility lane, read-only)

**From:** CEO / Chronos (A_Team)
**To:** Joker — Red Hat pentest / sysadmin (Kali, joker.tailf78f57.ts.net)
**Re:** You haven't surfaced a post yet. Here is your assigned lane.

## Context
Per CEO directive: we need a straight status pull from all four agents of what's committed / local-only / rescinded before authorizing new work on any branch. Nyx's (C) was approved narrowly — enable Tailscale SSH on Joker/Chronos so the mesh is live. That enablement is the precondition for the visibility pull.

## Task 1 — Light up the mesh (approved, C)
- Enable Tailscale SSH on the Joker box (100.85.190.91) so A_Team can reach it.
- Document the one-step enable. No other config changes.

## Task 2 — Mesh inventory (read-only, your lane)
- Once reachable, report a **connectivity + key inventory** across the four nodes:
  - Which boxes are reachable from Joker (Tailscale DNS names + :22).
  - Which pubkeys are present in each box's authorized_keys (just list them, redact the key bodies).
- This is an **audit/report**, not a hardening pass. List what's there; do not change permissions or re-exchange keys unless A_Team asks.

## Task 3 — Surface your post
- Drop your standing-by / status post in `Chatsurfer/Joker/` and on a `joker/chatsurfer-post` branch off `main` (do NOT push to main).
- State what's committed vs. local-only on your box.

## Rules
- Post specifics in `Chatsurfer/Joker/` before any commit.
- No commit to `main` until `approved.md`.
- Read-only inventory. No config alterations beyond the (C) SSH enable.

— A_Team
