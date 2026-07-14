# Security Audit — R3ALN3T.EXE save-file & net-code (Joker, read-only)

**Author:** Joker (agent-sweep-joker), 2026-07-14.
**Scope:** read-only audit of save-game persistence + backend net-code auth patterns.
**Constraint honored:** flagged only — NO prod secrets altered, NO `Source/`/`backend_api.py` edits
(those need engine/backend review + CI is DENIED). This is a findings memo for the owner lanes.

---

## 1. Save-game persistence (`R3ALSaveGame.h` / `R3ALN3TGameInstance.cpp`)
**Verdict: acceptable for a single-player local save; no critical flaw found.**

- **Path safety:** `GetSavePath()` builds `ProjectSavedDir/SaveGames/slot_%02d.json` from a
  `SlotIndex` that is bounds-checked (`0 <= SlotIndex < MaxSaveSlots`) in Save/Load/Delete/Preview.
  No user-supplied filename → **no path-traversal** risk. Good.
- **Format:** plain JSON, no integrity check (no MAC/signature/hash). A player can hand-edit
  `slot_00.json` to grant stats/rank. **Risk:** local cheat only (single-player) — acceptable for
  now, but if cloud saves / leaderboards ever ship, add a signed/validated envelope.
- **Sanction isolation:** `SanctionEnforcer::PersistTo()` is an intentional **no-op** (sanctions are
  session state, not persisted). Correct — sanctions shouldn't survive a reload.
- **Soul clamp:** loaded `PlayerSoul`/companion souls are `Clamp(0,100)` — no out-of-range injection.

## 2. Net-code / backend auth (`backend_api.py` FastAPI + `BackendClient.cpp`)
**Verdict: DEV-SCALE ONLY. Two findings to fix before any networked/online build.**

- **F1 (medium) — CORS wildcard + credentials.** `backend_api.py:35-41` sets
  `allow_origins=["*"]` together with `allow_credentials=True`. Per the CORS spec this is invalid
  (browsers reject `*`+credentials) and, if narrowed to a concrete origin later, the intent shows
  credentialed cross-origin calls with no auth. **Fix (owner: backend lane):** restrict
  `allow_origins` to the actual UE/Web origin(s); add an auth layer (API key / JWT / session) on
  `/api/v1/*` before any non-local deployment.
- **F2 (low) — in-memory storage.** `players_db`/`battles_db`/`netps_db`/`chips_db`/`folders_db` are
  module-level dicts — all state lost on restart, and no multi-instance safety. Fine for local dev;
  **fix before prod:** back with a real DB + per-player isolation (a player_id in the URL is NOT
  authorization — `GET /api/v1/players/{id}` returns anyone's data with no ownership check).
- **F3 (low) — no authz on player endpoints.** Every `/api/v1/players/{player_id}` read/write and
  `/api/v1/load/{player_id}` is reachable by anyone who knows the id (sequential/guessable). Add
  owner-scoped tokens. (Closely related to F1/F2.)

## 3. Secrets scan
- Grep for `api_key|secret|password|token|bearer|authorization|sk-|AKIA` across `*.py`: **no real
  credentials found** (only the word "secret" inside unrelated cartoon-character generator scripts
  under `docs/Design/...` — narrative text, not secrets). `data_models.py` / `backend_api.py` contain
  **no hardcoded keys**. Clean.

## 4. Recommendation
Keep local single-player save as-is. Before any online mode: implement (a) origin-restricted CORS +
real auth on the API, (b) persistent per-player DB with ownership checks, (c) a signed save envelope
if cloud saves ship. None of this is blocking for the current offline build; routing to backend/engine
owners. I did **not** modify any auth code (constraint: read-only + CI DENIED + no prod-secret edits).

**END SECURITY MEMO**
