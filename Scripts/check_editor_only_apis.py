#!/usr/bin/env python3
"""
check_editor_only_apis.py  -- regression guard for editor-only APIs in shipping UE source.

Some UObject/AActor APIs are compiled ONLY when WITH_EDITOR is defined
(e.g. AActor::SetActorLabel, AActor::GetActorLabel, AActor::SetFolderPath).
Calling them unconditionally in Game/Server/Shipping builds breaks the
game target compile (error C2039: 'X' is not a member of 'Y').

This script scans the project Source tree and flags any editor-only API call
that is NOT wrapped inside a `#if WITH_EDITOR ... #endif` region.

Usage:
    python scripts/check_editor_only_apis.py [--source <path>] [--project-root <path>]

Exit code 0 = clean, 1 = editor-only API found outside guard (CI/review gate fails).

NOTE: heuristic. It tracks #if/#ifdef/#endif nesting for WITH_EDITOR only and
reports calls on lines that are not inside a WITH_EDITOR block. False positives
are possible for macro-generated or templated code; treat a non-zero exit as
"manual review required", not "definitely broken".
"""
import argparse
import os
import re
import sys

# APIs that are editor-only in stock UE5 (extend as needed).
EDITOR_ONLY_APIS = [
    r"SetActorLabel",
    r"GetActorLabel",
    r"SetFolderPath",
    r"GetActorLabelSafe",
    r"SetActorLabelAndUpdateDisplay",
]

# Match the API as a method call:  something->API(  or  something.API(
API_RE = re.compile(r"(?:->|\.)\s*(" + "|".join(EDITOR_ONLY_APIS) + r")\s*\(")
# Preprocessor guard tracking
IF_RE = re.compile(r"^\s*#\s*if(def)?\b")
ENDIF_RE = re.compile(r"^\s*#\s*endif\b")
WITH_EDITOR_RE = re.compile(r"WITH_EDITOR")


def scan_file(path):
    findings = []
    in_with_editor = 0  # depth of nested WITH_EDITOR guards
    with open(path, "r", encoding="utf-8", errors="replace") as f:
        for lineno, line in enumerate(f, 1):
            stripped = line.strip()
            if IF_RE.match(stripped):
                if WITH_EDITOR_RE.search(stripped):
                    in_with_editor += 1
                # other #if blocks don't change WITH_EDITOR depth tracking
                continue
            if ENDIF_RE.match(stripped):
                # we only decrement on endif that closes a WITH_EDITOR we counted;
                # approximate by decrementing only if we are inside one.
                if in_with_editor > 0:
                    in_with_editor -= 1
                continue
            if in_with_editor == 0:
                m = API_RE.search(line)
                if m:
                    findings.append((lineno, m.group(1)))
    return findings


def main():
    ap = argparse.ArgumentParser()
    here = os.path.dirname(os.path.abspath(__file__))
    default_root = os.path.abspath(os.path.join(here, "..", "Project", "R3ALN3T_UE5", "Source"))
    ap.add_argument("--source", default=default_root, help="Source root to scan")
    args = ap.parse_args()

    if not os.path.isdir(args.source):
        print(f"ERROR: source path not found: {args.source}", file=sys.stderr)
        sys.exit(2)

    all_findings = []
    for root, dirs, files in os.walk(args.source):
        # skip Intermediate / generated
        dirs[:] = [d for d in dirs if d not in ("Intermediate", "Binaries", "DerivedDataCache")]
        for fn in files:
            if fn.endswith((".cpp", ".h", ".hpp", ".cc")):
                fp = os.path.join(root, fn)
                for lineno, api in scan_file(fp):
                    all_findings.append((fp, lineno, api))

    if all_findings:
        print("FAIL: editor-only API used outside #if WITH_EDITOR guard:")
        for fp, lineno, api in all_findings:
            rel = os.path.relpath(fp, os.path.abspath(os.path.join(args.source, "..", "..")))
            print(f"  {rel}:{lineno}: {api}")
        print(f"\n{len(all_findings)} occurrence(s). Wrap in #if WITH_EDITOR / #endif "
              f"or move to an editor-only module.")
        sys.exit(1)

    print("PASS: no editor-only API calls found outside WITH_EDITOR guards.")
    sys.exit(0)


if __name__ == "__main__":
    main()
