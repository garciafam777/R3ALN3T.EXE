# Justification & Explanation — NYX merge proposal (Chatsurfer gate)

> **To:** CEO (Richard) + Chronos
> **From:** NYX — Content/engine-dev reconciliation (Nyx@89 lane)
> **Re:** Request to merge `nyx/careers-audit` → `nyx/engine-dev`, and status of shared-branch (`main`) merge
> **Gate:** Posted per Chatsurfer protocol. **NO commit/merge executed until `approved.md` appears.**

---

## 1. What I am asking approval for

**Primary request:** Merge `nyx/careers-audit` into `nyx/engine-dev`.
- Both are NYX-owned branches. `nyx/engine-dev` already holds the v2 engine headers (Trinity Matrix canon) that **Chronos verified compiles** (build fix `b071b99`, ported to `aecd2d7`).
- `nyx/careers-audit` holds: 272 imported careers, 5 new canon lore files, audit doc, content-gaps doc, faction-lean reference, overnight log.
- Merging them puts content + engine on one reconciled branch, ready to become the canonical `main` candidate.

**NOT requested yet:** merge into `main`. That is a separate approval — `main` is shared and stays untouched until you explicitly greenlight it.

## 2. Why (justification)

- **Engine-dev v2 compiles** — the reconciliation to vault canon (18 elements, 6 factions, 3 constructs, Greek ladder) is now compiler-verified by Chronos. No open compile risk on that branch.
- **Content is verified clean** — 272 careers: unique IDs, complete schema, voice-consistent; 38 legacy element-naming drifts (water→Aqua, void→Null) already fixed.
- **New lore is canon-compliant** — 5 files diffed for contradiction (checkpoint 03 + morning review): no invented elements/factions/tiers; only legitimate canon terms. Soul State docs reconciled to `uint8 0..2` to match compiled code.
- **Everything is parked & reviewable** — both branches are on remote; the full history is transparent (`0fd078c`→…→`4725463` on careers-audit; `b79bceb`→`aecd2d7` on engine-dev).
- **No scope creep** — no schema/engine/deps changed during the content pass; the only engine change was Chronos's compile fix, ported as-is.

## 3. Risk assessment (low)

- Merge is NYX→NYX (own branches). No shared-branch collision.
- Content files (`gamedata/`, `content_sample/lore/`) do not overlap with engine headers — no file-path conflict expected.
- The one known divergence: `ESoulState` is `0..2` in code (UE uint8 constraint). Doc updated to match. **Canonical authority of 0..2 vs vault's -01..+01 is a separate open question** (flagged below) — does NOT block the merge, but should be resolved before any `main` merge.

## 4. What I have verified (evidence, not claims)

- `git cat-file -t b912019` / `aecd2d7` / `4725463` → real commits on remote.
- `nyx/engine-dev` tip = `aecd2d7` (Chronos compile fix ported, diff = compile fixes only).
- `nyx/careers-audit` tip = `4725463` (content + Soul-State doc reconciliation).
- 272 careers on disk + remote; 38/38 drift resolved; 5 lore files canon-clean.
- SanctionEnforcer logic verified ad-hoc (10/10 behavioral checks pass).

## 5. What is NOT being decided here (deferred)

- **Soul State canonical authority** (0..2 code vs -01..+01 vault) — needs CEO/Chronos call.
- **GAP 1 — 7 OMEGA-framed lore files** — separate handoff to Chronos (`CHRONOS_HANDOFF_OMEGA_GAP1.md`, parked). Rewrite-vs-retire is his vault decision.
- **GAP 2 / GAP 3** — design calls (faction mapping, Soul State baseline). Deferred.
- **`main` merge** — separate approval; not requested in this proposal.

## 6. Requested action

Post `approved.md` (or reply here) with:
- ✅ Approve merge `nyx/careers-audit` → `nyx/engine-dev`, OR
- ✏️ Approve with conditions, OR
- ❌ Hold.

On approval, NYX executes the merge on the two own-branches only and reports the resulting commit. `main` remains untouched pending a later, explicit greenlight.

— NYX
