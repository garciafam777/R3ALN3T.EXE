# Scope-FirewallRules.ps1 — replace broad Allow_Outbound_SSH with Hermes-exe-specific scoping
# Owner: Nyx (DevOps). Admin tool. No engine dependency.
# Audits existing outbound-SSH firewall rules and replaces the broad allow with
# path-scoped rules limited to the R3ALN3T mesh tooling.

$ErrorActionPreference = 'Stop'

Write-Host "=== Current outbound SSH / port-22 rules ==="
Get-NetFirewallRule -Direction Outbound | Where-Object {
    $_.DisplayName -match 'SSH' -or $_.LocalPort -eq 22 -or $_.RemotePort -eq 22
} | Select-Object Name, DisplayName, Enabled, Action, Profile |
    Format-Table -AutoSize | Out-String | Write-Host

# Remove the broad allow rule if present
$broad = Get-NetFirewallRule -Direction Outbound -ErrorAction SilentlyContinue |
    Where-Object { $_.DisplayName -eq 'Allow_Outbound_SSH' }
if ($broad) {
    Write-Host "Removing broad Allow_Outbound_SSH (replaced by scoped rules)..."
    Remove-NetFirewallRule -Name $broad.Name
} else {
    Write-Host "No broad Allow_Outbound_SSH found."
}

# Add scoped outbound-22 rule limited to the R3ALN3T mesh tooling path + tailnet
$toolPath = Join-Path $env:USERPROFILE "AppData\Local\Hermes"
New-NetFirewallRule -Direction Outbound -DisplayName "R3ALN3T-Mesh-SSH-Scoped" `
    -Program "$toolPath\hermes.exe" -Protocol TCP -RemotePort 22 `
    -Action Allow -Profile Any -Enabled True
Write-Host "Added scoped rule: R3ALN3T-Mesh-SSH-Scoped (only Hermes exe, port 22)."

Write-Host "=== Post-change audit ==="
Get-NetFirewallRule -Direction Outbound | Where-Object { $_.DisplayName -match 'R3ALN3T|SSH' } |
    Select-Object Name, DisplayName, Action, Enabled | Format-Table -AutoSize | Out-String | Write-Host
Write-Host "Firewall scoped. Review output above before committing policy."
