# R3ALN3T.EXE — Mesh Topology (Nyx/DevOps, draft)

> STATUS: PARTIAL. Tailnet up; full 12-pair bidirectional mesh NOT yet established.
> Per Chatsurfer hold: this doc is PROPOSAL/STATUS, not a main commit until approved.

## Nodes (Tailscale, tailf78f57.ts.net)
| Agent | Hostname | Tailnet IP | Role | Nyx→them | them→Nyx |
|-------|----------|-----------|------|-----------|----------|
| Nyx (this box) | nyx | 100.69.52.53 | DevOps | self | self |
| Echo | echo | 100.89.22.36 | Build/VFX | ✅ ECHO_OK | ✅ |
| Joker | joker | 100.85.190.91 | Sec/Sysadmin | ⚠️ unreachable now | ✅ (key in admin file) |
| Chronos | chronos | 100.116.26.120 | C-suite/Dir | ❌ Permission denied | ✅ (key in admin file) |

## Required 12 pairs (verified state)
- [x] Nyx↔Echo (both directions)
- [x] Nyx→Joker (his key on my box) / Joker→Nyx (my key on his Linux authorized_keys — PENDING his add)
- [ ] Nyx→Chronos (needs `tailscale up --ssh` on his box)
- [ ] Joker↔Echo, Joker↔Chronos, Echo↔Chronos — NOT TESTED (need their boxes up + Tailscale SSH)

## Key fingerprints (ed25519, REDACTED — verify via ssh-keygen -lf on each node)
- Nyx pub: ssh-ed25519 AAAAC3Nza...BLOG42... garci@R3ALN3T
- Joker pub: ssh-ed25519 AAAAC3Nza...BYHZU... kali@192.168.1.185
- Chronos pub: ssh-ed25519 AAAAC3Nza...ATlus... richa@Richard_G
- Echo pub: ssh-ed25519 AAAAC3Nza...IIuxQ... garci@R3ALN3T

## Sync pipeline (proposed)
- Content: `git push` to `content/hermes-data-grind` (or `nyx/chatsurfer-post`); all nodes `git pull`.
  Alternative for large shards: `rsync -avz` of `content_sample/` between nodes over tailnet.
- Source/: UE5 C++ owned by Chronos/Echo; Nyx does NOT push Source/ (out of lane + held).
- Hermes `terminal.backend: ssh` on each node with host=`*.tailf78f57.ts.net`, user per agent.

## Failover rules
- If a node's tailnet IP changes, rely on hostname (Tailscale MagicDNS) not IP.
- If Joker/Chronos boxes are down, Nyx continues content work; sync resumes on their return.
- Primary content sync path = git (auditable); rsync = bulk shard transfer only.

## Blockers
1. Joker box currently unreachable (was up earlier; may be asleep/offline).
2. Chronos Tailscale SSH not enabled → Permission denied. Needs `tailscale up --ssh` on his box.
3. Cross-node pairs (Joker↔Echo etc.) untested — need all 4 boxes up + Tailscale SSH on each.
