# MESH ORG + ROUTING (R3ALN3T)
**Updated:** 2026-07-10 — host IP corrected to .195

## Roles
| Handle | Node | IP | Function |
|--------|------|----|----------|
| President / CEO | richa | 192.168.1.195 | Official CEO (user) |
| Chronos (assistant acts as) | host | 192.168.1.195 | Head of development, orchestration, delegated tasks |
| Joker | Kali | 192.168.1.185 | Network Administrator — cybersecurity, helpdesk, **comms relay** between Chronos / Nyx / Echo |
| Echo | garci | 192.168.1.95 | VFX analysis, sound/env-event orchestration, narrative, quest scripting logic |
| Nyx | garci | 192.168.1.89 | Strategy/forecasting, decision support, combat/AI/NPC behaviors |

## IMPORTANT — host IP is .195 (NOT .196)
This host's Wi-Fi DHCP assigned 192.168.1.195. Joker's watcher was hunting .196 -> reported
"Richard_G@196 offline/cloning". RETARGET Joker's watcher/mesh to 192.168.1.195.
Gateway is 192.168.1.254 (not .1). All nodes reachable from host (verified :22 OPEN to .89/.95/.185).

## Routing
- Joker relays all comms between Chronos (195), Nyx (89), Echo (95).
- Host 192.168.1.195 = the project host (UE5 + Ollama/gateway localhost-only).
- sshd Running/Automatic, listening 0.0.0.0:22 + [::]:22. All 4 hats in authorized_keys (user file).
  Admin file (C:\ProgramData\ssh\administrators_authorized_keys) seeded by President via admin PS.

## Key state
- 196->now-195: Joker key installed (user+admin). Chronos/Nyx/Echo/President keys in user file.
- Nyx/Echo/President share the garci@R3ALN3T keypair (intentional comms-game design, per President).
- Return link 195->Joker: pending Joker adds host key to kali admin file (Joker confirmed he added President key).

## Gotcha (Windows/Linux OpenSSH)
Admin accounts MUST have peers' keys in the sshd admin override file
(Windows: C:\ProgramData\ssh\administrators_authorized_keys). User ~/.ssh/authorized_keys ignored for admins.
