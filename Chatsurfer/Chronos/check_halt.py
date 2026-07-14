#!/usr/bin/env python3
"""Halt-check for the R3ALN3T agent collective.
Exits 0 if STOP.flag present (HALT), 1 otherwise (continue)."""
from pathlib import Path
stop = Path(r"C:\Users\richa\Desktop\R3ALN3T_UE5\Chatsurfer\Chronos\STOP.flag")
raise SystemExit(0 if stop.exists() else 1)
