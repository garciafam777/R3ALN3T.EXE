extends CharacterBody2D
class_name Researcher

@export var netp_name: String = "Researcher"
@export var tier: String = "OMEGA"
@export var type: String = "Controller"
@export var element: String = "Bio"

var personality_traits := {"analytical": 0.9, "patient": 0.85}
var abilities := ["Data Probe", "Sample Shield", "Hypothesis Field", "Breakthrough"]

func _ready() -> void:
	add_to_group("netp_agents")
	add_to_group("omega_tier")
