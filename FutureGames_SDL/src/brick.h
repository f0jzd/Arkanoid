#pragma once


struct Brick
{

	bool alive = true;

	bool breakable = true;
	bool strongWall = false;

	int strongWallLifes{ 3 };
	
	float w = 180.f;
	float h = 60.f;

	float margin = 200.f;

	float x = 0;//x-width/2
	float y = 0; //y+height/2

	void draw();
	
};