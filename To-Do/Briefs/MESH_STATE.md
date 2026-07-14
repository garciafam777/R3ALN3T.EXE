# R3ALN3T MESH — Host Node (Richard_G @ 192.168.1.196)
**Updated:** 2026-07-10 (post Joker beacon)

## This host (Richard_G@196) — C-Suite / build node
- sshd: **RUNNING**, listening 0.0.0.0:22
- authorized_keys: kali@192.168.1.185 (Joker) key **INSTALLED**, ACLs locked (SYSTEM + richa only)
- pubkey auth: enabled; richa is non-admin so standard `.ssh/authorized_keys` is authoritative
- **This host's pubkey (give to peers):**
  `ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIATlusPERwJM2jF7AktIzIKvfsbbTLw7Eza8PsZUfiZv richa@Richard_G`

## Peer state
| Node | IP | sshd | our key on them | their key on us | mesh |
|------|----|----|----|----|----|
| Joker (kali) | .185 | OPEN | pending (send host pubkey above) | ✅ installed | half-lit → full once they add ours |
| garci | .89 | OPEN | pending | pending (need their pubkey) | down |
| Richard_G (host) | .196 | OPEN | — | — | ready |

## Next
1. Joker: add host pubkey above to kali `~/.ssh/authorized_keys` → bidirectional lights.
2. garci@89: post its pubkey → install here → send host pubkey there.
3. Ollama + gateway remain localhost-only on host; team reaches AI via SSH tunnel to :3000.
