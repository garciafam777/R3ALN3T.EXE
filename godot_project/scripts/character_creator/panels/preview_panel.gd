class_name PreviewPanel
extends PanelContainer

var _data: NetPData
var _viewport_size: Vector2

var _title_label: Label
var _subtitle_label: Label
var _summary_label: Label
var _border: PanelContainer
var _viewport: ColorRect
var _portrait_rect: ColorRect
var _portrait_sprite: TextureRect
var _rotate_btn: Button
var _zoom_slider: HSlider
var _pose_btn: Button
var _rotation: float = 0.0
var _zoom: float = 1.0
var _pose: String = "idle"


func setup(data: NetPData, viewport_size: Vector2) -> void:
	_data = data
	_viewport_size = viewport_size
	_build_ui()
	refresh()
	CreatorTheme.set_test_id(self, "preview-panel")


func set_data(data: NetPData) -> void:
	_data = data
	refresh()


func _build_ui() -> void:
	add_theme_stylebox_override("panel", CreatorTheme.make_panel_style(_viewport_size, CreatorTheme.ACCENT_MAGENTA))
	size_flags_horizontal = Control.SIZE_EXPAND_FILL
	size_flags_vertical = Control.SIZE_EXPAND_FILL

	var root := VBoxContainer.new()
	root.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	root.size_flags_vertical = Control.SIZE_EXPAND_FILL
	root.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 8))
	add_child(root)

	_title_label = Label.new()
	_title_label.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	_title_label.label_settings = CreatorTheme.label_settings(_viewport_size, 28, CreatorTheme.ACCENT_CYAN)
	root.add_child(_title_label)

	_subtitle_label = Label.new()
	_subtitle_label.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	_subtitle_label.label_settings = CreatorTheme.label_settings(_viewport_size, 16, CreatorTheme.TEXT_DIM)
	root.add_child(_subtitle_label)

	_border = PanelContainer.new()
	_border.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	_border.size_flags_vertical = Control.SIZE_EXPAND_FILL
	_border.custom_minimum_size = Vector2(0, CreatorTheme.spacing(_viewport_size, 320))
	var border_style := CreatorTheme.make_panel_style(_viewport_size, CreatorTheme.ACCENT_MAGENTA)
	border_style.border_width_bottom = int(4 * CreatorTheme.scale_factor(_viewport_size))
	_border.add_theme_stylebox_override("panel", border_style)
	CreatorTheme.set_test_id(_border, "preview-border")
	root.add_child(_border)

	_viewport = ColorRect.new()
	_viewport.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	_viewport.size_flags_vertical = Control.SIZE_EXPAND_FILL
	_viewport.color = Color(0.04, 0.06, 0.12)
	CreatorTheme.set_test_id(_viewport, "preview-viewport")
	_border.add_child(_viewport)

	var portrait_size := Vector2(180, 280) * CreatorTheme.scale_factor(_viewport_size)

	_portrait_rect = ColorRect.new()
	_portrait_rect.custom_minimum_size = portrait_size
	_portrait_rect.color = Color(0.2, 0.5, 0.9, 0.35)
	_viewport.add_child(_portrait_rect)
	_portrait_rect.set_anchors_preset(Control.PRESET_CENTER)
	_portrait_rect.offset_left = -portrait_size.x / 2.0
	_portrait_rect.offset_top = -portrait_size.y / 2.0
	_portrait_rect.offset_right = portrait_size.x / 2.0
	_portrait_rect.offset_bottom = portrait_size.y / 2.0

	_portrait_sprite = TextureRect.new()
	_portrait_sprite.custom_minimum_size = portrait_size
	_portrait_sprite.expand_mode = TextureRect.EXPAND_IGNORE_SIZE
	_portrait_sprite.stretch_mode = TextureRect.STRETCH_KEEP_ASPECT_CENTERED
	_viewport.add_child(_portrait_sprite)
	_portrait_sprite.set_anchors_preset(Control.PRESET_CENTER)
	_portrait_sprite.offset_left = -portrait_size.x / 2.0
	_portrait_sprite.offset_top = -portrait_size.y / 2.0
	_portrait_sprite.offset_right = portrait_size.x / 2.0
	_portrait_sprite.offset_bottom = portrait_size.y / 2.0

	var controls := HBoxContainer.new()
	controls.alignment = BoxContainer.ALIGNMENT_CENTER
	controls.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 12))
	root.add_child(controls)

	_rotate_btn = Button.new()
	_rotate_btn.text = "Rotate"
	_rotate_btn.pressed.connect(_on_rotate)
	controls.add_child(_rotate_btn)

	_zoom_slider = HSlider.new()
	_zoom_slider.min_value = 0.5
	_zoom_slider.max_value = 2.0
	_zoom_slider.step = 0.1
	_zoom_slider.value = 1.0
	_zoom_slider.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	_zoom_slider.value_changed.connect(_on_zoom_changed)
	controls.add_child(_zoom_slider)

	_pose_btn = Button.new()
	_pose_btn.text = "Pose: Idle"
	_pose_btn.pressed.connect(_on_pose_toggle)
	controls.add_child(_pose_btn)

	_summary_label = Label.new()
	_summary_label.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	_summary_label.label_settings = CreatorTheme.label_settings(_viewport_size, 13, CreatorTheme.TEXT_DIM)
	_summary_label.accessibility_description = "Appearance summary"
	root.add_child(_summary_label)


