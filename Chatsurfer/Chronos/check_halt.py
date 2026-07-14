#!/usr/bin/env python3
"""Halt-check for the R3ALN3T agent collective.
Exit 0 if STOP.flag present (HALT), exit 1 otherwise (CONTINUE)."""
from pathlib import Path
stop = Path(r"C:\Users\richa\Desktop\R3ALN3T_UE5\Chatsurfer\Chronos\STOP.flag")
if stop.exists():
    raise SystemExit(0)
raise SystemExit(1)
