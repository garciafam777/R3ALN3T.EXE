extends Node
class_name DeviceManager

enum DeviceType { KERNAL, MOD }

signal device_changed(device_type: String)

var current_device = DeviceType.KERNAL
var device_level = 1

# Device properties
var device_properties = {
	DeviceType.KERNAL: {
		"name": "Kernal",
		"description": "Premium, clean, simple interface",
		"ui_theme": "premium",
		"customization_level": 1,
		"admin_access": false
	},
	DeviceType.MOD: {
		"name": "MOD",
		"description": "Highly customizable, admin-focused",
		"ui_theme": "custom",
		"customization_level": 5,
		"admin_access": true
	}
}

func _ready():
	add_to_group("device_manager")
	print("Device Manager initialized - Current: %s" % get_device_name())

func switch_device():
	if current_device == DeviceType.KERNAL:
		current_device = DeviceType.MOD
	else:
		current_device = DeviceType.KERNAL
	
	var device_name = get_device_name()
	print("Switched to %s PED - %s" % [device_name, device_properties[current_device]["description"]])
	device_changed.emit(device_name)

func get_device_type() -> int:
	return current_device

func get_device_name() -> String:
	return device_properties[current_device]["name"]

func get_device_description() -> String:
	return device_properties[current_device]["description"]

func get_ui_theme() -> String:
	return device_properties[current_device]["ui_theme"]

func get_customization_level() -> int:
	return device_properties[current_device]["customization_level"]

func has_admin_access() -> bool:
	return device_properties[current_device]["admin_access"]

func set_device_level(level: int):
	device_level = clamp(level, 1, 10)
	print("Device level set to: %d" % device_level)

func get_device_level() -> int:
	return device_level

func is_kernal() -> bool:
	return current_device == DeviceType.KERNAL

func is_mod() -> bool:
	return current_device == DeviceType.MOD
