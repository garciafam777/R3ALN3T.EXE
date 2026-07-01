class_name GameSaveManager
extends RefCounted

## Encrypted game save slots (up to 10) with public metadata previews.

const MAX_SLOTS := 10
const SAVE_DIR := "user://game_saves/"


static func _ensure_dir() -> void:
	DirAccess.make_dir_recursive_absolute(SAVE_DIR)


static func _meta_path(slot: int) -> String:
	return SAVE_DIR + "slot_%02d.meta.json" % slot


static func _data_path(slot: int) -> String:
	return SAVE_DIR + "slot_%02d.dat" % slot


static func _default_meta(slot: int) -> Dictionary:
	return {
		"slot": slot,
		"occupied": false,
		"character_name": "",
		"last_played": "",
		"location": "R34L",
		"man_balance": 0,
		"active_netps": [],
		"password_hash": "",
		"salt": ""
	}


static func _default_game_state(player_name: String) -> Dictionary:
	return {
		"player_name": player_name,
		"location": "R34L",
		"man_balance": 500,
		"active_netps": ["Security", "SystemAdmin"],
		"netp_roster": [],
		"customizer_layout": {},
		"play_time_seconds": 0,
		"created_at": Time.get_datetime_string_from_system()
	}


static func list_all_slots() -> Array:
	_ensure_dir()
	var slots: Array = []
	for i in range(1, MAX_SLOTS + 1):
		slots.append(read_slot_meta(i))
	return slots


static func read_slot_meta(slot: int) -> Dictionary:
	_ensure_dir()
	var path := _meta_path(slot)
	if not FileAccess.file_exists(path):
		return _default_meta(slot)
	var file := FileAccess.open(path, FileAccess.READ)
	if file == null:
		return _default_meta(slot)
	var parsed: Variant = JSON.parse_string(file.get_as_text())
	file.close()
	if parsed is Dictionary:
		parsed["slot"] = slot
		return parsed
	return _default_meta(slot)


static func is_occupied(slot: int) -> bool:
	return read_slot_meta(slot).get("occupied", false)


static func create_new_game(slot: int, player_name: String, password: String) -> Error:
	if slot < 1 or slot > MAX_SLOTS:
		return ERR_INVALID_PARAMETER
	if player_name.strip_edges().is_empty():
		return ERR_INVALID_DATA
	if password.length() < 4:
		return ERR_INVALID_DATA
	if is_occupied(slot):
		return ERR_ALREADY_EXISTS

	_ensure_dir()
	var salt := _generate_salt()
	var state := _default_game_state(player_name.strip_edges())
	var meta := _default_meta(slot)
	meta["occupied"] = true
	meta["character_name"] = player_name.strip_edges()
	meta["last_played"] = Time.get_datetime_string_from_system()
	meta["location"] = state["location"]
	meta["man_balance"] = state["man_balance"]
	meta["active_netps"] = state["active_netps"]
	meta["salt"] = salt
	meta["password_hash"] = _hash_password(password, salt)

	var write_meta := _write_json(_meta_path(slot), meta)
	if write_meta != OK:
		return write_meta
	return _write_encrypted(slot, password, state)


static func verify_password(slot: int, password: String) -> bool:
	var meta := read_slot_meta(slot)
	if not meta.get("occupied", false):
		return false
	var salt: String = meta.get("salt", "")
	return _hash_password(password, salt) == meta.get("password_hash", "")


static func load_game(slot: int, password: String) -> Dictionary:
	if not verify_password(slot, password):
		return {}
	var path := _data_path(slot)
	if not FileAccess.file_exists(path):
		return {}
	var file := FileAccess.open(path, FileAccess.READ)
	if file == null:
		return {}
	var encoded := file.get_as_text()
	file.close()
	var decoded := _decode_payload(encoded, password)
	if decoded.is_empty():
		return {}
	_touch_last_played(slot, decoded)
	return decoded


static func save_game(slot: int, password: String, state: Dictionary) -> Error:
	if not verify_password(slot, password):
		return ERR_INVALID_DATA
	var meta := read_slot_meta(slot)
	meta["character_name"] = state.get("player_name", meta.get("character_name", ""))
	meta["last_played"] = Time.get_datetime_string_from_system()
	meta["location"] = state.get("location", "R34L")
	meta["man_balance"] = state.get("man_balance", 0)
	meta["active_netps"] = state.get("active_netps", [])
	var err := _write_json(_meta_path(slot), meta)
	if err != OK:
		return err
	return _write_encrypted(slot, password, state)


static func delete_slot(slot: int, password: String = "") -> Error:
	if slot < 1 or slot > MAX_SLOTS:
		return ERR_INVALID_PARAMETER
	if is_occupied(slot):
		if password.is_empty() or not verify_password(slot, password):
			return ERR_INVALID_DATA
	if FileAccess.file_exists(_meta_path(slot)):
		DirAccess.remove_absolute(_meta_path(slot))
	if FileAccess.file_exists(_data_path(slot)):
		DirAccess.remove_absolute(_data_path(slot))
	return OK


static func update_slot_preview(slot: int, patch: Dictionary) -> void:
	var meta := read_slot_meta(slot)
	if not meta.get("occupied", false):
		return
	for key in ["character_name", "location", "man_balance", "active_netps"]:
		if patch.has(key):
			meta[key] = patch[key]
	meta["last_played"] = Time.get_datetime_string_from_system()
	_write_json(_meta_path(slot), meta)


static func _touch_last_played(slot: int, state: Dictionary) -> void:
	update_slot_preview(slot, {
		"character_name": state.get("player_name", ""),
		"location": state.get("location", "R34L"),
		"man_balance": state.get("man_balance", 0),
		"active_netps": state.get("active_netps", [])
	})


static func _write_encrypted(slot: int, password: String, state: Dictionary) -> Error:
	var json_text := JSON.stringify(state)
	var encoded := _encode_payload(json_text, password)
	var file := FileAccess.open(_data_path(slot), FileAccess.WRITE)
	if file == null:
		return ERR_CANT_CREATE
	file.store_string(encoded)
	file.close()
	return OK


static func _encode_payload(text: String, password: String) -> String:
	var key := password.sha256_buffer()
	var bytes := text.to_utf8_buffer()
	for i in bytes.size():
		bytes[i] = bytes[i] ^ key[i % key.size()]
	return Marshalls.raw_to_base64(bytes)


static func _decode_payload(encoded: String, password: String) -> Dictionary:
	var key := password.sha256_buffer()
	var bytes := Marshalls.base64_to_raw(encoded)
	if bytes.is_empty():
		return {}
	for i in bytes.size():
		bytes[i] = bytes[i] ^ key[i % key.size()]
	var parsed: Variant = JSON.parse_string(bytes.get_string_from_utf8())
	if parsed is Dictionary:
		return parsed
	return {}


static func _hash_password(password: String, salt: String) -> String:
	return (salt + ":" + password).sha256_text()


static func _generate_salt() -> String:
	return str(randi() % 1000000) + Time.get_unix_time_from_system()


static func _write_json(path: String, data: Dictionary) -> Error:
	var file := FileAccess.open(path, FileAccess.WRITE)
	if file == null:
		return ERR_CANT_CREATE
	file.store_string(JSON.stringify(data, "\t"))
	file.close()
	return OK
