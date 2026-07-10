extends Control
class_name CharacterCreator

signal character_confirmed(data: NetPData)
signal creator_closed

var _content: Dictionary = {}
var _data: NetPData
var _viewport_size: Vector2

var _main_layout: HBoxContainer
var _left_column: VBoxContainer
var _right_column: VBoxContainer
var _bottom_bar: HBoxContainer
var _message_label: Label

var _identity_panel: IdentityPanel
var _appearance_panel: AppearancePanel
var _preview_panel: PreviewPanel
var _type_element_panel: TypeElementPanel
var _stats_panel: StatsPanel
var _programs_panel: ProgramsPanel

var _tabbed_manager: TabbedManager
var _narrow_stack: VBoxContainer
var _is_narrow_layout: bool = false
var _device_manager: DeviceManager = null


func _ready() -> void:
	_content = NetPContent.load_content()
	_data = NetPData.create_default()
	_data.apply_type_bias(_content)
	_build_shell()
	_build_panels()
	_connect_signals()
	_on_data_changed()
	_apply_responsive_layout()
	get_viewport().size_changed.connect(_on_viewport_resized)
	CreatorTheme.set_test_id(self, "character-creator")


func set_device_manager(manager: DeviceManager) -> void:
	_device_manager = manager
	if _tabbed_manager:
		_tabbed_manager.set_style_from_device(_device_manager)


func load_character(data: NetPData) -> void:
	_data = data.duplicate_data()
	_refresh_all_panels()
	_on_data_changed()


func load_character_by_id(character_id: String) -> bool:
	var loaded := NetPValidator.load_character(character_id)
	if loaded == null:
		return false
	load_character(loaded)
	return true


func _build_shell() -> void:
	set_anchors_preset(Control.PRESET_FULL_RECT)
	_viewport_size = get_viewport_rect().size

	var bg := ColorRect.new()
	bg.set_anchors_preset(Control.PRESET_FULL_RECT)
	bg.color = CreatorTheme.BG_DARK
	add_child(bg)

	var root := MarginContainer.new()
	root.set_anchors_preset(Control.PRESET_FULL_RECT)
	root.add_theme_constant_override("margin_left", CreatorTheme.spacing(_viewport_size, 24))
	root.add_theme_constant_override("margin_right", CreatorTheme.spacing(_viewport_size, 24))
	root.add_theme_constant_override("margin_top", CreatorTheme.spacing(_viewport_size, 16))
	root.add_theme_constant_override("margin_bottom", CreatorTheme.spacing(_viewport_size, 16))
	add_child(root)

	var vbox := VBoxContainer.new()
	vbox.set_anchors_preset(Control.PRESET_FULL_RECT)
	vbox.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	vbox.size_flags_vertical = Control.SIZE_EXPAND_FILL
	vbox.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 12))
	root.add_child(vbox)

	var title := Label.new()
	title.text = "NETP CHARACTER CREATOR"
	title.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	title.label_settings = CreatorTheme.label_settings(_viewport_size, 26, CreatorTheme.ACCENT_CYAN)
	vbox.add_child(title)

	_main_layout = HBoxContainer.new()
	_main_layout.size_flags_vertical = Control.SIZE_EXPAND_FILL
	_main_layout.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 16))
	vbox.add_child(_main_layout)

	_left_column = VBoxContainer.new()
	_left_column.custom_minimum_size.x = CreatorTheme.spacing(_viewport_size, 320)
	_left_column.size_flags_vertical = Control.SIZE_EXPAND_FILL
	_left_column.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 12))
	_main_layout.add_child(_left_column)

	_preview_panel = PreviewPanel.new()
	_preview_panel.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	_preview_panel.size_flags_vertical = Control.SIZE_EXPAND_FILL
	_main_layout.add_child(_preview_panel)

	_right_column = VBoxContainer.new()
	_right_column.custom_minimum_size.x = CreatorTheme.spacing(_viewport_size, 340)
	_right_column.size_flags_vertical = Control.SIZE_EXPAND_FILL
	_right_column.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 12))
	_main_layout.add_child(_right_column)

	_bottom_bar = HBoxContainer.new()
	_bottom_bar.alignment = BoxContainer.ALIGNMENT_CENTER
	_bottom_bar.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 16))
	vbox.add_child(_bottom_bar)

	_message_label = Label.new()
	_message_label.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	_message_label.label_settings = CreatorTheme.label_settings(_viewport_size, 14, CreatorTheme.TEXT_DIM)
	vbox.add_child(_message_label)

	_add_bottom_button("Save", _on_save)
	_add_bottom_button("Load", _on_load)
	_add_bottom_button("Randomize", _on_randomize)
	_add_bottom_button("Presets", _on_presets)
	_add_bottom_button("Export", _on_export)
	_add_bottom_button("Confirm", _on_confirm)
	_add_bottom_button("Close", _on_close)


