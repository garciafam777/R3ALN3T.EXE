extends CharacterBody2D
class_name Gatekeeper

@export var netp_name: String = "Gatekeeper"
@export var tier: String = "OMEGA"
@export var type: String = "Guardian"
@export var element: String = "Radiant"

var personality_traits := {"stoic": 0.9, "judicial": 0.88}
var abilities := ["Access Deny", "Threshold Ward", "Audit Beam", "Final Verdict"]

func _ready() -> void:
	add_to_group("netp_agents")
	add_to_group("omega_tier")
