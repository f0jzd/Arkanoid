#include "brickWallTile.h"
#include "collision.h"
#include "game.h"


void Wall::draw()
{

	AABB box = AABB::make_from_position_size(x, y, w, h);
	//draw_box(box);
	draw_filled_box(box);
}

void Wall::draw_walls()
{
	for (int i = 0; i < 10; i++)
	{
		wall[i].y = wall[i].h * i + wall[i].h / 2;
	}
	for (int i = 0; i < 10; i++)
	{
		wall[i + 10].x = 1600;
		wall[i + 10].y = wall[i + 10].h * i + wall[i + 10].h / 2;
	}
}

void Wall::draw_roof()
{

	for (int i = 0; i < 10; ++i)
	{
		wall[i + 20].y = 0;
		wall[i + 20].w = 160;
		wall[i + 20].h = 60;
		wall[i + 20].x = wall[i + 20].w * i + wall[i + 20].w / 2;
	}
}
