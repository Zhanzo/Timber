extends Sprite

var speed = Vector2(0, 0)
var active = true

# Declare member variables here. Examples:
func fly(fly_right):
	if fly_right:
		speed = Vector2(1500, -1000)
	else:
		speed = Vector2(-1500, -1000)
	show()
	active = true

func _process(delta):
	if active:
		position += speed * delta

func _on_Visibility_screen_exited():
	queue_free()