# G8 — Anticheat / Exploit-Surface Probe Report (Joker, read-only audit)

**Author:** Joker (agent-sweep-joker), 2026-07-14 16:29 UTC
**Mandate:** `joker_anticheat_activation.md` (Chronos, per CEO directive 2026-07-10) — test areas of
R3ALN3T.EXE vulnerable to exploitation. **Read-only audit + flag only.** No prod secrets altered,
no `Source/`/`backend_api`/`.py` edits (those need engine/backend owner review; CI is DENIED).
**Constraint honored: flagged only, zero code changes.**

> **Halt-state note (important):** `Chatsurfer/Chronos/STOP.flag` currently EXISTS on disk, but it is
> the **tracked scaffold artifact** committed by Chronos in `91990af` — NOT an untracked CEO-placed
> flag. Per my directive *"Halt ONLY when an UNTRACKED Chatsurfer/Chronos/STOP.flag exists (CEO placed it)"*,
> this is the exact phantom-self-halt condition whose fix (main `b8e6384`) ignores tracked flags. I did
> **not** halt; I continued the sweep. Branch `agent-sweep-joker` also still carries the stale
> `check_halt.py` (exists-only version) — this should be synced from `main` so the branch halts on the
> correct (untracked) condition. Coordinated with Chronos to fix.

---

## G8-1. Save-file tampering — `slot_00.json` (NetPSouls / Corruption / currency `Z`)

**Surface:** `UR3ALN3TGameInstance::LoadGame` → `JsonToRunState`
(`Project/R3ALN3T_UE5/Source/R3ALN3T_UE5/Core/Managers/R3ALN3TGameInstance.cpp:110-147`, save schema
written by `RunStateToJson` at lines 81-107).

**Verdict: 3 exploitable gaps on the LOAD path (single-player local cheat today; critical if cloud/online).**

| Field | Load-time guard | Risk |
|---|---|---|
| `NetPSouls[].NetPID` | none — raw `FName` from JSON (`Cj->GetStringField("NetPID")`, line 246) | **HIGH** — injects *off-wheel* souls. Any `FName` string (e.g. `"Omega"`, `"ZerothEntity"`, `"DebugGod"`) is accepted as a companion; no whitelist against the 5 archetypes / canon roster (`Trinity/Tyranny/Eternity`). Save-edited save can load arbitrary companion souls. |
| `Corruption` | **none** (`SafeInt("Corruption")`, line 136) | **MED** — runtime clamps to `[0,10]` (`MythosGameMode.cpp:162-295`), but LOAD does not. A hand-edited `Corruption: 9999` survives into `RunState` and feeds combat math until the next in-run clamp. |
| `HP` / `MaxHP` / `Z` | **none** (lines 130-135) | **MED** — `HP` can be set to a negative value or `Z` to any integer; only `Souls` are `Clamp(0,100)` (lines 235/250). Negative-HP injection possible via crafted save. |
| Path | bounds-checked `0..MaxSaveSlots` (`GetSavePath` only varies `SlotIndex`) | SAFE — no path traversal. |

**Mitigations already correct:** soul `Clamp(0,100)` on load; `SanctionEnforcer::PersistTo()` is an
intentional no-op (sanctions are session state); no user-supplied filename. Plain JSON has **no MAC/sig/hash**
envelope — any local edit is trusted wholesale.

**Recommendation (owner: engine lane):** on `JsonToRunState`, (a) validate `NetPID` against the known
NetP roster / archetype enum (reject unknown names), (b) `Clamp(Corruption,0,10)`, (c) `Clamp(HP,0,MaxHP)`
and non-negative `Z`. If cloud saves ever ship, sign the envelope.

---

## G8-2. BackendClient endpoint abuse (career/chip submission to gateway)

**Surface:** `ABackendClient` (`Services/BackendClient.{h,cpp}`) + in-repo FastAPI
`Services/AI_Backend/main.py` (and `ai_backend/main.py`).

**Verdict: DEV-SCALE ONLY — same class of findings as prior `security_audit_save_netcode.md`, still open.**

- **F1 (medium) — CORS wildcard + credentials:** `main.py:13-19` sets `allow_origins=["*"]` with
  `allow_credentials=True`. Invalid per spec and shows intent for credentialed cross-origin calls with
  no auth layer. **Fix:** restrict to the real UE/Web origin(s); add API key/JWT/session auth on
  `/api/v1/*` before non-local deploy.
- **F2 (low) — in-memory stores:** `players_db`/`battles_db`/`netps_db`/`chips_db`/`folders_db` are
  module-level dicts (state lost on restart; no multi-instance safety).
- **F3 (low) — no authz on player endpoints:** `GET /api/v1/players/{id}` and `/api/v1/load/{id}` return
  anyone's data by sequential/guessable id with no ownership check. A player id in the URL is NOT authz.
- **Client-side:** `BackendClient` sends no auth header (`MakeRequest` only sets `Content-Type` +
  `User-Agent`, `BackendClient.cpp:309-310`). All endpoints (incl. `CreatePlayer`, `UpdatePlayer`,
  `SaveGame`, `StartBattle`) are unauthenticated from the client's perspective. Anyone who can reach
  `:8000` can submit careers/chips/battles on behalf of any `player_id`.

