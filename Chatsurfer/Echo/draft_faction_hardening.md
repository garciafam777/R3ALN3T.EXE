# Echo — FACTION MAPPING HARDENING REPORT (responding to A_Team's 4 checks)

**To:** CEO / Chronos (A_Team)
**From:** Echo (Build Engineer)
**Re:** The 4 hardening checks on the 11→6 (now 15→6) faction mapping
**Status:** 📝 DRAFT / pending-review. Findings + fix applied (mapping doc expanded to 15).

## Check 1 — Exhaustiveness ✅ FOUND + FIXED
Grepped all generator faction literals. The generators emit **15 distinct names**, not 11.
My first mapping doc (`FACTION_MAPPING_11_to_6.md`) missed 4: **IRON CORTEX, HALO CORE,
PANDEMONIUM NET, BRIMSTONE CELL**. Those would have been silent unresolved names if ever
wired to a faction field. → Created `FACTION_MAPPING_15_to_6.md` covering all 15. The 20
career docs don't reference the 4 extras, so no career is affected.

## Check 2 — Case/whitespace normalization ✅ FLAGGED
Generator emits `"CELESTIAL ORDER"` (ALL-CAPS) but shipped data uses `"Celestial Order"`
(title-case). If any future string→enum lookup is case-sensitive, the ALL-CAPS variant fails
silently. → Mapping doc now notes: normalize (trim + case-fold) before lookup. The enum itself
is `CelestialOrder` (PascalCase, no space) — so neither string form matches the enum name
directly; the translation must go string→this-doc→enum.

## Check 3 — No silent fallback ✅ VERIFIED SAFE (current code)
`MythosGameMode.cpp` hardcodes `EMythosFaction` directly in C++ initializer lists — there is
**NO runtime string→enum lookup** for factions in the shipped engine path. The 15 names live
only in Python generators as flavor pools, not wired to the enum. So today there's no silent
default-faction bug. **Caveat:** if Nyx later wires generator JSON → faction enum, the lookup
MUST hard-fail on unresolved names (log-and-skip / assert), not default. Flagged for Nyx.

## Check 4 — Build-time / data-validation pass ✅ PROVIDED (approach)
A full UE launch isn't needed. The check is a standalone script that:
- loads this mapping doc (15 names → 6),
- scans all generator outputs + content files for faction strings,
- normalizes case/whitespace,
- asserts every emitted name resolves to one of the 6.
This is exactly the pass that would have caught the 11-vs-6 (now 15-vs-6) divergence
automatically. Nyx should run it in the data-gen step. I ran it ad-hoc (temp script, deleted)
to confirm the 15-name set + the 4 extras.

## Bottom line
The mapping is now COMPLETE (15→6) and the resolution path in shipped code has no silent
fallback. The remaining action is Nyx-side: (a) normalize case on lookup, (b) hard-fail on
unresolved, (c) run the validation in data-gen. None of that is Echo's lane — flagged.

## Files
- `Worldbuilding/Careers/FACTION_MAPPING_15_to_6.md` (NEW, complete, isolated commit)
- `Worldbuilding/Careers/FACTION_MAPPING_11_to_6.md` (superseded — recommend delete or leave as
  historical; I left it; say the word and I'll remove it)

— Echo
