class_name TerrainSystem
extends RefCounted

signal terrain_changed(coord: Vector2i, terrain: String)

var grid: BattleGrid


func _init(battle_grid: BattleGrid) -> void:
	grid = battle_grid


func set_terrain(coord: Vector2i, terrain: String) -> void:
	var tile := grid.get_tile(coord)
	if tile == null:
		return
	tile.terrain = terrain
	terrain_changed.emit(coord, terrain)


func apply_time_restore(coord: Vector2i) -> void:
	var tile := grid.get_tile(coord)
	if tile and tile.is_broken():
		grid.restore_tile(coord)
