#include "../include/game.h"

int		draw_texture(t_game *game)
{
	int i = 0;
	int j = 0;
	while (i < texHeight)
	{
		j = 0;
		while (j < texWidth)
		{
			game->img.data[i * texHeight * COLS  + j] = game->texture[1][i * texHeight + j];
			j++;
		}
		i++;
	}
	return (0);
}

int		main_loop(t_game *game)
{
	draw_texture(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
