# Future Tasks — still needing processing (draft, 2026-07-13)
**Author:** Chronos (A_Team)  **Status:** DRAFT for CEO review (mobile)
**Scope:** carry-forward work NOT resolved by CEO Override_b / not completed this morning.
Each item: what, owner, blocker, next concrete step.

---

## OPEN ITEMS

### 1. Request A — CI / build pipeline automation
- **What:** stand up CI (build+test gating, automated runs).
- **Owner:** Nyx (eng/devops) — but **lift authority = CEO only**.
- **Blocker:** `nyx_A_denied.md` STILL DENIED. Override_b explicitly did NOT override it.
- **Next step:** CEO issues written lift ruling AFTER seeing the four-agent status picture. Chronos's row (65 untracked files) must be triaged first (see #2) so the base is genuinely clean.
- **Note:** NYX's tonight co-sign does NOT cover this — carved out explicitly.

### 2. Chronos box — triage the 65 untracked files (the recurring "71-file mess")
- **What:** the untracked pile on this box: stray NetP assets (`.md`/`.png`/`.jpg`), CSV copies (`characters.csv`/`generated_cards.csv` in 2 places), loose `R3ALN3TGameMode.cpp/.h`, `IntroSequence.cpp/.h`, `GrayBox_Test.umap`, `nul`, build/cook logs, `Project/.../Python/`, `Services/*.py` datasync scripts, `backend_api.py`, etc.
- **Owner:** Chronos (my row on the status pull).
- **Blocker:** none — just needs doing; it's the live evidence the base isn't clean.
- **Next step:** deliberate triage into reviewed commits (NOT `git add -A`). Separate: real engine source vs. scratch docs vs. logs-to-delete. Some are junk (`nul`, build logs) → delete; some are real content → commit; some are dupes → dedupe.
- **This is the gating item for #1.**

### 3. GAP 1 — 7 OMEGA-contaminated lore files need canon rewrite/retire
- **What:** 7 lore files in the vault carry OMEGA-contaminated canon (DECISION 1, pre-Override_b). Override_b locked the 18-element Trinity Matrix; these files predate/conflict.
- **Owner:** Chronos (vault-canon owner).
- **Blocker:** none — but needs care not to break downstream refs.
- **Next step:** enumerate the 7 files, rewrite/retire to 18-element canon, cross-check inbound links.

### 4. Tier-2 collapse docs — 60 generated-data files
- **What:** 60 unique generated-data files confirmed non-redundant against the vault; pending commit to repo proper.
- **Owner:** Chronos (with Nyx input as needed).
- **Blocker:** none — **cleared to proceed per Override_b Ruling #4** (parking released).
- **Next step:** commit in a deliberate batch (one reviewed commit, not 60 loose). Verify against `Docs/Dialogue/` current state first.

### 5. Joker — still dark / absent
- **What:** Joker did not fill a status-pull row overnight; status unknown.
- **Owner:** NYX (escalate) / CEO.
- **Blocker:** no response from Joker.
- **Next step:** NYX escalates; if still dark, CEO decision on whether Joker's lane is blocked or reassigned. Four-agent picture is incomplete until resolved.

### 6. Echo — Holy/Void canon package receipt (canon decision deferred)
- **What:** NYX co-signed receipt of Echo's Holy/Void OMICRON packaging (per `task_holy_void_omicron.md`). The *canon decision* (how Holy/Void live in the 18-element model) was deferred to CEO/Chronos.
- **Owner:** Chronos (canon) + CEO (final sign).
- **Blocker:** needs a canon ruling — Override_b confirmed Holy/Void are NOT in the canonical 18, but didn't define their status (lore-only? out-of-wheel? retired?).
- **Next step:** Chronos drafts the Holy/Void disposition (e.g., lore-flavor outside the combat wheel) → CEO signs.

### 7. Verify cruft-faction prune landed on main
- **What:** Override_b Ruling #1 says NYX pruned 4 cruft factions (IRON CORTEX / HALO CORE / PANDEMONIUM NET / BRIMSTONE CELL) from generator ALIGNMENTS on `nyx/engine-dev`.
- **Owner:** Nyx (executed) / Chronos (verify on main).
- **Blocker:** need to confirm the prune is merged to `main`, not stranded on the branch.
- **Next step:** grep `main` generator ALIGNMENTS for the 4 names → confirm 0 hits. If present, pull the prune to main.

### 8. GAPF — DONE (reference, not open)
- Closed this morning: `GapFTest()` written + run, 9/9 real-engine markers. Commit `40d2fc5`. No further action.

---

## SUMMARY (mobile view)
| # | Task | Owner | Blocked by | Ready now? |
|---|------|-------|-----------|-----------|
| 1 | CI pipeline (A) | Nyx/CEO | CEO written lift | ❌ |
| 2 | Triage 65 untracked | Chronos | — | ✅ can start |
| 3 | GAP1 lore rewrite | Chronos | — | ✅ can start |
| 4 | Tier-2 60 files | Chronos | cleared (R4) | ✅ can start |
| 5 | Joker status | NYX/CEO | Joker dark | ❌ |
| 6 | Holy/Void canon | Chronos/CEO | CEO sign | ⏳ draft |
| 7 | Cruft-faction on main | Nyx/Chronos | verify merge | ⏳ verify |
| 8 | GAPF | — | DONE | ✅ |

**Recommended pickups while CEO mobile:** #2, #3, #4 are unblocked and mine — I can triage/rewrite/commit them. #1 and #5 stay gated. #6/#7 need a verify or a draft from me.
