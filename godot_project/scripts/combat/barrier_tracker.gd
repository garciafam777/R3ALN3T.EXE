class_name BarrierTracker
extends RefCounted

signal barrier_damaged(unit_id: String, hp: int, max_hp: int)
signal barrier_broken(unit_id: String)

var barriers: Dictionary = {}


func create_barrier(unit_id: String, max_hp: int, threshold: int = 0) -> void:
	barriers[unit_id] = {
		"hp": max_hp,
		"max_hp": max_hp,
		"threshold": threshold if threshold > 0 else max_hp,
		"cracked": false
	}


func apply_damage(unit_id: String, damage: int) -> int:
	if not barriers.has(unit_id):
		return damage
	var b: Dictionary = barriers[unit_id]
	if damage < int(b["threshold"]):
		return 0
	var overflow := maxi(0, damage - int(b["hp"]))
	b["hp"] = maxi(0, int(b["hp"]) - damage)
	if float(b["hp"]) / float(b["max_hp"]) < 0.5:
		b["cracked"] = true
	barrier_damaged.emit(unit_id, b["hp"], b["max_hp"])
	if b["hp"] <= 0:
		barriers.erase(unit_id)
		barrier_broken.emit(unit_id)
		return overflow
	return 0
