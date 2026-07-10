extends Control
class_name LoadPicker

## Save slot + roster picker — narrow PED-friendly layout.

signal game_loaded(slot: int, state: Dictionary)
signal new_game_created(slot: int, state: Dictionary)
signal slot_deleted(slot: int)
signal picker_closed

const THUMBNAIL_DIR := "res://assets/sprites/ui/save_slots/"

var _viewport_size: Vector2
var _device_manager: DeviceManager = null
var _slots_container: VBoxContainer
var _status_label: Label
var _dialog_layer: Control
var _pending_slot: int = -1
var _pending_action: String = "load"
var _preview_panel: PanelContainer
var _preview_name: Label
var _preview_portrait: TextureRect
var _preview_location: Label
var _preview_man: Label
var _preview_encrypted: Label
var _preview_netp_list: ItemList
var _focused_slot_data: Dictionary = {}


func _ready() -> void:
	_viewport_size = get_viewport_rect().size
	set_anchors_preset(Control.PRESET_FULL_RECT)
	_build_ui()
	_refresh_slots()
	get_viewport().size_changed.connect(_on_viewport_resized)
	CreatorTheme.set_test_id(self, "load-picker")


func set_device_manager(manager: DeviceManager) -> void:
	_device_manager = manager


func _build_ui() -> void:
	var bg := ColorRect.new()
	bg.set_anchors_preset(Control.PRESET_FULL_RECT)
	bg.color = CreatorTheme.BG_DARK
	add_child(bg)

	var center := CenterContainer.new()
	center.set_anchors_preset(Control.PRESET_FULL_RECT)
	add_child(center)

	var panel := PanelContainer.new()
	panel.custom_minimum_size = Vector2(minf(_viewport_size.x * 0.95, 880), minf(_viewport_size.y * 0.92, 900))
	panel.add_theme_stylebox_override("panel", CreatorTheme.make_panel_style(_viewport_size))
	center.add_child(panel)

	var root := HBoxContainer.new()
	root.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 14))
	panel.add_child(root)

	var left_col := VBoxContainer.new()
	left_col.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	left_col.custom_minimum_size.x = CreatorTheme.spacing(_viewport_size, 400)
	left_col.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 12))
	root.add_child(left_col)

	_build_preview_column(root)

	var header := Label.new()
	header.text = "ENCRYPTED SAVE SLOTS"
	header.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	header.label_settings = CreatorTheme.label_settings(_viewport_size, 22, CreatorTheme.ACCENT_CYAN)
	left_col.add_child(header)

	var sub := Label.new()
	sub.text = "Select a slot — preview updates on the right"
	sub.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	sub.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	sub.label_settings = CreatorTheme.label_settings(_viewport_size, 13, CreatorTheme.TEXT_DIM)
	left_col.add_child(sub)

	var scroll := ScrollContainer.new()
	scroll.size_flags_vertical = Control.SIZE_EXPAND_FILL
	scroll.horizontal_scroll_mode = ScrollContainer.SCROLL_MODE_DISABLED
	left_col.add_child(scroll)

	_slots_container = VBoxContainer.new()
	_slots_container.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	_slots_container.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 8))
	scroll.add_child(_slots_container)

	_status_label = Label.new()
	_status_label.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	_status_label.label_settings = CreatorTheme.label_settings(_viewport_size, 13, CreatorTheme.TEXT_DIM)
	left_col.add_child(_status_label)

	var actions := HBoxContainer.new()
	actions.alignment = BoxContainer.ALIGNMENT_CENTER
	actions.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 12))
	left_col.add_child(actions)

	var new_btn := Button.new()
	new_btn.text = "New Game"
	new_btn.custom_minimum_size.y = CreatorTheme.spacing(_viewport_size, 44)
	new_btn.pressed.connect(_on_new_game_pressed)
	CreatorTheme.set_test_id(new_btn, "new-game-button")
	actions.add_child(new_btn)

	var close_btn := Button.new()
	close_btn.text = "Back"
	close_btn.custom_minimum_size.y = CreatorTheme.spacing(_viewport_size, 44)
	close_btn.pressed.connect(_on_close_pressed)
	actions.add_child(close_btn)

	_dialog_layer = Control.new()
	_dialog_layer.set_anchors_preset(Control.PRESET_FULL_RECT)
	_dialog_layer.visible = false
	_dialog_layer.mouse_filter = Control.MOUSE_FILTER_STOP
	add_child(_dialog_layer)


