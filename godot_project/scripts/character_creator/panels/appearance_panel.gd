class_name AppearancePanel
extends PanelContainer

signal data_changed

var _content: Dictionary = {}
var _data: NetPData
var _viewport_size: Vector2
var _tab_container: TabContainer
var _sliders: Dictionary = {}


func setup(content: Dictionary, data: NetPData, viewport_size: Vector2) -> void:
	_content = content
	_data = data
	_viewport_size = viewport_size
	_build_ui()
	_sync_from_data()
	CreatorTheme.set_test_id(self, "appearance-panel")


func set_data(data: NetPData) -> void:
	_data = data
	_sync_from_data()


func get_data() -> NetPData:
	return _data


func _build_ui() -> void:
	add_theme_stylebox_override("panel", CreatorTheme.make_panel_style(_viewport_size))
	size_flags_vertical = Control.SIZE_EXPAND_FILL

	var root := VBoxContainer.new()
	root.size_flags_vertical = Control.SIZE_EXPAND_FILL
	add_child(root)

	var header := Label.new()
	header.text = "APPEARANCE"
	header.label_settings = CreatorTheme.label_settings(_viewport_size, 18, CreatorTheme.ACCENT_CYAN)
	root.add_child(header)

	_tab_container = TabContainer.new()
	_tab_container.size_flags_vertical = Control.SIZE_EXPAND_FILL
	root.add_child(_tab_container)

	_build_body_tab()
	_build_face_tab()
	_build_hair_tab()
	_build_color_tab()
	_build_accessory_tab()


func _build_body_tab() -> void:
	var tab := _make_scroll_tab("Body")
	_add_option_row(tab, "Body Type", "body_types", "body", "body_type")
	_add_slider_row(tab, "Height", "body", "height", 0.8, 1.2, 0.01)


func _build_face_tab() -> void:
	var tab := _make_scroll_tab("Face")
	_add_option_row(tab, "Face Shape", "face_shapes", "face", "face_shape")
	_add_option_row(tab, "Eye Type", "eye_types", "face", "eye_type")


func _build_hair_tab() -> void:
	var tab := _make_scroll_tab("Hair")
	CreatorTheme.set_test_id(_tab_container, "hair-tab")
	_add_option_row(tab, "Hair Style", "hair_styles", "hair", "hair_style")


func _build_color_tab() -> void:
	var tab := _make_scroll_tab("Color")
	_add_color_row(tab, "Primary", "colors", "primary", "color-picker")
	_add_color_row(tab, "Secondary", "colors", "secondary", "")
	_add_color_row(tab, "Glow", "colors", "glow", "")


func _build_accessory_tab() -> void:
	var tab := _make_scroll_tab("FX")
	var label := Label.new()
	label.text = "Glow intensity scales with tier rarity."
	label.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	label.label_settings = CreatorTheme.label_settings(_viewport_size, 13, CreatorTheme.TEXT_DIM)
	tab.add_child(label)
	_add_slider_row(tab, "Glow Intensity", "colors", "glow_intensity", 0.0, 1.0, 0.05)


func _make_scroll_tab(title: String) -> VBoxContainer:
	var scroll := ScrollContainer.new()
	scroll.name = title
	scroll.size_flags_vertical = Control.SIZE_EXPAND_FILL
	_tab_container.add_child(scroll)

	var tab := VBoxContainer.new()
	tab.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	tab.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 8))
	scroll.add_child(tab)
	return tab


func _add_option_row(parent: VBoxContainer, label_text: String, preset_key: String, section: String, field: String) -> void:
	var label := Label.new()
	label.text = label_text
	label.label_settings = CreatorTheme.label_settings(_viewport_size, 14)
	parent.add_child(label)

	var option := OptionButton.new()
	option.accessibility_name = label_text
	var presets: Dictionary = _content.get("appearance_presets", {})
	for value in presets.get(preset_key, []):
		option.add_item(str(value))
	option.item_selected.connect(func(idx): _on_option_selected(section, field, option.get_item_text(idx)))
	parent.add_child(option)
	_sliders["%s.%s" % [section, field]] = option


