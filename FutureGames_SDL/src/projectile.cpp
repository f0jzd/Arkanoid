#include "engine.h"
#include "projectile.h"
#include "collision.h"
#include "game.h"
#include "math.h"
#include <iostream>;



void Projectile::update()
{
	if (!step(velocity_x*delta_time,0.f))
	{
		velocity_x = -velocity_x;
	}
	if (!step(0.f, velocity_y * delta_time))
	{
		velocity_y = -velocity_y;
	}

}
void Projectile::draw()
{

	if (!alive)
	{
		return;
	}

	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	SDL_Rect rect = { (int)x-4, (int)y-4,(int)w,(int)h };

	//SDL_RenderFillRect(render, &rect);

}


bool Projectile::step(float dx, float dy)
{
	//Collision check with brick.
	Circle circle = { x+dx, y+dy, 4 };//Next collider of the bullet/ delta is change
	//draw_circle(circle);

	AABB box = AABB::make_from_position_size(player.x+player.playerWidth/2, player.y+player.playerHeight/2, player.playerWidth, player.playerHeight);
	//draw_box(box);


	for (int i = 0; i < BRICK_COLUMNS; i++)//Here we check collisions with all the bricks
	{
		for (int j = 0; j < BRICK_ROWS; j++)
		{
			Brick& brick = bricks[i][j];

			if (!brick.alive)
				continue;

			
			AABB box = AABB::make_from_position_size(brick.x, brick.y, brick.w, brick.h);


			if (aabb_circle_intersect(box, circle))//If the circle and box intersect a.k.a. the bullet and the brick, then something happens
			{
				
				if (!brick.breakable && !brick.strongWall)
				{
					return false;
				}
				else if (!brick.breakable || brick.strongWall)
				{
				     brick.strongWallLifes -= 1;
					 if (brick.strongWallLifes == 0)
					 {
					 	brick.alive = false;	
					 }
					return false;
				}

				if (brick.breakable)
				{
					brick.alive = false;
					return	false;
				}
								
			}
		}

	}

	if (dy<0.f)
	{
		if (aabb_circle_intersect(box,circle))
		{
			return false;
		}
	}

	

	if (aabb_circle_intersect(box, circle))
	{

		float playerX = player.x + player.playerWidth / 2;
		float playerY = player.y + player.playerHeight / 2+50;

		float k = circle.x - playerX;
		float j = circle.y - playerY;

		float len = sqrt(k * k + j * j);

		float directionX = k / len;
		float directionY = j / len;

		velocity_x = directionX * speed;
		velocity_y = -directionY * speed;

		return false;
	}



	//Check collision with game borders.
	if (x+dx < 0+30 || x+dx >= 1600-30 ||
		y+dy < 0+30)
	{
		return false;
	}
	if (y + dy >= 900)
	{
		player.playerLives -= 1;
		alive = false;
		player.ballFired = false;
	}
	

	x += dx;
	y += dy;
	return true;
}

