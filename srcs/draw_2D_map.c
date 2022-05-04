#include "../include/game.h"

void	draw_rectangle(t_game *game, int x, int y)
{
	int i;
	int j;

	x *= TILE_SIZE;
	y *= TILE_SIZE;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			game->img.data[(y  + i) * (game->map_width * TILE_SIZE) + x + j] = 0xFFFFFF;
			j++;
		}
		i++;
	}
}

void	draw_rectangles(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == '1' || game->map[i][j] == ' ')
				draw_rectangle(game, j, i);
			j++;
		}
		i++;
	}
}

void	draw_ray(t_game *game, int x)
{

	double cameraX = 2 * x / (double)(20) - 1;
	t_vec rayDir = vec_add(game->p.dir, vec_mul(game->p.plane, cameraX));

	float fTempY = game->p.pos.y * TILE_SIZE;
	// float fTempX = game->p.pos.x;
	double fM = tan(vec_angle(rayDir));
	int iX = game->p.pos.x * TILE_SIZE;
	while (1)
	{
		if (fTempY / TILE_SIZE < 0 || fTempY / TILE_SIZE > game->map_height)
			return ;
		if (iX / TILE_SIZE < 0 || iX / TILE_SIZE > game->map_width)
			return ;
		// printf("[%c] [%d] %d %d \n", game->map[(int)fTempY / TILE_SIZE][iX / TILE_SIZE], x, (int)fTempY, iX);
		if (game->map[(int)fTempY / TILE_SIZE][iX / TILE_SIZE] == '1' ||
			game->map[(int)fTempY / TILE_SIZE][iX / TILE_SIZE] == ' ')
			break;
		game->img.data[((int)(fTempY + 0.5f) * game->map_width * TILE_SIZE) + iX] = 0xFFDFFF;
		fTempY += fM;   
		iX++;
	}
	
}

void	draw_2D_map(t_game *game)
{
	int x;

	draw_rectangles(game);
	x = 20;
	while (x--)
	{
		draw_ray(game, x);
	}
}
