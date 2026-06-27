extends Control
class_name PersonaCustomizer

## Persona Customizer — tiered grid placement with Kernal/MOD device themes.

signal layout_saved(state: Dictionary)
signal customizer_closed

const SCENE_PATH := "res://scenes/persona_customizer/persona_customizer.tscn"

var _viewport_size: Vector2
var _device_manager: DeviceManager = null
var _grid_logic: CustomizerGrid
var _grid_visual: GridContainer
var _cell_buttons: Dictionary = {}
var _roster_list: ItemList
var _heat_bar: ProgressBar
var _bonus_label: Label
var _status_label: Label
var _selected_token: CustomizerGridToken = null
var _is_mod_theme: bool = false
var _mod_detail_label: Label
var _block_list: ItemList
var _preview_portrait: TextureRect
var _preview_label: Label
var _glitch_overlay: ColorRect
var _glitch_timer: float = 0.0


func _ready() -> void:
	_viewport_size = get_viewport_rect().size
	set_anchors_preset(Control.PRESET_FULL_RECT)
	_grid_logic = CustomizerGrid.new()
	add_child(_grid_logic)
	_build_ui()
	_load_roster()
	_grid_logic.grid_updated.connect(_refresh_grid_visual)
	_grid_logic.bug_heat_changed.connect(_on_heat_changed)
	_grid_logic.validation_changed.connect(_on_validation_changed)
	get_viewport().size_changed.connect(_on_viewport_resized)
	CreatorTheme.set_test_id(self, "persona-customizer")


func _process(delta: float) -> void:
	if _glitch_overlay == null:
		return
	if _grid_logic.bug_heat >= 40.0:
		_glitch_timer += delta
		_glitch_overlay.visible = int(_glitch_timer * 10) % 2 == 0
		_glitch_overlay.color.a = clampf(_grid_logic.bug_heat / 100.0, 0.15, 0.45)
	else:
		_glitch_overlay.visible = false


func get_token_at_cell(pos: Vector2i) -> CustomizerGridToken:
	return _grid_logic.get_token_at(pos)


func handle_drop(data: Dictionary, target_pos: Vector2i) -> void:
	var token: CustomizerGridToken = data.get("token")
	if token == null:
		return
	if data.has("from_pos"):
		var from: Vector2i = data["from_pos"]
		if from != target_pos:
			_grid_logic.remove_token(from)
	var copy := CustomizerGridToken.new()
	copy.id = token.id
	copy.display_name = token.display_name
	copy.tier = token.tier
	copy.type = token.type
	copy.element = token.element
	copy.primary_color = token.primary_color
	copy.secondary_color = token.secondary_color
	if _grid_logic.place_token(copy, target_pos):
		_refresh_grid_visual()
		_update_preview_from_grid()


func set_device_manager(manager: DeviceManager) -> void:
	_device_manager = manager
	_is_mod_theme = manager != null and manager.is_mod()
	_apply_device_theme()


func load_layout(state: Dictionary) -> void:
	_grid_logic.load_grid_state(state)


