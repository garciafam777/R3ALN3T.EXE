extends Node2D
class_name NetRoom

# Mirror room in the N3T where the NetP operates
# Digital reflection of the physical room

signal decrypt_requested
signal navigate_to_cyber_square
signal navigate_to_district(district_name: String)
signal customizer_requested
signal hidden_files_requested

@onready var decrypt_button = $EncryptDecryptNode/DecryptButton
@onready var customizer_button = $NetPCustomizerCloset/CustomizerButton
@onready var library_button = $HiddenFilesLibrary/LibraryButton
@onready var netp = $Navi
@onready var health_bar = $HUD/HealthBar
@onready var energy_bar = $HUD/EnergyBar

var current_netp: Node = null
var is_connected: bool = true

func _ready():
	decrypt_button.pressed.connect(_on_decrypt_pressed)
	customizer_button.pressed.connect(_on_customizer_pressed)
	library_button.pressed.connect(_on_library_pressed)
	if has_node("EncryptionManager"):
		$EncryptionManager.decryption_complete.connect(_on_decrypt_complete)
	print("N3T Room initialized - Connection established")


func _on_decrypt_pressed() -> void:
	if not is_connected:
		return
	decrypt_requested.emit()
	if has_node("EncryptionManager"):
		$EncryptionManager.start_decrypting()
	else:
		get_tree().change_scene_to_file("res://scenes/r34l_room/r34l_room.tscn")


func _on_decrypt_complete() -> void:
	get_tree().change_scene_to_file("res://scenes/r34l_room/r34l_room.tscn")

func _on_customizer_pressed() -> void:
	print("Persona Customizer requested...")
	customizer_requested.emit()
	var dm := _find_device_manager()
	var customizer := PersonaCustomizerLauncher.open_as_overlay(self, dm)
	customizer.layout_saved.connect(_on_customizer_layout_saved)
	customizer.customizer_closed.connect(func(): print("Persona customizer closed"))


func _find_device_manager() -> DeviceManager:
	var nodes := get_tree().get_nodes_in_group("device_manager")
	if not nodes.is_empty() and nodes[0] is DeviceManager:
		return nodes[0]
	return null


func _on_customizer_layout_saved(state: Dictionary) -> void:
	print("Persona layout saved from N3T Room")

func _on_library_pressed() -> void:
	print("Hidden Files Library requested...")
	hidden_files_requested.emit()
	# Open hidden files interface

func set_active_netp(netp_agent: Node) -> void:
	current_netp = netp_agent
	print("Active NetP set to: %s" % netp_agent.netp_name)
	_update_hud()

func _update_hud() -> void:
	if current_netp:
		health_bar.max_value = current_netp.max_hp
		health_bar.value = current_netp.hp
		energy_bar.max_value = current_netp.max_energy
		energy_bar.value = current_netp.energy

func update_hud_from_netp(hp: int, max_hp: int, energy: int, max_energy: int) -> void:
	health_bar.max_value = max_hp
	health_bar.value = hp
	energy_bar.max_value = max_energy
	energy_bar.value = energy

func navigate_to(destination: String) -> void:
	match destination:
		"cyber_square":
			navigate_to_cyber_square.emit()
		_:
			navigate_to_district.emit(destination)

func enable_data_streams(enabled: bool) -> void:
	# Toggle visual data stream effects
	$DataStreams.visible = enabled

func set_connection_status(status: bool) -> void:
	is_connected = status
	if not is_connected:
		decrypt_button.disabled = true
		decrypt_button.text = "DISCONNECTED"
	else:
		decrypt_button.disabled = false
		decrypt_button.text = "DECRYPT"
