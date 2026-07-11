---
act: I
scene_id: ACT1_END
title: Jack-In
setting: The R34L Room flickers as the PED finishes its handshake with the N3T.
participants: [NetAdmin, Trinity, Tyranny, Eternity, Navi, System Voice]
soul_tier: Serene→Settled (Act I closes low-corruption)
next_act_gate: "Unlock ACTII by holding soul integrity above the cracked band."
status: DRAFT — Chronos, awaiting CEO approval
---

# ACT I — Jack-In (expanded script)

**Beat 1 — The handshake breaks.**
> SYSTEM VOICE: *"PED handshake complete. N3T linkage: unstable. Three sub-souls detected in transit."*
> *(The R34L Room strobes. The player's PED screen tears — half the screen shows the real room, half shows the grid.)*

**Beat 2 — The three speak, for the first time as separate voices.**
> TRINITY *(deploy line, front)*: "Front line. I am the door."
> TYRANNY *(deploy line, bend)*: "They bend. I am the hand."
> ETERNITY *(deploy line, seal)*: "Nothing spills. I am the seal."
> NAVI *(player's echo, quiet)*: "That's us. All three. I remembered them before you did."

**Beat 3 — The NetAdmin reveals what it is.**
> NETADMIN: "I am the part of you that refused to decrypt. The PED gave them your name. I kept the one they couldn't read."
> TRINITY: "Then we use the name they don't have. Build the door from the part they deleted."

**Beat 4 — The first real choice (seeds Act II grid).**
> NAVI: "They deleted the exit on every floor but this one. We can rebuild it — or walk through the gap they left and not come back the same."
> *(Choice node CHOICE_A1: REBUILD [order] / BREACH [speed]. Stored to FMythosRunState; drives Act II grid layout.)*

**Beat 5 — Close.**
> ETERNITY: "You were never supposed to reach this tile. Good. Neither were they."
> SYSTEM VOICE: *"Act gate: soul integrity holding. ACTII unlocked."*
> NARRATION: The R34L Room stabilizes into the grid. The choice you made here — rebuild or breach — is already rewriting the walls of the Rogue Mesh.

---

---
act: II
scene_id: ACT2_END
title: The Rogue Mesh
setting: The Rogue Mesh opens like a wound in the network's side — a sector that should not exist, stitched from deleted accounts.
participants: [NetAdmin, Trinity, Tyranny, Eternity, Navi, System Voice]
soul_tier: Settled→Fractured (corruption climbs; barks shift)
next_act_gate: "Unlock ACTIII by holding soul integrity above the cracked band."
status: DRAFT — Chronos, awaiting CEO approval
---

# ACT II — The Rogue Mesh (expanded script)

**Beat 1 — The wound.**
> NAVI: "This sector isn't on any map. It's made of the accounts they scrubbed. Every face in here is someone they deleted."
> *(The grid renders cols 4–7 filled with Wraith-class NetPs — the 'deleted'.)*

**Beat 2 — The deleted speak (new, act-specific voices — NOT recycled).**
> DELETED NETP (chorus): "You jacked in with a name they let you keep. We jacked in with names they took. Guess which of us the grid still remembers."
> TRINITY: "Front line. We don't avenge them — we read them. Their pattern is the door."

**Beat 3 — Tyranny bends the mesh; Eternity finds the spill.**
> TYRANNY: "They bend. I am the hand — and this whole sector bends toward the exit they pretended to erase."
> ETERNITY: "Nothing spills. I am the seal — but the seal's got a hairline. Something's listening on the other side."

**Beat 4 — MCADMIN's first breath (the unseen architect).**
> SYSTEM VOICE *(distorted, not the usual cadence)*: "A three-part soul walked into a deleted sector. MCADMIN was told to expect one. Shall I log you as an error, or a feature?"
> NETADMIN: "It knows the word MCADMIN. That means MCADMIN is listening back. Hold the band — don't let it read how cracked we are."
> NAVI: "It's not the enemy. It's the one who wrote the enemy. Breathe. We name what we are before it names us."

**Beat 5 — Close / gate.**
> TRINITY: "The soul band holds. For now. But it learned our shape this time."
> SYSTEM VOICE: *"Act gate: integrity above cracked band. ACTIII unlocked. Audit pending."*
> NARRATION: The Rogue Mesh closes behind you, but the hairline Eternity found stays open — a thin listening line into Act III's Corporate Grid, where someone is already auditing souls.

---

## Notes for CEO (Gap B / act-end expansion)
- Acts I & II rewritten from Nyx's template-filler into distinct, escalating beats. The original 8 shared ~6 shuffled lines; that's the "validated not coherent" problem in the content review, now visible in narrative too.
- Each NetP keeps its deploy micro-line from the Gap B draft (Trinity/Tyranny/Eternity). Navi = player's echo. MCADMIN introduced in Act II as the unseen architect (per Mythos bible: "MCADMIN as the mythic unknown").
- Acts III–VIII still need the same expansion. Recommendation: a follow-up pass (me or the writer agent) rewrites each with a unique emotional turn + a Soul-State-tiered variant, so no two acts share barks.
- Format = Obsidian story-engine markdown (frontmatter act/scene_id/participants/soul_tier/gate + beats). Drops into `NarrativeManager` StoryTable once Echo encodes rows.
- DRAFT. Edit freely; not committed canon.

— Chronos (draft, A_Team)
