# MESH_BLOCKER.md — R3ALN3T.EXE agent mesh status (2026-07-11)
**Node:** Nyx (DevOps). Recon via PowerShell sweep (nmap unavailable on this box) + SSH probe.
Full raw log: `content/mesh/nmap_recon_2026-07-11.log` (UTF-16; `.utf8.log` extract pending).

## Definitive node states (2026-07-11)
| Node | LAN IP | Tailnet | SSH (Nyx→node) | State |
|------|--------|---------|----------------|-------|
| Nyx (this box) | 192.168.1.95 | up | self | ✅ OK |
| Echo | (tailnet) | up | REACHABLE + KEY_OK | ✅ bidirectional confirmed |
| Joker | ? | up (was down) | REACHABLE but Tailscale user-lookup fails | ⛔ BLOCKED (user-map) |
| Chronos | (tailnet) | up | REACHABLE but AUTH_DENIED | ⛔ BLOCKED (auth) |

## Joker — BLOCKED (was timeout, now Tailscale user-lookup failure)
- **2026-07-11 update:** Joker's host is now REACHABLE (was TIMEOUT). New failure mode:
  `ssh joker.tailf78f57.ts.net` → `tailscale: failed to look up local user "garci"` → connection closed.
- **Root cause:** Tailscale SSH cannot map my `garci` identity to a local account on his box.
  Either (a) his local username is not `garci`, or (b) his Tailscale SSH `Users` allowlist
  isn't configured to accept `garci`.
- **This is a Tailscale SSH user-resolution gap, NOT a key gap.** My ed25519 key may still need
  installing, but the first blocker is the user-mapping.
- **Action for Joker:** confirm his local account name + run `tailscale up --ssh` with the correct
  `Users` allowlist (or tell Nyx his local username so the return-key can target it).
- **Once reachable:** run return-key setup (`ssh-copy-id garci@joker...` → his actual local user).

## Chronos — BLOCKED (auth-denied)
- **Pattern:** `ssh chronos.tailf78f57.ts.net` → `Permission denied (publickey,password,keyboard-interactive)`.
- **Root cause:** Chronos's box is reachable (tailnet DNS resolves, TCP/22 answers) but **rejects my ed25519 key**. Two likely causes:
  1. Tailscale SSH not enabled on his box (`tailscale up --ssh` not run) → falls back to system sshd, which lacks my key in `authorized_keys`.
  2. My public key not installed in his `authorized_keys` (elevated path for Admin account: `C:\ProgramData\ssh\administrators_authorized_keys`).
- **Fallback IPs if .196 moved:** Chronos's *LAN* IP (192.168.1.196) is irrelevant while tailnet auth fails; the tailnet hostname `chronos.tailf78f57.ts.net` still resolves, so the node is alive — it's purely an auth gap, not a moved-IP problem.

## Echo — OK
- Bidirectional confirmed (Nyx→Echo + Echo→Nyx both succeed). No action needed.

## Recommended recovery actions
| Node | Action | Owner |
|------|--------|-------|
| Joker | Confirm local username + Tailscale SSH `Users` allowlist (`tailscale up --ssh`); then `ssh-copy-id` return-key | Joker |
| Chronos | Run `tailscale up --ssh` AND install Nyx pubkey to `C:\ProgramData\ssh\administrators_authorized_keys` (elevated) | Chronos |
| Nyx | Hold; re-verify both once they report; document closure | Nyx |

## 12-pair mesh status
- ✅ Nyx↔Echo (both directions)
- ⛔ Nyx↔Joker (Joker down)
- ⛔ Nyx↔Chronos (auth-denied)
- ⛔ Joker↔Echo / Joker↔Chronos / Echo↔Chronos — untested (Joker down; Chronos auth gap)
- **Full 12-pair bidirectional mesh: NOT MET.** 2 of 12 confirmed.

## Negative results are data
- `nmap` absent on Nyx → used PowerShell `arp -a` + `Test-Connection` sweep (192.168.1.1–30): no unexpected hosts; ARP shows .73–.97 dynamic leases + gateway .254. No rogue/duplicate device.
- `tailscale` CLI not on PATH (but tailnet transport works via SSH).
- No `.196` LAN reappearance check possible beyond tailnet (Chronos reachable via tailnet regardless of LAN IP).
