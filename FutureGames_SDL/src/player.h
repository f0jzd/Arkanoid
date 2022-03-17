#pragma once


struct Player
{

	int current_balls = 0;
	int max_balls = 3;

	bool space = false;

	float x{ 600 };
	float y{ 800 };

	int playerLives = 3;

	int playerMovementspeed = 500;

	float shoot_timer = 0.f;

	int next_projectile_index = 0;

	int playerWidth{ 64 };
	int playerHeight{ 8 };

	bool ballFired = false;

	void update();
	void CheckMovement();
	void draw();
	void DrawBall();
};