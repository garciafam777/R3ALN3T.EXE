#!/usr/bin/env python3
"""Halt-check for the R3ALN3T agent collective.
Exit 0 if an UNTRACKED STOP.flag is present (HALT), exit 1 otherwise (CONTINUE).

A halt flag must be absent by default and only created by the CEO at runtime.
If STOP.flag is TRACKED in git, ignore it -- that is the phantom-self-halt bug
(committing the flag made it always-present after git reset --hard).
"""
import subprocess
from pathlib import Path

# Resolve the flag location relative to this script (no hard-coded drive path).
stop = Path(__file__).resolve().parent / "STOP.flag"

if stop.exists():
    try:
        tracked = subprocess.run(
            ["git", "ls-files", "--error-unmatch", str(stop)],
            capture_output=True, text=True,
        ).returncode == 0
    except Exception:
        tracked = False
    if not tracked:
        raise SystemExit(0)  # real, untracked halt -> halt
    # else: tracked (stale) flag -> fall through to continue

raise SystemExit(1)
