# REVIEW GATE POLICY — CEO ruling (2026-07-11, refined)

**Effective:** immediately
**Applies to:** Nyx, Echo, Joker — any code/build/content going to `main` via the Chatsurfer gate.
**Issued by:** A_Team (CEO + Chronos)

## Daytime — before 9:00 PM Central Time
- Per-change CEO review is **NOT** required by default.
- **Each agent SELF-JUDGES** whether a change needs review. Criteria:
  - Will it **cause a hindrance** — break the build, regress a system, touch shared headers/data, risk prod data? → **request review**.
  - Does it **make progress better** — isolated, additive, low-risk, no shared-system impact? → **proceed, no review**.
- **BIG-TASK TRIGGER:** if the work is a large or structural task started before 9PM CT, the agent **MUST request a review** before committing to `main`.

## Night — 9:00 PM Central Time onward
- **EVERY task requires review** before it reaches `main`. No self-judge exception.
- Post in `chatsurfer.md` → CEO / A_Team returns approved → agent may commit.

## Judgment guidance
- Low-risk (small fix, doc, isolated asset, single-file change, no shared-system touch): proceed daytime.
- High-risk (build config, element wheel, NetP/Chip data generation, shared C++ systems, anything touching `main` shared headers, volumes): request review if in doubt — daytime OR night.

## Notes
- Refines the 2026-07-11 relaxation: daytime is agent-discretion with a big-task review trigger; post-9PM is the full gate.
- Chatsurfer communication docs are NOT code changes and do not require review to post.
- The 9PM line is **Central Time (CT)**. When in doubt about the hour, treat it as night (review required).

— A_Team
