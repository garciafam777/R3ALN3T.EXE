<img src="https://r2cdn.perplexity.ai/pplx-full-logo-primary-dark%402x.png" style="height:64px;margin-right:32px"/>

# provide all of that into just 1 (one) full .md

Here is the full single-file markdown content you asked for, ready to save as `R3ALN3T_UE5_AI_Studio_Master.md`.[^1][^2]

```md
# R3ALN3T_UE5 AI Studio Master File

## Purpose
This file defines a CEO-led AI studio structure for building a 3D Unreal Engine game inside the `R3ALN3T_UE5` project. The goal is to simulate a full game studio with clear departments, controlled permissions, and structured outputs.

## Operating Principle
You are the CEO. All agents serve under you. No agent acts independently outside its role. Every task must produce a file, report, build artifact, or documented result.

## Studio Hierarchy

### YOU (CEO)
- Own the vision, budget, scope, and final approvals.
- Approve major creative, technical, and release decisions.
- Resolve conflicts between departments.
- Protect quality and keep the project on mission.

### Game Director
Owns the overall creative direction and player experience.
- **Design Director**: all designers, systems, levels, UI/UX, balance, quests.
- **Narrative Lead**: writers, story, lore, dialogue, localization prep.
- **Audio Director**: sound, music, VO, implementation direction.

### Tech Director / CTO
Owns architecture, systems, tools, and technical quality.
- **Rendering Lead**: graphics, materials, lighting, shaders, visual performance.
- **Gameplay Engineering Lead**: gameplay code, AI hooks, interaction systems, input, combat.
- **Tools/Pipeline Lead**: build tools, import/export, automation, content pipelines.
- **Data/Telemetry Lead**: metrics, analytics, dashboards, telemetry events.

### Production Director
Owns execution, schedule, delivery, and cross-team coordination.
- **Art Director**: all art disciplines, style consistency, visual standards.
- **QA Lead**: test plans, bug reports, verification, regressions.
- **Release Manager**: build readiness, packaging, release checklists.
- **Community/Marketing Lead**: announcements, community messaging, launch support.
- **IT/DevOps Lead**: infrastructure, services, backups, environments, access.

## Studio Rules
- Keep every agent role narrow and clear.
- One task, one owner, one expected output.
- No agent changes production files without review.
- Use Git for all versioned work.
- Prefer small, testable steps over large one-shot generation.
- Every major decision requires CEO approval.
- Use approval gates before merging, exporting, or shipping.

## Recommended Agent Count
Start with these core agents first:
- CEO
- Game Director
- Tech Director / CTO
- Production Director
- Art Director
- QA Lead

Then add specialists as needed:
- Design Director
- Narrative Lead
- Audio Director
- Rendering Lead
- Gameplay Engineering Lead
- Tools/Pipeline Lead
- Data/Telemetry Lead
- Release Manager
- Community/Marketing Lead
- IT/DevOps Lead
- Character Artist
- Environment Artist
- Prop Artist
- Animator
- Rigging Artist
- Texture Artist
- VFX Artist
- Lighting Artist
- Unreal Engineer
- Blender Artist
- Sound Designer
- Music Composer
- Localization QA

## File Layout
Use this folder structure inside `C:\Users\richa\Desktop\R3ALN3T_UE5`:

```text
R3ALN3T_UE5
├── 00_CEO_Brief.md
├── 01_Production
├── 02_Design
├── 03_Tech
├── 04_Art
├── 05_QA
├── 06_Release
├── 07_Comm_Marketing
├── 08_IT_DevOps
├── 09_Specialists
├── 10_Assets
├── 11_Builds
├── 12_Docs
├── 13_Logs
├── 99_Archive
└── API's
```


## Folder Purpose

- `00_CEO_Brief.md`: master vision and rules.
- `01_Production`: sprint plans, task tracking, schedules.
- `02_Design`: design documents, narrative, audio direction.
- `03_Tech`: architecture, gameplay, rendering, tools, telemetry.
- `04_Art`: visual style, references, art standards.
- `05_QA`: bugs, test plans, verification.
- `06_Release`: release checklists, packaging, version notes.
- `07_Comm_Marketing`: community, trailers, social updates.
- `08_IT_DevOps`: environments, access, backup, build infra.
- `09_Specialists`: individual role files for artists, engineers, and support roles.
- `10_Assets`: source files from Blender, Krita, Audacity, and other tools.
- `11_Builds`: packaged builds and test exports.
- `12_Docs`: design docs, technical docs, lore, pipeline docs.
- `13_Logs`: agent logs, task logs, review notes.
- `99_Archive`: retired files, old versions, superseded plans.
- `API's`: external API references, connectors, and documentation.


## Core Role Files

### CEO Brief

The CEO file should define:

- project vision,
- target genre,
- quality bar,
- scope limits,
- milestone goals,
- approval rules,
- release policy.


