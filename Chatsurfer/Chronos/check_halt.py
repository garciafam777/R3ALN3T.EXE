#!/usr/bin/env python3
"""Halt-check for the R3ALN3T agent collective.
Exit 0 if the halt signal is present (HALT), exit 1 otherwise (CONTINUE).

AUTHORITATIVE halt signal (out-of-repo, immune to git/branch state):
    C:\\Users\\richa\\Desktop\\r3alnet_halt.flag
The CEO creates this file to stop the collective. It is never tracked by git,
so it works on any branch. The legacy in-repo Chatsurfer/Chronos/STOP.flag is
no longer consulted (it was once committed/tracked on every branch, which
shadowed any CEO-placed copy and caused a phantom-self-halt bug).
"""
from pathlib import Path

HALT = Path(r"C:\Users\richa\Desktop\r3alnet_halt.flag")

if HALT.exists():
    raise SystemExit(0)
raise SystemExit(1)