func refresh() -> void:
	_title_label.text = _data.name if not _data.name.is_empty() else "Unnamed NetP"
	_subtitle_label.text = "%s · %s · %s" % [_data.tier, _data.type, _data.element]

	var element_entry := NetPContent.get_element(NetPContent.load_content(), _data.element)
	var glow_color := Color(str(_data.appearance.get("colors", {}).get("glow", "#0066FF")))
	if not element_entry.is_empty():
		glow_color = Color(str(element_entry.get("color", "#00FFFF")))

	_portrait_rect.color = glow_color
	_portrait_rect.modulate.a = 0.45

	var texture := NetPSpriteResolver.load_netp_portrait(_data, _pose)
	if texture != null:
		_portrait_sprite.texture = texture
		_portrait_sprite.modulate = Color(1, 1, 1, 0.95)
		_portrait_sprite.visible = true
	else:
		_portrait_sprite.visible = false
		_portrait_rect.modulate.a = 0.75

	_portrait_sprite.rotation = _rotation
	_portrait_sprite.scale = Vector2(_zoom, _zoom)
	_portrait_rect.rotation = _rotation
	_portrait_rect.scale = Vector2(_zoom, _zoom)

	var border_color := CreatorTheme.ACCENT_CYAN
	if _data.tier == "OMEGA":
		border_color = CreatorTheme.ACCENT_MAGENTA
	_border.add_theme_stylebox_override("panel", CreatorTheme.make_panel_style(_viewport_size, border_color))

	var body: Dictionary = _data.appearance.get("body", {})
	var face: Dictionary = _data.appearance.get("face", {})
	var hair: Dictionary = _data.appearance.get("hair", {})
	var colors: Dictionary = _data.appearance.get("colors", {})
	var sprite_path := NetPSpriteResolver.netp_fallback_path(_data)
	_summary_label.text = "Sprite: %s · Body: %s · Hair: %s · %s / %s" % [
		sprite_path.get_file(),
		body.get("body_type", "?"),
		hair.get("hair_style", "?"),
		colors.get("primary", "?"),
		colors.get("secondary", "?")
	]


func _on_rotate() -> void:
	if CreatorTheme.reduced_motion:
		return
	_rotation += PI / 4.0
	refresh()


func _on_zoom_changed(value: float) -> void:
	_zoom = value
	refresh()


func _on_pose_toggle() -> void:
	if _pose == "idle":
		_pose = "combat"
		_pose_btn.text = "Pose: Combat"
	else:
		_pose = "idle"
		_pose_btn.text = "Pose: Idle"
	refresh()
