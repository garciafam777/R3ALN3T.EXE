class_name BattleTile
extends RefCounted

var coord: Vector2i = Vector2i.ZERO
var side: int = BattleConstants.Side.NEUTRAL
var terrain: String = "metal"
var state: int = BattleConstants.TileState.INTACT
var occupant_id: String = ""
var footprint_origin: bool = true


func is_walkable() -> bool:
	return state == BattleConstants.TileState.INTACT and occupant_id.is_empty()


func is_broken() -> bool:
	return state == BattleConstants.TileState.BROKEN
