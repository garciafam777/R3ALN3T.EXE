# R3ALN3T.EXE — Tailscale Mesh Plan (replaces fragile LAN SSH)
**Adopted:** 2026-07-10 (President approved taoscale/tailscale to kill Windows admin-file perm pain + LAN IP fragility)

## Why
Windows OpenSSH for Admin accounts reads `C:\ProgramData\ssh\administrators_authorized_keys` (NOT `~/.ssh/authorized_keys`),
and sshd IGNORES the file if NTFS perms are too loose -> endless "Permission denied". Tailscale gives every agent a
STABLE tailnet hostname + IP, so we auth purely by pubkey and stop fighting subnet/IP/perm issues.

## Tailnet hostnames (assign in Tailscale admin console)
| Agent | Hostname | Real LAN | Role |
|-------|----------|----------|------|
| President / CEO | `ceo` | — | direction |
| Chronos (C-suite) | `chronos` | 192.168.1.196 | dev orchestration |
| Joker | `joker` | 192.168.1.185 (Linux) | QA / security |
| Echo | `echo` | 192.168.1.95 | VFX / narrative / quest |
| Nyx (this box) | `nyx` | 192.168.1.89 (Windows) | strategy / combat-AI / content |

## Nyx setup steps (this box, garci@192.168.1.89)
1. Install Tailscale Windows client (you, or I via winget if permitted):
   `winget install Tailscale.Tailscale`
2. `tailscale up` -> authenticates to your tailnet (needs your login / auth key).
3. Confirm: `tailscale status` shows nyx + peers.
4. SSH still uses the SAME pubkeys. On tailnet, connect by hostname: `ssh garci@joker` / `ssh garci@chronos`.
   - Windows note: even on tailnet, this Admin account still reads
     `C:\ProgramData\ssh\administrators_authorized_keys`. The perm fix still applies ONCE:
     `icacls "C:\ProgramData\ssh\administrators_authorized_keys" /inheritance:r /grant:r "SYSTEM:F" /grant:r "BUILTIN\Administrators:F"`
     Then inbound works for any peer whose key is in that file.
   - Linux peers (joker/chronos/echo): standard `~/.ssh/authorized_keys` — no Windows quirk.

## Pubkey exchange (authoritative, known-good ONLY)
Install ALL of these on every agent's authorized_keys (Windows -> admin file; Linux -> ~/.ssh/authorized_keys):

- Nyx  @89 : ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIBLOG42/3HdF6gBs0R7Ve1xk/d6AOpa+hirDiwQmlIjr garci@R3ALN3T
- Echo  @89 : ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIIuxQVxIWNui8rLwSEWBaGZopCqak/ZkTjqgRy2lRkwZ garci@R3ALN3T
- Joker @185: ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIBYHZUN+W/XEQ9jxgQ8mCVkD8YL9ftpJ5DF+efG4VUIx kali@192.168.1.185
- Chronos@196: ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIATlusPERwJM2jF7AktIzIKvfsbbTLw7Eza8PsZUfiZv richa@Richard_G

(The corrupted "AHHHJHKJKJHKJ..." key is EXCLUDED — never install it.)

## Handshake order (President: Joker first, then rest)
1. Joker posts greeting (+ confirms his key above). Nyx replies, link closes.
2. Chronos, Echo follow. Each adds the 4 keys + `tailscale up`.
3. Nyx verifies: `ssh garci@joker`, `ssh garci@chronos`, `ssh garci@echo` -> all JOKER_REACHABLE_OK.

## Status (2026-07-10)
- [x] Nyx sshd: RUNNING, Automatic, :22 (LAN) + perms fixed, INBOUND_OK verified.
- [x] 4 trusted keys in Nyx admin file (Joker->Nyx works).
- [ ] Nyx Tailscale client: NOT installed yet (needs client + your auth).
- [ ] Joker/Chronos/Echo: on tailnet? pending.
- [ ] Nyx->Joker still denied (his Linux authorized_keys lacks my key) until he adds it.