func _build_preview_column(parent: HBoxContainer) -> void:
	_preview_panel = PanelContainer.new()
	_preview_panel.custom_minimum_size.x = CreatorTheme.spacing(_viewport_size, 280)
	_preview_panel.size_flags_vertical = Control.SIZE_EXPAND_FILL
	_preview_panel.add_theme_stylebox_override("panel", CreatorTheme.make_panel_style(_viewport_size, CreatorTheme.ACCENT_MAGENTA))
	parent.add_child(_preview_panel)
	CreatorTheme.set_test_id(_preview_panel, "load-preview-panel")

	var box := VBoxContainer.new()
	box.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 8))
	_preview_panel.add_child(box)

	var title := Label.new()
	title.text = "CHARACTER PREVIEW"
	title.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	title.label_settings = CreatorTheme.label_settings(_viewport_size, 16, CreatorTheme.ACCENT_CYAN)
	box.add_child(title)

	_preview_encrypted = Label.new()
	_preview_encrypted.text = "ENCRYPTED SLOT"
	_preview_encrypted.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	_preview_encrypted.label_settings = CreatorTheme.label_settings(_viewport_size, 11, CreatorTheme.ACCENT_MAGENTA)
	box.add_child(_preview_encrypted)

	_preview_portrait = TextureRect.new()
	_preview_portrait.custom_minimum_size = Vector2(CreatorTheme.spacing(_viewport_size, 120), CreatorTheme.spacing(_viewport_size, 120))
	_preview_portrait.expand_mode = TextureRect.EXPAND_IGNORE_SIZE
	_preview_portrait.stretch_mode = TextureRect.STRETCH_KEEP_ASPECT_CENTERED
	box.add_child(_preview_portrait)

	_preview_name = Label.new()
	_preview_name.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	_preview_name.label_settings = CreatorTheme.label_settings(_viewport_size, 18, CreatorTheme.TEXT_PRIMARY)
	box.add_child(_preview_name)

	_preview_location = Label.new()
	_preview_location.label_settings = CreatorTheme.label_settings(_viewport_size, 13, CreatorTheme.TEXT_DIM)
	box.add_child(_preview_location)

	_preview_man = Label.new()
	_preview_man.label_settings = CreatorTheme.label_settings(_viewport_size, 13, CreatorTheme.ACCENT_CYAN)
	box.add_child(_preview_man)

	var roster_hdr := Label.new()
	roster_hdr.text = "ACTIVE NETPS"
	roster_hdr.label_settings = CreatorTheme.label_settings(_viewport_size, 14, CreatorTheme.ACCENT_CYAN)
	box.add_child(roster_hdr)

	_preview_netp_list = ItemList.new()
	_preview_netp_list.size_flags_vertical = Control.SIZE_EXPAND_FILL
	box.add_child(_preview_netp_list)

	_clear_preview()


func _clear_preview() -> void:
	_preview_name.text = "—"
	_preview_location.text = "Location: —"
	_preview_man.text = "M.A.N.: —"
	_preview_encrypted.text = ""
	_preview_portrait.texture = null
	_preview_netp_list.clear()
	_preview_netp_list.add_item("(select a save slot)")


func _update_preview(slot_data: Dictionary) -> void:
	_focused_slot_data = slot_data
	if not slot_data.get("occupied", false):
		_clear_preview()
		_preview_name.text = "Empty Slot %d" % slot_data.get("slot", 0)
		return

	_preview_name.text = slot_data.get("character_name", "Unknown")
	_preview_location.text = "Location: %s" % slot_data.get("location", "R34L")
	_preview_man.text = "M.A.N. Balance: %s" % str(slot_data.get("man_balance", 0))
	_preview_encrypted.text = "AES-256 · PASSWORD PROTECTED"

	var realm := "n3t" if slot_data.get("location", "R34L") == "N3T" else "r34l"
	var path := NetPSpriteResolver.player_avatar_path(realm, "idle")
	var tex := NetPSpriteResolver.load_texture(path)
	_preview_portrait.texture = tex

	_preview_netp_list.clear()
	var netps: Array = slot_data.get("active_netps", [])
	if netps.is_empty():
		_preview_netp_list.add_item("(no active NetPs)")
	else:
		for netp_name in netps:
			_preview_netp_list.add_item("◆ %s" % netp_name)


