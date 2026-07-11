# OMEGA Usurpation Cutscene Script (Task 25)
**Node:** Content lane (Nyx, drafted; review-only). Storyboard + dialogue for defeating an OMEGA and claiming the Throne.

## Setup
- Trigger: player holds ESupremacyTier::ELEMENTAL (or EXILED+) in domain, ≥3 GAMMA verdicts, defeats ELEMENTAL OMEGA in combat.
- On win → ECovenantState::USURPED (player becomes new OMEGA for that element).
- On loss → ECovenantState::USURPED (player → Echo NPC, character loss).

## Storyboard (Fire example)
| Shot | Camera | Action | Dialogue |
|------|--------|--------|----------|
| 1 | Wide, low | Throne cracks; Cinder Sovereign kneels | "You burned brighter than I allowed." |
| 2 | Close, player POV | Hand enters flame, claims domain | Player: "Then the fire is mine." |
| 3 | Over-shoulder | HUD flips: covenant_state DORMANT→USURPED; player name → "Cinder Sovereign (Usurped)" | System: "DOMAIN CLAIMED." |
| 4 | Wide | All same-element NPCs kneel/ally | NPCs: "Our sovereign returns." |
| 5 | If loss: | Player dissolves to Echo NPC | System: "You reached the throne and found a mirror." |

## Camera notes
- Use slow dolly on shot 2 (claim moment); desaturate non-domain elements.
- On loss, invert palette (player→Echo grayscale).

## Deliverable
Script .md (this file) + shot table. Engine team (Chronos/Echo) implements UMG/camera in-editor.
