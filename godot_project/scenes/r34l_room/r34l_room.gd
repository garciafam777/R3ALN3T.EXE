extends Node2D
class_name R34LRoom

# Physical room where the player controls their Navi
# Entry point to encrypt into the N3T

signal encrypt_requested
signal decrypt_requested
signal governance_tasks_requested

@onready var encrypt_button = $SplitDesk/PersonalDesk/PersonalTerminal/EncryptButton
@onready var task_button = $SplitDesk/GovernanceDesk/GovernanceTerminal/TaskButton
@onready var player = $Player

var is_encrypted: bool = false

func _ready():
	encrypt_button.pressed.connect(_on_encrypt_pressed)
	task_button.pressed.connect(_on_tasks_pressed)
	if has_node("EncryptionManager"):
		$EncryptionManager.encryption_complete.connect(_on_encrypt_complete)
	print("R34L Room initialized - Split desk ready")


func _on_encrypt_pressed() -> void:
	if is_encrypted:
		return
	encrypt_requested.emit()
	if has_node("EncryptionManager"):
		$EncryptionManager.start_encrypting()
	else:
		get_tree().change_scene_to_file("res://scenes/net_room/net_room.tscn")


func _on_encrypt_complete() -> void:
	is_encrypted = true
	get_tree().change_scene_to_file("res://scenes/net_room/net_room.tscn")

func _on_tasks_pressed() -> void:
	print("Governance tasks requested...")
	governance_tasks_requested.emit()
	# Open task interface

func enable_encrypt() -> void:
	encrypt_button.disabled = false
	encrypt_button.modulate = Color(1, 1, 1, 1)

func disable_encrypt() -> void:
	encrypt_button.disabled = true
	encrypt_button.modulate = Color(0.5, 0.5, 0.5, 1)

func set_encrypted(status: bool) -> void:
	is_encrypted = status
	if is_encrypted:
		disable_encrypt()
	else:
		enable_encrypt()
