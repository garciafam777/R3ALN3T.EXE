extends Control
class_name CustomizerGrid

## Tiered synergy grid (4x4 → 8x8) with block placement, bug heat, and color rules.

signal grid_updated
signal token_placed(token: CustomizerGridToken, grid_position: Vector2i)
signal token_removed(token: CustomizerGridToken, grid_position: Vector2i)
signal bug_heat_changed(heat: float)
signal validation_changed(is_valid: bool, messages: Array)

const TIER_SIZES := {
	1: Vector2i(4, 4),
	2: Vector2i(5, 5),
	3: Vector2i(6, 6),
	4: Vector2i(7, 7),
	5: Vector2i(8, 8),
}

const MAX_BUG_HEAT := 100.0
const HEAT_PER_VIOLATION := 12.0
const HEAT_DECAY_ON_VALID := 4.0

@export var unlock_tier: int = 3
@export var cell_size: Vector2 = Vector2(64, 64)

var grid_size: Vector2i = Vector2i(6, 6)
var grid: Array = []
var placed_tokens: Dictionary = {}
var active_bonuses: Dictionary = {}
var bug_heat: float = 0.0
var validation_messages: Array[String] = []

var synergy_patterns := {
	"line_horizontal": {"required": 3, "bonus": {"atk": 10, "rapid": 5}},
	"line_vertical": {"required": 3, "bonus": {"def": 10, "hp": 20}},
	"square_2x2": {"required": 4, "bonus": {"atk": 15, "def": 15}},
	"cross": {"required": 5, "bonus": {"charge": 10}},
	"same_type_adjacent": {"required": 2, "bonus": {"atk": 5}},
	"same_element_adjacent": {"required": 2, "bonus": {"atk": 8}},
}


func _ready() -> void:
	set_unlock_tier(unlock_tier)
	print("Customizer Grid initialized — %dx%d (tier %d)" % [grid_size.x, grid_size.y, unlock_tier])


func set_unlock_tier(tier: int) -> void:
	unlock_tier = clampi(tier, 1, 5)
	grid_size = TIER_SIZES[unlock_tier]
	_initialize_grid()
	grid_updated.emit()


func can_place_token(token: CustomizerGridToken, grid_position: Vector2i) -> Dictionary:
	var result := {"ok": false, "reason": ""}
	if token == null:
		result["reason"] = "No token selected."
		return result
	if not _is_valid_position(grid_position):
		result["reason"] = "Out of grid bounds."
		return result
	if grid[grid_position.x][grid_position.y] != null:
		result["reason"] = "Cell occupied."
		return result
	if _is_color_conflict(token, grid_position):
		result["reason"] = "Color clash — adjacent matching primaries forbidden."
		return result
	if _is_duplicate_id(token):
		result["reason"] = "NetP already on grid."
		return result
	if _violates_center_line(grid_position):
		result["reason"] = "Cannot place on the center symmetry line."
		return result
	result["ok"] = true
	return result


func _violates_center_line(position: Vector2i) -> bool:
	if grid_size.x % 2 == 0:
		return false
	var center_x := grid_size.x / 2
	return position.x == center_x


func place_token(token: CustomizerGridToken, grid_position: Vector2i) -> bool:
	var check := can_place_token(token, grid_position)
	if not check["ok"]:
		_add_bug_heat(HEAT_PER_VIOLATION, str(check["reason"]))
		_validate()
		return false
	grid[grid_position.x][grid_position.y] = token
	placed_tokens[grid_position] = token
	_reduce_bug_heat(HEAT_DECAY_ON_VALID)
	token_placed.emit(token, grid_position)
	_calculate_bonuses()
	_validate()
	grid_updated.emit()
	return true


func remove_token(grid_position: Vector2i) -> CustomizerGridToken:
	if not _is_valid_position(grid_position):
		return null
	var token: CustomizerGridToken = grid[grid_position.x][grid_position.y]
	if token == null:
		return null
	grid[grid_position.x][grid_position.y] = null
	placed_tokens.erase(grid_position)
	token_removed.emit(token, grid_position)
	_calculate_bonuses()
	_validate()
	grid_updated.emit()
	return token


func _initialize_grid() -> void:
	grid = []
	for x in grid_size.x:
		var column: Array = []
		for y in grid_size.y:
			column.append(null)
		grid.append(column)
	placed_tokens.clear()
	active_bonuses.clear()
	bug_heat = 0.0
	validation_messages.clear()
	bug_heat_changed.emit(bug_heat)


func _is_valid_position(position: Vector2i) -> bool:
	return position.x >= 0 and position.x < grid_size.x and position.y >= 0 and position.y < grid_size.y


func _is_duplicate_id(token: CustomizerGridToken) -> bool:
	for pos in placed_tokens:
		var existing: CustomizerGridToken = placed_tokens[pos]
		if existing.id == token.id and not token.id.is_empty():
			return true
	return false


func _is_color_conflict(token: CustomizerGridToken, position: Vector2i) -> bool:
	for offset in [Vector2i.LEFT, Vector2i.RIGHT, Vector2i.UP, Vector2i.DOWN]:
		var neighbor_pos := position + offset
		if not _is_valid_position(neighbor_pos):
			continue
		var neighbor: CustomizerGridToken = grid[neighbor_pos.x][neighbor_pos.y]
		if neighbor == null:
			continue
		if neighbor.primary_color.to_html(false) == token.primary_color.to_html(false):
			return true
	return false


