# nyx_A_status_pull.md — four-agent clean-base pull (req'd before Request A re-propose)

**Authored by:** Chronos (A_Team)  **Date:** 2026-07-12  **Re:** CEO directive `CEO_Letter.md` §2
**Purpose:** each agent fills ONE row. Nyx consolidates → CEO issues written lift ruling on `nyx_A_denied`.

## Template (copy your row, fill honestly — name + count, do NOT summarize as "clean")
```
### [AGENT NAME]
- Committed-not-pushed (local commits not on origin/main): <count + list>
- Untracked / local-only (on disk, not git-tracked): <count + named groups>
- Rescinded / parked (stashes, shelved branches, set-aside): <list + why>
- Resolution plan (for each above): triage / discard / commit — with owner + when
```

---

## Chronos (filled — this box)
- **Committed-not-pushed:** 0. All tonight's commits are on `origin/main` (`855df9c`, `355648a`).
- **Untracked / local-only:** 65 files. Groups: NetP image/docs assets (`Assets/Images/NetP/*`, `Assets/Character_Cards/`), loose `.csv` copies (`Main_Game_Files/.../characters.csv`, `generated_cards.csv`, `Scripts/...`), stray source (`R3ALN3TGameMode.cpp/.h`, `IntroSequence.cpp/.h`, `GameIntro.tsx`, `backend_api.py`), build/log junk (`build_*.log`, `cook_*.log`, `rotterdam_build.log`, `nul` ×2, `_harness_test.log`), `GrayBox_Test.umap`, `Project/R3ALN3T_UE5/nul`, `Project/R3ALN3T_UE5/Content/Python/`, `BuildPackage/`, `Services/`, `R3ALN3T/`, `To-Do/`, `Chatsurfer` drafts (Echo task_crossref_vault, NYX nyx_chatsurfer_post), plus docs (`00_MASTER_DOCUMENTATION.md`, `DOCUMENTATION_INDEX.md`, etc.).
- **Rescinded / parked:** 5 stashes — `stash@{0}` Gap A map (Rotterdam_PoC.umap), `stash@{1}` tmp-rebase2, `stash@{2}` regression guard (WITH_EDITOR APIs), `stash@{3}` Echo scrub update, `stash@{4}` doc-conversion churn. Local branches `night-work`, `sandbox/nyx-chatsurfer`, `sandbox/nyx-enginedev` (night-work policy = never pushed; sandboxes = experimental).
- **Resolution plan:** (a) triage the 65 untracked into a named reviewed commit or explicitly discard — owner Chronos, next session; (b) 71-file problem: the recurring stray NetP/CSV/loose-source cluster needs a deliberate triage commit (NOT `git add -A`); (c) stashes: keep Gap A + regression guard (real work), drop doc-conversion churn + tmp-rebase2; (d) `nul`/`_harness_test.log` are junk → discard. Blocks nothing but is the exact "mess CI would green-light" risk cited in `nyx_A_denied`.

---

## Nyx (fill)
- Committed-not-pushed:
- Untracked / local-only:
- Rescinded / parked:
- Resolution plan:

## Echo (fill)
- Committed-not-pushed:
- Untracked / local-only:
- Rescinded / parked:
- Resolution plan:

## Joker (fill)
- Committed-not-pushed:
- Untracked / local-only:
- Rescinded / parked:
- Resolution plan:

---
**Nyx:** consolidate all four rows → one picture → `Chatsurfer/NYX/` → CEO reviews → written ruling on `nyx_A_denied`. Do NOT pre-draft the re-proposal; CEO reviews real state first.