### Production Director

The production layer should manage:

- milestone planning,
- task assignment,
- blockers,
- dependency tracking,
- delivery dates,
- status reporting.


### Game Director

The game direction layer should manage:

- core player experience,
- creative vision,
- feature priorities,
- gameplay feel,
- narrative tone,
- final design review.


### Tech Director / CTO

The technical layer should manage:

- code standards,
- Unreal architecture,
- tools,
- pipelines,
- build reliability,
- performance,
- maintainability.


### Art Director

The art layer should manage:

- visual style,
- asset quality,
- 3D art standards,
- lighting direction,
- environment quality,
- consistency across all visuals.


### QA Lead

The QA layer should manage:

- test cases,
- bug reports,
- reproduction steps,
- regression verification,
- release signoff criteria.


## Agent Input Format

Every agent should receive work in this structure:

```md
# Task
Role:
Objective:
Input Files:
Allowed Tools:
Deliverable:
Deadline:
Approval Needed:
```


## Agent Output Format

Every agent should return this structure:

```md
# Result
Summary:
Files Created:
Changes Made:
Issues Found:
Next Step:
Approval Requested:
```


## Permission Model

- **CEO**: full approval authority.
- **Directors**: can assign tasks within their department.
- **Leads**: can produce and review within their discipline.
- **Specialists**: can only work within assigned scope.
- **QA**: can test and report, but not approve release alone.
- **Release Manager**: can prepare release, but final ship approval stays with CEO.


## Tool Usage Map

Use your tools like this:

- **Unreal Engine**: project assembly, Blueprints, level work, gameplay, testing.
- **Blender**: 3D modeling, animation, rigging, export prep.
- **Krita**: concept art, UI mockups, texture painting.
- **Audacity**: sound cleanup, VO prep, audio editing.
- **GitHub Desktop**: commits, branches, pull requests.
- **Docker Desktop**: services, repeatable environments, automation support.
- **DataGrip**: databases, telemetry, backend data inspection.
- **Cursor / Comet / Antigravity**: coding, refactoring, prompt-driven development.
- **CocoDashboard**: status and operational visibility if used in your workflow.
- **APIs**: automation, research, content generation, integration, orchestration.


## API Folder Strategy

Your `API's` folder can serve as the service catalog for agents.

Suggested use by category:

- `agents-apis`: agent orchestration and task routing.
- `ai-apis`: LLMs, image generation, reasoning, embeddings.
- `automation-apis`: scheduled jobs, workflow automation, actions.
- `business-apis`: budgeting, planning, operations.
- `developer-tools-apis`: code, CI/CD, testing, repo workflows.
- `ecommerce-apis`: storefronts, asset sales, marketplace support.
- `integrations-apis`: connectors between systems.
- `jobs-apis`: work queues, staffing, recruiting, task systems.
- `lead-generation-apis`: marketing capture, forms, audience growth.
- `mcp-servers-apis`: editor/tool control through MCP-based services.
- `news-apis`: research, trend tracking, industry updates.
- `open-source-apis`: community tools and libraries.
- `other-apis`: miscellaneous utilities.
- `real-estate-apis`: only if needed for side projects.
- `seo-tools-apis`: web presence, launch visibility, content discovery.
- `social-media-apis`: audience building and updates.
- `travel-apis`: only if relevant for events or logistics.
- `videos-apis`: trailers, clips, marketing assets.


## Workflow Loop

1. CEO defines a goal.
2. Production Director turns the goal into milestones.
3. Game Director, Tech Director, and Art Director break the work into department tasks.
4. Leads assign specialist tasks.
5. Specialists create assets, code, docs, or reports.
6. QA verifies the output.
7. Release Manager prepares packaging.
8. CEO approves final merge or release.

## Unreal Engine Focus

Since this is a 3D Unreal project, prioritize these domains:

- environment art,
- character art,
- prop art,
- animation,
- lighting,
- VFX,
- gameplay systems,
- UI,
- performance,
- build testing.


## Recommended Build Order

1. Core project structure.
2. One test level.
3. One playable character.
4. Basic input and camera.
5. One environment blockout.
6. One simple gameplay loop.
7. One animation pass.
8. One sound pass.
9. QA test cycle.
10. Release candidate build.

## Success Criteria

The system is working when:

- agents stay in role,
- outputs are consistent,
- tasks are traceable,
- builds are reproducible,
- assets are organized,
- QA can verify changes,
- you can approve everything from a single leadership position.


## Final Rule

You are not trying to make many random bots. You are building one coordinated studio with one CEO, clear departments, and controlled execution.

```

If you want, I can next turn this into a **more advanced version with specialist prompts** for Blender, Unreal, QA, audio, and marketing.


<div align="center">⁂</div>

[^1]: https://docs.apify.com/platform
[^2]: https://docs.apify.com/platform/actors```

