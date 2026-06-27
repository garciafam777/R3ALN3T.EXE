extends CanvasLayer

signal flashback_toggled(enabled: bool)

var retro_enabled: bool = false
var _overlay: ColorRect


func _ready() -> void:
	layer = 128
	process_mode = Node.PROCESS_MODE_ALWAYS
	_overlay = ColorRect.new()
	_overlay.set_anchors_preset(Control.PRESET_FULL_RECT)
	_overlay.mouse_filter = Control.MOUSE_FILTER_IGNORE
	_overlay.visible = false
	_overlay.color = Color(0.08, 0.02, 0.12, 0.35)
	add_child(_overlay)


func toggle_flashback() -> void:
	retro_enabled = not retro_enabled
	_apply()
	flashback_toggled.emit(retro_enabled)


func set_flashback(enabled: bool) -> void:
	retro_enabled = enabled
	_apply()
	flashback_toggled.emit(retro_enabled)


func _apply() -> void:
	_overlay.visible = retro_enabled
	if retro_enabled:
		get_viewport().canvas_item_default_texture_filter = Viewport.DEFAULT_CANVAS_ITEM_TEXTURE_FILTER_NEAREST
	else:
		get_viewport().canvas_item_default_texture_filter = Viewport.DEFAULT_CANVAS_ITEM_TEXTURE_FILTER_LINEAR
	var root := get_tree().root
	if root:
		root.modulate = Color(0.85, 0.95, 1.0, 1.0) if retro_enabled else Color.WHITE
