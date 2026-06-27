class_name NetPData
extends Resource

## Source-of-truth character record for the creator and gameplay import.

@export var id: String = ""
@export var name: String = "New NetP"
@export var tier: String = "GAMMA"
@export var type: String = "Guardian"
@export var element: String = "Radiant"
@export var role: String = "Defender"
@export var faction: String = "Unassigned"
@export var pronouns: String = "they/them"

@export var appearance: Dictionary = {
	"body": {"body_type": "Athletic", "height": 1.0},
	"face": {"face_shape": "Angular", "eye_type": "Standard"},
	"hair": {"hair_style": "Short"},
	"colors": {"primary": "#00FFFF", "secondary": "#FF00FF", "glow": "#0066FF"}
}

@export var stats: Dictionary = {
	"hp": 600,
	"atk": 100,
	"rapid": 70,
	"charge": 90,
	"def": 75
}

@export var programs: Dictionary = {
	"primary": "",
	"secondary": "",
	"passive": "",
	"ultimate": "",
	"signature": ""
}


static func create_default() -> NetPData:
	var data := NetPData.new()
	data.id = _generate_id("GAMMA")
	data._apply_tier_defaults()
	return data


static func from_dict(source: Dictionary) -> NetPData:
	var data := NetPData.new()
	data.id = str(source.get("id", ""))
	data.name = str(source.get("name", "New NetP"))
	data.tier = str(source.get("tier", "GAMMA"))
	data.type = str(source.get("type", "Guardian"))
	data.element = str(source.get("element", "Radiant"))
	data.role = str(source.get("role", "Defender"))
	data.faction = str(source.get("faction", "Unassigned"))
	data.pronouns = str(source.get("pronouns", "they/them"))
	if source.has("appearance") and source["appearance"] is Dictionary:
		data.appearance = source["appearance"].duplicate(true)
	if source.has("stats") and source["stats"] is Dictionary:
		data.stats = source["stats"].duplicate(true)
	if source.has("programs") and source["programs"] is Dictionary:
		data.programs = source["programs"].duplicate(true)
	return data


func to_dict() -> Dictionary:
	return {
		"id": id,
		"name": name,
		"tier": tier,
		"type": type,
		"element": element,
		"role": role,
		"faction": faction,
		"pronouns": pronouns,
		"appearance": appearance.duplicate(true),
		"stats": stats.duplicate(true),
		"programs": programs.duplicate(true)
	}


func duplicate_data() -> NetPData:
	return from_dict(to_dict())


func apply_tier(tier_id: String, content: Dictionary) -> void:
	tier = tier_id
	_apply_tier_defaults(content)


func _apply_tier_defaults(content: Dictionary = {}) -> void:
	if content.is_empty():
		content = NetPContent.load_content()
	var tier_entry := NetPContent.get_tier(content, tier)
	if tier_entry.is_empty():
		return
	var bands: Dictionary = tier_entry.get("stat_bands", {})
	for stat_key in ["hp", "atk", "rapid", "charge", "def"]:
		var band: Array = bands.get(stat_key, [100, 200])
		if band.size() >= 2:
			stats[stat_key] = int((band[0] + band[1]) / 2.0)


func apply_type_bias(content: Dictionary) -> void:
	var type_entry := NetPContent.get_type(content, type)
	if type_entry.is_empty():
		return
	var tier_entry := NetPContent.get_tier(content, tier)
	if tier_entry.is_empty():
		return
	var bands: Dictionary = tier_entry.get("stat_bands", {})
	var bias: Dictionary = type_entry.get("stat_bias", {})
	for stat_key in ["hp", "atk", "rapid", "charge", "def"]:
		var band: Array = bands.get(stat_key, [100, 200])
		if band.size() < 2:
			continue
		var mid := (band[0] + band[1]) / 2.0
		var multiplier: float = bias.get(stat_key, 1.0)
		stats[stat_key] = int(mid * multiplier)


static func _generate_id(tier_id: String) -> String:
	var suffix := "%03d" % (randi() % 999 + 1)
	return "%s-%s" % [tier_id, suffix]
