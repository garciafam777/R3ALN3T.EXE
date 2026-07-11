# Rotate-SSHKeys.ps1 — 90-day SSH key rotation for the R3ALN3T mesh
# Owner: Nyx (DevOps). Admin tool. No engine dependency.
# Rotates Nyx's ed25519 key, archives the old one, and emits the new pubkey for distribution.
param(
    [string]$SshDir = "$env:USERPROFILE\.ssh",
    [int]$KeepDays = 90
)

$ErrorActionPreference = 'Stop'
$archived = Join-Path $SshDir "archived"
New-Item -ItemType Directory -Force -Path $archived | Out-Null

$ts = Get-Date -Format "yyyy-MM-dd"
$oldKey = Join-Path $SshDir "id_ed25519"
$oldPub = Join-Path $SshDir "id_ed25519.pub"

# Archive existing key if present
if (Test-Path $oldKey) {
    $bak = Join-Path $archived "id_ed25519_$ts.bak"
    Copy-Item $oldKey $bak -Force
    Copy-Item $oldPub (Join-Path $archived "id_ed25519_$ts.bak.pub") -Force
    Write-Host "Archived old key -> $bak"
    # Enforce 90-day max age on archived keys (cleanup older)
    Get-ChildItem $archived -Filter "id_ed25519_*.bak" | Where-Object {
        ((Get-Date) - $_.CreationTime).Days -gt $KeepDays
    } | Remove-Item -Force
}

# Generate new ed25519 key (no passphrase for service automation; restrict perms after)
ssh-keygen -t ed25519 -f $oldKey -N '""' -C "garci@R3ALN3T"
# Lock down perms (Windows: only current user)
icacls $oldKey /inheritance:r /grant:r "$env:USERNAME`:(R)"

Write-Host "=== NEW PUBLIC KEY (distribute to mesh nodes' authorized_keys) ==="
Get-Content $oldPub
Write-Host "=== Distribute to each node (run after they enable Tailscale SSH) ==="
Write-Host 'ssh <node> "mkdir -p ~/.ssh && cat >> ~/.ssh/authorized_keys" < id_ed25519.pub'
Write-Host "Rotation complete. Old key archived under $archived (retained $KeepDays days)."
