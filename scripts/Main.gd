extends Node2D

# Declare member variables here.
export (PackedScene) var Cloud
export (PackedScene) var Branch
export (PackedScene) var Log
export (PackedScene) var Bee
# export (PackedScene) var bee

const NUM_BRANCHES = 6

const NUM_BEES = 3

const NUM_CLOUDS = 6

const TOTAL_TIME = 6
var time_remaining = 6

var paused = true

var score = 0

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	if Input.is_action_pressed("exit_game"):
		get_tree().quit()
	if paused:
		if Input.is_action_pressed("start_game"):
			new_game()
	else:
		update_background(delta)
		
		if Input.is_action_just_pressed("move_left"):
			player_interaction(720, 800, true)
		elif Input.is_action_just_pressed("move_right"):
			player_interaction(1200, 800, false)
		else:
			time_remaining = max(0, time_remaining - delta)
			$HUD.update_time(time_remaining)
		
		if time_remaining == 0:
			time_out()
			
func spawn_background():
	for _i in range(NUM_CLOUDS):
		var c = Cloud.instance()
		$CloudContainer.add_child(c)
	for _i in range(NUM_BEES):
		var b = Bee.instance()
		$BeeContainer.add_child(b)

func spawn_branch():
	if $BranchContainer.get_child_count() < NUM_BRANCHES:
		var branch = Branch.instance()
		$BranchContainer.add_child(branch)

func spawn_log():
	var chopped_log = Log.instance()
	chopped_log.fly($Player.flip_h)
	$LogContainer.add_child(chopped_log)

func update_branch():
	for branch in $BranchContainer.get_children():
		branch.position.y += 200
		if branch.position.y == 1000:
			branch.queue_free()		

func update_background(delta):
	for cloud in $CloudContainer.get_children():
		cloud.position.x -= cloud.speed * delta
		if cloud.position.x < -200:
			cloud.position.x = 2000
	
	for bee in $BeeContainer.get_children():
		bee.position.x -= bee.speed * delta
		if bee.position.x > 2000:
			bee.position.x = -200

func clean_up():
	paused = true
	for cloud in $CloudContainer.get_children():
		cloud.queue_free()
	for chopped_log in $LogContainer.get_children():
		chopped_log.queue_free()
	for bee in $BeeContainer.get_children():
		bee.queue_free()

func time_out():
	clean_up()
	$OutOfTimePlayer.play()
	$HUD.game_over()

func game_over():
	clean_up()
	$RIP.show()
	$Player.hide()
	$HUD.squished()

func new_game():
	for branch in $BranchContainer.get_children():
		branch.queue_free()
	$Player.show()
	$RIP.hide()
	score = 0
	$Player.position = Vector2(1200, 800)
	time_remaining = TOTAL_TIME
	paused = false
	$HUD.hide_labels()
	spawn_background()

func player_interaction(x, y, flip_h):
	$Player.position = Vector2(x, y)
	$Player.set_flip_h(flip_h)
	$Player.chop()
	spawn_log()
	update_branch()
	spawn_branch()
	score += 1
	time_remaining = min(TOTAL_TIME, time_remaining + 0.5)
	$HUD.update_score(score)
	$HUD.update_time(time_remaining)