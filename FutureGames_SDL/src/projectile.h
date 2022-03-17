#pragma once

struct Projectile
{
	bool alive = false;
	bool can_move = false;

	float x;
	float y;
	float w = 8;
	float h = 8;

	float velocity_x;
	float velocity_y;
	float speed{500};



	void update();
	void draw();

	bool step(float dx, float dy);
};
