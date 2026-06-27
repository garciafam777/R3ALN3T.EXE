extends CharacterBody2D
class_name OpsMonitor

@export var netp_name: String = "OpsMonitor"
@export var tier: String = "OMEGA"
@export var type: String = "Technical"
@export var element: String = "Thermal"

var personality_traits := {"alert": 0.92, "methodical": 0.87}
var abilities := ["Metric Slash", "Uptime Guard", "Alert Cascade", "System Reboot"]

func _ready() -> void:
	add_to_group("netp_agents")
	add_to_group("omega_tier")