func _build_panels() -> void:
	_identity_panel = IdentityPanel.new()
	_identity_panel.setup(_content, _data, _viewport_size)

	_appearance_panel = AppearancePanel.new()
	_appearance_panel.setup(_content, _data, _viewport_size)

	_type_element_panel = TypeElementPanel.new()
	_type_element_panel.setup(_content, _data, _viewport_size)

	_stats_panel = StatsPanel.new()
	_stats_panel.setup(_content, _data, _viewport_size)

	_programs_panel = ProgramsPanel.new()
	_programs_panel.setup(_content, _data, _viewport_size)

	_preview_panel.setup(_data, _viewport_size)
	_build_narrow_tabs()
	_mount_wide_layout()


func _build_narrow_tabs() -> void:
	_narrow_stack = VBoxContainer.new()
	_narrow_stack.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	_narrow_stack.size_flags_vertical = Control.SIZE_EXPAND_FILL
	_narrow_stack.visible = false
	_main_layout.add_child(_narrow_stack)

	_tabbed_manager = TabbedManager.new()
	_tabbed_manager.setup(_viewport_size, TabbedManager.TabStyle.KERNAL)
	if _device_manager:
		_tabbed_manager.set_style_from_device(_device_manager)
	_tabbed_manager.size_flags_vertical = Control.SIZE_EXPAND_FILL
	_narrow_stack.add_child(_tabbed_manager)


func _mount_wide_layout() -> void:
	_tabbed_manager.clear_tabs()
	_left_column.visible = true
	_right_column.visible = true
	_narrow_stack.visible = false
	_ensure_child(_identity_panel, _left_column)
	_ensure_child(_appearance_panel, _left_column)
	_ensure_child(_type_element_panel, _right_column)
	_ensure_child(_stats_panel, _right_column)
	_ensure_child(_programs_panel, _right_column)
	_main_layout.move_child(_preview_panel, 1)


func _mount_narrow_layout() -> void:
	_left_column.visible = false
	_right_column.visible = false
	_narrow_stack.visible = true
	_tabbed_manager.clear_tabs()
	var identity_detail := Label.new()
	identity_detail.text = "Tier controls rarity band and unlocks."
	identity_detail.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	_tabbed_manager.add_tab("Identity", _identity_panel, identity_detail)
	_tabbed_manager.add_tab("Look", _appearance_panel)
	_tabbed_manager.add_tab("Type", _type_element_panel)
	_tabbed_manager.add_tab("Stats", _stats_panel)
	_tabbed_manager.add_tab("Programs", _programs_panel)
	_main_layout.move_child(_preview_panel, 0)


func _connect_signals() -> void:
	_identity_panel.data_changed.connect(_on_data_changed)
	_appearance_panel.data_changed.connect(_on_data_changed)
	_type_element_panel.data_changed.connect(_on_data_changed)
	_stats_panel.data_changed.connect(_on_data_changed)
	_programs_panel.data_changed.connect(_on_data_changed)


func _on_data_changed() -> void:
	_collect_data()
	_type_element_panel.set_data(_data)
	_preview_panel.set_data(_data)
	_preview_panel.refresh()
	_stats_panel.set_data(_data)
	_stats_panel.refresh()
	_programs_panel.set_data(_data)
	_validate()


func _collect_data() -> void:
	_data = _identity_panel.get_data()
	_data = _type_element_panel.get_data()
	_data = _stats_panel.get_data()
	_data = _appearance_panel.get_data()
	_data = _programs_panel.get_data()


func _validate() -> void:
	var roster := NetPValidator.list_saved_ids()
	var result := NetPValidator.validate(_data, _content, roster)
	_identity_panel.set_validation(result["errors"], result["warnings"])
	if result["valid"]:
		_message_label.text = "Ready to save or confirm."
		_message_label.add_theme_color_override("font_color", CreatorTheme.SUCCESS_COLOR)
	else:
		_message_label.text = " · ".join(result["errors"])
		_message_label.add_theme_color_override("font_color", CreatorTheme.ERROR_COLOR)


func _refresh_all_panels() -> void:
	_identity_panel.set_data(_data)
	_appearance_panel.set_data(_data)
	_type_element_panel.set_data(_data)
	_stats_panel.set_data(_data)
	_programs_panel.set_data(_data)
	_preview_panel.set_data(_data)


func _add_bottom_button(text: String, callback: Callable) -> void:
	var btn := Button.new()
	btn.text = text
	btn.custom_minimum_size = Vector2(
		CreatorTheme.spacing(_viewport_size, 120),
		CreatorTheme.spacing(_viewport_size, 44)
	)
	btn.pressed.connect(callback)
	_bottom_bar.add_child(btn)


