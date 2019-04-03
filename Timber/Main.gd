extends Node2D

# Declare member variables here.
export (PackedScene) var Cloud
export (PackedScene) var Branch
# export (PackedScene) var bee

const NUM_BRANCHES = 6

const NUM_CLOUDS = 6

const TOTAL_TIME = 6
var time_remaining = 6

var paused = true

var score = 0


# Called when the node enters the scene tree for the first time.
func _ready():
	$Player.position = Vector2(1200, 800)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	if Input.is_action_pressed("exit_game"):
		get_tree().quit()
	if paused:
		if Input.is_action_pressed("start_game"):
			time_remaining = TOTAL_TIME
			paused = false
			$HUD.hide_labels()
			spawn_clouds()
	else:
		update_clouds(delta)
		
		if Input.is_action_just_pressed("move_left"):
			$Player.position = Vector2(720, 800)
			$Player/Sprite.flip_h = true
			$Player.chop()
			update_branch()
			spawn_branch()
			score += 1
			time_remaining = min(TOTAL_TIME, time_remaining + 1)
			$HUD.update_score(score)
			$HUD.update_time(time_remaining)
		if Input.is_action_just_pressed("move_right"):
			$Player.position = Vector2(1200, 800)
			$Player/Sprite.flip_h = false
			$Player.chop()
			update_branch()
			spawn_branch()
			score += 1
			time_remaining = min(TOTAL_TIME, time_remaining + 1)
			$HUD.update_score(score)
			$HUD.update_time(time_remaining)
		
		time_remaining = max(0, time_remaining - delta)
		$HUD.update_time(time_remaining)
		
		if time_remaining == 0:
			game_over()
			
func spawn_clouds():
	for i in range(NUM_CLOUDS):
		var c = Cloud.instance()
		$CloudContainer.add_child(c)
		var height = rand_range(0, 500)
		var speed = rand_range(200, 500)
		c.position = Vector2(2000, height)
		c.speed = speed

func spawn_branch():
	if $BranchContainer.get_child_count() < NUM_BRANCHES:
		var branch = Branch.instance()
		$BranchContainer.add_child(branch)

func update_branch():
	for branch in $BranchContainer.get_children():
		branch.position.y += 200
		if branch.position.y == 800:
			branch.queue_free()		

func update_clouds(delta):
	for cloud in $CloudContainer.get_children():
		cloud.position.x -= cloud.speed * delta
		if cloud.position.x < -200:
			cloud.position.x = 2000

func game_over():
	paused = true
	for cloud in $CloudContainer.get_children():
		cloud.queue_free()
	$HUD.game_over()