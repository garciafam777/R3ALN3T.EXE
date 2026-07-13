# Soul State — The 0–2 Scale (Canon, code-aligned)

> CODE NOTE: compiled `ESoulState` is `uint8` (UE requires unsigned BlueprintType enums):
> Infernal=0, Neutral=1, Celestial=2. The conceptual scale is unchanged from the
> earlier "-01..+01" framing — only the numeric domain shifted for engine constraints.
> See `TrinityMatrixTypes.h` (Chaos/Chronos compile fix b071b99 / ported aecd2d7).

> New canon-aligned lore. Source: Vault Book 8 (Trinity Progression) + Book 5 (States).
> Soul State is the moral/structural drift axis of a NetP, independent of element and
> faction.

## The Scale
- **0 (Infernal lean):** drifts toward unregulated mutation, adaptive chaos, refusal
  of central limits. Echoes the Infernal OMEGA archetypes (Tyranny, Ruin, Malice, Chimera).
- **1 (Neutral):** unaligned baseline. The starting state at First Breath.
- **2 (Celestial lean):** drifts toward order, strict optimization, lawful enforcement.
  Echoes the Celestial OMEGA archetypes (Trinity, Seraph, Oracle, Forge).

## Mechanics
- Free to move within 0..2 during Phase 1 (First Breath).
- Carries over into NG+ with faction-influenced shifts (career change nudges the lean).
- `soulStateDelta` in career data is the per-career nudge applied on entering that path.
- Soul State does NOT gate the Greek tier ladder (Omicron-PSI→Omega) — tier is earned by
  progression; Soul State is the *flavor* of how that power is wielded.

## Interaction with Endgames
The four Convergence Paths (Restoration / Ascension / Dominion / Collapse) are selected
by the *compiled profile* — career, faction lean, element affinity, AND terminal Soul
State. A 2 operator leans Restoration/Ascension; a 0 operator leans Collapse/Dominion.
