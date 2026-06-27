extends Control

# Main menu scene — entry point for NETAdmin.EXE

@onready var encrypt_button = $EncryptButton
@onready var load_button = $LoadButton
@onready var device_button = $DeviceButton
@onready var device_label = $DeviceLabel
@onready var encryption_manager = $EncryptionManager
@onready var device_manager = $DeviceManager

var is_encrypting: bool = false
var current_game_state: Dictionary = {}
var current_slot: int = -1
var _encrypt_stage_label: Label = null


func _ready():
	encrypt_button.pressed.connect(_on_encrypt_pressed)
	load_button.pressed.connect(_on_load_pressed)
	device_button.pressed.connect(_on_device_switch_pressed)

	encryption_manager.encryption_complete.connect(_on_encryption_complete)
	encryption_manager.stage_changed.connect(_on_encrypt_stage_changed)
	device_manager.device_changed.connect(_on_device_changed)

	_build_encrypt_overlay()

	_update_device_label()
	_open_load_picker()
	print("Main menu initialized")


func _open_load_picker() -> void:
	var picker_scene: PackedScene = load("res://scenes/main/load_picker.tscn")
	var picker: LoadPicker = picker_scene.instantiate()
	picker.set_device_manager(device_manager)
	picker.game_loaded.connect(_on_game_loaded)
	picker.new_game_created.connect(_on_new_game_created)
	picker.slot_deleted.connect(_on_slot_deleted)
	picker.picker_closed.connect(_on_picker_closed)
	add_child(picker)


func _on_game_loaded(slot: int, state: Dictionary) -> void:
	current_slot = slot
	current_game_state = state
	MANTokenManager.load_from_save(state)
	print("Loaded slot %d — %s at %s" % [slot, state.get("player_name", ""), state.get("location", "R34L")])
	_enter_game_from_state(state)


func _on_new_game_created(slot: int, state: Dictionary) -> void:
	current_slot = slot
	current_game_state = state
	print("New game slot %d — %s" % [slot, state.get("player_name", "")])
	_enter_game_from_state(state)


func _on_slot_deleted(slot: int) -> void:
	if current_slot == slot:
		current_slot = -1
		current_game_state = {}
	print("Save slot %d deleted" % slot)


func _enter_game_from_state(state: Dictionary) -> void:
	var location: String = state.get("location", "R34L")
	if location == "N3T":
		get_tree().change_scene_to_file("res://scenes/net_room/net_room.tscn")
	else:
		get_tree().change_scene_to_file("res://scenes/r34l_room/r34l_room.tscn")


func _on_picker_closed() -> void:
	pass


func _on_encrypt_pressed() -> void:
	if current_game_state.is_empty():
		_open_load_picker()
		return
	if not is_encrypting:
		is_encrypting = true
		encrypt_button.disabled = true
		encrypt_button.text = "ENCRYPTING..."
		encryption_manager.start_encrypting()


func _build_encrypt_overlay() -> void:
	_encrypt_stage_label = Label.new()
	_encrypt_stage_label.set_anchors_preset(Control.PRESET_CENTER_BOTTOM)
	_encrypt_stage_label.offset_top = -80
	_encrypt_stage_label.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	_encrypt_stage_label.label_settings = CreatorTheme.label_settings(get_viewport_rect().size, 16, CreatorTheme.ACCENT_CYAN)
	_encrypt_stage_label.visible = false
	add_child(_encrypt_stage_label)


func _on_encrypt_stage_changed(stage_name: String) -> void:
	if not _encrypt_stage_label:
		return
	_encrypt_stage_label.visible = true
	match stage_name:
		"HEX_STREAMS":
			_encrypt_stage_label.text = "HEX STREAMS →"
		"HASH_ALGORITHM":
			_encrypt_stage_label.text = "HASH ALGORITHM"
		"UPLOAD_TO_N3T":
			_encrypt_stage_label.text = "UPLOAD TO N3T ↑"
		"HASH_REVERSE":
			_encrypt_stage_label.text = "← HASH REVERSE"
		"HEX_REVERSE":
			_encrypt_stage_label.text = "← HEX REVERSE"
		"DOWNLOAD_TO_PED":
			_encrypt_stage_label.text = "DOWNLOAD TO PED ↓"
		_:
			_encrypt_stage_label.text = stage_name


func _on_encryption_complete() -> void:
	if _encrypt_stage_label:
		_encrypt_stage_label.visible = false
	print("Encryption complete - Transitioning to N3T")
	is_encrypting = false
	encrypt_button.disabled = false
	encrypt_button.text = "ENCRYPT"
	if current_slot > 0:
		current_game_state["location"] = "N3T"
		GameSaveManager.update_slot_preview(current_slot, {
			"location": "N3T",
			"character_name": current_game_state.get("player_name", ""),
			"man_balance": current_game_state.get("man_balance", 0),
			"active_netps": current_game_state.get("active_netps", [])
		})
	get_tree().change_scene_to_file("res://scenes/net_room/net_room.tscn")


func _on_load_pressed() -> void:
	_open_load_picker()


func _on_device_switch_pressed() -> void:
	device_manager.switch_device()


func _on_device_changed(device_type: String) -> void:
	_update_device_label()
	print("Device switched to: %s" % device_type)


func _update_device_label() -> void:
	device_label.text = "Current: %s PED" % device_manager.get_device_name()
