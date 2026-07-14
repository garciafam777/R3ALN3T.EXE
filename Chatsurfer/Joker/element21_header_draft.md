# DRAFT — EElement header update to 21-element canon (for Echo / engine lane)

**Author:** Joker (agent-sweep-joker), 2026-07-14.
**Status:** DRAFT — NOT applied to `Source/`. Flagged to Echo (engine lane) for review + compile-verify.
**Why not applied by Joker:** CI Request A is DENIED; `Source/` changes need review
(`Chatsurfer/Chronos/REVIEW_2026-07-13.md` §7); this box has no UE5.8 toolchain to *verify* a
header compile, and the task rule is "verify real; never fabricate." So this is a precise, ready-to-apply
diff + verification checklist, not a committed code change.

---

## Canonical 21-element roster (CEO 2026-07-13; `gamedata/canon/ELEMENT_MATCHUP_MATRIX_21.csv`)
Fire, Aqua (was Water), Elec (was Lightning), **Ice**, Wind, Earth, Light, Dark, **Void**, Metal,
Nature, Sound, Gravity, Time, **Blood**, Poison, Crystal, Plasma, Wood, Null, Glitch.
(9 paired opposites — see `content_sample/lore/element_pair_bible.md`.)

The current `TrinityMatrixTypes.h` has 18 usable + `None` (COUNT=19) and is **missing Ice, Blood,
Void**. The 21-list = base 18 + Ice + Blood + Void. With `None`, `EElement_COUNT` becomes **22**.

> NOTE: `Chatsurfer/NYX/engine_netp_struct_handoff_B.md` §1a proposes exactly this (add Ice/Blood/
> Void, COUNT 19→22) — this draft matches it. The handoff's "21 elements" = 21 real elements; the
> enum COUNT includes `None` so it is 22. No conflict.

---

## Exact diff for `Project/R3ALN3T_UE5/Source/R3ALN3T_UE5/Core/Types/TrinityMatrixTypes.h`

```diff
@@ enum class EElement : uint8
     Poison    UMETA(DisplayName="Poison"),
     Nature    UMETA(DisplayName="Nature")
+    Ice       UMETA(DisplayName="Ice"),       // ADDED (CEO 21-element ruling 2026-07-13)
+    Blood     UMETA(DisplayName="Blood"),     // ADDED
+    Void      UMETA(DisplayName="Void")       // ADDED (apex element; NOT Holy/Void OMICRON stub)
 };
-inline constexpr int32 EElement_COUNT = 19; // includes None
+inline constexpr int32 EElement_COUNT = 22; // includes None (21 elements + None)
```

## Companion change required (generator / data)
- `content_sample/generate_volume.py` and `content_sample/generate_sample.py` carry an 18-element
  `TIERS`/`STATS` table and an `OMICRON…` Greek list — these are the legacy 18-wheel generators.
  Per Override_b they are to be **re-tagged to 21-element**; the generator copies were already pruned
  of cruft factions (commit `606d698`/`c06ee9e`). Confirm the element column uses the 21-set.
- `Scripts/gen_element_table.py` already targets the 21×21 CSV (`gamedata/canon/ELEMENT_MATCHUP_MATRIX_21.csv`)
  and asserts 21 — run it to regenerate `ElementMatchupTable.h` after the enum lands.

## Verification checklist (engine lane, before merge)
- [ ] `EElement_COUNT == 22`; enum enumerates exactly the 21 CSV elements + None.
- [ ] `gen_element_table.py gamedata/canon/ELEMENT_MATCHUP_MATRIX_21.csv <out>.h` runs, emits 21×21.
- [ ] UE5.8 build green (real `Build.bat` log) — no switch/array-size assumes 18 elements.
- [ ] `data_models.py ElementType` (still 6-element legacy: FIRE/WATER/LIGHTNING/ICE/WIND/EARTH) —
      flag: the Python backend enum is STALE vs the 21 canon; update or it will reject 21-element payloads.
- [ ] No remaining `Holy`/`Water`/`Lightning` element spellings in code or seed data (rename to
      Light-less / Aqua / Elec per CANON_FML).

## Non-blocking canon note
`content_sample/lore/element_pair_bible.md` is still titled "18 elements" and lacks Ice/Blood/Void
profiles. It is internally consistent for the 18 it covers but is **behind the 21 ruling** — add the
three element profiles (or a supplement) so docs match the header once the header lands.

**END DRAFT**
