class_name AttackShapeResolver
extends RefCounted

static func tiles_for_move(origin: Vector2i, facing: Vector2i, shape: String, grid: BattleGrid) -> Array:
	match shape:
		"long_sword_line":
			return _line_forward(origin, facing, 4, grid)
		"wide_sword_row":
			return _wide_row(origin, facing, 4, grid)
		"bomb_default":
			return _line_forward(origin, facing, 4, grid)
		"cross":
			return _cross(origin, grid)
		"cone":
			return _cone(origin, facing, grid)
		"full_row":
			return _full_row(origin.y, grid)
		_:
			return _adjacent(origin, grid)


static func _line_forward(origin: Vector2i, facing: Vector2i, length: int, grid: BattleGrid) -> Array:
	var tiles: Array = []
	var pos := origin + facing
	for _i in length:
		if not grid.in_bounds(pos):
			break
		tiles.append(pos)
		pos += facing
	return tiles


static func _wide_row(origin: Vector2i, facing: Vector2i, width: int, grid: BattleGrid) -> Array:
	var tiles: Array = []
	var front := origin + facing
	var lateral := Vector2i(-facing.y, facing.x)
	var half := width / 2
	for i in range(-half, half + 1):
		var pos := front + lateral * i
		if grid.in_bounds(pos):
			tiles.append(pos)
	return tiles


static func _adjacent(origin: Vector2i, grid: BattleGrid) -> Array:
	var tiles: Array = []
	for offset in [Vector2i.LEFT, Vector2i.RIGHT, Vector2i.UP, Vector2i.DOWN]:
		var pos := origin + offset
		if grid.in_bounds(pos):
			tiles.append(pos)
	return tiles


static func _cross(origin: Vector2i, grid: BattleGrid) -> Array:
	var tiles: Array = [origin]
	for offset in [Vector2i.LEFT, Vector2i.RIGHT, Vector2i.UP, Vector2i.DOWN]:
		var pos := origin + offset
		if grid.in_bounds(pos):
			tiles.append(pos)
	return tiles


static func _cone(origin: Vector2i, facing: Vector2i, grid: BattleGrid) -> Array:
	var tiles: Array = _line_forward(origin, facing, 2, grid)
	var lateral := Vector2i(-facing.y, facing.x)
	for pos in tiles.duplicate():
		for side in [-1, 1]:
			var p := pos + lateral * side
			if grid.in_bounds(p) and p not in tiles:
				tiles.append(p)
	return tiles


static func _full_row(row: int, grid: BattleGrid) -> Array:
	var tiles: Array = []
	for x in BattleConstants.GRID_COLS:
		var pos := Vector2i(x, row)
		if grid.in_bounds(pos):
			tiles.append(pos)
	return tiles
