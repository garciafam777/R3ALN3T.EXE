$battlePath = "C:\Users\garci\Desktop\CY Software\R3ALN3T.EXE\R3ALN3T_EXE\Source\R3ALN3T_EXE\Battle"

Write-Host "=== Full listing of Battle folder ===" -ForegroundColor Cyan
Get-ChildItem $battlePath -Force | Select-Object Name, Length, LastWriteTime | Format-Table -AutoSize

Write-Host ""
Write-Host "=== Searching for any duplicate-style filenames (e.g. with (1), copy, etc.) ===" -ForegroundColor Cyan
Get-ChildItem $battlePath -Recurse | Where-Object { $_.Name -match '\(\d+\)|copy|Copy' }

Write-Host ""
Write-Host "=== Searching entire R3ALN3T_EXE Source tree for ANY file named BattleGridTypes.h ===" -ForegroundColor Cyan
Get-ChildItem "C:\Users\garci\Desktop\CY Software\R3ALN3T.EXE\R3ALN3T_EXE\Source" -Recurse -Filter "BattleGridTypes*" | Select-Object FullName

Write-Host ""
Write-Host "=== Searching entire Source tree for ANY file containing 'enum class EElementType' ===" -ForegroundColor Cyan
Get-ChildItem "C:\Users\garci\Desktop\CY Software\R3ALN3T.EXE\R3ALN3T_EXE\Source" -Recurse -Include *.h,*.cpp | Select-String -Pattern "enum class EElementType" | Select-Object Path, LineNumber