func _add_slider_row(parent: VBoxContainer, label_text: String, section: String, field: String, min_v: float, max_v: float, step: float) -> void:
	var row := HBoxContainer.new()
	parent.add_child(row)

	var label := Label.new()
	label.text = label_text
	label.custom_minimum_size.x = CreatorTheme.spacing(_viewport_size, 100)
	label.label_settings = CreatorTheme.label_settings(_viewport_size, 14)
	row.add_child(label)

	var slider := HSlider.new()
	slider.min_value = min_v
	slider.max_value = max_v
	slider.step = step
	slider.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	row.add_child(slider)

	var value_label := Label.new()
	value_label.custom_minimum_size.x = CreatorTheme.spacing(_viewport_size, 48)
	value_label.label_settings = CreatorTheme.label_settings(_viewport_size, 14, CreatorTheme.ACCENT_CYAN)
	row.add_child(value_label)

	slider.value_changed.connect(func(v): _on_slider_changed(section, field, v, value_label))
	_sliders["%s.%s" % [section, field]] = slider


func _add_color_row(parent: VBoxContainer, label_text: String, section: String, field: String, test_id: String) -> void:
	var row := HBoxContainer.new()
	parent.add_child(row)

	var label := Label.new()
	label.text = label_text
	label.custom_minimum_size.x = CreatorTheme.spacing(_viewport_size, 100)
	label.label_settings = CreatorTheme.label_settings(_viewport_size, 14)
	row.add_child(label)

	var picker := ColorPickerButton.new()
	picker.accessibility_name = label_text
	picker.custom_minimum_size = Vector2(48, 32) * CreatorTheme.scale_factor(_viewport_size)
	picker.color_changed.connect(func(c): _on_color_changed(section, field, c))
	if not test_id.is_empty():
		CreatorTheme.set_test_id(picker, test_id)
	row.add_child(picker)

	var hex_label := Label.new()
	hex_label.label_settings = CreatorTheme.label_settings(_viewport_size, 13, CreatorTheme.TEXT_DIM)
	row.add_child(hex_label)
	_sliders["%s.%s_hex" % [section, field]] = hex_label
	_sliders["%s.%s" % [section, field]] = picker


func _on_option_selected(section: String, field: String, value: String) -> void:
	if not _data.appearance.has(section):
		_data.appearance[section] = {}
	_data.appearance[section][field] = value
	data_changed.emit()


func _on_slider_changed(section: String, field: String, value: float, value_label: Label) -> void:
	if not _data.appearance.has(section):
		_data.appearance[section] = {}
	_data.appearance[section][field] = value
	value_label.text = "%.2f" % value
	data_changed.emit()


func _on_color_changed(section: String, field: String, color: Color) -> void:
	if not _data.appearance.has(section):
		_data.appearance[section] = {}
	_data.appearance[section][field] = color.to_html(false)
	var hex_label: Label = _sliders.get("%s.%s_hex" % [section, field])
	if hex_label:
		hex_label.text = color.to_html(false)
	data_changed.emit()


func _sync_from_data() -> void:
	for key in _sliders:
		if key.ends_with("_hex"):
			continue
		var parts: PackedStringArray = key.split(".")
		if parts.size() != 2:
			continue
		var section := parts[0]
		var field := parts[1]
		var section_data: Dictionary = _data.appearance.get(section, {})
		var value = section_data.get(field)
		var control = _sliders[key]
		if control is OptionButton and value != null:
			for i in control.item_count:
				if control.get_item_text(i) == str(value):
					control.select(i)
		elif control is HSlider and value != null:
			control.value = float(value)
		elif control is ColorPickerButton and value != null:
			control.color = Color(str(value))
