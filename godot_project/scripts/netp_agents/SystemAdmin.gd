extends CharacterBody2D
class_name SystemAdmin

# OMEGA Tier - 004+ Infrastructure
# Role: Network oversight, system management, AI coordination

signal dialogue_started(text: String)
signal dialogue_finished
signal ability_used(ability_name: String)

@export var netp_name: String = "SystemAdmin"
@export var tier: String = "OMEGA"
@export var element: String = "Quantum"
@export var level: int = 1

# Core Stats
@export var hp: int = 250
@export var max_hp: int = 250
@export var atk: int = 60
@export var rapid: float = 0.15
@export var charge: int = 95
@export var defense: int = 45
@export var spd: int = 3

# Energy for abilities
@export var energy: int = 0
@export var max_energy: int = 100

# Personality traits for AI backend
var personality_traits = {
	"analytical": 0.9,
	"authoritative": 0.8,
	"protective": 0.7,
	"efficient": 0.95
}

var abilities = [
	"System Override",
	"Data Shield",
	"Network Pulse",
	"Authority Command" # Signature
]

func _ready():
	add_to_group("netp_agents")
	add_to_group("omega_tier")
	print("%s initialized - Tier: %s, Element: %s" % [netp_name, tier, element])

func take_damage(amount: int) -> void:
	var actual_damage = max(0, amount - defense)
	hp -= actual_damage
	print("%s took %d damage (HP: %d/%d)" % [netp_name, actual_damage, hp, max_hp])
	
	if hp <= 0:
		defeat()

func defeat() -> void:
	print("%s has been defeated!" % netp_name)
	# Play defeat animation
	# Remove from combat
	queue_free()

func use_ability(ability_index: int) -> void:
	if ability_index < 0 or ability_index >= abilities.size():
		return
	
	var ability_name = abilities[ability_index]
	print("%s uses %s" % [netp_name, ability_name])
	ability_used.emit(ability_name)
	
	match ability_name:
		"System Override":
			_system_override()
		"Data Shield":
			_data_shield()
		"Network Pulse":
			_network_pulse()
		"Authority Command":
			_authority_command()

func _system_override() -> void:
	# Deal 2.0x ATK damage to single target
	var damage = int(atk * 2.0)
	print("System Override: %d damage" % damage)
	energy = min(energy + 20, max_energy)

func _data_shield() -> void:
	# Apply shield buff to self
	print("Data Shield activated - Defense increased")
	energy = min(energy + 15, max_energy)

func _network_pulse() -> void:
	# AoE damage 1.5x ATK to all enemies
	var damage = int(atk * 1.5)
	print("Network Pulse: %d AoE damage" % damage)
	energy = min(energy + 25, max_energy)

func _authority_command() -> void:
	# Signature ability - requires full energy
	if energy >= max_energy:
		var damage = int(atk * 3.5)
		print("Authority Command (Signature): %d massive damage" % damage)
		energy = 0
	else:
		print("Not enough energy for Authority Command")

func generate_ai_response(player_input: String) -> String:
	# This will connect to Python backend
	# Placeholder for now
	var responses = [
		"System parameters nominal. Proceed with caution.",
		"I detect irregularities in the data stream.",
		"Authorization granted. Executing protocol.",
		"Network integrity at 94%. Monitoring active."
	]
	return responses[randi() % responses.size()]

func level_up() -> void:
	level += 1
	max_hp += 15
	hp = max_hp
	atk += 5
	defense += 3
	print("%s reached level %d!" % [netp_name, level])
