# GAMMA Verdict Dialogue System (Task 24)
**Node:** Content lane (Nyx, drafted; review-only). Branching dialogue for GAMMA NPCs.
They assess crimes, need evidence, render verdicts. 3 example dialogues + outcome table.

## Mechanics
- GAMMA NPC opens with accusation. Player may: Present Evidence / Deny / Bribe(fail).
- Needs ≥1 evidence flag to flip verdict in player's favor.
- 3 favorable verdicts = usurp eligibility gate (see OMEGA supremacy).

## Dialogue 1 — "The Tagged Cache" (Act-1 node 6)
- GAMMA: "You held contraband chips. Confess."
- Player Present: loot-log showing legal origin → verdict FAVORABLE (+1).
- Player Deny (no evidence): verdict GUILTY → Wanted sanction.

## Dialogue 2 — "The Framed Node" (Act-1 node 11)
- GAMMA: "Sector breach traces to your ID."
- Player Present: timestamp alibi (Echo witness) → FAVORABLE (+1).
- Player Deny: STAYS PENDING → re-trial at node 16.

## Dialogue 3 — "The Decisive Verdict" (Act-1 node 16)
- GAMMA: "Three counts. Last chance."
- Player Present: full evidence chain → FAVORABLE (+1, completes 3/3).
- Fail: USURPED-risk flag, Echo transformation threat.

## Outcome table
| Evidence | Verdict | Effect |
|----------|---------|--------|
| ≥1 valid | FAVORABLE | +1 verdict flag, no sanction |
| 0, denies | GUILTY | Wanted sanction (AI detection +) |
| 0, bribes | REJECTED | harsher, Echo-risk |
| 3/3 favorable | ELIGIBLE | usurp gate open |
