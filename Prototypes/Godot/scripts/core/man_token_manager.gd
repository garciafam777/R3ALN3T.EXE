extends Node

signal balance_changed(gold: int, blue: int, red: int, total: int)
signal transaction_logged(entry: Dictionary)

var gold: int = 0
var blue: int = 0
var red: int = 0
var transaction_log: Array = []


func _ready() -> void:
	gold = 120
	blue = 200
	red = 80
	_emit_balance()


func total_balance() -> int:
	return gold + blue + red


func credit(strand: String, amount: int, reason: String = "") -> void:
	match strand:
		"gold": gold += amount
		"blue": blue += amount
		"red": red += amount
	_log(strand, amount, reason, "credit")
	_emit_balance()


func debit(strand: String, amount: int, reason: String = "") -> bool:
	match strand:
		"gold":
			if gold < amount: return false
			gold -= amount
		"blue":
			if blue < amount: return false
			blue -= amount
		"red":
			if red < amount: return false
			red -= amount
		_:
			return false
	_log(strand, -amount, reason, "debit")
	_emit_balance()
	return true


func load_from_save(state: Dictionary) -> void:
	var strands: Dictionary = state.get("man_strands", {})
	if not strands.is_empty():
		gold = int(strands.get("gold", gold))
		blue = int(strands.get("blue", blue))
		red = int(strands.get("red", red))
	elif state.has("man_balance"):
		blue = int(state.get("man_balance", blue))
	_emit_balance()


func to_save_fragment() -> Dictionary:
	return {"man_balance": total_balance(), "man_strands": {"gold": gold, "blue": blue, "red": red}}


func _log(strand: String, amount: int, reason: String, kind: String) -> void:
	var entry := {"time": Time.get_datetime_string_from_system(), "strand": strand, "amount": amount, "reason": reason, "kind": kind}
	transaction_log.append(entry)
	if transaction_log.size() > 50:
		transaction_log.pop_front()
	transaction_logged.emit(entry)


func _emit_balance() -> void:
	balance_changed.emit(gold, blue, red, total_balance())