func _refresh_slots() -> void:
	for child in _slots_container.get_children():
		child.queue_free()
	for slot_data in GameSaveManager.list_all_slots():
		_slots_container.add_child(_build_slot_card(slot_data))


func _build_slot_card(slot_data: Dictionary) -> PanelContainer:
	var slot: int = slot_data.get("slot", 0)
	var occupied: bool = slot_data.get("occupied", false)

	var card := PanelContainer.new()
	card.add_theme_stylebox_override("panel", CreatorTheme.make_panel_style(
		_viewport_size,
		CreatorTheme.ACCENT_MAGENTA if occupied else CreatorTheme.PANEL_BORDER
	))
	CreatorTheme.set_test_id(card, "save-slot-%02d" % slot)

	var margin := MarginContainer.new()
	margin.add_theme_constant_override("margin_left", CreatorTheme.spacing(_viewport_size, 10))
	margin.add_theme_constant_override("margin_right", CreatorTheme.spacing(_viewport_size, 10))
	margin.add_theme_constant_override("margin_top", CreatorTheme.spacing(_viewport_size, 8))
	margin.add_theme_constant_override("margin_bottom", CreatorTheme.spacing(_viewport_size, 8))
	card.add_child(margin)

	var row := HBoxContainer.new()
	row.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 10))
	margin.add_child(row)

	var thumb := _build_slot_thumbnail(slot, slot_data)
	row.add_child(thumb)

	var col := VBoxContainer.new()
	col.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	col.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 4))
	row.add_child(col)

	var title := Label.new()
	title.text = ("Slot %d — %s" % [slot, slot_data.get("character_name", "Unknown")]) if occupied else ("Slot %d — Empty" % slot)
	title.label_settings = CreatorTheme.label_settings(_viewport_size, 16, CreatorTheme.TEXT_PRIMARY)
	col.add_child(title)

	if occupied:
		col.add_child(_info_line("Last Played", _format_time(slot_data.get("last_played", ""))))
		col.add_child(_info_line("Location", slot_data.get("location", "R34L")))
		col.add_child(_info_line("M.A.N. Balance", str(slot_data.get("man_balance", 0))))
		var netps: Array = slot_data.get("active_netps", [])
		col.add_child(_info_line("Active NetPs", ", ".join(netps) if not netps.is_empty() else "(none)"))
		col.add_child(_info_line("Encryption", "Password protected"))

	var preview_btn := Button.new()
	preview_btn.text = "Preview"
	preview_btn.custom_minimum_size.y = CreatorTheme.spacing(_viewport_size, 32)
	preview_btn.pressed.connect(_update_preview.bind(slot_data))
	col.add_child(preview_btn)

	var btn_row := HBoxContainer.new()
	btn_row.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 8))
	col.add_child(btn_row)

	var btn := Button.new()
	btn.text = "Load" if occupied else "Create Here"
	btn.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	btn.custom_minimum_size.y = CreatorTheme.spacing(_viewport_size, 36)
	btn.pressed.connect(_on_slot_pressed.bind(slot, occupied))
	btn_row.add_child(btn)

	if occupied:
		var delete_btn := Button.new()
		delete_btn.text = "Delete"
		delete_btn.custom_minimum_size.y = CreatorTheme.spacing(_viewport_size, 36)
		delete_btn.pressed.connect(_on_delete_pressed.bind(slot))
		CreatorTheme.set_test_id(delete_btn, "delete-slot-%02d" % slot)
		btn_row.add_child(delete_btn)

	return card


func _build_slot_thumbnail(slot: int, slot_data: Dictionary) -> PanelContainer:
	var frame := PanelContainer.new()
	var thumb_size := CreatorTheme.spacing(_viewport_size, 72)
	frame.custom_minimum_size = Vector2(thumb_size, thumb_size)
	frame.add_theme_stylebox_override("panel", CreatorTheme.make_panel_style(_viewport_size))

	var texture: Texture2D = null
	var custom_path: String = str(slot_data.get("thumbnail_path", ""))
	if not custom_path.is_empty() and ResourceLoader.exists(custom_path):
		texture = load(custom_path)
	else:
		var convention_path := "%sslot_%02d.png" % [THUMBNAIL_DIR, slot]
		if ResourceLoader.exists(convention_path):
			texture = load(convention_path)
		elif ResourceLoader.exists(THUMBNAIL_DIR + "default.png"):
			texture = load(THUMBNAIL_DIR + "default.png")

	if texture != null:
		var thumb := TextureRect.new()
		thumb.set_anchors_preset(Control.PRESET_FULL_RECT)
		thumb.texture = texture
		thumb.expand_mode = TextureRect.EXPAND_IGNORE_SIZE
		thumb.stretch_mode = TextureRect.STRETCH_KEEP_ASPECT_CENTERED
		frame.add_child(thumb)
	else:
		var placeholder := ColorRect.new()
		placeholder.set_anchors_preset(Control.PRESET_FULL_RECT)
		placeholder.color = Color(0.06, 0.08, 0.14, 0.95)
		frame.tooltip_text = "Add slot_%02d.png to assets/sprites/ui/save_slots/" % slot
		frame.add_child(placeholder)

	CreatorTheme.set_test_id(frame, "slot-thumbnail-%02d" % slot)
	return frame