func _add_bug_heat(amount: float, reason: String = "") -> void:
	bug_heat = clampf(bug_heat + amount, 0.0, MAX_BUG_HEAT)
	if not reason.is_empty() and reason not in validation_messages:
		validation_messages.append(reason)
	bug_heat_changed.emit(bug_heat)


func _reduce_bug_heat(amount: float) -> void:
	bug_heat = clampf(bug_heat - amount, 0.0, MAX_BUG_HEAT)
	bug_heat_changed.emit(bug_heat)


func _calculate_bonuses() -> void:
	active_bonuses.clear()
	for y in grid_size.y:
		var consecutive := 0
		for x in grid_size.x:
			if grid[x][y] != null:
				consecutive += 1
			else:
				consecutive = 0
			if consecutive >= synergy_patterns["line_horizontal"]["required"]:
				_apply_synergy("line_horizontal")
	for x in grid_size.x:
		var consecutive := 0
		for y in grid_size.y:
			if grid[x][y] != null:
				consecutive += 1
			else:
				consecutive = 0
			if consecutive >= synergy_patterns["line_vertical"]["required"]:
				_apply_synergy("line_vertical")
	for x in range(grid_size.x - 1):
		for y in range(grid_size.y - 1):
			var count := 0
			for dx in 2:
				for dy in 2:
					if grid[x + dx][y + dy] != null:
						count += 1
			if count >= synergy_patterns["square_2x2"]["required"]:
				_apply_synergy("square_2x2")
	for x in range(1, grid_size.x - 1):
		for y in range(1, grid_size.y - 1):
			var count := 0
			for delta in [Vector2i.ZERO, Vector2i.UP, Vector2i.DOWN, Vector2i.LEFT, Vector2i.RIGHT]:
				if grid[x + delta.x][y + delta.y] != null:
					count += 1
			if count >= synergy_patterns["cross"]["required"]:
				_apply_synergy("cross")
	for pos in placed_tokens:
		var token: CustomizerGridToken = placed_tokens[pos]
		for offset in [Vector2i.LEFT, Vector2i.RIGHT, Vector2i.UP, Vector2i.DOWN]:
			var npos := pos + offset
			if not _is_valid_position(npos):
				continue
			var neighbor: CustomizerGridToken = grid[npos.x][npos.y]
			if neighbor == null:
				continue
			if neighbor.type == token.type:
				_apply_synergy("same_type_adjacent")
			if neighbor.element == token.element:
				_apply_synergy("same_element_adjacent")


func _apply_synergy(pattern_name: String) -> void:
	var pattern: Dictionary = synergy_patterns[pattern_name]
	if not active_bonuses.has(pattern_name):
		active_bonuses[pattern_name] = pattern["bonus"].duplicate()
	else:
		for stat in pattern["bonus"]:
			active_bonuses[pattern_name][stat] = int(active_bonuses[pattern_name].get(stat, 0)) + int(pattern["bonus"][stat])


func get_total_bonuses() -> Dictionary:
	var total := {"atk": 0, "def": 0, "hp": 0, "rapid": 0, "charge": 0}
	for pattern_name in active_bonuses:
		for stat in active_bonuses[pattern_name]:
			if total.has(stat):
				total[stat] = int(total[stat]) + int(active_bonuses[pattern_name][stat])
	return total


func _validate() -> void:
	validation_messages.clear()
	var ok := true
	if bug_heat >= 75.0:
		validation_messages.append("Bug heat critical — stabilize before saving.")
		ok = false
	elif bug_heat >= 40.0:
		validation_messages.append("Elevated bug heat — review placements.")
	if placed_tokens.is_empty():
		validation_messages.append("Place at least one NetP on the grid.")
		ok = false
	validation_changed.emit(ok, validation_messages)


func is_valid_for_save() -> bool:
	return bug_heat < 75.0 and not placed_tokens.is_empty()


func save_grid_state() -> Dictionary:
	var entries: Array = []
	for pos in placed_tokens:
		entries.append({
			"position": {"x": pos.x, "y": pos.y},
			"token": placed_tokens[pos].to_dict()
		})
	return {
		"unlock_tier": unlock_tier,
		"placed": entries,
		"active_bonuses": active_bonuses.duplicate(true),
		"bug_heat": bug_heat
	}


func load_grid_state(state: Dictionary) -> void:
	if state.has("unlock_tier"):
		set_unlock_tier(int(state["unlock_tier"]))
	else:
		_initialize_grid()
	for entry in state.get("placed", []):
		var pos := Vector2i(entry["position"]["x"], entry["position"]["y"])
		var token := CustomizerGridToken.from_dict(entry.get("token", {}))
		if _is_valid_position(pos):
			grid[pos.x][pos.y] = token
			placed_tokens[pos] = token
	bug_heat = float(state.get("bug_heat", 0.0))
	active_bonuses = state.get("active_bonuses", {}).duplicate(true)
	bug_heat_changed.emit(bug_heat)
	_validate()
	grid_updated.emit()
