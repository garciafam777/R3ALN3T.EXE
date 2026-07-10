class_name PersonaCustomizerLauncher
extends RefCounted

const SCENE_PATH := "res://scenes/persona_customizer/persona_customizer.tscn"


static func open_as_overlay(parent: Node, device_manager: DeviceManager = null) -> PersonaCustomizer:
	var layer := CanvasLayer.new()
	layer.layer = 100
	parent.add_child(layer)
	var scene: PackedScene = load(SCENE_PATH)
	var customizer: PersonaCustomizer = scene.instantiate()
	if device_manager:
		customizer.set_device_manager(device_manager)
	layer.add_child(customizer)
	customizer.set_anchors_preset(Control.PRESET_FULL_RECT)
	customizer.customizer_closed.connect(layer.queue_free)
	return customizer


static func open_as_scene(tree: SceneTree) -> void:
	tree.change_scene_to_file(SCENE_PATH)
