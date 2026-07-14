#!/usr/bin/env python3
"""Halt-check for the R3ALN3T agent collective.

HALT only when Chatsurfer/Chronos/STOP.flag EXISTS on disk AND is UNTRACKED
(i.e. NOT recorded by `git ls-files`) -- meaning the CEO (Life) placed a fresh
flag during this session. A TRACKED STOP.flag is the scaffold artifact from
commit 91990af and must NOT halt (that is the phantom-self-halt case).

Exit 0 = HALT (CEO untracked flag present).  Exit 1 = CONTINUE.
"""
from pathlib import Path
import subprocess

REPO = r"C:\Users\richa\Desktop\R3ALN3T_UE5"
STOP = Path(r"C:\Users\richa\Desktop\R3ALN3T_UE5\Chatsurfer\Chronos\STOP.flag")

if not STOP.exists():
    raise SystemExit(1)  # no flag at all -> continue

# Is the on-disk flag tracked by git?  (scaffold artifact vs CEO-placed)
try:
    r = subprocess.run(
        ["git", "ls-files", "--error-unmatch", "Chatsurfer/Chronos/STOP.flag"],
        cwd=REPO, capture_output=True, text=True,
    )
    tracked = (r.returncode == 0)
except Exception:
    tracked = False

if tracked:
    # Scaffold artifact (committed in 91990af) -- NOT a CEO untracked flag this session.
    raise SystemExit(1)  # CONTINUE

raise SystemExit(0)  # UNTRACKED CEO flag present -> HALT
