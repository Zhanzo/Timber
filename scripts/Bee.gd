extends Sprite

var speed = 0

func _ready():
	flip_h = true
	var height = rand_range(500, 800)
	speed = rand_range(-100, -300)
	position = Vector2(-200, height)
