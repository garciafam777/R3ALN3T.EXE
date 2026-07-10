extends Control
class_name NetPRosterPicker

## Picks a saved NetP character from the creator roster.

signal character_selected(character_id: String)
signal picker_closed

var _viewport_size: Vector2
var _list: ItemList
var _status_label: Label
var _ids: Array[String] = []


func _ready() -> void:
	_viewport_size = get_viewport_rect().size
	set_anchors_preset(Control.PRESET_FULL_RECT)
	_build_ui()
	_refresh_list()
	CreatorTheme.set_test_id(self, "netp-roster-picker")


func _build_ui() -> void:
	var bg := ColorRect.new()
	bg.set_anchors_preset(Control.PRESET_FULL_RECT)
	bg.color = Color(0, 0, 0, 0.7)
	add_child(bg)

	var center := CenterContainer.new()
	center.set_anchors_preset(Control.PRESET_FULL_RECT)
	add_child(center)

	var panel := PanelContainer.new()
	panel.custom_minimum_size = Vector2(minf(_viewport_size.x * 0.9, 480), minf(_viewport_size.y * 0.7, 600))
	panel.add_theme_stylebox_override("panel", CreatorTheme.make_panel_style(_viewport_size))
	center.add_child(panel)

	var root := VBoxContainer.new()
	root.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 10))
	panel.add_child(root)

	var header := Label.new()
	header.text = "NETP ROSTER"
	header.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	header.label_settings = CreatorTheme.label_settings(_viewport_size, 20, CreatorTheme.ACCENT_CYAN)
	root.add_child(header)

	_list = ItemList.new()
	_list.size_flags_vertical = Control.SIZE_EXPAND_FILL
	_list.item_activated.connect(_on_item_activated)
	root.add_child(_list)

	_status_label = Label.new()
	_status_label.label_settings = CreatorTheme.label_settings(_viewport_size, 12, CreatorTheme.TEXT_DIM)
	root.add_child(_status_label)

	var row := HBoxContainer.new()
	row.alignment = BoxContainer.ALIGNMENT_CENTER
	root.add_child(row)

	var load_btn := Button.new()
	load_btn.text = "Load Selected"
	load_btn.pressed.connect(_on_load_pressed)
	row.add_child(load_btn)

	var cancel_btn := Button.new()
	cancel_btn.text = "Cancel"
	cancel_btn.pressed.connect(_on_cancel_pressed)
	row.add_child(cancel_btn)


func _refresh_list() -> void:
	_list.clear()
	_ids = NetPValidator.list_saved_ids()
	for char_id in _ids:
		var data := NetPValidator.load_character(char_id)
		if data == null:
			continue
		_list.add_item("%s — %s / %s" % [data.name, data.tier, data.type])
	if _ids.is_empty():
		_status_label.text = "No saved NetPs yet. Save a character first."


func _on_load_pressed() -> void:
	var selected := _list.get_selected_items()
	if selected.is_empty():
		_status_label.text = "Select a character from the list."
		return
	character_selected.emit(_ids[selected[0]])
	queue_free()


func _on_item_activated(_index: int) -> void:
	_on_load_pressed()


func _on_cancel_pressed() -> void:
	picker_closed.emit()
	queue_free()
