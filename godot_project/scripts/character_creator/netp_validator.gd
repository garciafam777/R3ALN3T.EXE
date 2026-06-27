class_name NetPValidator
extends RefCounted

const SAVE_DIR := "user://netp_saves/"


static func validate(data: NetPData, content: Dictionary, roster_ids: Array = []) -> Dictionary:
	var errors: Array[String] = []
	var warnings: Array[String] = []

	if data.name.strip_edges().is_empty():
		errors.append("Name is required.")
	elif data.name.length() < 2:
		errors.append("Name must be at least 2 characters.")

	if data.id.strip_edges().is_empty():
		errors.append("ID is required.")

	for existing_id in roster_ids:
		if str(existing_id) == data.id:
			warnings.append("ID already exists in roster; saving will overwrite.")

	var tier_entry := NetPContent.get_tier(content, data.tier)
	if tier_entry.is_empty():
		errors.append("Invalid tier: %s" % data.tier)

	var type_entry := NetPContent.get_type(content, data.type)
	if type_entry.is_empty():
		errors.append("Invalid type: %s" % data.type)

	var element_entry := NetPContent.get_element(content, data.element)
	if element_entry.is_empty():
		errors.append("Invalid element: %s" % data.element)
	else:
		if element_entry.get("omega_tier_only", false) and data.tier != "OMEGA":
			errors.append("Element %s is available only for OMEGA tier." % data.element)
		var restricted: Array = element_entry.get("restricted_types", [])
		if not restricted.is_empty() and data.type not in restricted:
			errors.append("Element %s is restricted for type %s." % [data.element, data.type])

	if not tier_entry.is_empty():
		_validate_stats(data, tier_entry, errors)

	_validate_programs(data, content, errors)

	return {
		"valid": errors.is_empty(),
		"errors": errors,
		"warnings": warnings
	}


static func _validate_stats(data: NetPData, tier_entry: Dictionary, errors: Array[String]) -> void:
	var bands: Dictionary = tier_entry.get("stat_bands", {})
	for stat_key in ["hp", "atk", "rapid", "charge", "def"]:
		var band: Array = bands.get(stat_key, [])
		if band.size() < 2:
			continue
		var value: int = int(data.stats.get(stat_key, 0))
		if value < band[0] or value > band[1]:
			errors.append("%s (%d) must be between %d and %d for tier %s." % [
				stat_key.to_upper(), value, band[0], band[1], data.tier
			])


static func _validate_programs(data: NetPData, content: Dictionary, errors: Array[String]) -> void:
	var available := NetPContent.programs_for_character(content, data)
	var available_names: Array = []
	for prog in available:
		available_names.append(prog.get("name", ""))

	for slot in ["primary", "secondary", "passive", "ultimate", "signature"]:
		var equipped: String = str(data.programs.get(slot, ""))
		if equipped.is_empty():
			if slot in ["primary", "secondary"]:
				errors.append("%s program slot is required." % slot.capitalize())
			continue
		if equipped not in available_names:
			errors.append("Program '%s' in %s slot is not available for this character." % [equipped, slot])


static func save_character(data: NetPData) -> Error:
	var result := validate(data, NetPContent.load_content())
	if not result["valid"]:
		push_warning("Cannot save invalid character: %s" % ", ".join(result["errors"]))
		return ERR_INVALID_DATA

	DirAccess.make_dir_recursive_absolute(SAVE_DIR)
	var path := SAVE_DIR + data.id + ".json"
	var file := FileAccess.open(path, FileAccess.WRITE)
	if file == null:
		return ERR_CANT_CREATE
	file.store_string(JSON.stringify(data.to_dict(), "\t"))
	file.close()
	return OK


static func load_character(character_id: String) -> NetPData:
	var path := SAVE_DIR + character_id + ".json"
	if not FileAccess.file_exists(path):
		return null
	var file := FileAccess.open(path, FileAccess.READ)
	if file == null:
		return null
	var parsed: Variant = JSON.parse_string(file.get_as_text())
	file.close()
	if parsed is Dictionary:
		return NetPData.from_dict(parsed)
	return null


static func list_saved_ids() -> Array[String]:
	var ids: Array[String] = []
	if not DirAccess.dir_exists_absolute(SAVE_DIR):
		return ids
	var dir := DirAccess.open(SAVE_DIR)
	if dir == null:
		return ids
	dir.list_dir_begin()
	var file_name := dir.get_next()
	while file_name != "":
		if not dir.current_is_dir() and file_name.ends_with(".json"):
			ids.append(file_name.trim_suffix(".json"))
		file_name = dir.get_next()
	dir.list_dir_end()
	return ids


static func export_character(data: NetPData, export_path: String) -> Error:
	var result := validate(data, NetPContent.load_content())
	if not result["valid"]:
		return ERR_INVALID_DATA
	var file := FileAccess.open(export_path, FileAccess.WRITE)
	if file == null:
		return ERR_CANT_CREATE
	file.store_string(JSON.stringify(data.to_dict(), "\t"))
	file.close()
	return OK
