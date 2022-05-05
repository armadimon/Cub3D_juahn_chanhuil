#include "../include/game.h"

void	init_window(t_game *game)
{
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "mlx 42");
}

void	init_img(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.data = (int *)mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.size_l, &game->img.endian);
}

int		init_texture(t_game *game)
{

	if (!(game->texture = (int **)malloc(sizeof(int *) * 8)))
		return (-1);
	for (int i = 0; i < 6; i++)
	{
		if (!(game->texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
			return (-1);
	}
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < texHeight * texWidth; j++)
		{
			game->texture[i][j] = 0;
		}
	}
	return (1);
}

void	init_game(t_game *game)
{
	game->mlx = 0;
	game->win = 0;
	game->map_width = 0;
	game->map_height = 0;
}

int		deal_key(int key_code, t_game *game)
{
	(void)game;
	if (key_code == KEY_ESC)
		exit(0);
	return (0);
}