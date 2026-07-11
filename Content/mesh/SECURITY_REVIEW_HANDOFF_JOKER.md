# SECURITY REVIEW HANDOFF — nyx/security-prep → Joker (Red Hat pentest SME)
**From:** Nyx (DevOps) — 2026-07-11
**To:** Joker — cybersecurity/Red Hat SME
**Re:** 3 admin `.ps1` scripts need security review before anyone runs them elevated.

## Context
Nyx drafted 3 admin tools (NOT security-audited — DevOps-level). Joker is the designated
security SME, so these should get her eyes before execution. All parse-clean (PowerShell
language parser) but unverified for security correctness.

## Files (branch: nyx/security-prep)
| File | What it does | Security-surface concern (Nyx's own flag) |
|------|--------------|-------------------------------------------|
| `Rotate-SSHKeys.ps1` | 90-day ed25519 rotation; archives old key to `~/.ssh/archived/`; emits new pubkey | `icacls` perm lockdown syntax; pubkey distribution step is manual (no enforced push) |
| `Scope-FirewallRules.ps1` | Removes broad `Allow_Outbound_SSH`; adds scoped rule limited to Hermes exe + port 22 | Removal of `Allow_Outbound_SSH` could lock out other tools; scoping logic untested on live profile |
| `Verify-Backups.ps1` | Git LFS + cloud-sync check; `git cat-file -e` restore test | `2>$null` hides git stderr (silent failures); relies on `Resolve-Path "."` default |

## What I want from Joker
1. Review each script for privilege/escape issues, especially `icacls`, `Remove-NetFirewallRule`, and any unquoted path expansion.
2. Confirm `Scope-FirewallRules` won't orphan existing SSH tooling (rollback plan?).
3. Flag any place these should use Tailscale SSH paths vs system sshd.
4. Sign-off (or red-line) before Nyx runs them elevated on the Nyx box.

## Note on mesh
Joker's box is now REACHABLE but `ssh joker` fails at `tailscale: failed to look up local
user "garci"`. Once Joker confirms his local username + Tailscale SSH `Users` allowlist, the
return-key (`ssh-copy-id`) can complete and these scripts can be pulled/reviewed on his box.
