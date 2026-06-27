extends CharacterBody2D
class_name Security

# OMEGA Tier - 004+ Infrastructure
# Role: Network defense, threat neutralization, access control

signal dialogue_started(text: String)
signal dialogue_finished
signal ability_used(ability_name: String)

@export var netp_name: String = "Security"
@export var tier: String = "OMEGA"
@export var element: String = "Static"
@export var level: int = 1

# Core Stats
@export var hp: int = 280
@export var max_hp: int = 280
@export var atk: int = 55
@export var rapid: float = 0.10
@export var charge: int = 90
@export var defense: int = 55
@export var spd: int = 2

# Energy for abilities
@export var energy: int = 0
@export var max_energy: int = 100

# Personality traits for AI backend
var personality_traits = {
	"vigilant": 0.95,
	"strict": 0.9,
	"protective": 0.85,
	"tactical": 0.8
}

var abilities = [
	"Firewall Break",
	"Static Guard",
	"Lockdown Protocol",
	"Zero Hour" # Signature
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
	queue_free()

func use_ability(ability_index: int) -> void:
	if ability_index < 0 or ability_index >= abilities.size():
		return
	
	var ability_name = abilities[ability_index]
	print("%s uses %s" % [netp_name, ability_name])
	ability_used.emit(ability_name)
	
	match ability_name:
		"Firewall Break":
			_firewall_break()
		"Static Guard":
			_static_guard()
		"Lockdown Protocol":
			_lockdown_protocol()
		"Zero Hour":
			_zero_hour()

func _firewall_break() -> void:
	# Deal 1.8x ATK damage, pierces defense
	var damage = int(atk * 1.8)
	print("Firewall Break: %d piercing damage" % damage)
	energy = min(energy + 20, max_energy)

func _static_guard() -> void:
	# Apply damage reduction buff
	print("Static Guard activated - Damage reduction increased")
	energy = min(energy + 15, max_energy)

func _lockdown_protocol() -> void:
	# Immobilize enemies, deal 1.2x ATK damage
	var damage = int(atk * 1.2)
	print("Lockdown Protocol: %d damage, enemies immobilized" % damage)
	energy = min(energy + 25, max_energy)

func _zero_hour() -> void:
	# Signature ability - devastating attack
	if energy >= max_energy:
		var damage = int(atk * 4.0)
		print("Zero Hour (Signature): %d devastating damage" % damage)
		energy = 0
	else:
		print("Not enough energy for Zero Hour")

func generate_ai_response(player_input: String) -> String:
	# This will connect to Python backend
	var responses = [
		"Threat detected. Engaging countermeasures.",
		"Perimeter secure. No unauthorized access.",
		"Protocol violation. Initiating lockdown.",
		"All systems green. Standing by."
	]
	return responses[randi() % responses.size()]

func level_up() -> void:
	level += 1
	max_hp += 20
	hp = max_hp
	atk += 4
	defense += 4
	print("%s reached level %d!" % [netp_name, level])
