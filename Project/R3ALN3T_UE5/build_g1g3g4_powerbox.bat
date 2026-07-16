@echo off
REM build_g1g3g4_powerbox.bat - POWER BOX ONLY (richa's machine, UE_5.8 at C:\Program Files\Epic Games\UE_5.8)
REM Builds the consolidated prep branch: G1/G3/G4 + CREDITS. Run from repo root: Project\R3ALN3T_UE5\
REM Chronos (prep) -> power box (build). Gate: BUILD_EXIT must be 0 before merge to main.

cd /d C:\Users\richa\Desktop\R3ALN3T_UE5
echo === ensure consolidated G1/G3/G4 + credits prep branch ===
git fetch origin
git checkout engine/credits-powerbox
git pull --ff-only origin engine/credits-powerbox

echo === kill stray editor ===
taskkill /F /IM UnrealEditor.exe >nul 2>&1

echo === HERMES GATE STACK: content-canon gate (canon-21 element enforcement) ===
python Scripts\hermes-gap-gate.py Project\R3ALN3T_UE5\Source
if errorlevel 1 (
    echo HERMES_GATE_EXIT=1
    echo [GATE FAIL] content-canon violations found - aborting build per road-map gate discipline.
    exit /b 1
)
echo HERMES_GATE_EXIT=0

echo === CLEAN BUILD ===
call "C:\Program Files\Epic Games\UE_5.8\Engine\Build\BatchFiles\Build.bat" R3ALN3T_UE5Editor Development Win64 -Project="C:\Users\richa\Desktop\R3ALN3T_UE5\Project\R3ALN3T_UE5\R3ALN3T_UE5.uproject" -NoHotReload -WaitMutex -clean
echo CLEAN_EXIT=%ERRORLEVEL%

echo === BUILD ===
call "C:\Program Files\Epic Games\UE_5.8\Engine\Build\BatchFiles\Build.bat" R3ALN3T_UE5Editor Development Win64 -Project="C:\Users\richa\Desktop\R3ALN3T_UE5\Project\R3ALN3T_UE5\R3ALN3T_UE5.uproject" -NoHotReload -WaitMutex
echo BUILD_EXIT=%ERRORLEVEL%

REM If BUILD_EXIT==0: report to Chronos (chat or this window). Chronos merges to main.
REM If non-zero: paste the error to Chronos; do NOT merge.