func _build_ui() -> void:
	var bg := ColorRect.new()
	bg.set_anchors_preset(Control.PRESET_FULL_RECT)
	bg.color = CreatorTheme.BG_DARK
	add_child(bg)

	var margin := MarginContainer.new()
	margin.set_anchors_preset(Control.PRESET_FULL_RECT)
	margin.add_theme_constant_override("margin_left", CreatorTheme.spacing(_viewport_size, 20))
	margin.add_theme_constant_override("margin_right", CreatorTheme.spacing(_viewport_size, 20))
	margin.add_theme_constant_override("margin_top", CreatorTheme.spacing(_viewport_size, 16))
	margin.add_theme_constant_override("margin_bottom", CreatorTheme.spacing(_viewport_size, 16))
	add_child(margin)

	var root := VBoxContainer.new()
	root.set_anchors_preset(Control.PRESET_FULL_RECT)
	root.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 10))
	margin.add_child(root)

	var header := Label.new()
	header.text = "PERSONA CUSTOMIZER"
	header.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	header.label_settings = CreatorTheme.label_settings(_viewport_size, 24, CreatorTheme.ACCENT_CYAN)
	root.add_child(header)

	var body := HBoxContainer.new()
	body.size_flags_vertical = Control.SIZE_EXPAND_FILL
	body.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 16))
	root.add_child(body)

	# Roster panel
	var roster_panel := PanelContainer.new()
	roster_panel.custom_minimum_size.x = CreatorTheme.spacing(_viewport_size, 220)
	roster_panel.add_theme_stylebox_override("panel", CreatorTheme.make_panel_style(_viewport_size))
	body.add_child(roster_panel)
	var roster_box := VBoxContainer.new()
	roster_panel.add_child(roster_box)
	var roster_title := Label.new()
	roster_title.text = "NETP ROSTER"
	roster_title.label_settings = CreatorTheme.label_settings(_viewport_size, 14, CreatorTheme.ACCENT_CYAN)
	roster_box.add_child(roster_title)
	_roster_list = ItemList.new()
	_roster_list.size_flags_vertical = Control.SIZE_EXPAND_FILL
	_roster_list.item_selected.connect(_on_roster_selected)
	roster_box.add_child(_roster_list)

	var block_title := Label.new()
	block_title.text = "BLOCK LIBRARY"
	block_title.label_settings = CreatorTheme.label_settings(_viewport_size, 14, CreatorTheme.ACCENT_MAGENTA)
	roster_box.add_child(block_title)
	_block_list = ItemList.new()
	_block_list.custom_minimum_size.y = CreatorTheme.spacing(_viewport_size, 140)
	_block_list.item_selected.connect(_on_block_selected)
	roster_box.add_child(_block_list)
	_load_block_library()

	var preview_title := Label.new()
	preview_title.text = "NETP PREVIEW"
	preview_title.label_settings = CreatorTheme.label_settings(_viewport_size, 14, CreatorTheme.ACCENT_CYAN)
	roster_box.add_child(preview_title)
	_preview_portrait = TextureRect.new()
	_preview_portrait.custom_minimum_size = Vector2(CreatorTheme.spacing(_viewport_size, 100), CreatorTheme.spacing(_viewport_size, 120))
	_preview_portrait.expand_mode = TextureRect.EXPAND_IGNORE_SIZE
	_preview_portrait.stretch_mode = TextureRect.STRETCH_KEEP_ASPECT_CENTERED
	roster_box.add_child(_preview_portrait)
	_preview_label = Label.new()
	_preview_label.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	_preview_label.label_settings = CreatorTheme.label_settings(_viewport_size, 11, CreatorTheme.TEXT_DIM)
	roster_box.add_child(_preview_label)

	# Grid panel
	var grid_panel := PanelContainer.new()
	grid_panel.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	grid_panel.add_theme_stylebox_override("panel", CreatorTheme.make_panel_style(_viewport_size, CreatorTheme.ACCENT_MAGENTA))
	body.add_child(grid_panel)
	var grid_box := VBoxContainer.new()
	grid_panel.add_child(grid_box)
	var grid_title := Label.new()
	grid_title.text = "SYNERGY GRID"
	grid_title.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	grid_title.label_settings = CreatorTheme.label_settings(_viewport_size, 14, CreatorTheme.ACCENT_CYAN)
	grid_box.add_child(grid_title)
	var grid_scroll := ScrollContainer.new()
	grid_scroll.size_flags_vertical = Control.SIZE_EXPAND_FILL
	grid_box.add_child(grid_scroll)
	_grid_visual = GridContainer.new()
	_grid_visual.columns = _grid_logic.grid_size.x
	grid_scroll.add_child(_grid_visual)

	# Stats panel
	var stats_panel := PanelContainer.new()
	stats_panel.custom_minimum_size.x = CreatorTheme.spacing(_viewport_size, 240)
	stats_panel.add_theme_stylebox_override("panel", CreatorTheme.make_panel_style(_viewport_size))
	body.add_child(stats_panel)
	var stats_box := VBoxContainer.new()
	stats_box.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 8))
	stats_panel.add_child(stats_box)
	var heat_lbl := Label.new()
	heat_lbl.text = "BUG HEAT"
	heat_lbl.label_settings = CreatorTheme.label_settings(_viewport_size, 14, CreatorTheme.ERROR_COLOR)
	stats_box.add_child(heat_lbl)
	_heat_bar = ProgressBar.new()
	_heat_bar.max_value = CustomizerGrid.MAX_BUG_HEAT
	_heat_bar.custom_minimum_size.y = CreatorTheme.spacing(_viewport_size, 22)
	stats_box.add_child(_heat_bar)
	_bonus_label = Label.new()
	_bonus_label.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	_bonus_label.label_settings = CreatorTheme.label_settings(_viewport_size, 12, CreatorTheme.TEXT_DIM)
	stats_box.add_child(_bonus_label)
	var tier_row := HBoxContainer.new()
	stats_box.add_child(tier_row)
	for t in range(1, 6):
		var tb := Button.new()
		tb.text = "%d×%d" % [CustomizerGrid.TIER_SIZES[t].x, CustomizerGrid.TIER_SIZES[t].x]
		tb.pressed.connect(func(): _grid_logic.set_unlock_tier(t); _refresh_grid_visual())
		tier_row.add_child(tb)
	_mod_detail_label = Label.new()
	_mod_detail_label.visible = false
	_mod_detail_label.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	_mod_detail_label.label_settings = CreatorTheme.label_settings(_viewport_size, 11, CreatorTheme.ACCENT_MAGENTA)
	stats_box.add_child(_mod_detail_label)

	_status_label = Label.new()
	_status_label.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	_status_label.label_settings = CreatorTheme.label_settings(_viewport_size, 12, CreatorTheme.TEXT_DIM)
	root.add_child(_status_label)

	var actions := HBoxContainer.new()
	actions.alignment = BoxContainer.ALIGNMENT_CENTER
	actions.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 12))
	root.add_child(actions)
	for spec in [["Save Layout", _on_save], ["Clear", _on_clear], ["Close", _on_close]]:
		var btn := Button.new()
		btn.text = spec[0]
		btn.custom_minimum_size.y = CreatorTheme.spacing(_viewport_size, 40)
		btn.pressed.connect(spec[1])
		actions.add_child(btn)

	_refresh_grid_visual()
	_apply_device_theme()

	_glitch_overlay = ColorRect.new()
	_glitch_overlay.set_anchors_preset(Control.PRESET_FULL_RECT)
	_glitch_overlay.mouse_filter = Control.MOUSE_FILTER_IGNORE
	_glitch_overlay.visible = false
	_glitch_overlay.color = Color(1, 0, 1, 0.25)
	add_child(_glitch_overlay)


