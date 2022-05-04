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
	// mlx_key_hook(game.win, user_move, &game);
	// mlx_hook(game.win, 17, 0, &key_press_exit, &game);
	mlx_loop(game.mlx);
	return (0);
}
