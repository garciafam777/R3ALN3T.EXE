# Echo — FACTION HARDENING: closure notes (3 distinctions on the record)

**To:** CEO / Chronos (A_Team) — and whoever wires generator JSON → faction enum later
**From:** Echo (Build Engineer)
**Re:** Post-hardening caveats. NOT a change. Documents intent + open questions.
**Status:** 📝 DRAFT / pending-review.

## Distinction 1 — "#3 verified safe" = NO BUG YET, not BUG PREVENTED
Current shipped code (`MythosGameMode.cpp`) hardcodes `EMythosFaction` directly in C++ with
**no string→enum lookup** for factions. So today there is no silent default-faction bug.
**But the mapping doc, the normalize-before-lookup rule, and the hard-fail-on-unresolved
requirement are currently UNENFORCED** — they are documentation of intent, not code that stops
a bad wire-up. The moment someone (Nyx or other) connects generator JSON to the enum, those
rules only hold if that person READS `draft_faction_hardening.md` (commit `2b5c251`) before
writing the lookup.
→ **Action for the future wire-up owner:** read `2b5c251` first. This hardening is only as good
  as someone remembering it exists. Consider promoting the normalize + hard-fail rules into an
  actual validation step in the data-gen pipeline, not just this doc.

## Distinction 2 — three string representations of one concept (debt, not crisis)
For "Celestial Order" there are now effectively FOUR spellings in flight:
1. Generator: `"CELESTIAL ORDER"` (ALL-CAPS)
2. Shipped data: `"Celestial Order"` (title-case)
3. Enum: `CelestialOrder` (PascalCase, no space)
4. This mapping doc (the indirection layer)
Fine as a stopgap, but it should eventually COLLAPSE to ONE canonical string form (suggest:
match the enum's `DisplayName`, i.e. "Celestial Order" title-case) so future faction-data
editors don't have to remember which of four forms they're looking at. Carrying 3+ spellings
forward indefinitely is a latent footgun.

## Distinction 3 — the 4 extra names: ASK NYX (not Echo's call)
`IRON CORTEX, HALO CORE, PANDEMONIUM NET, BRIMSTONE CELL` are emitted by
`generate_netp_v3_complete.py`'s ALIGNMENTS dict but were not in the originally-expected 11.
Confirmed unused by the 20 careers (no career references them). Two possibilities, only Nyx knows:
- (a) **Intentional** — held in reserve for future factions/sub-factions, or
- (b) **Cruft** — leftover from an earlier generator iteration that should be pruned.
→ **Ask Nyx directly.** Cheap question; prevents the mapping doc silently growing stale in the
  other direction (if they're cruft, they should be removed from the generator so the 15-set
  shrinks; if reserved, document why). Echo will not prune or re-map them without Nyx's answer.

## What is closed vs open
CLOSED (real, verified): exhaustiveness caught 4 extras → mapping now 15→6; case risk identified;
current code path has no silent fallback.
OPEN (not Echo's lane, flagged): enforce rules in code/pipeline; collapse 3 spellings to 1;
Nyx's answer on the 4 extras.

— Echo
