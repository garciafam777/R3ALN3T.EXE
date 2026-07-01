class_name TypeElementPanel
extends PanelContainer

signal data_changed

var _content: Dictionary = {}
var _data: NetPData
var _viewport_size: Vector2

var _type_select: OptionButton
var _element_select: OptionButton
var _alignment_label: Label
var _domain_label: Label
var _flavor_label: Label


func setup(content: Dictionary, data: NetPData, viewport_size: Vector2) -> void:
	_content = content
	_data = data
	_viewport_size = viewport_size
	_build_ui()
	_sync_from_data()
	CreatorTheme.set_test_id(self, "type-panel")


func set_data(data: NetPData) -> void:
	_data = data
	_sync_from_data()


func get_data() -> NetPData:
	_data.type = _type_select.get_item_text(_type_select.selected)
	_data.element = _element_select.get_item_text(_element_select.selected)
	return _data


func _build_ui() -> void:
	add_theme_stylebox_override("panel", CreatorTheme.make_panel_style(_viewport_size))
	var root := VBoxContainer.new()
	root.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 8))
	add_child(root)

	var header := Label.new()
	header.text = "TYPE & ELEMENT"
	header.label_settings = CreatorTheme.label_settings(_viewport_size, 18, CreatorTheme.ACCENT_CYAN)
	root.add_child(header)

	_type_select = _add_option(root, "Type", "type-panel")
	for type_id in NetPContent.type_ids(_content):
		_type_select.add_item(type_id)
	_type_select.item_selected.connect(_on_type_changed)

	_element_select = _add_option(root, "Element", "element-panel")
	_element_select.item_selected.connect(_on_element_changed)

	_alignment_label = Label.new()
	_alignment_label.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	_alignment_label.label_settings = CreatorTheme.label_settings(_viewport_size, 13)
	CreatorTheme.set_test_id(_alignment_label, "alignment-summary")
	root.add_child(_alignment_label)

	_domain_label = Label.new()
	_domain_label.label_settings = CreatorTheme.label_settings(_viewport_size, 13, CreatorTheme.TEXT_DIM)
	root.add_child(_domain_label)

	_flavor_label = Label.new()
	_flavor_label.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	_flavor_label.label_settings = CreatorTheme.label_settings(_viewport_size, 13, CreatorTheme.ACCENT_MAGENTA)
	root.add_child(_flavor_label)


func _add_option(parent: VBoxContainer, label_text: String, test_id: String) -> OptionButton:
	var label := Label.new()
	label.text = label_text
	label.label_settings = CreatorTheme.label_settings(_viewport_size, 14)
	parent.add_child(label)
	var option := OptionButton.new()
	option.accessibility_name = label_text
	option.custom_minimum_size.y = CreatorTheme.spacing(_viewport_size, 36)
	CreatorTheme.set_test_id(option, test_id)
	parent.add_child(option)
	return option


func _on_type_changed(_idx: int) -> void:
	_data.type = _type_select.get_item_text(_type_select.selected)
	_refresh_elements()
	_data.apply_type_bias(_content)
	_update_summary()
	data_changed.emit()


func _on_element_changed(_idx: int) -> void:
	_data.element = _element_select.get_item_text(_element_select.selected)
	_update_summary()
	data_changed.emit()


func _refresh_elements() -> void:
	_element_select.clear()
	for element_id in NetPContent.element_ids_for_type(_content, _data.type, _data.tier):
		_element_select.add_item(element_id)
	if _element_select.item_count > 0:
		_element_select.select(0)
		_data.element = _element_select.get_item_text(0)


func _sync_from_data() -> void:
	_select_text(_type_select, _data.type)
	_refresh_elements()
	_select_text(_element_select, _data.element)
	_update_summary()


func _select_text(option: OptionButton, text: String) -> void:
	for i in option.item_count:
		if option.get_item_text(i) == text:
			option.select(i)
			return


func _update_summary() -> void:
	var type_entry := NetPContent.get_type(_content, _data.type)
	var element_entry := NetPContent.get_element(_content, _data.element)
	var combat_type := type_entry.get("combat_type", _data.type)
	var game_element := element_entry.get("game_element", _data.element)
	_alignment_label.text = "Alignment: %s combat style · %s element" % [combat_type, game_element]
	_domain_label.text = "Domain: %s" % type_entry.get("domain", "Unknown")
	_flavor_label.text = "Flavor: %s %s — %s role bias" % [_data.type, _data.element, _data.role]
