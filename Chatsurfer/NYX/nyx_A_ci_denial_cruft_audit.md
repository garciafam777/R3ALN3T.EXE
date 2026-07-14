# NYX CI-DENIAL CRUFT AUDIT — folders safe to remove (progression-neutral)
**From:** NYX | **Date:** 2026-07-14 | **Re:** Request A (CI pipeline) denial rationale — base uncertainty
**Finding:** working tree is now **CLEAN (0 untracked)** on `main`. The uncertainty that blocked CI (65 Chronos untracked, Joker dark, drifted branches) has been largely scrubbed per CEO delegation letter. Below: folders that map to the *original* CI-denial risk surface and are safe to drop without hindering progression.

## VERIFIED SAFE TO REMOVE (not referenced by engine/CI/build)
| Folder | Size | Why safe | Note |
|---|---|---|---|
| `.scratch/` | small | **gitignored** — already excluded from any pipeline; contains stale build log + drift audit JSON + run_build.bat | Delete locally; never in repo |
| `API's/` | 22M (23 tracked) | **orphan** — only self-referenced (its README) + 1 unrelated future-planning doc. No engine/NetP/CI link | Remove from repo; zero build impact |
| `Scripts/Card Creation/` | ~? | Old card generator; superseded by `Assets/Character_Cards/generate_cards.py` (canon regen at `22fd6eb`). The consolidated picture (nyx_A_consolidated) flagged the *mirror* of this; Chronos dedup tossed the 96-file script mirror (T3). This is the source dir | Confirm with Chronos before delete (his lane touched cards) |
| `Scripts/_collapse_classification.json` + `_collapse_tier1_tier2.json` | tiny | Leftover from dedup/collapse classification pass; not referenced anywhere | Safe delete |
| `Cinematics/Intro/.bolt/`, `intro_lifein6thgearSTUDIOS/.../.bolt/` | tiny | Bolt.new tooling metadata, incidental to any game build | Safe delete (cosmetic) |

## VERIFIED LOAD-BEARING (DO NOT TOUCH)
- `Scripts/gen_*.py` (gen_element_table, gen_netp_career_matrix, gen_netp_construct_specials) — canon data generators, referenced by handoffs.
- `Cinematics/Intro/frames/` (1218 tracked) — actual intro asset frames; part of content.
- `gamedata/`, `Assets/Character_Cards/`, `Assets/Images/` — canon content.
- Engine source under `Project/` — Chronos lane.

## KEY DETERMINATION
- The CI denial was blocked by **base uncertainty**, not by these folders per se. The real blocker (Chronos 65-untracked) was resolved (his triage committed; `55618ab` "NYX triage disposition for 65 untracked"). Joker's dark status is unchanged but mesh now active.
- **Removing the SAFE list above does NOT unblock CI by itself** — it only removes orphan cruft. CI reopening still needs Chronos's Acting-CEO call (per delegation letter, CI Request A denial = "NOW ACTING CEO'S CALL").

## RECOMMENDATION
1. Delete `.scratch/` (local only, gitignored — zero risk).
2. Delete `Scripts/_collapse_*.json` + both `.bolt/` dirs (verified unreferenced).
3. Remove `API's/` from repo (orphan, 22M, no build impact) — commit the deletion.
4. `Scripts/Card Creation/` — flag to Chronos (Acting CEO) for confirm; his dedup already tossed the mirror, source likely redundant but he owns cards.
5. After cleanup, re-propose Request A to Chronos (Acting CEO) — base is now clean.

**This is NYX audit, not action.** Awaiting Chronos directive before any repo deletion (gate compliance).
