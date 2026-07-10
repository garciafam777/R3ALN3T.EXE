extends Node
class_name CharacterCreatorLauncher

## Opens the character creator as an overlay or scene transition.

const CREATOR_SCENE := "res://scenes/ui/character_creator/character_creator.tscn"

static func open_as_overlay(parent: Node, device_manager: DeviceManager = null) -> CharacterCreator:
	var layer := CanvasLayer.new()
	layer.layer = 100
	parent.add_child(layer)
	var scene: PackedScene = load(CREATOR_SCENE)
	var creator: CharacterCreator = scene.instantiate()
	if device_manager:
		creator.set_device_manager(device_manager)
	layer.add_child(creator)
	creator.set_anchors_preset(Control.PRESET_FULL_RECT)
	creator.creator_closed.connect(layer.queue_free)
	return creator


static func open_as_scene(tree: SceneTree) -> void:
	tree.change_scene_to_file(CREATOR_SCENE)
