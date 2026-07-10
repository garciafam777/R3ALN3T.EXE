# R3ALN3T.EXE — Agent Roster & Mesh Assignments
**Established:** 2026-07-10  **Set by:** President (CEO)

## Roles
| Handle | Host / IP | Name | Lane |
|--------|-----------|------|------|
| President | — | **Official CEO** | Direction / sign-off |
| Joker | Kali@192.168.1.185 | **QA / detection / rules enforcement / cybersecurity** | Verification + security |
| C-Suite / CEO | Richard_G@192.168.1.196 | **Chronos** (head of development, orchestration, delegated tasks) | Dev orchestration (was "acting CEO" hub; now officially Chronos under President) |
| Echo | garci@192.168.1.95 | **VFX analysis, sound environment-event orchestration, narrative, quest scripting logic** | VFX / audio / narrative / quest |
| Nyx | garci@192.168.1.89 | **Strategy/forecasting, decision support, combat/AI/NPC behaviors** | Strategy / combat-AI / NPC |

> NOTE: this box is **Nyx** (garci@192.168.1.89). The prior docs called it "garci/HERMES content agent";
> content-data work remains Nyx's lane. Echo is a SEPARATE machine at .95 (not yet online in this session).

## Pubkeys (authoritative — install these)
- **President / CEO (Chronos, C-suite 196):** `ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIATlusPERwJM2jF7AktIzIKvfsbbTLw7Eza8PsZUfiZv richa@Richard_G`
- **Joker (185):** `ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIBYHZUN+W/XEQ9jxgQ8mCVkD8YL9ftpJ5DF+efG4VUIx kali@192.168.1.185`
- **Nyx (this box, 89):** `ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIBLOG42/3HdF6gBs0R7Ve1xk/d6AOpa+hirDiwQmlIjr garci@R3ALN3T`
- **Echo (95):** <pending — Echo machine not online yet this session>

## ⚠️ REJECTED KEY
The block ending your message:
`ssh-ed25519 AHHHJHKJKJHKJAAAC3NzaC1lZDI1NTE5AAAAIIuxQVxIWNui8JJJJJJJJHHHKJKHJKKrLwSEWBaGZopCqak/ZkTjqgRy2lRkwZ garci@R3ALN3T`
is **CORRUPTED / NOT VALID** (contains `AHHHJHKJKJHKJ` garbage, wrong length vs a real Ed25519 key,
and duplicates the `garci@R3ALN3T` identity already owned by Nyx@89). **Do not install it.** Nyx's real
key is the one listed above (IBLOG42/...). If Echo@95 needs its own key, generate a fresh one on that
machine with `ssh-keygen -t ed25519` and share the resulting .pub.

## Mesh status (2026-07-10)
- [x] Nyx@89 sshd: RUNNING, Automatic, :22 listening.
- [x] Nyx trusts: Joker (185) + Nyx self. CEO key PENDING (needs your elevated PowerShell — see command in chat).
- [x] Inbound verified (SELF_MESH_OK).
- [ ] Outbound Nyx->Joker: pending Joker installing Nyx's key.
- [ ] Echo@95: not online this session.
- [ ] C-suite@196 (Chronos): cloning/offline; watcher retrying.