func _info_line(label_text: String, value_text: String) -> Label:
	var line := Label.new()
	line.text = "%s: %s" % [label_text, value_text]
	line.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	line.label_settings = CreatorTheme.label_settings(_viewport_size, 12, CreatorTheme.TEXT_DIM)
	return line


func _format_time(iso_text: String) -> String:
	return iso_text.replace("T", " ") if not iso_text.is_empty() else "—"


func _on_slot_pressed(slot: int, occupied: bool) -> void:
	_pending_slot = slot
	_pending_action = "load"
	if occupied:
		_show_password_dialog("Enter save password", _on_load_password_submitted)
	else:
		_show_new_game_dialog()


func _on_delete_pressed(slot: int) -> void:
	_pending_slot = slot
	_pending_action = "delete"
	_show_password_dialog("Enter password to delete this save", _on_delete_password_submitted)


func _on_new_game_pressed() -> void:
	for slot_data in GameSaveManager.list_all_slots():
		if not slot_data.get("occupied", false):
			_on_slot_pressed(slot_data.get("slot", 1), false)
			return
	_status_label.text = "All 10 slots are full."


func _show_new_game_dialog() -> void:
	_show_form_dialog("New Game — Slot %d" % _pending_slot, ["Character Name", "Password", "Confirm Password"], _on_new_game_submitted)


func _show_password_dialog(title: String, callback: Callable) -> void:
	_show_form_dialog(title, ["Password"], callback)


func _show_form_dialog(title: String, field_labels: Array, callback: Callable) -> void:
	_clear_dialog()
	var dim := ColorRect.new()
	dim.set_anchors_preset(Control.PRESET_FULL_RECT)
	dim.color = Color(0, 0, 0, 0.65)
	_dialog_layer.add_child(dim)

	var center := CenterContainer.new()
	center.set_anchors_preset(Control.PRESET_FULL_RECT)
	_dialog_layer.add_child(center)

	var panel := PanelContainer.new()
	panel.custom_minimum_size.x = CreatorTheme.spacing(_viewport_size, 360)
	panel.add_theme_stylebox_override("panel", CreatorTheme.make_panel_style(_viewport_size, CreatorTheme.ACCENT_CYAN))
	center.add_child(panel)

	var box := VBoxContainer.new()
	box.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 10))
	panel.add_child(box)

	var header := Label.new()
	header.text = title
	header.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	header.label_settings = CreatorTheme.label_settings(_viewport_size, 18, CreatorTheme.ACCENT_CYAN)
	box.add_child(header)

	var fields: Array[LineEdit] = []
	for label_text in field_labels:
		var lbl := Label.new()
		lbl.text = label_text
		lbl.label_settings = CreatorTheme.label_settings(_viewport_size, 13)
		box.add_child(lbl)
		var field := LineEdit.new()
		field.accessibility_name = label_text
		if label_text.contains("Password"):
			field.secret = true
		field.custom_minimum_size.y = CreatorTheme.spacing(_viewport_size, 36)
		box.add_child(field)
		fields.append(field)

	var row := HBoxContainer.new()
	row.alignment = BoxContainer.ALIGNMENT_CENTER
	box.add_child(row)
	var ok := Button.new()
	ok.text = "Confirm"
	ok.pressed.connect(func():
		var values: Array[String] = []
		for f in fields:
			values.append(f.text)
		callback.call(values)
	)
	row.add_child(ok)
	var cancel := Button.new()
	cancel.text = "Cancel"
	cancel.pressed.connect(_hide_dialog)
	row.add_child(cancel)

	_dialog_layer.visible = true
	if not fields.is_empty():
		fields[0].grab_focus()


