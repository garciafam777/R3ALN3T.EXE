class_name NetPContent
extends RefCounted

const CONTENT_PATH := "res://data/netp_content.json"

static var _cache: Dictionary = {}


static func load_content() -> Dictionary:
	if not _cache.is_empty():
		return _cache
	var file := FileAccess.open(CONTENT_PATH, FileAccess.READ)
	if file == null:
		push_error("Failed to load NetP content: %s" % CONTENT_PATH)
		return {}
	var parsed: Variant = JSON.parse_string(file.get_as_text())
	file.close()
	if parsed is Dictionary:
		_cache = parsed
	else:
		push_error("Invalid NetP content JSON")
		_cache = {}
	return _cache


static func get_tier(content: Dictionary, tier_id: String) -> Dictionary:
	for entry in content.get("tiers", []):
		if entry.get("id", "") == tier_id:
			return entry
	return {}


static func get_type(content: Dictionary, type_id: String) -> Dictionary:
	for entry in content.get("types", []):
		if entry.get("id", "") == type_id:
			return entry
	return {}


static func get_element(content: Dictionary, element_id: String) -> Dictionary:
	for entry in content.get("elements", []):
		if entry.get("id", "") == element_id:
			return entry
	return {}


static func tier_ids(content: Dictionary) -> Array:
	var ids: Array = []
	for entry in content.get("tiers", []):
		ids.append(entry.get("id", ""))
	return ids


static func type_ids(content: Dictionary) -> Array:
	var ids: Array = []
	for entry in content.get("types", []):
		ids.append(entry.get("id", ""))
	return ids


static func element_ids_for_type(content: Dictionary, type_id: String, tier_id: String = "") -> Array:
	var ids: Array = []
	for entry in content.get("elements", []):
		if entry.get("omega_tier_only", false) and tier_id != "OMEGA":
			continue
		var restricted: Array = entry.get("restricted_types", [])
		if restricted.is_empty() or type_id in restricted:
			ids.append(entry.get("id", ""))
	return ids


static func programs_for_character(content: Dictionary, data: NetPData) -> Array:
	var results: Array = []
	var tier_rank := _tier_rank(data.tier)
	for prog in content.get("programs", []):
		if prog.get("omega_only", false) and data.tier != "OMEGA":
			continue
		var prog_rank := _tier_rank(str(prog.get("rarity", "PSI")))
		if prog_rank > tier_rank + 1:
			continue
		results.append(prog)
	return results


static func _tier_rank(tier_id: String) -> int:
	var order := ["PSI", "ZETA", "EPSILON", "DELTA", "GAMMA", "BETA", "ALPHA", "OMEGA"]
	var idx := order.find(tier_id)
	return idx if idx >= 0 else 0