func _apply_device_theme() -> void:
	if _device_manager == null:
		return
	_is_mod_theme = _device_manager.is_mod()
	var accent := CreatorTheme.ACCENT_MAGENTA if _is_mod_theme else CreatorTheme.ACCENT_CYAN
	if _heat_bar:
		_heat_bar.modulate = accent
	if _mod_detail_label:
		_mod_detail_label.visible = _is_mod_theme
		_mod_detail_label.text = "MOD: synergy logs, tier resize, and heat diagnostics enabled." if _is_mod_theme else ""


func _load_block_library() -> void:
	_block_list.clear()
	for block in CustomizerBlock.library():
		_block_list.add_item("[%s] %s" % [CustomizerBlock.family_name(block.family), block.label])
		_block_list.set_item_metadata(_block_list.item_count - 1, block)


func _on_block_selected(index: int) -> void:
	var block: CustomizerBlock = _block_list.get_item_metadata(index)
	if block:
		_selected_token = block.to_token()
		_status_label.text = "Block selected: %s — drag to grid or click cell" % block.label
		_update_preview(_selected_token)


func _update_preview(token: CustomizerGridToken) -> void:
	if token == null:
		return
	var data := NetPData.new()
	data.name = token.display_name
	data.tier = token.tier
	data.type = token.type
	data.element = token.element
	data.appearance = {"colors": {"primary": token.primary_color.to_html(false), "glow": token.secondary_color.to_html(false)}}
	_preview_portrait.texture = NetPSpriteResolver.load_netp_portrait(data)
	_preview_label.text = "%s · %s · %s" % [token.display_name, token.tier, token.type]


func _load_roster() -> void:
	_roster_list.clear()
	for char_id in NetPValidator.list_saved_ids():
		var data := NetPValidator.load_character(char_id)
		if data == null:
			continue
		_roster_list.add_item("%s [%s]" % [data.name, data.tier])
		_roster_list.set_item_metadata(_roster_list.item_count - 1, char_id)
	# Default starter tokens if roster empty
	if _roster_list.item_count == 0:
		for name in ["Security", "SystemAdmin", "Coder", "Researcher", "Gatekeeper", "OpsMonitor"]:
			var token := CustomizerGridToken.new()
			token.id = name
			token.display_name = name
			token.tier = "OMEGA"
			token.type = "Mechanical"
			token.element = "Static"
			token.primary_color = Color("#0066FF") if name == "Security" else Color("#FF00FF")
			_roster_list.add_item("%s [OMEGA]" % name)
			_roster_list.set_item_metadata(_roster_list.item_count - 1, token)