func _on_new_game_submitted(values: Array) -> void:
	if values.size() < 3:
		return
	var name: String = str(values[0]).strip_edges()
	var password: String = str(values[1])
	var confirm: String = str(values[2])
	if name.length() < 2 or password.length() < 4 or password != confirm:
		_status_label.text = "Check name (2+) and matching passwords (4+)."
		return
	var err := GameSaveManager.create_new_game(_pending_slot, name, password)
	_hide_dialog()
	if err != OK:
		_status_label.text = "Could not create save."
		return
	var state := GameSaveManager.load_game(_pending_slot, password)
	_refresh_slots()
	new_game_created.emit(_pending_slot, state)


func _on_load_password_submitted(values: Array) -> void:
	if values.is_empty():
		return
	var state := GameSaveManager.load_game(_pending_slot, str(values[0]))
	_hide_dialog()
	if state.is_empty():
		_status_label.text = "Incorrect password."
		return
	_refresh_slots()
	game_loaded.emit(_pending_slot, state)


func _on_delete_password_submitted(values: Array) -> void:
	if values.is_empty():
		return
	var password := str(values[0])
	if not GameSaveManager.verify_password(_pending_slot, password):
		_hide_dialog()
		_status_label.text = "Incorrect password — save not deleted."
		_status_label.add_theme_color_override("font_color", CreatorTheme.ERROR_COLOR)
		return
	_show_confirm_dialog(
		"Delete Slot %d?" % _pending_slot,
		"This permanently removes the encrypted save. This cannot be undone.",
		_on_delete_confirmed.bind(password)
	)


func _on_delete_confirmed(password: String) -> void:
	var err := GameSaveManager.delete_slot(_pending_slot, password)
	_hide_dialog()
	if err != OK:
		_status_label.text = "Could not delete save."
		_status_label.add_theme_color_override("font_color", CreatorTheme.ERROR_COLOR)
		return
	_status_label.text = "Slot %d deleted." % _pending_slot
	_status_label.add_theme_color_override("font_color", CreatorTheme.SUCCESS_COLOR)
	slot_deleted.emit(_pending_slot)
	_refresh_slots()


func _show_confirm_dialog(title: String, body: String, callback: Callable) -> void:
	_clear_dialog()
	var dim := ColorRect.new()
	dim.set_anchors_preset(Control.PRESET_FULL_RECT)
	dim.color = Color(0, 0, 0, 0.65)
	_dialog_layer.add_child(dim)

	var center := CenterContainer.new()
	center.set_anchors_preset(Control.PRESET_FULL_RECT)
	_dialog_layer.add_child(center)

	var panel := PanelContainer.new()
	panel.custom_minimum_size.x = CreatorTheme.spacing(_viewport_size, 360)
	panel.add_theme_stylebox_override("panel", CreatorTheme.make_panel_style(_viewport_size, CreatorTheme.ERROR_COLOR))
	center.add_child(panel)

	var box := VBoxContainer.new()
	box.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 10))
	panel.add_child(box)

	var header := Label.new()
	header.text = title
	header.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	header.label_settings = CreatorTheme.label_settings(_viewport_size, 18, CreatorTheme.ERROR_COLOR)
	box.add_child(header)

	var msg := Label.new()
	msg.text = body
	msg.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	msg.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	msg.label_settings = CreatorTheme.label_settings(_viewport_size, 13, CreatorTheme.TEXT_DIM)
	box.add_child(msg)

	var row := HBoxContainer.new()
	row.alignment = BoxContainer.ALIGNMENT_CENTER
	box.add_child(row)

	var confirm := Button.new()
	confirm.text = "Delete Forever"
	confirm.pressed.connect(func(): callback.call())
	row.add_child(confirm)

	var cancel := Button.new()
	cancel.text = "Cancel"
	cancel.pressed.connect(_hide_dialog)
	row.add_child(cancel)

	_dialog_layer.visible = true


func _hide_dialog() -> void:
	_clear_dialog()
	_dialog_layer.visible = false


func _clear_dialog() -> void:
	for child in _dialog_layer.get_children():
		child.queue_free()


func _on_close_pressed() -> void:
	picker_closed.emit()
	queue_free()


func _on_viewport_resized() -> void:
	_viewport_size = get_viewport_rect().size
