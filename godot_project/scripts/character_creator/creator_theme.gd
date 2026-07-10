class_name CreatorTheme
extends RefCounted

## Viewport-scaled cyberpunk theme for the 4K character creator.

const BASE_WIDTH := 1920.0
const BASE_HEIGHT := 1080.0

const BG_DARK := Color("#0A0A12")
const PANEL_BG := Color(0.08, 0.06, 0.14, 0.92)
const PANEL_BORDER := Color("#00FFFF")
const ACCENT_MAGENTA := Color("#FF00FF")
const ACCENT_CYAN := Color("#00FFFF")
const TEXT_PRIMARY := Color("#E8F4FF")
const TEXT_DIM := Color("#8899AA")
const ERROR_COLOR := Color("#FF4466")
const SUCCESS_COLOR := Color("#44FFAA")

static var reduced_motion: bool = false
static var high_contrast: bool = false


static func scale_factor(viewport: Vector2) -> float:
	return clampf(min(viewport.x / BASE_WIDTH, viewport.y / BASE_HEIGHT), 0.75, 2.5)


static func font_size(viewport: Vector2, base: int) -> int:
	return int(round(base * scale_factor(viewport)))


static func spacing(viewport: Vector2, base: int) -> int:
	return int(round(base * scale_factor(viewport)))


static func make_panel_style(viewport: Vector2, border_color: Color = PANEL_BORDER) -> StyleBoxFlat:
	var style := StyleBoxFlat.new()
	var s := scale_factor(viewport)
	style.bg_color = PANEL_BG if not high_contrast else Color(0.0, 0.0, 0.0, 0.95)
	style.border_color = border_color if not high_contrast else Color.WHITE
	style.set_border_width_all(int(2 * s))
	style.set_corner_radius_all(int(8 * s))
	style.content_margin_left = spacing(viewport, 16)
	style.content_margin_right = spacing(viewport, 16)
	style.content_margin_top = spacing(viewport, 12)
	style.content_margin_bottom = spacing(viewport, 12)
	return style


static func set_test_id(node: Node, test_id: String) -> void:
	node.set_meta("data-test-id", test_id)


static func label_settings(viewport: Vector2, size: int, color: Color = TEXT_PRIMARY) -> LabelSettings:
	var ls := LabelSettings.new()
	ls.font_size = font_size(viewport, size)
	ls.font_color = color
	return ls
