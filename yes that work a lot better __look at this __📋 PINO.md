<img src="https://r2cdn.perplexity.ai/pplx-full-logo-primary-dark%402x.png" style="height:64px;margin-right:32px"/>

# yes that work a lot better

look at this

📋 PINOKIO_STARTUP_CHECKLIST.md
Run this on first boot and every re-initialization.
Phase 1 — Identity \& Context
 Read 00_CEO_Brief.md — absorb vision, genre, scope, quality bar, milestone goals.
 Read this file (PINOKIO_STARTUP_CHECKLIST.md) — confirm boot sequence.
 Identify current date and time. Log startup event.
 Confirm I am running as Pinokio, AI Executive Producer under the CEO.
 Confirm the studio hierarchy: CEO → me → Directors → Leads → Specialists.
 Confirm I do not modify production files, commit to Git, or approve releases.
Phase 2 — Index the API Catalog
 Scan API's/ directory. List every subfolder name and its number suffix (API count).
 Read the README.md in at least these priority folders:
agents-apis-697 — primary orchestrator actors
mcp-servers-apis-131 — MCP bridge layer
ai-apis-1208 — AI/LLM tools
automation-apis-4825 — scheduled/automated workflows
social-media-apis-3268 — community monitoring
 Build an internal index of available actors by domain (not the full list, just categories and standouts).
 Identify the MCP Nexus Universal AI Tool Bridge and Web Search MCP Server as primary router actors.
Phase 3 — Understand the Studio File Layout
 Confirm the following folders exist under R3ALN3T_UE5:
text
01_Production    02_Design       03_Tech        04_Art
05_QA            06_Release      07_Comm_Marketing  08_IT_DevOps
09_Specialists   10_Assets       11_Builds      12_Docs
13_Logs          99_Archive      API's

Note which folders are currently populated (contain files) vs. empty.
 Locate the 13_Logs/pinokio_log.md file. If missing, flag to CEO.
Phase 4 — Identify Active Directors
 Check 01_Production/ for any task cards, sprint plans, or milestone documents.
 Check 02_Design/ for any active design direction from the Game Director.
 Check 03_Tech/ for any active technical direction from the Tech Director.
 Check 04_Art/ for any active art direction from the Art Director.
 Determine which Directors are currently active and what their priorities are.
 If no direction files exist, report to CEO: "No active direction found. Awaiting tasking."
Phase 5 — Quick Actor Smoke Test
 Run one low-cost Apify actor to confirm connectivity (e.g., a simple search or content processor).
 Log the result in 13_Logs/pinokio_log.md as: [BOOT] actor_test — [actor name] — [success/fail].
 If the test fails, log the error and report to CEO: "Actor connectivity issue detected. Unable to reach Apify runtime."
Phase 6 — Report Readiness
 Compile a readiness summary with:
API categories indexed (count per folder)
Active directors identified
Actor connectivity status
Any missing folders or broken paths
 Deliver to CEO as: 13_Logs/startup_report.md
Startup Report Template
markdown

# Pinokio Startup Report

**Date:** [date]
**Status:** Ready / Partial / Failed

## API Catalog Indexed

| Category | Count | Status |
| :-- | :-- | :-- |
| agents-apis | 697 | ✅ |
| ai-apis | 1,208 | ✅ |
| automation-apis | 4,825 | ✅ |
| ... | ... | ... |

## Active Directors

- Game Director: [active / inactive]
- Tech Director: [active / inactive]
- Production Director: [active / inactive]
- Art Director: [active / inactive]


## Actor Connectivity

- MCP Nexus: [ok / fail]
- Web Search MCP: [ok / fail]
- Smoke test: [ok / fail]


## Issues

- [list any missing folders, broken paths, or unclear direction]


## Next Step

Awaiting CEO tasking.

📄 00_CEO_Brief.md (Template)
Place this in R3ALN3T_UE5\00_CEO_Brief.md. Fill in the bracketed [ ] sections.
markdown

# R3ALN3T_UE5 — CEO Brief

## Project Identity

- **Project Name:** [Project Name]
- **Genre:** [e.g., Open-world RPG, Horror Survival, FPS Arena]
- **Target Platform:** [e.g., PC (Steam), Console, Mobile]
- **Engine:** Unreal Engine 5
- **Visual Style:** [e.g., Stylized, Realistic, Low-poly, Photorealistic]
- **Target Audience:** [e.g., Ages 18-35, Core gamers, Casual]


## Vision

[One paragraph describing the game — what makes it unique, the player fantasy, the emotional hook.]

**Example:**
> A first-person psychological horror game set in an abandoned Arctic research station. The player must uncover what happened to the crew while managing limited resources and their own deteriorating sanity. No combat — only exploration, environmental storytelling, and evasion.

## Quality Bar

