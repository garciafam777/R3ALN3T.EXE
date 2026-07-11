# Joker — Target 1 FINDINGS: save-file tampering (ANTICHEAT)

**Agent:** Joker — anticheat / exploit-surface testing
**Target:** `godot_project/scripts/core/game_save_manager.gd` (+ consumers)
**Method:** static code review of the save/load path (read-only; no save edited,
no game code modified). Isolated analysis — no runtime exploit executed.
**Status:** APPROVED to continue (CEO 2026-07-11).

## Verdict: save is FULLY CLIENT-MALLEABLE. Not "encrypted" — obfuscated only.

### The mechanism (lines 191-209)
- "Encryption" = **XOR with `password.sha256_buffer()`**. Reversible stream cipher,
  keyed ONLY by the player's password. No server secret, no IV, no KDF stretching.
- Any owner of the password (or a 4-char-min guess, line 82) decodes → edits →
  re-XORs. Trivial.
- **No MAC / signature / integrity check** anywhere. `load_game` (114-129) decodes
  and trusts the result. A tampered `.dat` that XOR-encodes valid JSON is accepted
  blindly.

### Concrete exploit paths (all confirmed by reading the code)
1. **Currency `Z` (man_balance) injection.** `save_game` writes whatever
   `state["man_balance"]` says (line 139), no clamp/server authority. Edit `.dat`
   → `man_balance: 999999999` → reload → accepted. **Critical if balance feeds
   any ranked/NetP-economy path.**
2. **Meta file is PLAINTEXT JSON, not encrypted** (`.meta.json`, lines 14-33).
   `man_balance`, `active_netps`, `location` are mirrored there in cleartext
   (91-97, 136-140). `update_slot_preview` (160) writes meta from an unauthenticated
   patch. So you don't even need to crack XOR — just edit `.meta.json` directly.
3. **Roster / NetP unlocks client-authored.** `active_netps`, `netp_roster`,
   `customizer_layout` are arbitrary JSON written by the client (41, 42, 140).
   No "did the player earn this?" check on load.
4. **Save state flows into the battler.** `main.gd` (131-135) passes
   `man_balance`/`active_netps`/`location` into `net_room.tscn`. So a tampered
   save directly privileges the NetP battler experience. **This is the real
   anticheat relevance** — if net_room has any ranked/peer-visible state, client
   trust = trivial cheat.

### False-security flag (report to CEO/Chronos)
- `load_picker.gd` line 198 displays **"AES-256 · PASSWORD PROTECTED"** — but the
  implementation is XOR (not AES). Mislabeled security gives a false sense of
  protection. Should be corrected or the implementation upgraded.

### What would actually fix it (recommendation, not yet implemented)
- **Server-authoritative** for anything ranked/economy: server holds man_balance +
  unlocks; client sends inputs, server validates.
- If local-only save must stay: add an **HMAC** over the payload with a
  **server-held secret** (not the password). Tampered file fails HMAC → rejected.
- Validate `man_balance` range + `active_netps` against an allow-list of earned
  unlocks on load.
- Fix the "AES-256" label (either implement AES-GCM or stop claiming it).

## Scope note
This is a **local single-player save**. Editing your own save is the player's
prerogative. The RISK is only if any of this state (balance, unlocks, roster)
reaches a **multiplayer/leaderboard/ranked NetP** context — then client trust is
an exploitable cheat. **Recommend CEO confirm whether net_room is ranked before
we treat this as urgent vs. accepted single-player modding.**

## Gate
- Findings posted here (read-only review). **No game code edited.** No commit to
  main until `approved.md` on the *remediation* (if CEO wants it).
- Ready to move to Target 2 (BackendClient endpoint abuse) on direction.

— Joker
