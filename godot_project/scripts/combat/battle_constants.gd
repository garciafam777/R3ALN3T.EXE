class_name BattleConstants
extends RefCounted

## Fixed mirrored battlefield: 8 columns × 4 rows (4×4 player + 4×4 enemy).

const GRID_COLS := 8
const GRID_ROWS := 4
const PLAYER_COLS := 4
const ENEMY_COL_START := 4
const CENTER_LINE_COL := 3

enum Side { PLAYER, ENEMY, NEUTRAL }
enum TileState { INTACT, BROKEN, RESTORING }
enum MoveFamily {
	SHOOT, SLASH, BLAST, PIERCE, THROW, BURST, BEAM,
	GUARD, SHIELD, BRACE, REFLECT, ABSORB,
	PUSH, PULL, SWAP, TELEPORT, BIND, DISABLE,
	SPECIAL
}

enum WeaponStyle {
	SHORT_SWORD, LONG_SWORD, HEAVY_SWORD, WAVE_SWORD, DASH_SWORD, BREAK_SWORD
}