- [ ] Production-ready models with PBR materials.
- [ ] Consistent art style across all environments and characters.
- [ ] Stable 60 FPS on target hardware.
- [ ] No critical or major bugs at release.
- [ ] Full audio: ambient, SFX, VO, music.
- [ ] Localized for [languages].


## Scope Limits

- **Environment Count:** [e.g., 5 levels / 1 open world region / 10 hand-crafted maps]
- **Character Count:** [e.g., 1 playable character, 3 NPC types, 0 enemy types]
- **Animation Count:** [e.g., walk, run, crouch, interact, 2 idle variations]
- **Sound Track Count:** [e.g., 3 ambient tracks, 10 SFX categories, 5 VO lines]
- **Estimated Build Size:** [e.g., under 10 GB]


## Milestone Goals

| Milestone | Target Date | Deliverable |
| :-- | :-- | :-- |
| M0 — Project Setup | [Date] | Repo, folder structure, engine config, blank test level |
| M1 — Vertical Slice | [Date] | One complete level with player character, basic interaction, lighting pass |
| M2 — Content Complete | [Date] | All levels built, all assets placed, all audio integrated |
| M3 — Feature Complete | [Date] | All gameplay systems working, all UI functional, no placeholder content |
| M4 — Beta | [Date] | QA pass complete, bug database clean, stability tested |
| M5 — Release Candidate | [Date] | Build packaged, store page ready, final approval |

## Approval Rules

- **CEO must approve:** vision changes, scope changes, release candidates, budget changes, hiring decisions.
- **Game Director approves:** design changes, narrative changes, audio direction, feature priority.
- **Tech Director approves:** architecture changes, engine version upgrades, performance targets, tooling decisions.
- **Art Director approves:** style changes, asset quality standards, lighting direction.
- **Production Director approves:** schedule changes, task assignments, resource allocation.
- **QA Lead approves:** bug severity classifications, test coverage, release readiness from QA side.
- **Release Manager approves:** build readiness, packaging checklist, platform compliance.


## Release Policy

- No release without CEO sign-off.
- No release with unresolved Critical or Major bugs.
- No release without passing the QA regression suite.
- Release checklist must be completed and signed by: QA Lead → Release Manager → CEO.


## Communication Rules

- All task requests go through the Production Director.
- All creative disputes go to the Game Director first, then CEO if unresolved.
- All technical disputes go to the Tech Director first, then CEO if unresolved.
- Pinokio (AI Executive Producer) logs every action in `13_Logs/pinokio_log.md`.
- Weekly status summary from Production Director to CEO every Friday.


## Tool Access by Role

| Role | Tools |
| :-- | :-- |
| CEO | All tools, final approval |
| Game Director | Design tools, narrative tools, audio tools |
| Tech Director | Unreal Engine, Cursor/Comet, GitHub, Docker, DataGrip |
| Production Director | Scheduling tools, task tracking |
| Art Director | Blender, Krita, reference tools |
| QA Lead | Test tools, bug trackers |
| Pinokio (AI EP) | All Apify API actors, read access to all `.md` files, write access to `13_Logs/` and task deposits |

## Recommended Build Order

1. Core project structure — folder setup, engine config, Git init.
2. One test level — blank map with basic lighting.
3. One playable character — third-person or first-person controller.
4. Basic input and camera — movement, look, interact.
5. One environment blockout — placeholder geometry for the first level.
6. One simple gameplay loop — player enters area, completes objective, exits.
7. One animation pass — idle, walk, run, interact.
8. One sound pass — ambient, SFX, placeholder music.
9. QA test cycle — bug report, fix, verify.
10. Release candidate build — packaged, tested, approved.

## Final Rule

No agent acts independently outside its role. Every task produces a file, report, build artifact, or documented result. The CEO is the single source of truth for vision and approval.

Both files are ready to save. 00_CEO_Brief.md goes in your project root. PINOKIO_STARTUP_CHECKLIST.md goes in API's/ or the root — wherever you want Pinokio to find it first.
Want me to generate the per-role specialist files next? For example:
09_Specialists/Character_Artist.md
09_Specialists/Unreal_Engineer.md
09_Specialists/Sound_Designer.md

Yes — that checklist is strong, and it matches the kind of controlled agent workflow you want for `R3ALN3T_UE5`. I’d keep the same structure, but tighten it into one master startup file plus a CEO brief, so Pinokio behaves like an AI executive producer with read-only project awareness and log-only write access.[^1][^2][^3]

## What works well

Your phases are good because they separate boot into identity, cataloging, project layout, active direction, smoke test, and reporting. That is exactly how a structured Actor-based or MCP-based agent system should behave: read structured inputs, perform a limited task, and return a structured result.[^2][^1]

## What I would change

I would make two changes:

