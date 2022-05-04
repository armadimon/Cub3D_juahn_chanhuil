#include "../include/game.h"

int	draw_verline(t_game *game, int line_height)
{
	int drawStart = -line_height / 2 + (game->map_height * TILE_SIZE) / 2;
	if(drawStart < 0)
		drawStart = 0;
	int drawEnd = line_height / 2 + (game->map_height * TILE_SIZE) / 2;
	if(drawEnd >= game->map_height * TILE_SIZE)
		drawEnd = game->map_height * TILE_SIZE - 1;
}