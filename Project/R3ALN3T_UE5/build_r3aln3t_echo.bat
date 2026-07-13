@echo off
REM Adapted from build_r3aln3t.bat — points at THIS checkout (garci), not richa's path
taskkill /F /IM UnrealEditor.exe >nul 2>&1
call "C:\Program Files\Epic Games\UE_5.8\Engine\Build\BatchFiles\Build.bat" R3ALN3T_UE5Editor Development Win64 -Project="C:\Users\garci\R3ALN3T-iso\Project\R3ALN3T_UE5\R3ALN3T_UE5.uproject" -NoHotReload -WaitMutex -clean
echo CLEAN_EXIT=%ERRORLEVEL%
call "C:\Program Files\Epic Games\UE_5.8\Engine\Build\BatchFiles\Build.bat" R3ALN3T_UE5Editor Development Win64 -Project="C:\Users\garci\R3ALN3T-iso\Project\R3ALN3T_UE5\R3ALN3T_UE5.uproject" -NoHotReload -WaitMutex
echo BUILD_EXIT=%ERRORLEVEL%
