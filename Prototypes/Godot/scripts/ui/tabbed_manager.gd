class_name TabbedManager
extends Control

## PED-optimized tab framework — Kernal (minimal) vs MOD (expandable).

signal tab_changed(index: int, title: String)

enum TabStyle { KERNAL, MOD }

var _style: TabStyle = TabStyle.KERNAL
var _viewport_size: Vector2 = Vector2(1920, 1080)
var _tab_container: TabContainer
var _mod_drawers: Dictionary = {}
var _tab_titles: Array[String] = []
var _tab_contents: Array[Control] = []


func _init() -> void:
	size_flags_horizontal = Control.SIZE_EXPAND_FILL
	size_flags_vertical = Control.SIZE_EXPAND_FILL


func setup(viewport_size: Vector2, style: TabStyle = TabStyle.KERNAL) -> void:
	_viewport_size = viewport_size
	_style = style
	if _tab_container == null:
		_build_shell()


func set_style(style: TabStyle) -> void:
	_style = style
	_apply_style()


func set_style_from_device(device_manager: DeviceManager) -> void:
	if device_manager and device_manager.is_mod():
		set_style(TabStyle.MOD)
	else:
		set_style(TabStyle.KERNAL)


func add_tab(title: String, content: Control, mod_detail: Control = null) -> int:
	if _tab_container == null:
		_build_shell()

	var wrapper := _wrap_tab_content(title, content, mod_detail)
	_tab_container.add_child(wrapper)
	_tab_titles.append(title)
	_tab_contents.append(content)
	_apply_style()
	return _tab_titles.size() - 1


func set_active_tab(index: int) -> void:
	if _tab_container and index >= 0 and index < _tab_container.get_tab_count():
		_tab_container.current_tab = index


func get_tab_count() -> int:
	return _tab_titles.size()


func clear_tabs() -> void:
	if _tab_container == null:
		return
	for content in _tab_contents:
		if is_instance_valid(content) and content.get_parent():
			content.get_parent().remove_child(content)
	_tab_contents.clear()
	for child in _tab_container.get_children():
		child.queue_free()
	_tab_titles.clear()
	_mod_drawers.clear()


func _build_shell() -> void:
	_tab_container = TabContainer.new()
	_tab_container.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	_tab_container.size_flags_vertical = Control.SIZE_EXPAND_FILL
	_tab_container.tab_changed.connect(_on_tab_changed)
	add_child(_tab_container)
	CreatorTheme.set_test_id(self, "tabbed-manager")
	_apply_style()


func _wrap_tab_content(title: String, content: Control, mod_detail: Control) -> Control:
	var scroll := ScrollContainer.new()
	scroll.name = title
	scroll.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	scroll.size_flags_vertical = Control.SIZE_EXPAND_FILL

	var root := VBoxContainer.new()
	root.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	root.add_theme_constant_override("separation", CreatorTheme.spacing(_viewport_size, 8))
	scroll.add_child(root)

	content.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	root.add_child(content)

	if _style == TabStyle.MOD and mod_detail != null:
		var drawer := _create_mod_drawer(title, mod_detail)
		root.add_child(drawer)
		_mod_drawers[title] = drawer

	return scroll


func _create_mod_drawer(title: String, detail: Control) -> PanelContainer:
	var panel := PanelContainer.new()
	panel.add_theme_stylebox_override("panel", CreatorTheme.make_panel_style(_viewport_size, CreatorTheme.ACCENT_MAGENTA))

	var box := VBoxContainer.new()
	panel.add_child(box)

	var toggle := Button.new()
	toggle.text = "▸ %s Details" % title
	toggle.alignment = HORIZONTAL_ALIGNMENT_LEFT
	toggle.pressed.connect(func():
		detail.visible = not detail.visible
		toggle.text = ("▾ " if detail.visible else "▸ ") + "%s Details" % title
	)
	box.add_child(toggle)

	detail.visible = false
	detail.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	box.add_child(detail)
	return panel


func _apply_style() -> void:
	if _tab_container == null:
		return

	var font_size := CreatorTheme.font_size(_viewport_size, 14 if _style == TabStyle.KERNAL else 13)
	_tab_container.add_theme_font_size_override("font_size", font_size)

	if _style == TabStyle.KERNAL:
		_tab_container.tabs_rearrange_group = 0
		_tab_container.add_theme_constant_override("side_margin", CreatorTheme.spacing(_viewport_size, 8))
	else:
		_tab_container.tabs_rearrange_group = 1
		_tab_container.add_theme_constant_override("side_margin", CreatorTheme.spacing(_viewport_size, 4))


func _on_tab_changed(tab_index: int) -> void:
	var title := _tab_titles[tab_index] if tab_index < _tab_titles.size() else ""
	tab_changed.emit(tab_index, title)


func refresh_viewport(viewport_size: Vector2) -> void:
	_viewport_size = viewport_size
	_apply_style()
