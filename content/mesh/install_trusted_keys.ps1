# R3ALN3T.EXE - install trusted mesh keys (run ELEVATED on each Windows agent)
# Works on .89 (Nyx), .95 (Echo), .196 (Chronos). Idempotent.
# Writes all known-good peer pubkeys to BOTH:
#   - $env:USERPROFILE\.ssh\authorized_keys        (user-level)
#   - C:\ProgramData\ssh\administrators_authorized_keys (admin-level; Windows OpenSSH
#     uses this for Administrator-group accounts and IGNORES the user-level file)
# Then fixes perms and restarts sshd.
#
# KNOWN-GOOD KEYS ONLY. The corrupted "AHHHJHKJKJHKJ..." key is deliberately excluded.
# Add Echo's key here once Echo generates one: ssh-keygen -t ed25519 on .95.

$keys = @(
 'ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIBLOG42/3HdF6gBs0R7Ve1xk/d6AOpa+hirDiwQmlIjr garci@R3ALN3T',   # Nyx  @89
 'ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIBYHZUN+W/XEQ9jxgQ8mCVkD8YL9ftpJ5DF+efG4VUIx kali@192.168.1.185', # Joker @185
 'ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIATlusPERwJM2jF7AktIzIKvfsbbTLw7Eza8PsZUfiZv richa@Richard_G'   # CEO/Chronos @196
)

# user-level (UTF-8, 600)
$ud = "$env:USERPROFILE\.ssh"
New-Item -ItemType Directory -Force -Path $ud | Out-Null
$uf = Join-Path $ud 'authorized_keys'
Set-Content -Path $uf -Value ($keys -join [Environment]::NewLine) -Encoding ASCII
icacls $uf /inheritance:r /grant ('{0}:F' -f $env:USERNAME) /grant '*S-1-5-18:F' | Out-Null

# admin-level (ProgramData) - used for Administrator accounts
$pd = 'C:\ProgramData\ssh'
New-Item -ItemType Directory -Force -Path $pd | Out-Null
$af = Join-Path $pd 'administrators_authorized_keys'
Set-Content -Path $af -Value ($keys -join [Environment]::NewLine) -Encoding ASCII
icacls $af /inheritance:r /grant 'BUILTIN\Administrators:F' /grant 'NT AUTHORITY\SYSTEM:F' | Out-Null

# ensure sshd running
if (-not (Get-Service sshd -ErrorAction SilentlyContinue)) {
  Add-WindowsCapability -Online -Name OpenSSH.Server~~~~0.0.1.0 | Out-Null
}
Set-Service sshd -StartupType Automatic -ErrorAction SilentlyContinue
Restart-Service sshd -Force -ErrorAction SilentlyContinue
Start-Sleep 1
Write-Host "DONE. sshd=$( (Get-Service sshd).Status ). Trusted keys installed: $($keys.Count)"
