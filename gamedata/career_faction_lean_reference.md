# Career → Faction Lean (DERIVED REFERENCE — not canon data)

> DERIVED / INFERRED reference for review. NOT a data edit to the 272 career files.
> Source basis: Vault Book 8 division→faction examples (Division I sample rows) +
> career category semantics. Use to seed `UR3ALSaveGame::FactionRep` or to validate
> flavor consistency. Owner decision needed (Chronos) before treating as canonical.

## Method
Each career's `job__<division>__*.js` prefix maps to a division. Book 8 gives explicit
faction leans for several Division I careers; the rest are inferred from division purpose.
Marked [CONFIRMED] where Book 8 states it, [INFERRED] otherwise.

## Division → lean table
| Division | Inferred primary lean | Basis |
|----------|----------------------|-------|
| Government & Administration | Aegis Concord / N3T Dominion | [CONFIRMED] Book 8 Div I (Digital Admin→Aegis, Policy Architect→Aegis/N3T, Ambassador→N3T, Treasury→N3T, Ethics Comm→Celestial) |
| Cybersecurity | N3T Dominion (defense) / Undernet Syndicate (offense) | [INFERRED] from Penetration Tester / Blackhat Broker split |
| IT | N3T Dominion | [INFERRED] |
| Science Research | Celestial Order (Archive) | [INFERRED] |
| Engineering | Aegis Concord | [INFERRED] |
| Medical / Biosystem | Celestial Order | [INFERRED] |
| Military & Defense | Aegis Concord | [INFERRED] |
| Economics & Trade | N3T Dominion | [INFERMED] |
| Space Operations | N3T Dominion / Celestial Order | [INFERRED] |
| Transportation & Logistics | Aegis Concord | [INFERRED] |
| Agriculture & Biosphere | Free Grid Collective | [INFERRED] |
| Artificial Intelligence | Celestial Order (Oracle) / Undernet (rogue) | [INFERRED] |
| Exploration | Free Grid Collective | [INFERRED] |
| Entertainment & Arts | Free Grid Collective | [INFERRED] |
| Education | Celestial Order | [INFERRED] |
| Construction | Aegis Concord | [INFERRED] |
| Communications & Media | N3T Dominion | [INFERRED] |
| Law & Justice | Aegis Concord / Celestial Order | [INFERRED] |
| Intelligence | Undernet Syndicate / N3T Dominion | [INFERRED] |
| Abyssal / Deep | Abyssal Covenant | [INFERMED] from category name |

## Caveat
This is a *starting lean* only. Per Book 8, Soul State + story flags shift lean across a
campaign; the career's fixed starting faction is what this table estimates. 173/252
careers already name a canon element in flavor; 0 have conflicting faction mentions
(see OVERNIGHT_LOG cp02). No career data was modified to produce this reference.
