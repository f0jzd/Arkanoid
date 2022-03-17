#include "brick.h"
#include "collision.h"
#include <SDL/SDL.h>
#include "engine.h"

void Brick::draw()
{
	if (!alive)
	{
		return;
	}
	if (!breakable)
	{
		SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
	}

	else if (breakable && strongWall)
	{
		SDL_SetRenderDrawColor(render, 0, 150, 255, 255);
	}
	else
	{
		SDL_SetRenderDrawColor(render, 0, 255, 255, 255);
	}

	AABB box = AABB::make_from_position_size(x, y, w, h);
	draw_box(box);
}