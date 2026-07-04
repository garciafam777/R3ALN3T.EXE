# ================================================
# Generate Unreal Visual Studio Project Files
# ================================================

$ProjectPath = "C:\Users\garci\Desktop\CY Software\R3ALN3T.EXE\R3ALN3T_EXE\R3ALN3T_EXE.uproject"

# Common location for UnrealVersionSelector
$UVS = "C:\Program Files (x86)\Epic Games\Launcher\Engine\Binaries\Win64\UnrealVersionSelector.exe"

# ================================================

Write-Host "Unreal Engine Project File Generator" -ForegroundColor Cyan
Write-Host "=====================================" -ForegroundColor Cyan

if (-not (Test-Path $ProjectPath)) {
    Write-Host "❌ Project file not found:" -ForegroundColor Red
    Write-Host $ProjectPath
    exit 1
}

if (-not (Test-Path $UVS)) {
    Write-Host "❌ UnrealVersionSelector.exe not found at:" -ForegroundColor Red
    Write-Host $UVS
    Write-Host "`nPlease update the `$UVS variable in the script with the correct path." -ForegroundColor Yellow
    exit 1
}

Write-Host "Project: " -NoNewline
Write-Host $ProjectPath -ForegroundColor White

Write-Host "`nGenerating Visual Studio project files..." -ForegroundColor Yellow

try {
    $process = Start-Process -FilePath $UVS -ArgumentList "/projectfiles", "`"$ProjectPath`"" -Wait -NoNewWindow -PassThru
    
    if ($process.ExitCode -eq 0) {
        Write-Host "`n✅ Successfully generated Visual Studio project files!" -ForegroundColor Green
    } else {
        Write-Host "`n⚠️ Process completed with exit code: $($process.ExitCode)" -ForegroundColor Yellow
    }
}
catch {
    Write-Host "`n❌ Error occurred:" -ForegroundColor Red
    Write-Host $_.Exception.Message
}

Write-Host "`nPress any key to exit..." -ForegroundColor Gray
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")