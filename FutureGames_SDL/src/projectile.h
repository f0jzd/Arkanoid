#pragma once

struct Projectile
{
	bool alive = false;
	bool can_move = false;

	float x;
	float y;

	float velocity_x;
	float velocity_y;
	float speed{500};



	void update();
	void draw();
	void update_projectile();

	bool step(float dx, float dy);
};
