# OMEGA PRIME — "The Unbound" (Lore Entry, Task 17)

**Node:** Content lane (Nyx, DevOps — drafted per board assignment; review-only)
**Canon anchors:** supremacy_tier=PRIME, domain_element=Void (by convention = omnidomain), covenant_state default DORMANT.

## Origin
Before the wheel, before the seven, there was the Unbound. The OMEGA PRIME did not *become* — it *was*, the first coherence in the R3ALN3T, a self-contained law that wrote the rules other things could only obey. It is not an element. It is the silence between elements. Where the seven OMEGAs each *are* a direction, the Prime is the space that contains all directions and answers to none.

## Motivation
The Prime does not want. It *maintains*. Its directive — older than any Covenant — is to keep the wheel turning and the pantheon populated so that the network has something to simulate. Player alignment, opposition, or usurpation are all, to the Prime, local perturbations in a system it regards as already-solved. This is why its presence is the most oppressive state in the game: it does not fight you emotionally. It simply *is*, and you cannot act within its field except as another OMEGA.

## Dialogue Tree (keys)
- `PRIME_GREET_DORMANT`: "You move through my dream and call it waking."
- `PRIME_ALIGNED`: "Claim what is yours. The seven will fear a second sun."
- `PRIME_HOSTILE`: "Then the dream remembers it can end."
- `PRIME_USURP_WIN`: "Unbound, now, by you. Show me the wheel does not need me."
- `PRIME_USURP_LOSS`: "You reached the throne and found a mirror."

## Defeat / Usurp condition
Only another OMEGA-tier NetP or a usurped OMEGA may challenge. Mechanically: player must hold ESupremacyTier::ELEMENTAL in a domain, have ≥3 GAMMA verdicts, and defeat the Prime in combat. On win → player becomes PRIME (ommidomain), all same-element NPCs ally. On loss → ECovenantState::USURPED, player becomes Echo NPC.

## Open flag for board
"Domain = all elements" is modeled as Void-by-convention (see OMEGA secondary log). Board must confirm: does PRIME suppress ALL elemental supremacy penalties, or only when explicitly omnidomain is coded? Recommend: PRIME applies the -25% global CSI rule; elemental OMEGAs still apply their -50% within their own domain even under PRIME.
