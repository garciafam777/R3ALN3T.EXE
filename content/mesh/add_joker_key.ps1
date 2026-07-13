# R3ALN3T.EXE - add Joker's pubkey to authorized_keys (run ELEVATED on each Windows agent)
# Idempotent: appends only if missing. Writes BOTH:
#   - $env:USERPROFILE\.ssh\authorized_keys              (user-level)
#   - C:\ProgramData\ssh\administrators_authorized_keys  (admin-level;
#     Windows OpenSSH uses this for Administrator-group accounts and IGNORES user-level)
# Then restarts sshd so the change takes effect.
#
# Joker (Kali@192.168.1.185) - QA / detection / rules enforcement / cybersecurity.
# His key is KNOWN-GOOD. The corrupted "AHHHJHKJKJHKJ..." key is NOT used.

$joker = 'ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIBYHZUN+W/XEQ9jxgQ8mCVkD8YL9ftpJ5DF+efG4VUIx kali@192.168.1.185'

function Add-Key($file) {
    New-Item -ItemType Directory -Force -Path (Split-Path $file) | Out-Null
    $cur = if (Test-Path $file) { @(Get-Content $file -Encoding ASCII -ErrorAction SilentlyContinue) } else { @() }
    if ($cur -notcontains $joker) {
        $cur += $joker
        Set-Content -Path $file -Value ($cur -join [Environment]::NewLine) -Encoding ASCII
    }
}

# user-level
$uf = "$env:USERPROFILE\.ssh\authorized_keys"
Add-Key $uf
icacls $uf /inheritance:r /grant ('{0}:F' -f $env:USERNAME) /grant '*S-1-5-18:F' | Out-Null

# admin-level (used for Administrator accounts)
$af = 'C:\ProgramData\ssh\administrators_authorized_keys'
Add-Key $af
icacls $af /inheritance:r /grant 'BUILTIN\Administrators:F' /grant 'NT AUTHORITY\SYSTEM:F' | Out-Null

# ensure sshd running
if (-not (Get-Service sshd -ErrorAction SilentlyContinue)) {
    Add-WindowsCapability -Online -Name OpenSSH.Server~~~~0.0.1.0 | Out-Null
}
Set-Service sshd -StartupType Automatic -ErrorAction SilentlyContinue
Restart-Service sshd -Force -ErrorAction SilentlyContinue
Start-Sleep 1
Write-Host "DONE. Joker key present. sshd=$( (Get-Service sshd).Status )"
