extends Node
class_name UIThemeManager

# UI Theme Manager for Kernal vs MOD devices
# Kernal: Clean, minimal, premium (Apple-like)
# MOD: Powerful, customizable, admin-focused (Android-like)

signal theme_changed(theme_name: String)

enum ThemeType { KERNAL, MOD }

var current_theme = ThemeType.KERNAL

# Theme configurations
var themes = {
	ThemeType.KERNAL: {
		"name": "Kernal",
		"description": "Premium, clean, simple interface",
		"primary_color": Color(0.2, 0.6, 1.0),  # Light blue
		"secondary_color": Color(0.9, 0.9, 0.95),  # Off-white
		"accent_color": Color(0.0, 0.8, 1.0),  # Cyan
		"background_color": Color(0.95, 0.95, 0.98),  # Nearly white
		"text_color": Color(0.1, 0.1, 0.15),  # Dark gray
		"button_color": Color(0.2, 0.6, 1.0),
		"button_hover_color": Color(0.3, 0.7, 1.0),
		"border_radius": 8,
		"font_size_normal": 16,
		"font_size_large": 24,
		"font_size_title": 32,
		"spacing": 12,
		"shadow_enabled": true,
		"shadow_color": Color(0, 0, 0, 0.1),
		"animation_speed": 0.3
	},
	ThemeType.MOD: {
		"name": "MOD",
		"description": "Highly customizable, admin-focused",
		"primary_color": Color(0.8, 0.2, 0.8),  # Purple
		"secondary_color": Color(0.15, 0.15, 0.2),  # Dark gray
		"accent_color": Color(1.0, 0.5, 0.0),  # Orange
		"background_color": Color(0.1, 0.1, 0.12),  # Dark
		"text_color": Color(0.9, 0.9, 0.95),  # Light gray
		"button_color": Color(0.6, 0.2, 0.8),
		"button_hover_color": Color(0.8, 0.3, 1.0),
		"border_radius": 4,
		"font_size_normal": 14,
		"font_size_large": 20,
		"font_size_title": 28,
		"spacing": 8,
		"shadow_enabled": false,
		"shadow_color": Color(0, 0, 0, 0.3),
		"animation_speed": 0.15
	}
}

func _ready():
	print("UI Theme Manager initialized - Current: %s" % get_theme_name())

func set_theme(theme_type: int) -> void:
	if theme_type in themes:
		current_theme = theme_type
		var theme_name = get_theme_name()
		print("Theme changed to: %s" % theme_name)
		theme_changed.emit(theme_name)
		_apply_theme_to_scene()

func get_current_theme() -> Dictionary:
	return themes[current_theme]

func get_theme_name() -> String:
	return themes[current_theme]["name"]

func get_theme_description() -> String:
	return themes[current_theme]["description"]

func get_primary_color() -> Color:
	return themes[current_theme]["primary_color"]

func get_secondary_color() -> Color:
	return themes[current_theme]["secondary_color"]

func get_accent_color() -> Color:
	return themes[current_theme]["accent_color"]

func get_background_color() -> Color:
	return themes[current_theme]["background_color"]

func get_text_color() -> Color:
	return themes[current_theme]["text_color"]

func get_button_color() -> Color:
	return themes[current_theme]["button_color"]

func get_button_hover_color() -> Color:
	return themes[current_theme]["button_hover_color"]

func is_kernal() -> bool:
	return current_theme == ThemeType.KERNAL

func is_mod() -> bool:
	return current_theme == ThemeType.MOD

func _apply_theme_to_scene() -> void:
	# Apply theme to current scene's UI elements
	var root = get_tree().current_scene
	if root:
		_apply_theme_recursive(root)

func _apply_theme_recursive(node: Node) -> void:
	# Apply theme to Control nodes
	if node is Control:
		_apply_theme_to_control(node)
	
	# Recursively apply to children
	for child in node.get_children():
		_apply_theme_recursive(child)

func _apply_theme_to_control(control: Control) -> void:
	var theme = get_current_theme()
	
	# Apply colors
	if control is ColorRect:
		control.color = theme["background_color"]
	elif control is Label:
		control.modulate = theme["text_color"]
	elif control is Button:
		# Button styling will be applied via theme resource
		pass
	
	# Apply font sizes
	if control is Label or control is Button:
		if control.name.contains("Title"):
			control.theme_override_font_size = theme["font_size_title"]
		elif control.name.contains("Large"):
			control.theme_override_font_size = theme["font_size_large"]
		else:
			control.theme_override_font_size = theme["font_size_normal"]

func create_theme_resource() -> Theme:
	var theme = Theme.new()
	var theme_config = get_current_theme()
	
	# Create font (using default font for now)
	var font = ThemeDB.fallback_font
	
	# Configure colors
	theme.set_color("font_color", "Label", theme_config["text_color"])
	theme.set_color("font_hover_color", "Button", theme_config["button_hover_color"])
	theme.set_color("font_pressed_color", "Button", theme_config["text_color"])
	
	theme.set_color("button_color", "Button", theme_config["button_color"])
	
	theme.set_font("font", "Label", font)
	theme.set_font("font", "Button", font)
	
	theme.set_font_size("font_size", "Label", theme_config["font_size_normal"])
	theme.set_font_size("font_size", "Button", theme_config["font_size_normal"])
	
	return theme
