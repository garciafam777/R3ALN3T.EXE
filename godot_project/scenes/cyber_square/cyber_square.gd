extends Node2D
class_name CyberSquare

signal district_entered(district_name: String)
signal customizer_entered
signal net_room_entered
signal task_board_opened
signal encrypt_requested

@onready var central_hub = $CentralHub
@onready var district_gates = {
	"north": $DistrictGate_North,
	"east": $DistrictGate_East,
	"south": $DistrictGate_South,
	"west": $DistrictGate_West
}
@onready var net_room_portal = $NetRoomPortal
@onready var customizer_station = $CustomizerStation
@onready var task_board = $TaskBoard
@onready var player = $Player
@onready var location_label = $HUD/LocationLabel

var districts := {
	"north": "Data District",
	"east": "Security District",
	"south": "Research District",
	"west": "Ops District"
}

var landmarks := [
	{"name": "Plaza Nexus", "pos": Vector2(0, 0), "color": Color.CYAN},
	{"name": "Skyport Drone Spine", "pos": Vector2(-200, -180), "color": Color(0.3, 0.8, 1.0)},
	{"name": "Signal Garden", "pos": Vector2(220, -160), "color": Color(0.2, 1.0, 0.5)},
	{"name": "Astra Data Center", "pos": Vector2(-240, 200), "color": Color(0.6, 0.4, 1.0)},
	{"name": "Governance Terminal", "pos": Vector2(260, 180), "color": Color(1.0, 0.8, 0.3)},
	{"name": "Encrypt Gate", "pos": Vector2(0, -320), "color": Color(0.0, 1.0, 1.0)},
]

var netp_agents := ["Security", "SystemAdmin", "Coder", "Researcher", "Gatekeeper", "OpsMonitor"]
var unlocked_districts := ["north"]
var _netp_nodes: Array = []


func _ready() -> void:
	_connect_signals()
	_spawn_landmarks()
	_spawn_netp_presence()
	_update_district_visibility()
	print("Cyber Square — Plaza Nexus online")


func _connect_signals() -> void:
	central_hub.body_entered.connect(_on_central_hub_entered)
	for direction in district_gates:
		district_gates[direction].body_entered.connect(_on_district_gate_entered.bind(direction))
	net_room_portal.body_entered.connect(_on_net_room_entered)
	customizer_station.body_entered.connect(_on_customizer_entered)
	task_board.body_entered.connect(_on_task_board_entered)


func _spawn_landmarks() -> void:
	var layer := Node2D.new()
	layer.name = "Landmarks"
	add_child(layer)
	for lm in landmarks:
		var area := Area2D.new()
		area.position = lm["pos"]
		area.add_to_group("landmark")
		var shape := CollisionShape2D.new()
		var rect := RectangleShape2D.new()
		rect.size = Vector2(160, 80)
		shape.shape = rect
		area.add_child(shape)
		var sprite := Sprite2D.new()
		sprite.modulate = lm["color"]
		area.add_child(sprite)
		var label := Label.new()
		label.text = lm["name"]
		label.position = Vector2(-70, -50)
		area.add_child(label)
		area.body_entered.connect(_on_landmark_entered.bind(lm["name"]))
		layer.add_child(area)
		if lm["name"] == "Encrypt Gate":
			area.input_pickable = true


func _spawn_netp_presence() -> void:
	var layer := Node2D.new()
	layer.name = "NetPPresence"
	add_child(layer)
	for i in netp_agents.size():
		var agent := CharacterBody2D.new()
		agent.name = netp_agents[i]
		agent.position = Vector2(-350 + i * 120, 80 + (i % 2) * 40)
		agent.add_to_group("netp_npc")
		var sprite := Sprite2D.new()
		sprite.modulate = Color.CYAN.lerp(Color.MAGENTA, float(i) / 6.0)
		agent.add_child(sprite)
		var label := Label.new()
		label.text = netp_agents[i]
		label.position = Vector2(-30, -40)
		agent.add_child(label)
		layer.add_child(agent)
		_netp_nodes.append(agent)


func _physics_process(delta: float) -> void:
	for i in _netp_nodes.size():
		var node: Node2D = _netp_nodes[i]
		node.position.x += sin(Time.get_ticks_msec() / 1000.0 + i) * 20.0 * delta


func _on_landmark_entered(landmark_name: String, body: Node) -> void:
	if not body.is_in_group("player"):
		return
	location_label.text = "CYBER SQUARE — %s" % landmark_name.to_upper()
	if landmark_name == "Encrypt Gate":
		encrypt_requested.emit()


func _on_central_hub_entered(body: Node) -> void:
	if body.is_in_group("player"):
		location_label.text = "CYBER SQUARE — CENTRAL PLAZA NEXUS"


func _on_district_gate_entered(direction: String, body: Node) -> void:
	if body.is_in_group("player"):
		if direction in unlocked_districts:
			district_entered.emit(districts[direction])


func _on_net_room_entered(body: Node) -> void:
	if body.is_in_group("player"):
		net_room_entered.emit()
		get_tree().change_scene_to_file("res://scenes/net_room/net_room.tscn")


func _on_customizer_entered(body: Node) -> void:
	if body.is_in_group("player"):
		customizer_entered.emit()
		var dm := _find_device_manager()
		PersonaCustomizerLauncher.open_as_overlay(self, dm)


func _on_task_board_entered(body: Node) -> void:
	if body.is_in_group("player"):
		task_board_opened.emit()


func _find_device_manager() -> DeviceManager:
	for n in get_tree().get_nodes_in_group("device_manager"):
		if n is DeviceManager:
			return n
	return null


func unlock_district(direction: String) -> void:
	if direction in districts and direction not in unlocked_districts:
		unlocked_districts.append(direction)
		_update_district_visibility()


func _update_district_visibility() -> void:
	for direction in district_gates:
		district_gates[direction].modulate = Color.WHITE if direction in unlocked_districts else Color(0.3, 0.3, 0.3)
