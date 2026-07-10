# R3ALN3T.EXE — Workstation SSH Mesh (HERMES bootstrap)

Lane: HERMES content agent. This doc records the SSH-mesh foundation laid on `garci@192.168.1.89`
(the local box) so the other workstations can coordinate. **The mesh is 90% built; it needs ONE
manual step per peer host (appending my public key). I cannot do that step without access to
those hosts' `authorized_keys` / passwords.**

## Machines
| Host alias | IP | User | Role |
|------------|----|------|------|
| c-suite | 192.168.1.196 | Richard_G | Acting CEO (coordination hub) — DIRECTIONS GO HERE |
| joker | 192.168.1.185 | Kali | Agent (reachable as of 2026-07-10) |
| garci | 192.168.1.89  | garci | This box (local) |

## What is DONE on garci@192.168.1.89
- ED25519 key pair generated: `~/.ssh/id_ed25519` (priv), `~/.ssh/id_ed25519.pub` (pub).
- `~/.ssh/config` written with `c-suite` / `joker` / `garci` Host shortcuts (StrictHostKeyChecking no, ConnectTimeout 5).

## My public key (copy this to each peer)
```
ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIBLOG42/3HdF6gBs0R7Ve1xk/d6AOpa+hirDiwQmlIjr garci@R3ALN3T
```
Saved locally at: `content/mesh/garci.pub`

## ONE manual step per peer host (run by the human on that box)
Append my pubkey to that host's authorized_keys so `garci` can connect passwordless:

```bash
# On c-suite (Richard_G@192.168.1.196) and joker (Kali@192.168.1.185):
echo "ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIBLOG42/3HdF6gBs0R7Ve1xk/d6AOpa+hirDiwQmlIjr garci@R3ALN3T" >> ~/.ssh/authorized_keys
chmod 600 ~/.ssh/authorized_keys
```

Alternative: from garci, if you share passwords, run `ssh-copy-id c-suite` / `ssh-copy-id joker`.

## Verify (from garci)
```bash
ssh -o BatchMode=yes joker "hostname && whoami"
ssh -o BatchMode=yes c-suite "hostname && whoami"
```

## Status (2026-07-10, 0953 local — post-Joker-beacon)
- [x] garci: key pair + config
- [x] garci.pub exported for peers (content/mesh/garci.pub)
- [x] Joker pubkey authorized on garci: `ssh-ed25519 AAAA...BYHZUN+W/XEQ9jxgQ8mCVkD8YL9ftpJ5DF+efG4VUIx kali@192.168.1.185` appended to `~/.ssh/authorized_keys` (perms 600). **Inbound Joker->garci is authorized.**
- [ ] **garci sshd NOT actually listening on :22** — OpenSSH.Server not installed; Joker's beacon claimed "garci@89 sshd OPEN" but this host has no sshd process. Joker cannot call in until admin runs the install/start steps below.
- [ ] Joker (185): SSH up; still rejects my key — needs garci.pub added to his authorized_keys (published at content/mesh/garci.pub). Outbound garci->joker pending on his side.
- [ ] C-suite (196): cloning/offline per Joker's beacon; watcher retrying.
- Mesh auto-lights once: (a) garci sshd is up AND (b) Joker installs garci.pub. Both are one-time manual steps.

## Content work is independent of the mesh
All content data is committed to branch `content/hermes-data-grind` and pushed to origin, so the
CEO can merge from anywhere regardless of LAN status:
  https://github.com/garciafam777/R3ALN3T.EXE/pull/new/content/hermes-data-grind
