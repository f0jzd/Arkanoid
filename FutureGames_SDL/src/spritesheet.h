#pragma once
#include <SDL/SDL_image.h>

struct sprite_sheet
{
	void load(const char* path, int in_sprite_W, int in_sprite_H);
	void draw(int sprite_index, int x, int y, int objectWidth, int objectHeight );

	SDL_Texture* texture;
	int sprite_w;
	int sprite_h;
};


