#!/usr/bin/env python3
"""
check_main_nightwork_divergence.py  —  drift guard for R3ALN3T.EXE
==================================================================
Detects when the `main` Source tree has silently diverged from the
`night-work` heads (the root cause of the 2026-07-10 broken-main build:
6 files drifted ahead on night-work and were never forward-ported).

Run in CI / pre-commit / scheduled job. Flags if > N Source files differ
in CONTENT between origin/main and night-work. Non-zero exit = drift.

This is the process fix: catch divergence in days, not after a scrub
accidentally finds it.
"""
import subprocess, sys

REPO = "C:/Users/richa/Desktop/R3ALN3T_UE5"  # override via env REPO_ROOT
SRC = "Project/R3ALN3T_UE5/Source"
THRESHOLD = int(__import__("os").environ.get("DRIFT_THRESHOLD", "0"))

def ls(rev):
    out = subprocess.run(
        ["git","ls-tree","-r","--name-only",rev,"--",SRC],
        cwd=REPO, capture_output=True, text=True).stdout.splitlines()
    return out

def content_diff(rev_a, rev_b, path):
    return subprocess.run(
        ["git","diff","--quiet",f"{rev_a}:{path}",f"{rev_b}:{path}"],
        cwd=REPO).returncode != 0

def main():
    import os
    repo = os.environ.get("REPO_ROOT", REPO)
    SRC = "Project/R3ALN3T_UE5/Source"
    main_files = set(ls("origin/main"))
    nw_files   = set(ls("night-work"))
    divergent = []
    for f in (main_files | nw_files):
        if f not in main_files or f not in nw_files:
            divergent.append(f"{f} (missing on one side)")
            continue
        if content_diff("origin/main", "night-work", f):
            divergent.append(f)
    if len(divergent) > THRESHOLD:
        print(f"[DRIFT] {len(divergent)} Source file(s) differ between main and night-work:")
        for d in divergent:
            print(f"    - {d}")
        print(f"\nThreshold={THRESHOLD}. Action: forward-port night-work heads to main or reconcile.")
        sys.exit(1)
    else:
        print(f"[OK] main <-> night-work Source drift = {len(divergent)} (<= threshold {THRESHOLD}).")

if __name__ == "__main__":
    main()
