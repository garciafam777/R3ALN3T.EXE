class_name StatusEffectSystem
extends RefCounted

const TERRAIN_DOT := {
	"fire": {"damage": 10, "interval": 1.0},
	"poison": {"damage": 30, "interval": 5.0},
}

var unit_effects: Dictionary = {}
var light_barrier_used: Dictionary = {}


func apply_terrain_tick(unit_id: String, terrain: String, delta: float) -> int:
	if not TERRAIN_DOT.has(terrain):
		return 0
	var spec: Dictionary = TERRAIN_DOT[terrain]
	if not unit_effects.has(unit_id):
		unit_effects[unit_id] = {"terrain": terrain, "timer": 0.0}
	var fx: Dictionary = unit_effects[unit_id]
	fx["timer"] = float(fx.get("timer", 0.0)) + delta
	if fx["timer"] >= float(spec["interval"]):
		fx["timer"] = 0.0
		return int(spec["damage"])
	return 0


func movement_modifier(terrain: String) -> float:
	match terrain:
		"water", "mud":
			return 0.7
		_:
			return 1.0


func heal_modifier(terrain: String) -> int:
	if terrain in ["grass", "nature", "earth"]:
		return 5
	return 0


func try_light_barrier(unit_id: String, terrain: String) -> int:
	if terrain != "light" or light_barrier_used.get(unit_id, false):
		return 0
	light_barrier_used[unit_id] = true
	return 100
