extends Control
class_name PEDDeviceSelection

# PED Device Selection Menu
# Allows player to choose between Kernal and MOD devices

signal device_selected(device_type: int)
signal back_requested

@onready var kernal_button = $DeviceContainer/KernalCard/KernalContent/KernalSelectButton
@onready var mod_button = $DeviceContainer/MODCard/MODContent/MODSelectButton
@onready var back_button = $BackButton

var device_manager: DeviceManager = null

func _ready():
	kernal_button.pressed.connect(_on_kernal_selected)
	mod_button.pressed.connect(_on_mod_selected)
	back_button.pressed.connect(_on_back_pressed)
	
	# Apply visual styling to cards
	_style_kernal_card()
	_style_mod_card()
	
	print("PED Device Selection initialized")

func set_device_manager(manager: DeviceManager):
	device_manager = manager

func _on_kernal_selected() -> void:
	print("Kernal device selected")
	if device_manager:
		device_manager.switch_device()  # Will switch to Kernal if currently MOD
	device_selected.emit(DeviceManager.DeviceType.KERNAL)
	# Transition to main menu or next scene

func _on_mod_selected() -> void:
	print("MOD device selected")
	if device_manager:
		device_manager.switch_device()  # Will switch to MOD if currently Kernal
	device_selected.emit(DeviceManager.DeviceType.MOD)
	# Transition to main menu or next scene

func _on_back_pressed() -> void:
	print("Back to previous menu")
	back_requested.emit()
	# Return to previous scene

func _style_kernal_card():
	var card = $DeviceContainer/KernalCard
	var style_box = StyleBoxFlat.new()
	style_box.bg_color = Color(0.95, 0.95, 0.98)
	style_box.border_width_left = 3
	style_box.border_width_right = 3
	style_box.border_width_top = 3
	style_box.border_width_bottom = 3
	style_box.border_color = Color(0.2, 0.6, 1.0)
	style_box.corner_radius_top_left = 12
	style_box.corner_radius_top_right = 12
	style_box.corner_radius_bottom_left = 12
	style_box.corner_radius_bottom_right = 12
	card.add_theme_stylebox_override("panel", style_box)

func _style_mod_card():
	var card = $DeviceContainer/MODCard
	var style_box = StyleBoxFlat.new()
	style_box.bg_color = Color(0.15, 0.15, 0.2)
	style_box.border_width_left = 3
	style_box.border_width_right = 3
	style_box.border_width_top = 3
	style_box.border_width_bottom = 3
	style_box.border_color = Color(0.8, 0.2, 0.8)
	style_box.corner_radius_top_left = 12
	style_box.corner_radius_top_right = 12
	style_box.corner_radius_bottom_left = 12
	style_box.corner_radius_bottom_right = 12
	card.add_theme_stylebox_override("panel", style_box)

func highlight_device(device_type: int):
	# Highlight the selected device card
	match device_type:
		DeviceManager.DeviceType.KERNAL:
			kernal_button.modulate = Color(1, 1, 1, 1)
			mod_button.modulate = Color(0.5, 0.5, 0.5, 1)
		DeviceManager.DeviceType.MOD:
			mod_button.modulate = Color(1, 1, 1, 1)
			kernal_button.modulate = Color(0.5, 0.5, 0.5, 1)