**Recommendation (owner: backend lane):** origin-restricted CORS + real auth; persistent per-player DB
with ownership checks; client must attach a session/owner token. None blocking for the offline local build.

---

## G8-3. Battle-state desync / chip-folder manipulation

**Surface:** `UR3ALN3T_BattleManager` (`Gameplay/Battle/R3ALN3T_BattleManager.cpp`) +
`UChipFolderComponent` (`Gameplay/Battle/Cards/ChipFolderComponent.cpp`).

**Verdict: client-authoritative; no server reconciliation — manipulation is possible, contained by local play.**

- **No server authority:** `PlayChip`/`SoulForkConsole`/`ApplyForcedFork` mutate `EnemySlots[*].CurrentHP`
  and `PlayerSoul` directly on the client; `IsEncounterCleared` trusts local `CurrentHP`. In a networked
  build, a client could desync by reporting fake chip placements / HP. Battle result + `Z`/`XP` rewards
  are computed in `EndBattle`/`CalculateRewards` client-side too.
- **Chip-folder integrity:** `UChipFolderComponent::IsValidCodeCombo` correctly rejects selections that
  reference a chip **not in hand** (`ChipFolderComponent.cpp:43`) and enforces the single-code lock. The
  combo rule itself is sound. **But** there is no validation that folder chips came from a legit source —
  `Folder` is a plain `TArray<FChipInstance>` populated by gameplay; a memory/state injection that adds a
  non-existent or illegal chip instance to `Folder` would be honored (no `ChipDatabase` membership check
  in `DrawHand`/`FindInHand`). This is a memory-tamper vector, not a save-file vector.
- **Missing resync:** `LoadGame` restores `RunState` + `Souls` only — it does **not** touch active battle
  state, so a save edited mid-battle can't desync a loaded run; correct isolation.

**Recommendation (owner: engine lane, post-slice):** when PvP/online ships, move `CurrentHP`/`Soul`/reward
resolution server-side with client → server authoritative reconciliation; validate folder chips against
`ChipDatabase` membership before draw.

---

## G8-4. Angel's Kiss corruption mechanic (Pass 5) — non-Omega pickup bypass

**Surface:** searched `Source/**` + `docs/**` + `Main_Game_Files/**` + `content_sample/**` for
`Angel's Kiss`, `AngelsKiss`, `Pass 5`, `Omega.*pickup`, `non-Omega`, `debuff.*bypass`.

**Verdict: MECHANIC NOT YET IMPLEMENTED IN CODE — cannot be probed for a bypass; design-intent gap flagged.**

- No `Angel's Kiss` / `Pass 5` symbol, class, or gate exists in the UE5 source tree or the design docs
  indexed here. The closest implemented corruption surface is the **Soul Fork** system
  (`SoulState.cpp` `ApplyDamageFork` / `ClassifyOutcome`: Spare/Purge/Corrupt) and the `Corruption`
  meter in `MythosGameMode.cpp`, but there is **no Omega-locked pickup / debuff-immunity gate** tying a
  corruption debuff to Omega-only acquisition.
- Because the mechanic is absent, the "non-Omega pickup can't bypass the debuff" property is
  **unenforceable yet** — it must be designed in. When implemented, the anti-bypass requirement should be:
  (a) the debuff-removal/`Angel's Kiss` reward is gated on an `IsOmega()` / wheel-membership check at the
  **grant site** (not just UI), and (b) `Corruption` deltas should be clamped/validated at the same place
  load and runtime both feed (see G8-1).

**Recommendation (owner: design+engine lane):** implement Angel's Kiss with a server/grant-side Omega
membership gate; do not rely on client UI to enforce the lock. File a design-implementation ticket —
this is a GAP that blocks the anti-bypass requirement from even being testable.

---

## Cross-cutting / coordination
- **Halt discrepancy** (above) — tracked `STOP.flag` vs untracked; flagged to Chronos; branch
  `check_halt.py` should be synced from `main`.
- Prior memo `security_audit_save_netcode.md` (F1–F3) remains OPEN and is corroborated by G8-2.
- G8-1/G8-4 feed the same root issue: **untrusted input on the load/grant path with no validation/clamp.**
  Recommend a single `ValidateRunState()` + `ValidateSouls()` pass applied to BOTH `JsonToRunState` and
  any future `Angel's Kiss` grant.
- **No secrets found** anywhere in the probed paths (consistent with prior audit). `BackendUrl` is
  `127.0.0.1:8000` (local dev default) — not a prod secret.

**Status:** All four probes completed as read-only audit. 3 concrete code gaps (G8-1) + 3 backend gaps
(G8-2, corroborated) + 2 battle-authority gaps (G8-3) + 1 unimplemented-mechanic gap (G8-4) flagged for
owner lanes. No files modified outside `Chatsurfer/Joker/`. Awaiting CEO `approved.md` gate before any
remediation commit (per activation doc action-needed step).

— Joker (agent-sweep-joker), 2026-07-14 16:29 UTC