func _on_roster_selected(index: int) -> void:
	var meta = _roster_list.get_item_metadata(index)
	if meta is CustomizerGridToken:
		_selected_token = meta
	elif meta is String:
		var data := NetPValidator.load_character(meta)
		_selected_token = CustomizerGridToken.from_netp_data(data) if data else null
	_status_label.text = "Selected: %s — click or drag to grid" % (_selected_token.display_name if _selected_token else "none")
	if _selected_token:
		_update_preview(_selected_token)


func _refresh_grid_visual() -> void:
	for child in _grid_visual.get_children():
		child.queue_free()
	_cell_buttons.clear()
	_grid_visual.columns = _grid_logic.grid_size.x
	for y in _grid_logic.grid_size.y:
		for x in _grid_logic.grid_size.x:
			var pos := Vector2i(x, y)
			var btn := CustomizerGridCell.new()
			btn.grid_pos = pos
			btn.host = self
			btn.custom_minimum_size = _grid_logic.cell_size
			var token: CustomizerGridToken = _grid_logic.get_token_at(pos)
			if token:
				btn.text = token.display_name.substr(0, 3)
				btn.modulate = token.primary_color
			elif _grid_logic._violates_center_line(pos):
				btn.text = "|"
				btn.modulate = Color(0.4, 0.4, 0.5)
			else:
				btn.text = "·"
			btn.pressed.connect(_on_cell_pressed.bind(pos))
			_grid_visual.add_child(btn)
			_cell_buttons[pos] = btn
	var bonuses := _grid_logic.get_total_bonuses()
	_bonus_label.text = "Bonuses: ATK+%d DEF+%d HP+%d RAPID+%d CHARGE+%d" % [
		bonuses.atk, bonuses.def, bonuses.hp, bonuses.rapid, bonuses.charge
	]


func _on_cell_pressed(pos: Vector2i) -> void:
	var existing := _grid_logic.get_token_at(pos)
	if existing:
		_grid_logic.remove_token(pos)
		_status_label.text = "Removed %s" % existing.display_name
		return
	if _selected_token == null:
		_status_label.text = "Select a NetP from the roster first."
		return
	var token := CustomizerGridToken.new()
	token.id = _selected_token.id
	token.display_name = _selected_token.display_name
	token.tier = _selected_token.tier
	token.type = _selected_token.type
	token.element = _selected_token.element
	token.primary_color = _selected_token.primary_color
	token.secondary_color = _selected_token.secondary_color
	if _grid_logic.place_token(token, pos):
		_status_label.text = "Placed %s at (%d,%d)" % [token.display_name, pos.x, pos.y]
		_update_preview(token)
	else:
		_status_label.text = "Placement failed — check bug heat / color rules."


func _on_heat_changed(heat: float) -> void:
	_heat_bar.value = heat
	if heat >= 75.0:
		_heat_bar.modulate = CreatorTheme.ERROR_COLOR
	elif heat >= 40.0:
		_heat_bar.modulate = Color.ORANGE
	else:
		_heat_bar.modulate = CreatorTheme.ACCENT_CYAN if not _is_mod_theme else CreatorTheme.ACCENT_MAGENTA


func _on_validation_changed(_ok: bool, messages: Array) -> void:
	if messages.is_empty():
		_status_label.text = "Grid stable."
	else:
		_status_label.text = " · ".join(messages)


func _on_save() -> void:
	if not _grid_logic.is_valid_for_save():
		_status_label.text = "Cannot save — fix validation issues first."
		return
	var state := _grid_logic.save_grid_state()
	layout_saved.emit(state)
	_status_label.text = "Layout saved."


func _on_clear() -> void:
	_grid_logic.clear_grid()
	_refresh_grid_visual()


func _on_close() -> void:
	customizer_closed.emit()
	queue_free()


func _on_viewport_resized() -> void:
	_viewport_size = get_viewport_rect().size
