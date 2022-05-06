/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:00:22 by juahn             #+#    #+#             */
/*   Updated: 2022/05/06 18:21:30 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

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

void	error(char *msg)
{
	printf("Error\n : %s\n", msg);
	exit (0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_list	*map_buffer;

	map_buffer = 0;
	if (argc != 2)
		error("ARG_ERROR");
	game.mlx = mlx_init();
	reset_data(&game);
	if (init_texture(&game) == -1)
		error("MALLOC_ERROR");
	if (!read_and_parse_map(&game, map_buffer, argv[1]))
		error("MAP_ERROR");
	init_window(&game);
	init_img(&game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_hook(game.win, 2, 0, user_move, &game);
	mlx_hook(game.win, 3, 0, user_stop, &game);
	mlx_hook(game.win, 17, 0, &key_press_exit, &game);
	mlx_loop(game.mlx);
	return (0);
}
