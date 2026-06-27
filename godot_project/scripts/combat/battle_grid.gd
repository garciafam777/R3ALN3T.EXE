class_name BattleGrid
extends RefCounted

signal tile_changed(coord: Vector2i)
signal unit_moved(unit_id: String, from: Vector2i, to: Vector2i)

var tiles: Array = []
var units: Dictionary = {}


func _init() -> void:
	_build_grid()


func _build_grid() -> void:
	tiles.clear()
	for x in BattleConstants.GRID_COLS:
		var col: Array = []
		for y in BattleConstants.GRID_ROWS:
			var tile := BattleTile.new()
			tile.coord = Vector2i(x, y)
			tile.side = BattleConstants.Side.PLAYER if x < BattleConstants.PLAYER_COLS else BattleConstants.Side.ENEMY
			col.append(tile)
		tiles.append(col)


func in_bounds(coord: Vector2i) -> bool:
	return coord.x >= 0 and coord.x < BattleConstants.GRID_COLS and coord.y >= 0 and coord.y < BattleConstants.GRID_ROWS


func get_tile(coord: Vector2i) -> BattleTile:
	if not in_bounds(coord):
		return null
	return tiles[coord.x][coord.y]


func place_unit(unit_id: String, coord: Vector2i, side: int) -> bool:
	var tile := get_tile(coord)
	if tile == null or not tile.is_walkable():
		return false
	if side == BattleConstants.Side.PLAYER and coord.x >= BattleConstants.ENEMY_COL_START:
		return false
	if side == BattleConstants.Side.ENEMY and coord.x < BattleConstants.ENEMY_COL_START:
		return false
	tile.occupant_id = unit_id
	units[unit_id] = {"coord": coord, "side": side, "movement": 2}
	tile_changed.emit(coord)
	return true


func move_unit(unit_id: String, target: Vector2i) -> bool:
	if not units.has(unit_id):
		return false
	var info: Dictionary = units[unit_id]
	var from: Vector2i = info["coord"]
	var reachable: Array = get_reachable(from, int(info.get("movement", 1)), int(info["side"]))
	if target not in reachable:
		return false
	get_tile(from).occupant_id = ""
	get_tile(target).occupant_id = unit_id
	units[unit_id]["coord"] = target
	unit_moved.emit(unit_id, from, target)
	tile_changed.emit(from)
	tile_changed.emit(target)
	return true


func get_reachable(start: Vector2i, movement: int, side: int) -> Array:
	var results: Array = []
	var visited: Dictionary = {}
	var queue: Array = [{"pos": start, "cost": 0}]
	while not queue.is_empty():
		var node: Dictionary = queue.pop_front()
		var pos: Vector2i = node["pos"]
		var cost: int = node["cost"]
		var key := "%d,%d" % [pos.x, pos.y]
		if visited.has(key):
			continue
		visited[key] = true
		if cost > 0:
			results.append(pos)
		if cost >= movement:
			continue
		for offset in [Vector2i.LEFT, Vector2i.RIGHT, Vector2i.UP, Vector2i.DOWN]:
			var next := pos + offset
			var tile := get_tile(next)
			if tile == null or not tile.is_walkable():
				continue
			if side == BattleConstants.Side.PLAYER and next.x >= BattleConstants.ENEMY_COL_START:
				continue
			if side == BattleConstants.Side.ENEMY and next.x < BattleConstants.ENEMY_COL_START:
				continue
			queue.append({"pos": next, "cost": cost + 1})
	return results


func break_tile(coord: Vector2i) -> void:
	var tile := get_tile(coord)
	if tile == null:
		return
	if not tile.occupant_id.is_empty():
		_push_unit_off_broken(coord, tile.occupant_id)
	tile.state = BattleConstants.TileState.BROKEN
	tile_changed.emit(coord)


func restore_tile(coord: Vector2i) -> void:
	var tile := get_tile(coord)
	if tile == null:
		return
	tile.state = BattleConstants.TileState.INTACT
	tile_changed.emit(coord)


func _push_unit_off_broken(coord: Vector2i, unit_id: String) -> void:
	for offset in [Vector2i.UP, Vector2i.DOWN, Vector2i.LEFT, Vector2i.RIGHT]:
		var dest := coord + offset
		var tile := get_tile(dest)
		if tile and tile.is_walkable():
			units[unit_id]["coord"] = dest
			tile.occupant_id = unit_id
			get_tile(coord).occupant_id = ""
			unit_moved.emit(unit_id, coord, dest)
			return
