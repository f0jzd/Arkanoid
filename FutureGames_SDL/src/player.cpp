#include "player.h"
#include"engine.h"
#include"game.h"

void Player::update()
{
	Projectile& proj = projectiles[current_balls];

	if (!proj.can_move && current_balls < 3)
	{
		proj.alive = true;
		proj.x = player.x + playerWidth / 2;
		proj.y = player.y - playerHeight;
	}

	CheckMovement();

	
	if (GetKeyPressed(SDL_SCANCODE_SPACE))//HERE WE FIRE BULLET; ENEMY GO boom.
	{
		//space = true;
		proj.alive = true;
		current_balls++;
		proj.velocity_y = -proj.speed;
		proj.velocity_x = 0;
	}
}

void Player::CheckMovement()
{
	if (GetKey(SDL_SCANCODE_D))
		x += playerMovementspeed * delta_time;

	if (GetKey(SDL_SCANCODE_A))
		x -= playerMovementspeed * delta_time;

	
}

void Player::draw()
{
	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	SDL_Rect rect = { x,y,player.playerWidth, player.playerHeight };
	SDL_RenderFillRect( render, &rect);
}




