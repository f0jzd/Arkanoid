#include "collision.h"
#include <SDL/SDL.h>
#include "engine.h"


AABB AABB::make_from_position_size(float x, float y, float w, float h)
{

	AABB box;
	box.x_min = x - w / 2;
	box.x_max = x + w / 2;

	box.y_min = y - h / 2;
	box.y_max = y + h / 2;


	return box;
}

void draw_box(const AABB& box)
{
	SDL_Rect rect = {
		box.x_min,
		box.y_min,
		box.x_max - box.x_min,
		box.y_max - box.y_min
	};
	
	SDL_RenderDrawRect(render, &rect);
}

void draw_filled_box(const AABB& box)
{
	SDL_Rect rect = {
		box.x_min,
		box.y_min,
		box.x_max - box.x_min,
		box.y_max - box.y_min
	};

	SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
	SDL_RenderFillRect(render, &rect);
	//SDL_RenderDrawRect(render, &rect);
}

