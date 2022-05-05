#include "../include/game.h"
#include <stdio.h>
void	reset_data(t_game *game)
{
	game->map_data.C_blue = -1;
	game->map_data.C_red = -1;
	game->map_data.C_green = -1;
	game->map_data.F_red = -1;
	game->map_data.F_green = -1;
	game->map_data.F_blue = -1;
	game->map_flag = 0;
	game->side = 0;
	game->screen_height = 0;
	game->screen_width = 0;
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
	if (key == K_A)
		game->p.pos = vec_add(game->p.pos, vec_mul(vec_rot(game->p.dir, 90), 0.25));
	else if (key == K_D)
		game->p.pos = vec_add(game->p.pos, vec_mul(vec_rot(game->p.dir, 270), 0.25));
	else if (key == K_W)
		game->p.pos = vec_add(game->p.pos, vec_mul(vec_rot(game->p.dir, 0), 0.25));
	else if (key == K_S)
		game->p.pos = vec_add(game->p.pos, vec_mul(vec_rot(game->p.dir, 180), 0.25));
	else if (key == K_Q)
	{
		game->p.dir = vec_rot(game->p.dir, 5);
		game->p.plane = vec_rot(game->p.plane, 5);
	}
	else if (key == K_E)
	{
		game->p.dir = vec_rot(game->p.dir, -5);
		game->p.plane = vec_rot(game->p.plane, -5);
	}
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
	printf("%d, %d", game.screen_height, game.screen_width);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_key_hook(game.win, user_move, &game);
	mlx_hook(game.win, 17, 0, &key_press_exit, &game);
	mlx_loop(game.mlx);
	return (0);
}
