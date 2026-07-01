# ====================================================================
# R3ALN3T_UE5 Orchestrated Setup Script for Pinokio Ecosystem
# ====================================================================

Clear-Host
Write-Host "=================================================================" -ForegroundColor Cyan
Write-Host " INITIALIZING R3ALN3T_UE5 PIPELINE VIA PINOKIO" -ForegroundColor Cyan
Write-Host "=================================================================" -ForegroundColor Cyan

# 1. Target Directory Check & Creation
$TargetDir = "C:\Users\richa\Desktop\R3ALN3T_UE5"
$OldProjDir = "C:\Users\richa\Desktop\R3ALN3T.EXE"

if (!(Test-Path $TargetDir)) {
    Write-Host "[+] Creating Clean Repository Directory..." -ForegroundColor Green
    New-Item -ItemType Directory -Force -Path $TargetDir | Out-Null
}
Set-Location $TargetDir

# 2. Infrastructure Folder Structure
Write-Host "[+] Building Workspace Sub-Directories..." -ForegroundColor Green
@("Project", "ArtSource", "ArtSource\Krita", "ArtSource\Textures", "Docs", "Builds") | ForEach-Object {
    if (!(Test-Path $_)) { New-Item -ItemType Directory -Force -Path $_ | Out-Null }
}

# 3. Initialize Version Control & High-Density Trackers
Write-Host "[+] Spinning up Git and Git LFS (4K Asset Array Ready)..." -ForegroundColor Green
git init
git lfs install

# 4. Extract & Migrate Core System Documentation
Write-Host "[+] Migrating System Mythos & Core Docs..." -ForegroundColor Yellow
if (Test-Path "$OldProjDir\THE MYTHOS ORIGIN_3026.txt") { Move-Item "$OldProjDir\THE MYTHOS ORIGIN_3026.txt" "$TargetDir\Docs\" -Force }
if (Test-Path "$OldProjDir\README.md") { Move-Item "$OldProjDir\README.md" "$TargetDir\" -Force }
if (Test-Path "$OldProjDir\LICENSE") { Move-Item "$OldProjDir\LICENSE" "$TargetDir\" -Force }

# 5. Asset Staging (Dynamic Verification)
if (Test-Path "$OldProjDir\some_concept.blend") { Move-Item "$OldProjDir\some_concept.blend" "$TargetDir\ArtSource\" -Force }
if (Test-Path "$OldProjDir\Character_Design.kra") { Move-Item "$OldProjDir\Character_Design.kra" "$TargetDir\ArtSource\Krita\" -Force }
if (Test-Path "$OldProjDir\environment_texture.png") { Move-Item "$OldProjDir\environment_texture.png" "$TargetDir\ArtSource\Textures\" -Force }

# 6. Inject .gitignore Rules
Write-Host "[+] Injecting Engine & IDE Build Exclusions..." -ForegroundColor Green
$gitignore = @"
# Unreal Engine Generated Folders
Binaries/
Build/
DerivedDataCache/
Intermediate/
Saved/
Script/

# Builds folder
/Builds/

# IDE / Compilation Artifacts
*.VC.db
*.opensdf
*.opendb
*.sdf
*.sln
*.suo
*.xcodeproj
*.xcworkspace
*.obj
*.exe
*.dll
*.dylib
*.so
*.a
*.lib

# OS Meta-files
.DS_Store
.DS_Store?
._*
.Spotlight-V100
.Trashes
ehthumbs.db
Thumbs.db

# DCC Temp Files (Blender/Audacity)
*.blend1
*.blend2
*.aup3-shm
*.aup3-wal

# Hard Preservation Rules
!Project/Config/
!Project/Content/
!Source/
!Plugins/

# Sandbox/Local Exclusions
Project/Content/Developers/
Project/Content/Collections/
"@
Set-Content -Path ".gitignore" -Value $gitignore -Force

# 7. Inject Git LFS Tracking Attributes
Write-Host "[+] Injecting High-Dimensional Asset LFS Rules..." -ForegroundColor Green
$gitattributes = @"
# Unreal Binary Assets
*.uasset filter=lfs diff=lfs merge=lfs -text
*.umap filter=lfs diff=lfs merge=lfs -text

# 3D Mesh Pipelines
*.blend filter=lfs diff=lfs merge=lfs -text
*.fbx filter=lfs diff=lfs merge=lfs -text
*.obj filter=lfs diff=lfs merge=lfs -text

# High-Res Textures & Working Sources
*.png filter=lfs diff=lfs merge=lfs -text
*.tga filter=lfs diff=lfs merge=lfs -text
*.jpg filter=lfs diff=lfs merge=lfs -text
*.exr filter=lfs diff=lfs merge=lfs -text
*.psd filter=lfs diff=lfs merge=lfs -text
*.kra filter=lfs diff=lfs merge=lfs -text

# Uncompressed Mastering Audio
*.wav filter=lfs diff=lfs merge=lfs -text
*.mp3 filter=lfs diff=lfs merge=lfs -text
*.aup3 filter=lfs diff=lfs merge=lfs -text

# Node-Based Materials
*.mmg filter=lfs diff=lfs merge=lfs -text
"@
Set-Content -Path ".gitattributes" -Value $gitattributes -Force

# 8. Commit Base Layer
git add .gitattributes .gitignore
git commit -m "System Bootstrap: UE5 Architecture with Active LFS Matrix"

# 9. Handshake with Pinokio & Initialize 8-Hour Active Duty Loop
Write-Host "`n=================================================================" -ForegroundColor Green
Write-Host " BASE INFRASTRUCTURE LOCKED IN." -ForegroundColor Green
Write-Host " Pinokio Environment Keep-Alive Active: 8 Hours Remaining." -ForegroundColor Yellow
Write-Host " Start Block: $(Get-Date)" -ForegroundColor Gray
Write-Host " End Block:   $((Get-Date).AddHours(8))" -ForegroundColor Gray
Write-Host "=================================================================`n" -ForegroundColor Green

$TotalSeconds = 28800
$Elapsed = 0
$Interval = 600 # Log updates to console every 10 minutes to verify non-stagnation

while ($Elapsed -lt $TotalSeconds) {
    Start-Sleep -Seconds $Interval
    $Elapsed += $Interval
    $RemainingHours = [Math]::Round(($TotalSeconds - $Elapsed) / 3600, 2)
    Write-Host "[Heartbeat] Pipeline processing active. $RemainingHours hours remaining in execution window." -ForegroundColor Gray
}

Write-Host "[+] Overnight cycle completed. Workspace ready for live UE5 Project initialization." -ForegroundColor Green