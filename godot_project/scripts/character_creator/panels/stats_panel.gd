class_name StatsPanel
extends PanelContainer

signal data_changed

var _content: Dictionary = {}
var _data: NetPData
var _viewport_size: Vector2
var _show_modified: bool = true
var _base_stats: Dictionary = {}
var _stat_rows: Dictionary = {}
var _toggle: CheckButton


func setup(content: Dictionary, data: NetPData, viewport_size: Vector2) -> void:
	_content = content
	_data = data
	_viewport_size = viewport_size
	_base_stats = data.stats.duplicate(true)
	_build_ui()
	refresh()
	CreatorTheme.set_test_id(self, "stats-panel")


func set_data(data: NetPData) -> void:
	_data = data
	refresh()


func get_data() -> NetPData:
	for stat_key in _stat_rows:
		var row: Dictionary = _stat_rows[stat_key]
		_data.stats[stat_key] = int(row["slider"].value)
	return _data


func refresh() -> void:
	var tier_entry := NetPContent.get_tier(_content, _data.tier)
	var bands: Dictionary = tier_entry.get("stat_bands", {})
	for stat_key in _stat_rows:
		var row: Dictionary = _stat_rows[stat_key]
		var band: Array = bands.get(stat_key, [0, 9999])
		if band.size() >= 2:
			row["slider"].min_value = band[0]
			row["slider"].max_value = band[1]
		var value: int = int(_data.stats.get(stat_key, 0))
		row["slider"].value = value
		row["value_label"].text = str(value)
		var max_bar: float = float(band[1]) if band.size() >= 2 else float(value)
		row["bar"].max_value = max_bar
		row["bar"].value = value
		if _data.tier == "OMEGA":
			row["bar"].modulate = CreatorTheme.ACCENT_MAGENTA
		else:
			row["bar"].modulate = CreatorTheme.ACCENT_CYAN


func _build_ui() -> void:
	add_theme_stylebox_override("panel", CreatorTheme.make_panel_style(_viewport_size))
	var root := VBoxContainer.new()
	root.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 6))
	add_child(root)

	var header_row := HBoxContainer.new()
	root.add_child(header_row)
	var header := Label.new()
	header.text = "STATS"
	header.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	header.label_settings = CreatorTheme.label_settings(_viewport_size, 18, CreatorTheme.ACCENT_CYAN)
	header_row.add_child(header)
	_toggle = CheckButton.new()
	_toggle.text = "Modified view"
	_toggle.button_pressed = true
	_toggle.toggled.connect(_on_toggle)
	header_row.add_child(_toggle)

	for stat_key in ["hp", "atk", "rapid", "charge", "def"]:
		_add_stat_row(root, stat_key)


func _add_stat_row(parent: VBoxContainer, stat_key: String) -> void:
	var row_box := VBoxContainer.new()
	parent.add_child(row_box)

	var top := HBoxContainer.new()
	row_box.add_child(top)

	var name_label := Label.new()
	name_label.text = stat_key.to_upper()
	name_label.custom_minimum_size.x = CreatorTheme.spacing(_viewport_size, 72)
	name_label.label_settings = CreatorTheme.label_settings(_viewport_size, 14)
	name_label.tooltip_text = _stat_tooltip(stat_key)
	top.add_child(name_label)

	var value_label := Label.new()
	value_label.custom_minimum_size.x = CreatorTheme.spacing(_viewport_size, 56)
	value_label.label_settings = CreatorTheme.label_settings(_viewport_size, 14, CreatorTheme.ACCENT_CYAN)
	top.add_child(value_label)

	var bar := ProgressBar.new()
	bar.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	bar.show_percentage = false
	bar.custom_minimum_size.y = CreatorTheme.spacing(_viewport_size, 18)
	top.add_child(bar)

	var slider := HSlider.new()
	slider.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	slider.value_changed.connect(func(v): _on_stat_changed(stat_key, int(v)))
	row_box.add_child(slider)

	_stat_rows[stat_key] = {"bar": bar, "slider": slider, "value_label": value_label}
	var test_id := "%s-stat" % stat_key
	CreatorTheme.set_test_id(bar, test_id)


func _stat_tooltip(stat_key: String) -> String:
	match stat_key:
		"hp": return "Health points — survivability"
		"atk": return "Attack power — base damage"
		"rapid": return "Attack speed — multi-hit chance"
		"charge": return "Turn initiative — acts earlier when higher"
		"def": return "Defense — reduces incoming damage"
		_: return stat_key


func _on_stat_changed(stat_key: String, value: int) -> void:
	_data.stats[stat_key] = value
	var row: Dictionary = _stat_rows[stat_key]
	row["value_label"].text = str(value)
	row["bar"].value = value
	data_changed.emit()


func _on_toggle(pressed: bool) -> void:
	_show_modified = pressed
	if not pressed:
		for stat_key in _base_stats:
			_data.stats[stat_key] = _base_stats[stat_key]
	else:
		_data.apply_type_bias(_content)
	refresh()
