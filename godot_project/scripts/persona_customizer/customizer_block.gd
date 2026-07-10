class_name CustomizerBlock
extends RefCounted

enum Family { CORE, SUPPORT, HAZARD, MUTATOR, ADMIN }

var family: int = Family.CORE
var block_id: String = ""
var label: String = ""
var primary_color: Color = Color("#00FFFF")
var heat_cost: float = 0.0


static func library() -> Array:
	return [
		_make(Family.CORE, "core_anchor", "Core Anchor", "#00FFFF", 0),
		_make(Family.CORE, "core_pulse", "Core Pulse", "#0066FF", 1),
		_make(Family.SUPPORT, "support_link", "Support Link", "#44FF88", 0),
		_make(Family.SUPPORT, "support_boost", "Support Boost", "#88FFCC", 2),
		_make(Family.HAZARD, "hazard_spike", "Hazard Spike", "#FF4400", 4),
		_make(Family.HAZARD, "hazard_void", "Hazard Void", "#8B00FF", 5),
		_make(Family.MUTATOR, "mutator_glitch", "Mutator Glitch", "#FF00FF", 6),
		_make(Family.MUTATOR, "mutator_shift", "Mutator Shift", "#FF66CC", 3),
		_make(Family.ADMIN, "admin_override", "Admin Override", "#FFE566", 0),
		_make(Family.ADMIN, "admin_lock", "Admin Lock", "#FFAA00", 2),
	]


static func family_name(family: int) -> String:
	match family:
		Family.CORE: return "Core"
		Family.SUPPORT: return "Support"
		Family.HAZARD: return "Hazard"
		Family.MUTATOR: return "Mutator"
		Family.ADMIN: return "Admin"
		_: return "Unknown"


static func _make(family: int, block_id: String, label: String, color_hex: String, heat: float) -> CustomizerBlock:
	var b := CustomizerBlock.new()
	b.family = family
	b.block_id = block_id
	b.label = label
	b.primary_color = Color(color_hex)
	b.heat_cost = heat
	return b


func to_token() -> CustomizerGridToken:
	var t := CustomizerGridToken.new()
	t.id = block_id
	t.display_name = label
	t.primary_color = primary_color
	t.type = family_name(family)
	return t
