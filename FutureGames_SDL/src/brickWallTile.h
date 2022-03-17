#pragma once

struct Wall
{
	float h = 100.f;
	float w = 60.f;

	float x = 0;//x-width/2
	float y = 0; //y+height/2

	void draw();
	void draw_walls();
	void draw_roof();
};