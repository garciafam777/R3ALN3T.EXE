class_name IdentityPanel
extends PanelContainer

signal data_changed

var _content: Dictionary = {}
var _data: NetPData
var _viewport_size: Vector2

var _name_input: LineEdit
var _id_input: LineEdit
var _tier_select: OptionButton
var _faction_select: OptionButton
var _role_select: OptionButton
var _pronoun_select: OptionButton
var _status_label: Label


func setup(content: Dictionary, data: NetPData, viewport_size: Vector2) -> void:
	_content = content
	_data = data
	_viewport_size = viewport_size
	_build_ui()
	_sync_from_data()
	CreatorTheme.set_test_id(self, "identity-panel")


func set_data(data: NetPData) -> void:
	_data = data
	_sync_from_data()


func get_data() -> NetPData:
	_data.name = _name_input.text
	_data.id = _id_input.text
	_data.tier = _tier_select.get_item_text(_tier_select.selected)
	_data.faction = _faction_select.get_item_text(_faction_select.selected)
	_data.role = _role_select.get_item_text(_role_select.selected)
	_data.pronouns = _pronoun_select.get_item_text(_pronoun_select.selected)
	return _data


func set_validation(errors: Array, warnings: Array) -> void:
	if not errors.is_empty():
		_status_label.text = errors[0]
		_status_label.add_theme_color_override("font_color", CreatorTheme.ERROR_COLOR)
		_name_input.add_theme_color_override("font_color", CreatorTheme.ERROR_COLOR)
	elif not warnings.is_empty():
		_status_label.text = warnings[0]
		_status_label.add_theme_color_override("font_color", CreatorTheme.TEXT_DIM)
	else:
		_status_label.text = "Identity valid"
		_status_label.add_theme_color_override("font_color", CreatorTheme.SUCCESS_COLOR)
		_name_input.remove_theme_color_override("font_color")


func _build_ui() -> void:
	add_theme_stylebox_override("panel", CreatorTheme.make_panel_style(_viewport_size))
	var root := VBoxContainer.new()
	root.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 10))
	add_child(root)

	var header := Label.new()
	header.text = "IDENTITY"
	header.label_settings = CreatorTheme.label_settings(_viewport_size, 20, CreatorTheme.ACCENT_CYAN)
	root.add_child(header)

	_name_input = _add_labeled_field(root, "Name", "name-input")
	_name_input.text_changed.connect(_on_field_changed)
	_id_input = _add_labeled_field(root, "ID", "")
	_id_input.text_changed.connect(_on_field_changed)

	_tier_select = _add_labeled_option(root, "Tier", "tier-select")
	for tier_id in NetPContent.tier_ids(_content):
		_tier_select.add_item(tier_id)
	_tier_select.item_selected.connect(_on_tier_changed)

	_faction_select = _add_labeled_option(root, "Faction", "")
	for faction in _content.get("factions", []):
		_faction_select.add_item(str(faction))
	_faction_select.item_selected.connect(_on_field_changed)

	_role_select = _add_labeled_option(root, "Role", "")
	for role in _content.get("roles", []):
		_role_select.add_item(str(role))
	_role_select.item_selected.connect(_on_field_changed)

	_pronoun_select = _add_labeled_option(root, "Pronouns", "")
	for pronoun in _content.get("pronouns", []):
		_pronoun_select.add_item(str(pronoun))
	_pronoun_select.item_selected.connect(_on_field_changed)

	_status_label = Label.new()
	_status_label.text = "Enter character identity"
	_status_label.label_settings = CreatorTheme.label_settings(_viewport_size, 14, CreatorTheme.TEXT_DIM)
	_status_label.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	root.add_child(_status_label)


func _add_labeled_field(parent: VBoxContainer, label_text: String, test_id: String) -> LineEdit:
	var label := Label.new()
	label.text = label_text
	label.label_settings = CreatorTheme.label_settings(_viewport_size, 14)
	parent.add_child(label)
	var field := LineEdit.new()
	field.accessibility_name = label_text
	field.custom_minimum_size.y = CreatorTheme.spacing(_viewport_size, 36)
	if not test_id.is_empty():
		CreatorTheme.set_test_id(field, test_id)
	parent.add_child(field)
	return field


func _add_labeled_option(parent: VBoxContainer, label_text: String, test_id: String) -> OptionButton:
	var label := Label.new()
	label.text = label_text
	label.label_settings = CreatorTheme.label_settings(_viewport_size, 14)
	parent.add_child(label)
	var option := OptionButton.new()
	option.accessibility_name = label_text
	option.custom_minimum_size.y = CreatorTheme.spacing(_viewport_size, 36)
	if not test_id.is_empty():
		CreatorTheme.set_test_id(option, test_id)
	parent.add_child(option)
	return option


func _sync_from_data() -> void:
	_name_input.text = _data.name
	_id_input.text = _data.id
	_select_option_text(_tier_select, _data.tier)
	_select_option_text(_faction_select, _data.faction)
	_select_option_text(_role_select, _data.role)
	_select_option_text(_pronoun_select, _data.pronouns)


func _select_option_text(option: OptionButton, text: String) -> void:
	for i in option.item_count:
		if option.get_item_text(i) == text:
			option.select(i)
			return


func _on_tier_changed(_index: int) -> void:
	_data.tier = _tier_select.get_item_text(_tier_select.selected)
	_data.apply_tier(_data.tier, _content)
	_data.apply_type_bias(_content)
	data_changed.emit()


func _on_field_changed(_arg = null) -> void:
	data_changed.emit()
