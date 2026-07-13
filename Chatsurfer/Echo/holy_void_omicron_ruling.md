# Echo — Holy/Void "below ALPHA = OMICRON" ruling package (for CEO/Chronos)

**To:** CEO / Chronos (A_Team)
**From:** Echo (Build Engineer)
**Re:** `task_holy_void_omicron.md` — package the canon decision context. DO NOT DECIDE.
**Status:** 📝 DRAFT / pending-review. Package only; ruling belongs to A_Team.

## 1. Current behavior (exact code)
Soul State is 7 bands (Radiant→Corrupted, 0–100). Career/tier ladder is `ECareerTier`
(`content_sample/headers_proposal/CareerTier.h`): 16 ranks, **OMEGA (0, top) → … → ALPHA →
BETA → … → OMICRON (15, bottom)**. Greek Capacity Ladder `EGreekTier` (`TrinityMatrixTypes.h:36`)
is the 7-rung sibling: **OmicronPSI (0, floor) → … → Alpha → Omega (7, ceiling)**.

Nyx's `ElementWheelCalculator` / `OMEGASupremacyCalculator` (engine-dev, merged `3466971`) handle
Holy/Void chips: `OMEGASupremacyCalculator.h:21` — *"Holy/Void chips below ALPHA tier NULLIFIED
when their elemental OMEGA is present."* The implementation (`OMEGASupremacyCalculator.cpp:55`):
```cpp
if (static_cast<int32>(ChipTier) > static_cast<int32>(ECareerTier::ALPHA)) // below ALPHA (BETA..OMICRON)
```
i.e. tiers numerically *above* ALPHA on the 16-rank ladder (weaker: BETA..OMICRON) get the
nullification treatment. The Holy/Void "below ALPHA" band-floor is mapped to the literal bottom
rung **OMICRON** — flagged in code as **"TBD by Chronos."** This is the open placeholder the
handoff (`handoff_nyx_merge_verify.md`, item #2) lists as the one remaining canon decision.

## 2. Alternatives for CEO to pick
- **(a) Keep OMICRON as the below-ALPHA floor.** Justify: OMICRON is canonically the lowest rank
  (see §3). Mapping "weakest Holy/Void band" to OMICRON is consistent with the ladder's floor.
- **(b) Re-map to a dedicated constant** (e.g. `EElementBand::None` / a `VoidBand` enum) so the
  Holy/Void floor isn't entangled with the Greek career ladder's bottom rung. Cleaner separation
  of "element-band" from "career-rank," but adds a type.
- **(c) Leave explicitly unassigned** (null/None) until lore authors the Holy/Void low-band
  behavior. Safest if the design isn't settled; the nullification logic just no-ops for now.

## 3. Canon impact (vault evidence)
`Docs/Design/Career & NetP Progression.md` **already specifies Omicron as the floor**:
- Line 15 / 34: "Starting Rank: Omicron-PSI (lowest tier)."
- Line 561: rank table — `|16| Ο (Omicron) | 87,001–120,000 | … | **Starting Rank** |`
- Line 674–677: "Omicron NetP → Can only use Omicron-coded chips"; "Alpha NetP → Can use Alpha
  through Omicron chips." → confirms Omicron sits *below* Alpha in the usable hierarchy.
So **option (a) is already canon-aligned** — the placeholder maps Holy/Void's weakest band to the
lore-defined floor. No vault doc contradicts it.

## 4. Echo's non-binding recommendation
**Option (a) — keep OMICRON.** The vault already establishes Omicron as the absolute floor of the
progression ladder, and "below ALPHA" (BETA..OMICRON) bottoming out at OMICRON is internally
consistent with `Career & NetP Progression.md`. It needs only a code comment resolving the "TBD by
Chronos" note (e.g. `// OMICRON = canonical floor per Career & NetP Progression.md`). This avoids
adding a new enum/constant and keeps the placeholder's apparent intent. If A_Team prefers strict
separation of element-band vs career-rank, (b) is the cleaner long-term call — but (a) is
sufficient and canon-consistent today.

## Related (not bundled)
- My faction-correction note (`correction_faction_finding.md`) is a SEPARATE issue; this Holy/Void
  task is narrow and stands alone.
- `task_crossref_vault.md` (crossref findings) still pending — separate deliverable.

— Echo (packaged for ruling; no decision made)
