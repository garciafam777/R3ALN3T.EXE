#!/usr/bin/env bash
# setup-profiles.sh — create all R3ALN3T.EXE Hermes agent profiles (8 roles + orchestrator).
# Portable: Hermes stores profiles at ~/.hermes/profiles on Windows (git-bash/MSYS) and
# ~/.config/hermes/profiles on Linux. This script detects and uses the right one.
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROFILES_SRC="$SCRIPT_DIR"

ROLES="researcher writer architect modeler level-designer programmer qa-tester build-engineer orchestrator"

# --- resolve Hermes profile root (portable) ---
if [ -n "${HOME:-}" ] && [ -d "$HOME/.hermes" ]; then
  HERMES_ROOT="$HOME/.hermes/profiles"
elif [ -n "${XDG_CONFIG_HOME:-}" ] && [ -d "$XDG_CONFIG_HOME/hermes" ]; then
  HERMES_ROOT="$XDG_CONFIG_HOME/hermes/profiles"
elif [ -n "${HOME:-}" ] && [ -d "$HOME/.config/hermes" ]; then
  HERMES_ROOT="$HOME/.config/hermes/profiles"
else
  HERMES_ROOT="$HOME/.hermes/profiles"
fi

echo "Hermes profile root: $HERMES_ROOT"
mkdir -p "$HERMES_ROOT"

for p in $ROLES; do
  SRC="$PROFILES_SRC/$p/SOUL.md"
  if [ ! -f "$SRC" ]; then
    echo "SKIP $p (no $SRC)"
    continue
  fi
  DST="$HERMES_ROOT/$p"
  mkdir -p "$DST"
  cp "$SRC" "$DST/SOUL.md"
  echo "INSTALLED $p -> $DST/SOUL.md"
done

echo ""
echo "Done. Profiles installed. Next:"
echo "  cp -r '$PROFILES_SRC/project-workspace-template' '<your-game-project>/'"
echo "  # then delegate from the orchestrator role, passing the SOUL contract as context."
