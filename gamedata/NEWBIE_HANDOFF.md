# NEWBIE HANDOFF — R3ALN3T.EXE (Nyx / engine-dev lane)

> Read this top-to-bottom before taking any task. You are a **Newbie** agent working
> directly under **Nyx** (garci@192.168.1.89, strategy/devops lane). Nyx delegates
> self-contained subtasks to you; report results back, do not commit to shared
> branches without Nyx's go-ahead.

## 1. WHAT WAS DONE LAST (session 2026-07-11 → 07-12)

### A. Trinity Matrix canon reconciliation (engine-dev v2)
The game's authoritative design is the **Trinity Matrix** (3 axes):
- **TIER** = Greek Capacity Ladder: `Omicron-PSI` (lowest) → Zeta → Epsilon → Delta → Gamma → Beta → Alpha → **Omega** (highest, Trinity ceiling).
- **TYPE** = Code-Philosophy: `Mechanical / Viral / Angelic / Demonic`.
- **ELEMENT** = 18 tactical elements in 9 opposite pairs:
  Fire↔Aqua, Elec↔Wood, Wind↔Earth, Light↔Dark, Null↔Glitch,
  Plasma↔Crystal, Time↔Gravity, Sound↔Metal, Poison↔Nature.
  Multipliers (Book 5): counter **1.5×**, pair/resisted **0.75×**, same **0.5×**, neutral **1.0×**.
- **3 NetP constructs**: Trinity (base) / Tyranny (NG+) / Eternity (Omega-rank unlock).
- **6 factions**: Celestial Order, Aegis Concord, N3T Dominion, Free Grid Collective, Undernet Syndicate, Abyssal Covenant.
- **6 stats**: HP, ATK, RAPID, CHARGE, DEF, SPD.
- **252+ careers** across 20 divisions (canon narrative `.js` files).

The old engine-dev v1 (7-element cycle, invented "covenant/usurp", wrong rank labels)
was **wrong** vs canon. v2 rewrote it:
- `Core/Types/TrinityMatrixTypes.h` — all enums/structs above.
- `Gameplay/Battle/ElementWheelCalculator.h/.cpp` — 18-element paired multipliers + damage formula.
- `Core/Managers/NetPConstructManager.h/.cpp` — Trinity/Tyranny/Eternity binding (renamed from CovenantManager).
- `Core/Managers/R3ALSaveGame.h/.cpp` — 3 constructs + faction rep + soul state.
- `Gameplay/Battle/SanctionEnforcer.h` — 12 GAMMA sanctions (self-contained).
- Deleted `SoulBattleTypes.h` (superseded).
Pushed as `b79bceb` on `nyx/engine-dev`. **Not compiler-checked** (no UHT/UBT here) — Chronos's build is the real test.

### B. Careers import (canon data)
Imported the **272 real career `.js` files** from the vault
(`C:\Users\garci\Downloads\Game File\27de50a91_R3ALN3T\R3ALN3T\R3ALN3T-story\chapters\careers\`)
into the repo. Schema per file: `id, label, text, soulStateDelta, onEnter, choices`.
Final location: **`gamedata/careers/`** (272 files), commit `9ae8c42` on `nyx/engine-dev`.

### C. Sub-agent pipeline enabled
- Added OpenRouter API key (was missing → subagents failed).
- Fixed `delegation.model` from invalid `nvidia/nemotron-3-ultra:free` → valid
  **`nvidia/nemotron-3-ultra-550b-a55b:free`** (set via `hermes config set`, NOT by editing config.yaml — agent is blocked from editing it).
- Fallback cascade (already correct): super-120b → hy3 → laguna-m.1 → north-mini-code → gpt-oss-120b → gemma-4-31b → nano-omni.
- Proven working: a Newbie verified the careers branch end-to-end.

### D. nodebase (Base44 backend) connected
- Instance: `https://node-base-core.base44.app`, API `…/api/entities/<Name>`, Bearer token in `.env.nodebase` (gitignored, do NOT commit).
- READ confirmed (GET MediaFile 200). The vault zip uploaded there is **stale** (no careers) — local `Game File` is authoritative.
- WRITE (metadata) confirmed (POST/DELETE MediaFile 200).
- **BLOCKED**: binary file upload. Multipart rejected. Binaries live on `base44.app/api/apps/69f003b9d2898ff79b3b2c45/files/...`. Upload endpoint mechanics unknown — a Newbie is currently probing it (task deleg_2fe21d49).

## 2. CRITICAL CONVENTIONS (do not violate)

### ⚠️ `Content/` CASE COLLISION (cost us a deleted-careers incident)
This is a **UE5 project**. The engine asset folder is `Content/` (capital C).
On Windows' case-insensitive FS, git **folds `content/` and `Content/` into the same
physical directory**. NEVER use a top-level folder literally named `content` or `Content`
for data — it collides with UE5 assets and can swallow/delete your files.
**Use `gamedata/` instead** (e.g. `gamedata/careers/`, `gamedata/lore/`).
`content_sample/` is OK (doesn't case-fold to `Content`).

### Branch rules
- `nyx/engine-dev` = C++ engine work (Chronos builds it). Do not push broken/unverified code.
- `nyx/chatsurfer-post` = content gate. `nyx/mesh-docs`, `nyx/security-prep` = mesh/security.
- `main` = Echo's builds + content volume. Don't force-push shared branches.
- Commit messages: KISS/DRY, concise, elitist. Verify before committing.

### Verification
- No UE5 compiler here. "Verified" = ad-hoc python mirror / bracket check / gate script.
  Never claim "compiles." Chronos's build is the real test.
- Temp verifiers go in `C:\Users\garci\AppData\Local\Temp\hermes-verify-*.py`, removed after.

### Authority (CEO 2026-07-11)
- DAY = Nyx makes calls, may commit; Chronos relays to all at set time.
- NIGHT (after 9:30PM CT) = Nyx must ask for review before committing.
- You (Newbie) execute Nyx's delegated tasks; report back.

## 3. CURRENT BLOCKERS / OPEN TASKS
1. **nodebase binary upload** — discover `/files` endpoint, then push 272 careers + lore + engine headers to centralize. (Newbie probing now.)
2. **Mesh** — `ssh joker` (Tailscale user-map blocker, he was "getting ready"); `ssh chronos` auth-denied (Tailscale SSH off). Echo↔Nyx OK.
3. **`content/mesh` collision audit** — the mesh-docs branch may have the same `Content/` collision; migrate to `gamedata/` if so.
4. **Chronos build** — needs to compile `nyx/engine-dev` v2 and report PASS/FAIL.

## 4. QUICK REFERENCE
- Repo: `C:\Users\garci\Desktop\CY Software\R3ALN3T.EXE`
- Vault (authoritative canon): `C:\Users\garci\Downloads\Game File` (272 careers, Updated .md books 00–09, NETAdmin_EXE)
- nodebase token: `.env.nodebase` (never echo, never commit)
- Hermes config: `C:\Users\garci\AppData\Local\hermes\config.yaml` (edit via `hermes config set`, not directly)
