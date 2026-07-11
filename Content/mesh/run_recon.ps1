$ErrorActionPreference = 'SilentlyContinue'
$log = "content/mesh/nmap_recon_2026-07-11.log"
"R3ALN3T mesh recon - 2026-07-11 (PowerShell sweep; nmap unavailable)" | Out-File $log -Encoding utf8
"=== local IP config ===" | Out-File $log -Append
(ipconfig | Select-String 'IPv4') | Out-File $log -Append
"=== ARP table (seen devices) ===" | Out-File $log -Append
(arp -a) | Out-File $log -Append
"=== ping sweep 192.168.1.1-30 ===" | Out-File $log -Append
1..30 | ForEach-Object {
    $ip = "192.168.1.$_"
    if (Test-Connection $ip -Count 1 -Quiet) { "UP: $ip" | Out-File $log -Append }
}
"=== known mesh nodes (tailnet) ===" | Out-File $log -Append
foreach ($h in @('echo.tailf78f57.ts.net','joker.tailf78f57.ts.net','chronos.tailf78f57.ts.net')) {
    try {
        $r = Test-Connection $h -Count 1 -Quiet
        if ($r) { "$h : REACHABLE" | Out-File $log -Append } else { "$h : NO" | Out-File $log -Append }
    } catch {
        "$h : ERR" | Out-File $log -Append
    }
}
"=== tailnet status ===" | Out-File $log -Append
(tailscale status 2>&1) | Out-File $log -Append
Write-Host "recon complete"