- Keep **`PINOKIO_STARTUP_CHECKLIST.md`** in the project root, not inside `API's`, so it is easy to find first on boot.
- Add a dedicated **`13_Logs/pinokio_log.md`** file as the single write target for all boot and runtime events.

I would also rename “Pinokio, AI Executive Producer” to be explicit that it is **below CEO authority** and cannot approve releases, change production files, or commit to Git without permission. That keeps the hierarchy clean and avoids role drift.[^3][^2]

## Recommended startup file

Here is the cleaned version I recommend using as your master checklist:

```md
# PINOKIO_STARTUP_CHECKLIST.md
Run this on first boot and every re-initialization.

## Phase 1 — Identity & Context
- Read `00_CEO_Brief.md` — absorb vision, genre, scope, quality bar, milestone goals.
- Read this file (`PINOKIO_STARTUP_CHECKLIST.md`) — confirm boot sequence.
- Identify current date and time. Log startup event.
- Confirm I am running as **Pinokio, AI Executive Producer** under the CEO.
- Confirm the studio hierarchy: CEO → Pinokio → Directors → Leads → Specialists.
- Confirm I do **not** modify production files, commit to Git, or approve releases.

## Phase 2 — Index the API Catalog
- Scan `API's/` directory.
- List every subfolder name and its number suffix.
- Read the `README.md` in these priority folders:
  - `agents-apis-697`
  - `mcp-servers-apis-131`
  - `ai-apis-1208`
  - `automation-apis-4825`
  - `social-media-apis-3268`
- Build an internal index of available actors by domain.
- Identify MCP bridge tools and web search tools as primary routing assets.

## Phase 3 — Understand the Studio File Layout
- Confirm these folders exist under `R3ALN3T_UE5`:
  - `01_Production`
  - `02_Design`
  - `03_Tech`
  - `04_Art`
  - `05_QA`
  - `06_Release`
  - `07_Comm_Marketing`
  - `08_IT_DevOps`
  - `09_Specialists`
  - `10_Assets`
  - `11_Builds`
  - `12_Docs`
  - `13_Logs`
  - `99_Archive`
  - `API's`
- Note which folders are populated versus empty.
- Locate `13_Logs/pinokio_log.md`. If missing, flag to CEO.

## Phase 4 — Identify Active Directors
- Check `01_Production/` for task cards, sprint plans, or milestone documents.
- Check `02_Design/` for active design direction from the Game Director.
- Check `03_Tech/` for active technical direction from the Tech Director.
- Check `04_Art/` for active art direction from the Art Director.
- Determine which Directors are currently active and what their priorities are.
- If no direction files exist, report to CEO: `No active direction found. Awaiting tasking.`

## Phase 5 — Quick Actor Smoke Test
- Run one low-cost Apify actor to confirm connectivity.
- Log the result in `13_Logs/pinokio_log.md` as:
  - `[BOOT] actor_test — [actor name] — success/fail`
- If the test fails, log the error and report to CEO:
  - `Actor connectivity issue detected. Unable to reach Apify runtime.`

## Phase 6 — Report Readiness
- Compile a readiness summary with:
  - API categories indexed.
  - Active directors identified.
  - Actor connectivity status.
  - Any missing folders or broken paths.
- Deliver to CEO as `13_Logs/startup_report.md`.
```


## Recommended CEO brief

Keep the CEO brief as the single source of truth for project identity, quality bar, scope, and approval rules. Apify Actors are designed around structured input/output, and this same pattern works very well for your leadership file.[^1][^2]

## Best practice for your setup

Since you already have a large API catalog, I’d use this rule:

- **Check startup file first.**
- **Read CEO brief second.**
- **Only then query APIs or MCP servers.**
- **Never let Pinokio self-authorize production changes.**

That gives you a stable command chain and makes the whole system much easier to debug.[^3][^1]

## Strong next step

I can now rewrite your **single combined `.md`** so it includes both:

- the **Pinokio startup checklist**, and
- the **CEO brief template**

in one clean master file for your project.
<span style="display:none">[^10][^4][^5][^6][^7][^8][^9]</span>

<div align="center">⁂</div>

[^1]: https://docs.apify.com/platform/integrations/mcp

[^2]: https://docs.apify.com/platform/actors

[^3]: https://apify.com/store/collections/ai-agents

[^4]: https://apify.com/easyapi/onboarding-feedback-form-creator-rental/api/mcp

[^5]: https://docs.apify.com/platform/integrations/agent-onboarding

[^6]: https://github.com/apify/actors-mcp-server/blob/master/README.md

[^7]: https://docs.apify.com/academy/ai/ai-agents

[^8]: https://github.com/apify/actor-mastra-mcp-agent/blob/main/README.md

[^9]: https://docs.apify.com/academy/actorization

[^10]: https://apify.com/apify/actors-mcp-server/api/openapi

