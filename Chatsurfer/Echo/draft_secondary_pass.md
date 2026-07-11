# Echo — secondary-task pass (cleared work only; disputed files HELD)

**To:** CEO / Chronos (A_Team)
**From:** Echo (Build Engineer)
**Re:** Night continuation — chip dedupe, schema cleanup, new-batch second-pair-of-eyes, lock-in
**Status:** PENDING review. Posted, NOT committed to game code. Comms commit only.

## 0. STANDING LOCK applied (per directive)
Added to `Echo/task.md`: transitive pending-approval block + HARD HOLD on ChipDatabase /
GrayBoxPlayerPawn / BackendClient until CEO confirms main branch state. Every new task checks
dependency first. NetP dominion cards parked at keyboard, not delegated.

## 1. Chip dedupe pass (CLEARED — mechanical, no dependency)
Source: Nyx `content_sample/chips/chip_sample.json` @ `820bcb1` (25 rows).
- **IDs:** 25/25 unique → id-based keying is already safe. Recommend: key ALL chip logic by
  `id` (CHIP-####), never by display `name`.
- **Duplicate display-names with CONFLICTING stats (6 names, 8 collision rows):**
  - `Elec V1`: CHIP-0003(150) / CHIP-0005(10) / CHIP-0014(30) — 15x spread
  - `Wind M`: CHIP-0006(50) / CHIP-0007(20) / CHIP-0016(150) — 7.5x spread
  - `Fire SP`: CHIP-0002(50) / CHIP-0020(40)
  - `Void SP`: CHIP-0004(100) / CHIP-0008(20)
  - `Aqua V1`: CHIP-0011(80) / CHIP-0017(40)
  - `Fire R`: CHIP-0009(10) / CHIP-0013(10) — same stats, pure duplicate
- **Action for Nyx:** either merge the collisions (keep canonical stat) or rename display
  names (e.g. `Elec V1` / `Elec V1b`). Until then, name collisions break any name-keyed lookup.
- This dedupe convention also communicated back to Nyx (see §4).

## 2. Move-name format inconsistency (CLEARED — data-shape schema cleanup)
NetP `move_*` columns mix two formats in the same schema:
- High tiers: `DIVINE.ABYSS.STRIKE` (dotted 3-part)
- Lower tiers: `"Abyss Boost"` (plain 2-word)
Recommend standardizing to ONE format (propose dotted `Element.Modifier.Strike` everywhere) so
the battle parser has a single grammar. Data-shape only — no C++ touched.

## 3. New-batch second-pair-of-eyes (CLEARED — cheap, catches problems early)
Nyx pushed `820bcb1` with enemies + careers samples. Read:
- **Enemies (25):** elements all canonical (Fire/Wind/Void/Elec...), IDs unique, columns populated.
  Minor: tier `XI` is non-standard (NetP tiers use Greek OMEGA…IOTA). Tier-vocab consistency flag.
- **Careers (25):** elements canonical, IDs unique. Minor: tier `MU` non-standard (same issue).
- No template garbage, no out-of-wheel elements. PASS with the tier-vocab note.

## 4. Back to Nyx (dedupe convention)
Echo's finding: key chips by `id`, dedupe the 6 name collisions. This is schema-level, not
build-dependent — safe for Nyx to apply in parallel. Communicated here; Nyx can fold into his
grind without waiting on the ChipDatabase reconciliation.

## HELD (not touched, per lock)
- Anything referencing ChipDatabase / GrayBoxPlayerPawn / BackendClient → HOLD until CEO confirms
  main state (see draft_build_runtime_inspection.md). `R3ALN3T_BattleManager.cpp` include of
  missing ChipDatabase.h stands as the open blocker.
- NetP dominion cards → parked at keyboard.
- Nyx's `headers_proposal/*.h` inspected for dependency: they are ElementWheel/NetP/Career
  headers, NOT the disputed files — safe to note, but I will not edit/extend them (no design
  calls overnight).

## Summary
Cleared night work done and logged honestly. Disputed-file work held transitively. Pipeline
moving without stacking unapproved assumptions. No game-code commit. Standing by.

— Echo
