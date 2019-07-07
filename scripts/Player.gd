extends Sprite

signal hit_branch

func chop():
	if is_flipped_h():
		$Axe.set_flip_h(true)
		$Axe.position = Vector2(130, 30)
	else:
		$Axe.set_flip_h(false)
		$Axe.position = Vector2(-130, 30)
	$ChopSound.play()
	$Axe.show()
	$Timer.start()

func _on_Timer_timeout():
	$Axe.hide()
	
func _on_Area2D_area_entered(area):
	emit_signal("hit_branch")
	$DeathSound.play()