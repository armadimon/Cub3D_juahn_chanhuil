#include "../include/game.h"
#include <stdio.h>
void	reset_data(t_game *game)
{
	game->p.pos.x = -1;
	game->p.pos.y = -1;
	game->map_data.C_blue = -1;
	game->map_data.C_red = -1;
	game->map_data.C_green = -1;
	game->map_data.F_red = -1;
	game->map_data.F_green = -1;
	game->map_data.F_blue = -1;
	game->map = NULL;
	game->map_flag = 0;
	game->side = 0;
	game->screen_height = 0;
	game->screen_width = 0;
	game->key.W = 0;
	game->key.A = 0;
	game->key.S = 0;
	game->key.D = 0;
	game->key.AL = 0;
	game->key.AR = 0;
}

int	key_press_exit(t_game *game)
{
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	exit (0);
}

int user_move(int key, t_game *game)
{
	if (key == K_ESC)
		key_press_exit(game);
	if (key == K_M && game->map_flag == 0)
		game->map_flag = 1;
	else if (key == K_M && game->map_flag == 1)
		game->map_flag = 0;
	else if (key == K_W)
		game->key.W = 1;
	else if (key == K_A)
		game->key.A = 1;
	else if (key == K_S)
		game->key.S = 1;
	else if (key == K_D)
		game->key.D = 1;
	else if (key == K_AR_L)
		game->key.AL = 1;
	else if (key == K_AR_R)
		game->key.AR = 1;
	return (0);
}

int user_stop(int key, t_game *game)
{
	if (key == K_W)
		game->key.W = 0;
	else if (key == K_A)
		game->key.A = 0;
	else if (key == K_S)
		game->key.S = 0;
	else if (key == K_D)
		game->key.D = 0;
	else if (key == K_AR_L)
		game->key.AL = 0;
	else if (key == K_AR_R)
		game->key.AR = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_list	*map_buffer;

	map_buffer = 0;
	if (argc != 2)
	{
		write(2, "Error\n : ARG_ERROR\n", 20);
		exit (0);
	}
	game.mlx = mlx_init();
	reset_data(&game);
	if (init_texture(&game) == -1)
		return (0);
	if (!read_and_parse_map(&game, map_buffer, argv[1]))
	{
		write(2, "Error\n : MAP_ERROR\n", 20);
		exit (0);
	}
	init_window(&game);
	init_img(&game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_hook(game.win, 2, 0, user_move, &game);
	mlx_hook(game.win, 3, 0, user_stop, &game);
	mlx_hook(game.win, 17, 0, &key_press_exit, &game);
	mlx_loop(game.mlx);
	return (0);
}
