# Battle Grid System

Battlefield layout and implementation reference for NETAdmin.EXE.

## Battlefield dimensions

- **Total grid:** 8 columns × 4 rows
- **Player side:** columns 0–3 (4×4)
- **Enemy side:** columns 4–7 (4×4)
- **Center line:** between columns 3 and 4

Implementation: `godot_project/scripts/combat/battle_grid.gd`

## Tile rules

- One small unit per tile unless a large/boss footprint is defined.
- Broken tiles cannot be entered.
- Units on destroyed tiles are pushed to the nearest valid tile.
- Terrain type affects movement, DOT, and healing.

## Movement

- Each NetP has a movement value (tiles per action).
- Movement range is previewed before commit (`get_reachable`).
- Cannot pass through occupied tiles unless a Program allows it.

## Attack types

Action families: Shoot, Slash, Blast, Pierce, Throw, Burst, Beam, Guard, Shield, Brace, Reflect, Absorb, Push, Pull, Swap, Teleport, Bind, Disable, Special.

Weapon styles: Short sword, Long sword, Heavy sword, Wave sword, Dash sword, Break sword.

## Range display

- **Cyan** — movement range (battle arena prototype)
- **Magenta** — attack shape preview
- Shapes resolved by `attack_shape_resolver.gd`

## Sprite fitment

- Idle fits tile silhouette.
- Attacks align to facing direction.
- Guard = crossed arms block pose.
- Barrier = arms outward + barrier HP overlay.
- Projectiles originate from a defined body anchor.

## Special move patterns

- Line (long sword — 4 tiles ahead)
- Wide row (wide sword — 4 across front row)
- Cross, cone, full row
- NetP-specific specials defined on character cards

## Guard and cover

- **Guard:** damage reduction, normal block pose.
- **Barrier:** separate HP pool; sub-threshold hits ignored; cracks below 50%; breaks at 0.

Implementation: `barrier_tracker.gd`

## Large unit rules

- 2×1, 2×2, or custom footprints (planned).
- Footprint affects targeting and positioning priority.

## Turn flow

1. Start turn  
2. Select unit  
3. Preview move / attack  
4. Resolve Program  
5. Apply terrain + status ticks  
6. End turn  

## Prototype scene

Run `godot_project/scenes/combat/battle_arena.tscn` to test movement and long-sword preview.

---

# Battle Actions, Status Effects, and Terrain

## Attack shape rules

### Sword attacks
- **Long sword:** 4 tiles straight ahead.
- **Wide sword:** 4 tiles across the row in front.
- Other styles: diagonal, arc, dash, multi-hit.

### Bomb attacks
- Default bomb lands 4 tiles forward.
- **Locator bombs** target highest-HP enemy directly.

### Ranged attacks
- Visible tile path or impact zone required.

## Guard and barrier rules

See barrier HP threshold logic in `barrier_tracker.gd`.

## Special moves

- NetP-specific; described on each character card.
- May use line, cone, cross, zone, or summon patterns.

## Status effects

| Terrain | Effect |
|---------|--------|
| Fire | 10 HP/sec DOT |
| Poison | 30 HP per 5 sec |
| Water/Mud | Slow movement |
| Metal | Normal movement |
| Grass/Nature/Earth | Heal on stand |
| Void | Ghost spawns (planned) |
| Wind | Push/pull |
| Light | One-time 100 HP barrier per battle |
| Dark | Strong buffs for dark-tier units |
| Time | Restores broken cells (not direct player effect) |

Implementation: `status_effect_system.gd`, `terrain_system.gd`

## Broken cell rules

- Cannot move onto broken tiles.
- Occupied broken tiles push unit to adjacent valid tile.
- Time terrain can restore broken tiles.

## Design priority

1. Grid movement ✓  
2. Basic attack shapes ✓  
3. Guard and barrier ✓  
4. Terrain damage and healing ✓  
5. Status timers ✓  
6. Broken tile logic ✓  
7. Special move card definitions  
8. Advanced terrain + void ghosts  
