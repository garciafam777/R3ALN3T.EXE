extends Control
class_name BattleArena

## Visual prototype for the 8×4 mirrored battle grid.

var _grid: BattleGrid
var _terrain: TerrainSystem
var _barriers: BarrierTracker
var _status: StatusEffectSystem
var _cell_size := Vector2(72, 72)
var _cells: Dictionary = {}
var _selected_unit: String = "player_1"
var _reachable: Array = []
var _attack_preview: Array = []


func _ready() -> void:
	_grid = BattleGrid.new()
	_terrain = TerrainSystem.new(_grid)
	_barriers = BarrierTracker.new()
	_status = StatusEffectSystem.new()
	_build_ui()
	_grid.place_unit("player_1", Vector2i(1, 1), BattleConstants.Side.PLAYER)
	_grid.place_unit("enemy_1", Vector2i(5, 2), BattleConstants.Side.ENEMY)
	_refresh_all()
	_grid.tile_changed.connect(func(_c): _refresh_all())
	CreatorTheme.set_test_id(self, "battle-arena")


func _build_ui() -> void:
	set_anchors_preset(Control.PRESET_FULL_RECT)
	var bg := ColorRect.new()
	bg.set_anchors_preset(Control.PRESET_FULL_RECT)
	bg.color = CreatorTheme.BG_DARK
	add_child(bg)
	var center := CenterContainer.new()
	center.set_anchors_preset(Control.PRESET_FULL_RECT)
	add_child(center)
	var panel := GridContainer.new()
	panel.columns = BattleConstants.GRID_COLS
	center.add_child(panel)
	for y in BattleConstants.GRID_ROWS:
		for x in BattleConstants.GRID_COLS:
			var coord := Vector2i(x, y)
			var btn := Button.new()
			btn.custom_minimum_size = _cell_size
			btn.pressed.connect(_on_cell_pressed.bind(coord))
			panel.add_child(btn)
			_cells[coord] = btn
	var hud := Label.new()
	hud.name = "HudLabel"
	hud.set_anchors_preset(Control.PRESET_BOTTOM_WIDE)
	hud.offset_top = -48
	hud.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	hud.label_settings = CreatorTheme.label_settings(get_viewport_rect().size, 14, CreatorTheme.ACCENT_CYAN)
	add_child(hud)


func _on_cell_pressed(coord: Vector2i) -> void:
	if coord in _reachable:
		_grid.move_unit(_selected_unit, coord)
		_reachable.clear()
		_attack_preview.clear()
	elif _attack_preview.has(coord):
		$HudLabel.text = "Attack hit tile %s" % coord
		_attack_preview.clear()
	else:
		_reachable = _grid.get_reachable(
			_grid.units[_selected_unit]["coord"],
			int(_grid.units[_selected_unit].get("movement", 2)),
			BattleConstants.Side.PLAYER
		)
		var origin: Vector2i = _grid.units[_selected_unit]["coord"]
		_attack_preview = AttackShapeResolver.tiles_for_move(origin, Vector2i.RIGHT, "long_sword_line", _grid)
		$HudLabel.text = "Move (cyan) / Attack preview (magenta)"


func _refresh_all() -> void:
	for coord in _cells:
		var btn: Button = _cells[coord]
		var tile := _grid.get_tile(coord)
		var label := ""
		if tile.occupant_id:
			label = tile.occupant_id.substr(0, 1).to_upper()
		btn.text = label if not label.is_empty() else "·"
		if coord.x == BattleConstants.CENTER_LINE_COL or coord.x == BattleConstants.ENEMY_COL_START:
			btn.modulate = Color(0.5, 0.5, 0.6)
		elif tile.is_broken():
			btn.modulate = Color(0.3, 0.1, 0.1)
		elif coord in _attack_preview:
			btn.modulate = CreatorTheme.ACCENT_MAGENTA
		elif coord in _reachable:
			btn.modulate = CreatorTheme.ACCENT_CYAN
		elif tile.side == BattleConstants.Side.PLAYER:
			btn.modulate = Color(0.4, 0.7, 1.0)
		else:
			btn.modulate = Color(1.0, 0.4, 0.5)
