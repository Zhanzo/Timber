extends Sprite

var speed = 0

func _ready():
	var height = rand_range(0, 500)
	speed = rand_range(200, 500)
	position = Vector2(2000, height)
