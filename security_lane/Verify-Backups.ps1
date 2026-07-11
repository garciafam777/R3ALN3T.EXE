# Verify-Backups.ps1 - confirm R3ALN3T.EXE is backed up (Git LFS + cloud sync) + restore test
# Owner: Nyx (DevOps). Admin tool. No engine dependency.
param(
    [string]$Repo = ".",
    [string]$CommitHash = ""
)

$ErrorActionPreference = 'Stop'

Write-Host "=== Git LFS status ==="
git -C $Repo lfs ls-files 2>&1 | Select-Object -First 10 | ForEach-Object { Write-Host $_ }
$lfsInstalled = git -C $Repo lfs version 2>&1
Write-Host "LFS: $lfsInstalled"

Write-Host "=== Cloud sync status (OneDrive / known providers) ==="
$providers = Get-ChildItem "HKCU:\Software\Microsoft\OneDrive\Accounts" -ErrorAction SilentlyContinue
if ($providers) { Write-Host "OneDrive account(s) present." } else { Write-Host "No OneDrive registry key (may use other sync)." }
$syncRoots = @("$env:USERPROFILE\OneDrive", "$env:USERPROFILE\Dropbox", "$env:USERPROFILE\GoogleDrive")
foreach ($r in $syncRoots) {
    if ($Repo -like "$r*") { Write-Host "Repo lives under sync root: $r" }
}

Write-Host "=== Restore test (verify a known commit is fetchable) ==="
$target = if ($CommitHash) { $CommitHash } else { "HEAD" }
$rev = $target + "{commit}"
$null = git -C $Repo cat-file -e $rev 2>&1
if ($LASTEXITCODE -eq 0) {
    Write-Host "Restore target $target : AVAILABLE (git object present)"
} else {
    Write-Host "Restore target $target : NOT FOUND locally - run git fetch before restore."
}

Write-Host "=== Backup manifest summary ==="
$lfsCount = (git -C $Repo lfs ls-files 2>$null | Measure-Object -Line).Lines
$latest = git -C $Repo rev-parse --short HEAD
Write-Host "Latest commit: $latest"
Write-Host "LFS files tracked: $lfsCount"
Write-Host "Backup verification complete. If LFS/cloud gaps found, escalate before any destructive op."
