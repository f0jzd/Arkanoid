#include "game.h"

Player player;
Projectile projectiles[PROJECTILE_MAX];
Brick bricks[BRICK_COLUMNS][BRICK_ROWS];
Wall wall[40];
Brick placedBrick[BRICK_MAX];

bool custom_level_loaded;
int placedB = 0;