func _on_save() -> void:
	_collect_data()
	var err := NetPValidator.save_character(_data)
	if err == OK:
		_message_label.text = "Saved %s" % _data.id
		_message_label.add_theme_color_override("font_color", CreatorTheme.SUCCESS_COLOR)
	else:
		_message_label.text = "Save failed — fix validation errors first."
		_message_label.add_theme_color_override("font_color", CreatorTheme.ERROR_COLOR)
	_validate()


func _on_load() -> void:
	var picker := NetPRosterPicker.new()
	add_child(picker)
	picker.character_selected.connect(_on_roster_character_selected)
	picker.picker_closed.connect(picker.queue_free)


func _on_roster_character_selected(character_id: String) -> void:
	if load_character_by_id(character_id):
		_message_label.text = "Loaded %s" % character_id
		_on_data_changed()
	else:
		_message_label.text = "Failed to load %s" % character_id


func _on_randomize() -> void:
	_data = NetPData.create_default()
	var tiers: Array = NetPContent.tier_ids(_content)
	_data.tier = tiers[randi() % tiers.size()]
	_data.apply_tier(_data.tier, _content)
	var types: Array = NetPContent.type_ids(_content)
	_data.type = types[randi() % types.size()]
	var elements: Array = NetPContent.element_ids_for_type(_content, _data.type, _data.tier)
	_data.element = elements[randi() % elements.size()]
	_assign_random_programs()
	var roles: Array = _content.get("roles", ["Defender"])
	_data.role = str(roles[randi() % roles.size()])
	_data.name = "NetP-%d" % (randi() % 9000 + 1000)
	_data.id = _generate_id(_data.tier)
	_data.apply_type_bias(_content)
	_refresh_all_panels()
	_on_data_changed()
	_message_label.text = "Randomized character."


func _generate_id(tier_id: String) -> String:
	return "%s-%03d" % [tier_id, randi() % 999 + 1]


func _assign_random_programs() -> void:
	var available: Array = NetPContent.programs_for_character(_content, _data)
	if available.is_empty():
		return
	available.shuffle()
	var slots := ["primary", "secondary", "passive", "ultimate", "signature"]
	for i in slots.size():
		if i < available.size():
			_data.programs[slots[i]] = available[i].get("name", "")


func _on_presets() -> void:
	var preset := NetPData.from_dict({
		"id": "OMEGA-004",
		"name": "Radiant Sentinel",
		"tier": "OMEGA",
		"type": "Angelic",
		"element": "Light",
		"role": "Defender",
		"appearance": {
			"body": {"body_type": "Armored", "height": 1.1},
			"face": {"face_shape": "Angular", "eye_type": "Glow"},
			"hair": {"hair_style": "Flowing"},
			"colors": {"primary": "#00FFFF", "secondary": "#FF00FF", "glow": "#FFE566"}
		},
		"stats": {"hp": 2000, "atk": 260, "rapid": 180, "charge": 200, "def": 180},
		"programs": {
			"primary": "Halo Guard",
			"secondary": "Prism Break",
			"passive": "Seraph Ward",
			"ultimate": "Radiant Exile",
			"signature": "Radiant Exile"
		}
	})
	load_character(preset)
	_message_label.text = "Loaded OMEGA preset: Radiant Sentinel"


func _on_export() -> void:
	_collect_data()
	var path := "user://export_%s.json" % _data.id
	var err := NetPValidator.export_character(_data, path)
	if err == OK:
		_message_label.text = "Exported to %s" % path
	else:
		_message_label.text = "Export failed — character is invalid."


func _on_confirm() -> void:
	_collect_data()
	var result := NetPValidator.validate(_data, _content)
	if not result["valid"]:
		_message_label.text = "Cannot confirm: " + ", ".join(result["errors"])
		return
	NetPValidator.save_character(_data)
	character_confirmed.emit(_data.duplicate_data())
	_message_label.text = "Character confirmed: %s" % _data.name


func _on_close() -> void:
	creator_closed.emit()
	queue_free()


func _on_viewport_resized() -> void:
	_viewport_size = get_viewport_rect().size
	_apply_responsive_layout()


func _apply_responsive_layout() -> void:
	var narrow := _viewport_size.x < 1200.0
	if narrow == _is_narrow_layout:
		if _tabbed_manager:
			_tabbed_manager.refresh_viewport(_viewport_size)
		return
	_is_narrow_layout = narrow
	if narrow:
		_mount_narrow_layout()
		_preview_panel.custom_minimum_size = Vector2(0, CreatorTheme.spacing(_viewport_size, 280))
	else:
		_mount_wide_layout()
		_left_column.custom_minimum_size.x = CreatorTheme.spacing(_viewport_size, 320)
		_right_column.custom_minimum_size.x = CreatorTheme.spacing(_viewport_size, 340)
		_preview_panel.custom_minimum_size = Vector2(CreatorTheme.spacing(_viewport_size, 400), 0)


func _ensure_child(panel: Control, parent: VBoxContainer) -> void:
	if panel.get_parent() != parent:
		parent.add_child(panel)
