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

void	draw_2D_map_BG(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->screen_height)
	{
		j = 0;
		while (j < game->screen_width)
		{
			game->img.data[i * game->screen_width + j] = 0x000000;
			j++;
		}
		i++;
	}
}

void	draw_ray(t_game *game, int x)
{

	double cameraX = 2 * x / (double)(game->map_width * TILE_SIZE) - 1;
	t_vec rayDir = vec_add(game->p.dir, vec_mul(game->p.plane, cameraX));

	float fTempY = game->p.pos.y * TILE_SIZE;
	float fTempX = game->p.pos.x * TILE_SIZE;
	// double fM = rayDirY / rayDirX;

	int color = 0xFF0000;
	double fM = tan(vec_angle(rayDir));
	int iX = game->p.pos.x * TILE_SIZE;
	int iY = game->p.pos.y * TILE_SIZE;
	if (fM <= 1.0f && fM >= -1.0f)
	{
		while (1)
		{
			if (fTempY / TILE_SIZE < 0 || fTempY / TILE_SIZE > game->map_height)
				return ;
			if (iX / TILE_SIZE < 0 || iX / TILE_SIZE > game->map_width)
				return ;
			if (game->map[(int)fTempY / TILE_SIZE][iX / TILE_SIZE] == '1' ||
				game->map[(int)fTempY / TILE_SIZE][iX / TILE_SIZE] == ' ')
				break;
			// int i = 0
			// while (i < iX)
			game->img.data[((int)(fTempY) * game->map_width * TILE_SIZE) + iX] = color;
			if (rayDir.x < 0)
				iX--;
			else
				iX++;
			if (rayDir.y < 0)
				fTempY -= fabs(fM);
			else
				fTempY += fabs(fM);
		}
	}
	else
	{
		fM = 1 / fM;
		while (1)
		{
			if (fM < 1.0f)
			{
				if (fTempX / TILE_SIZE < 0 || fTempX / TILE_SIZE > game->map_width)
					return ;
				if (iY / TILE_SIZE < 0 || iY / TILE_SIZE > game->map_height)
					return ;
				if (game->map[iY / TILE_SIZE][(int)fTempX / TILE_SIZE] == '1' ||
					game->map[iY / TILE_SIZE][(int)fTempX / TILE_SIZE] == ' ')
					break;
				game->img.data[(iY * game->map_width * TILE_SIZE) + (int)(fTempX)] = 0xFF0000;
				if (rayDir.x < 0)
					fTempX -= fabs(fM);
				else
					fTempX += fabs(fM);
				if (rayDir.y < 0)
					iY--;
				else
					iY++;
			}
		}
	}
	
}

void	draw_2D_map(t_game *game)
{
	int x;

	draw_2D_map_BG(game);
	draw_rectangles(game);
	x = 0;
	while (x < game->map_width * TILE_SIZE)
	{
		draw_ray(game, x);
		x++;
	}
}
