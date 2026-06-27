extends Node
class_name EncryptionManager

signal encrypting_started
signal decrypting_started
signal encryption_complete
signal decryption_complete
signal stage_changed(stage_name: String)

var encryption_stage: int = 0
var is_encrypting: bool = false
var is_decrypting: bool = false

# Visual effect nodes
var hex_stream_container: Node2D
var hash_visualization: Node2D
var upload_beam: Node2D

# Animation stages
enum Stage {
	IDLE,
	HEX_STREAMS,
	HASH_ALGORITHM,
	UPLOAD_TO_N3T,
	HASH_REVERSE,
	HEX_REVERSE,
	DOWNLOAD_TO_PED
}

# Hex characters for stream animation
var hex_chars = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"]

func _ready():
	_setup_visual_effects()
	print("Encryption Manager initialized")

func start_encrypting():
	if is_encrypting or is_decrypting:
		return
	
	is_encrypting = true
	encryption_stage = Stage.HEX_STREAMS
	print("Encrypting... Hex streams converting to hash...")
	emit_signal("encrypting_started")
	
	# Trigger animation sequence
	_run_encryption_sequence()

func start_decrypting():
	if is_encrypting or is_decrypting:
		return
	
	is_decrypting = true
	encryption_stage = Stage.HASH_REVERSE
	print("Decrypting... Hash sequence reversing to PED...")
	emit_signal("decrypting_started")
	
	# Trigger reverse animation sequence
	_run_decryption_sequence()

func _run_encryption_sequence():
	# Stage 1: Hexadecimal streams
	await _animate_hex_streams()
	
	# Stage 2: Hash algorithm visualization
	await _animate_hash_algorithm()
	
	# Stage 3: Upload to N3T
	await _animate_upload_to_n3t()
	
	# Complete
	is_encrypting = false
	encryption_stage = Stage.IDLE
	emit_signal("encryption_complete")
	print("Encryption sequence complete")

func _run_decryption_sequence():
	# Stage 1: Hash reverse
	await _animate_hash_reverse()
	
	# Stage 2: Hex reverse
	await _animate_hex_reverse()
	
	# Stage 3: Download to PED
	await _animate_download_to_ped()
	
	# Complete
	is_decrypting = false
	encryption_stage = Stage.IDLE
	emit_signal("decryption_complete")
	print("Decryption sequence complete")

func _animate_hex_streams() -> void:
	encryption_stage = Stage.HEX_STREAMS
	stage_changed.emit("HEX_STREAMS")
	print("Stage: Hexadecimal streams flowing...")
	
	# Create flowing hex character particles
	if hex_stream_container:
		hex_stream_container.visible = true
		_spawn_hex_streams()
	
	await get_tree().create_timer(1.5).timeout
	
	if hex_stream_container:
		hex_stream_container.visible = false

func _animate_hash_algorithm() -> void:
	encryption_stage = Stage.HASH_ALGORITHM
	stage_changed.emit("HASH_ALGORITHM")
	print("Stage: Hash algorithm processing...")
	
	# Visualize hash algorithm (condensing hex into hash)
	if hash_visualization:
		hash_visualization.visible = true
		_animate_hash_condensation()
	
	await get_tree().create_timer(1.5).timeout
	
	if hash_visualization:
		hash_visualization.visible = false

func _animate_upload_to_n3t() -> void:
	encryption_stage = Stage.UPLOAD_TO_N3T
	stage_changed.emit("UPLOAD_TO_N3T")
	print("Stage: Uploading to N3T network...")
	
	# Upload beam animation
	if upload_beam:
		upload_beam.visible = true
		_animate_upload_beam()
	
	await get_tree().create_timer(1.0).timeout
	
	if upload_beam:
		upload_beam.visible = false

func _animate_hash_reverse() -> void:
	encryption_stage = Stage.HASH_REVERSE
	stage_changed.emit("HASH_REVERSE")
	print("Stage: Hash sequence reversing...")
	
	# Reverse hash visualization (expanding back to hex)
	if hash_visualization:
		hash_visualization.visible = true
		_animate_hash_expansion()
	
	await get_tree().create_timer(1.5).timeout
	
	if hash_visualization:
		hash_visualization.visible = false

func _animate_hex_reverse() -> void:
	encryption_stage = Stage.HEX_REVERSE
	stage_changed.emit("HEX_REVERSE")
	print("Stage: Hex streams reversing...")
	
	# Reverse hex stream animation
	if hex_stream_container:
		hex_stream_container.visible = true
		_spawn_hex_streams_reverse()
	
	await get_tree().create_timer(1.5).timeout
	
	if hex_stream_container:
		hex_stream_container.visible = false

func _animate_download_to_ped() -> void:
	encryption_stage = Stage.DOWNLOAD_TO_PED
	stage_changed.emit("DOWNLOAD_TO_PED")
	print("Stage: Downloading back to PED...")
	
	# Download beam animation (reverse of upload)
	if upload_beam:
		upload_beam.visible = true
		_animate_download_beam()
	
	await get_tree().create_timer(1.0).timeout
	
	if upload_beam:
		upload_beam.visible = false

