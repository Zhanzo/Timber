extends Node2D

# Declare member variables here. Examples:
# var a = 2
# var b = "text"

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

func chop():
	if $Sprite.flip_h:
		$Axe.flip_h = true
		$Axe.position = $Sprite.position + Vector2(130, 30)
	else:
		$Axe.flip_h = false
		$Axe.position = $Sprite.position + Vector2(-130, 30)
	$Axe.visible = true
	$Timer.start()
		


func _on_Timer_timeout():
	$Axe.visible = false
