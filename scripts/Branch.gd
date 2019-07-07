extends Sprite

# Called when the node enters the scene tree for the first time.
func _ready():
	var side = randi() % 2
	if side == 0:
		flip_h = true
		position = Vector2(600, 200)
	elif side == 1:
		position = Vector2(1320, 200)
