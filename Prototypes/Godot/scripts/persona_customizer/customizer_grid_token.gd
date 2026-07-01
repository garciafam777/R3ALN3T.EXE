class_name CustomizerGridToken
extends RefCounted

## Lightweight NetP token for grid placement (data-driven).

var id: String = ""
var display_name: String = "NetP"
var tier: String = "GAMMA"
var type: String = "Guardian"
var element: String = "Radiant"
var primary_color: Color = Color("#00FFFF")
var secondary_color: Color = Color("#FF00FF")


static func from_netp_data(data: NetPData) -> CustomizerGridToken:
	var token := CustomizerGridToken.new()
	token.id = data.id
	token.display_name = data.name
	token.tier = data.tier
	token.type = data.type
	token.element = data.element
	var colors: Dictionary = data.appearance.get("colors", {})
	if colors.has("primary"):
		token.primary_color = Color(str(colors["primary"]))
	if colors.has("secondary"):
		token.secondary_color = Color(str(colors["secondary"]))
	return token


static func from_dict(source: Dictionary) -> CustomizerGridToken:
	var token := CustomizerGridToken.new()
	token.id = str(source.get("id", ""))
	token.display_name = str(source.get("name", "NetP"))
	token.tier = str(source.get("tier", "GAMMA"))
	token.type = str(source.get("type", "Guardian"))
	token.element = str(source.get("element", "Radiant"))
	if source.has("primary_color"):
		token.primary_color = Color(str(source["primary_color"]))
	return token


func to_dict() -> Dictionary:
	return {
		"id": id,
		"name": display_name,
		"tier": tier,
		"type": type,
		"element": element,
		"primary_color": primary_color.to_html(false),
		"secondary_color": secondary_color.to_html(false)
	}
