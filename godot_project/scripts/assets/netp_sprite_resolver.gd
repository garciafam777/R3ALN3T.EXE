class_name NetPSpriteResolver
extends RefCounted

## Resolves NetP / player / UI sprite paths from naming conventions.

const NETP_ROOT := "res://assets/sprites/netps/"
const PLAYER_ROOT := "res://assets/sprites/player/"
const UI_ROOT := "res://assets/sprites/ui/"


static func netp_portrait_path(netp_id: String, pose: String = "idle") -> String:
	var folder := _normalize_id(netp_id)
	return "%s%s/%s_portrait.svg" % [NETP_ROOT, folder, pose]


static func netp_full_path(data: NetPData, pose: String = "idle") -> String:
	var folder := _folder_for_data(data)
	var file_name := "%s_%s_%s_%s.svg" % [
		data.tier.to_lower(),
		data.type.to_lower(),
		data.element.to_lower(),
		pose
	]
	return NETP_ROOT + folder + "/" + file_name


static func netp_fallback_path(data: NetPData) -> String:
	var folder := _folder_for_data(data)
	return NETP_ROOT + folder + "/idle_portrait.svg"


static func player_avatar_path(realm: String = "r34l", pose: String = "idle") -> String:
	return "%splayer_%s_%s.svg" % [PLAYER_ROOT, realm.to_lower(), pose]


static func ui_icon_path(icon_name: String) -> String:
	return UI_ROOT + icon_name + ".svg"


static func load_texture(path: String) -> Texture2D:
	if not ResourceLoader.exists(path):
		return null
	var tex: Texture2D = load(path)
	return tex


static func load_netp_portrait(data: NetPData, pose: String = "idle") -> Texture2D:
	var paths := [
		netp_full_path(data, pose),
		netp_fallback_path(data),
		netp_portrait_path(_folder_for_data(data), pose),
		netp_portrait_path("default", "idle")
	]
	for path in paths:
		var tex := load_texture(path)
		if tex != null:
			return tex
	return null


static func _folder_for_data(data: NetPData) -> String:
	if not data.name.is_empty():
		return _normalize_id(data.name)
	if not data.id.is_empty():
		return _normalize_id(data.id.split("-")[0])
	return "default"


static func _normalize_id(value: String) -> String:
	var cleaned := value.strip_edges().replace(" ", "")
	if cleaned.is_empty():
		return "default"
	return cleaned
