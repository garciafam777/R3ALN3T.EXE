class_name ProgramsPanel
extends PanelContainer

signal data_changed

const SLOTS := ["primary", "secondary", "passive", "ultimate", "signature"]

var _content: Dictionary = {}
var _data: NetPData
var _viewport_size: Vector2

var _search: LineEdit
var _library: ItemList
var _slot_buttons: Dictionary = {}
var _filtered_programs: Array = []


func setup(content: Dictionary, data: NetPData, viewport_size: Vector2) -> void:
	_content = content
	_data = data
	_viewport_size = viewport_size
	_build_ui()
	_refresh_library()
	_sync_slots()
	CreatorTheme.set_test_id(self, "programs-panel")


func set_data(data: NetPData) -> void:
	_data = data
	_refresh_library()
	_sync_slots()


func get_data() -> NetPData:
	return _data


func _build_ui() -> void:
	add_theme_stylebox_override("panel", CreatorTheme.make_panel_style(_viewport_size))
	size_flags_vertical = Control.SIZE_EXPAND_FILL

	var root := VBoxContainer.new()
	root.size_flags_vertical = Control.SIZE_EXPAND_FILL
	root.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 6))
	add_child(root)

	var header := Label.new()
	header.text = "PROGRAMS"
	header.label_settings = CreatorTheme.label_settings(_viewport_size, 18, CreatorTheme.ACCENT_CYAN)
	root.add_child(header)

	for slot in SLOTS:
		var btn := Button.new()
		btn.text = "%s: (empty)" % slot.capitalize()
		btn.alignment = HORIZONTAL_ALIGNMENT_LEFT
		btn.pressed.connect(_on_slot_pressed.bind(slot))
		btn.custom_minimum_size.y = CreatorTheme.spacing(_viewport_size, 32)
		root.add_child(btn)
		_slot_buttons[slot] = btn
		if slot == "primary":
			CreatorTheme.set_test_id(btn, "primary-program-slot")

	_search = LineEdit.new()
	_search.placeholder_text = "Search programs..."
	_search.text_changed.connect(_on_search)
	_search.text_submitted.connect(_on_search)
	_search.gui_input.connect(_on_search_input)
	CreatorTheme.set_test_id(_search, "program-search")
	root.add_child(_search)

	_library = ItemList.new()
	_library.size_flags_vertical = Control.SIZE_EXPAND_FILL
	_library.item_activated.connect(_on_program_selected)
	root.add_child(_library)


func _refresh_library() -> void:
	_filtered_programs = NetPContent.programs_for_character(_content, _data)
	_apply_filter(_search.text if _search else "")


func _apply_filter(query: String) -> void:
	_library.clear()
	var q := query.to_lower()
	for prog in _filtered_programs:
		var name: String = prog.get("name", "")
		if q.is_empty() or name.to_lower().contains(q):
			var line := "%s [%s/%s] CD:%d" % [
				name,
				prog.get("type", ""),
				prog.get("element", ""),
				prog.get("cooldown", 0)
			]
			_library.add_item(line)


func _sync_slots() -> void:
	for slot in SLOTS:
		var equipped: String = str(_data.programs.get(slot, ""))
		var btn: Button = _slot_buttons[slot]
		if equipped.is_empty():
			btn.text = "%s: (empty) — click to equip" % slot.capitalize()
		else:
			btn.text = "%s: %s" % [slot.capitalize(), equipped]


func _on_slot_pressed(slot: String) -> void:
	if _library.get_selected_items().is_empty():
		return
	var idx := _library.get_selected_items()[0]
	var prog: Dictionary = _get_program_at_list_index(idx)
	if prog.is_empty():
		return
	_data.programs[slot] = prog.get("name", "")
	_sync_slots()
	data_changed.emit()


func _on_program_selected(index: int) -> void:
	var prog: Dictionary = _get_program_at_list_index(index)
	if prog.is_empty():
		return
	for slot in SLOTS:
		if str(_data.programs.get(slot, "")).is_empty():
			_data.programs[slot] = prog.get("name", "")
			_sync_slots()
			data_changed.emit()
			return


func _get_program_at_list_index(list_index: int) -> Dictionary:
	var q := _search.text.to_lower() if _search else ""
	var visible: Array = []
	for prog in _filtered_programs:
		var name: String = prog.get("name", "")
		if q.is_empty() or name.to_lower().contains(q):
			visible.append(prog)
	if list_index >= 0 and list_index < visible.size():
		return visible[list_index]
	return {}


func _on_search(text: String) -> void:
	_apply_filter(text)


func _on_search_input(event: InputEvent) -> void:
	if event is InputEventKey and event.pressed and event.keycode == KEY_ESCAPE:
		_search.text = ""
		_apply_filter("")
		get_viewport().set_input_as_handled()