func get_current_stage() -> int:
	return encryption_stage

func is_active() -> bool:
	return is_encrypting or is_decrypting

func cancel():
	if is_encrypting or is_decrypting:
		is_encrypting = false
		is_decrypting = false
		encryption_stage = Stage.IDLE
		print("Encryption/Decryption cancelled")

func _setup_visual_effects():
	# Create containers for visual effects
	hex_stream_container = Node2D.new()
	hex_stream_container.name = "HexStreamContainer"
	add_child(hex_stream_container)
	hex_stream_container.visible = false
	
	hash_visualization = Node2D.new()
	hash_visualization.name = "HashVisualization"
	add_child(hash_visualization)
	hash_visualization.visible = false
	
	upload_beam = Node2D.new()
	upload_beam.name = "UploadBeam"
	add_child(upload_beam)
	upload_beam.visible = false

func _spawn_hex_streams():
	# Create flowing hex character particles
	for i in range(20):
		var hex_label = Label.new()
		hex_label.text = hex_chars[randi() % hex_chars.size()]
		hex_label.modulate = Color(0, 1, 1, 0.8)
		hex_label.position = Vector2(randf() * 1280, randf() * 720)
		hex_stream_container.add_child(hex_label)
		
		# Animate the hex character
		_tween_hex_character(hex_label)

func _spawn_hex_streams_reverse():
	# Create reverse flowing hex character particles
	for i in range(20):
		var hex_label = Label.new()
		hex_label.text = hex_chars[randi() % hex_chars.size()]
		hex_label.modulate = Color(1, 0.5, 0, 0.8)
		hex_label.position = Vector2(randf() * 1280, randf() * 720)
		hex_stream_container.add_child(hex_label)
		
		# Animate the hex character in reverse
		_tween_hex_character_reverse(hex_label)

func _tween_hex_character(label: Label):
	var tween = create_tween()
	tween.set_parallel(true)
	
	# Move across screen
	tween.tween_property(label, "position:x", label.position.x + 200, 1.0)
	tween.tween_property(label, "position:y", label.position.y + 50, 1.0)
	tween.tween_property(label, "modulate:a", 0.0, 1.0)
	
	tween.tween_callback(label.queue_free).set_delay(1.0)

func _tween_hex_character_reverse(label: Label):
	var tween = create_tween()
	tween.set_parallel(true)
	
	# Move in reverse direction
	tween.tween_property(label, "position:x", label.position.x - 200, 1.0)
	tween.tween_property(label, "position:y", label.position.y - 50, 1.0)
	tween.tween_property(label, "modulate:a", 0.0, 1.0)
	
	tween.tween_callback(label.queue_free).set_delay(1.0)

func _animate_hash_condensation():
	# Visualize hex condensing into a hash
	var hash_label = Label.new()
	hash_label.text = "0x" + _generate_random_hash()
	hash_label.modulate = Color(0, 1, 1, 1)
	hash_label.position = Vector2(640, 360)
	hash_label.theme_override_font_size = 48
	hash_visualization.add_child(hash_label)
	
	var tween = create_tween()
	tween.tween_property(hash_label, "scale", Vector2(1.5, 1.5), 0.5)
	tween.tween_property(hash_label, "scale", Vector2(1.0, 1.0), 0.5)
	tween.tween_property(hash_label, "modulate:a", 0.0, 0.5)

func _animate_hash_expansion():
	# Visualize hash expanding back into hex
	var hash_label = Label.new()
	hash_label.text = "0x" + _generate_random_hash()
	hash_label.modulate = Color(1, 0.5, 0, 1)
	hash_label.position = Vector2(640, 360)
	hash_label.theme_override_font_size = 48
	hash_visualization.add_child(hash_label)
	
	var tween = create_tween()
	tween.tween_property(hash_label, "scale", Vector2(2.0, 2.0), 0.5)
	tween.tween_property(hash_label, "modulate:a", 0.0, 1.0)

func _animate_upload_beam():
	# Create upward beam effect
	var beam = ColorRect.new()
	beam.size = Vector2(50, 400)
	beam.position = Vector2(615, 360)
	beam.color = Color(0, 1, 1, 0.5)
	upload_beam.add_child(beam)
	
	var tween = create_tween()
	tween.tween_property(beam, "position:y", -100, 1.0)
	tween.tween_property(beam, "modulate:a", 0.0, 1.0)

func _animate_download_beam():
	# Create downward beam effect (reverse of upload)
	var beam = ColorRect.new()
	beam.size = Vector2(50, 400)
	beam.position = Vector2(615, -100)
	beam.color = Color(1, 0.5, 0, 0.5)
	upload_beam.add_child(beam)
	
	var tween = create_tween()
	tween.tween_property(beam, "position:y", 360, 1.0)
	tween.tween_property(beam, "modulate:a", 0.0, 1.0)

func _generate_random_hash() -> String:
	var hash = ""
	for i in range(32):
		hash += hex_chars[randi() % hex_chars.size()]
	return hash
