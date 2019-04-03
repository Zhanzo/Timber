extends CanvasLayer

func update_score(value):
 $MarginContainer/ScoreLabel.text = "Score: " + str(value)

func hide_labels():
	$StartLabel.visible = false
	$EndLabel.visible = false
	
func game_over():
	$EndLabel.visible = true

func update_time(time_remaining):
	$TimeBar.value = time_remaining
