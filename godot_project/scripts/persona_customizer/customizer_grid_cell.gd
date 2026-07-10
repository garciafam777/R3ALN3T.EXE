extends Button
class_name CustomizerGridCell

var grid_pos: Vector2i = Vector2i.ZERO
var host: PersonaCustomizer = null


func _get_drag_data(_at_position: Vector2) -> Variant:
	var token: CustomizerGridToken = host.get_token_at_cell(grid_pos) if host else null
	if token == null:
		return null
	return {"token": token, "from_pos": grid_pos}


func _can_drop_data(_at_position: Vector2, data: Variant) -> bool:
	return data is Dictionary and data.has("token") and host != null


func _drop_data(_at_position: Vector2, data: Variant) -> void:
	if host and data is Dictionary:
		host.handle_drop(data, grid_pos)
