extends CharacterBody2D
class_name Coder

signal ability_used(ability_name: String)

@export var netp_name: String = "Coder"
@export var tier: String = "OMEGA"
@export var type: String = "Technical"
@export var element: String = "Static"

var personality_traits := {"curious": 0.9, "precise": 0.85, "inventive": 0.8}
var abilities := ["Compile Strike", "Debug Shield", "Runtime Loop", "Kernel Panic"]

func _ready() -> void:
	add_to_group("netp_agents")
	add_to_group("omega_tier")
