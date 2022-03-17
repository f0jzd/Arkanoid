#include "engine.h"
#include "spritesheet.h"


void sprite_sheet::draw(int sprite_index, int x, int y, int objectWidth,int objectHeight )
{
	SDL_Rect src = { sprite_index * sprite_w, 0 ,sprite_w,sprite_h };
	SDL_Rect dst = { x,y,objectWidth,objectHeight };

	SDL_RenderCopy(render, texture, &src, &dst);
	
}
void sprite_sheet::load(const char* path, int in_sprite_W, int in_sprite_H)
{
	texture = IMG_LoadTexture(render, path);
	sprite_w = in_sprite_W;
	sprite_h = in_sprite_H;


}


