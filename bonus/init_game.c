/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:36:06 by juahn             #+#    #+#             */
/*   Updated: 2022/05/09 15:40:23 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game_bonus.h"

void	init_window(t_game *game)
{
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "mlx 42");
}

void	init_img(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.data = (int *)mlx_get_data_addr(game->img.img,
			&game->img.bpp, &game->img.size_l, &game->img.endian);
}

int	load_tex_enemy_and_sprite(t_game *game)
{
	t_img	img;

	load_image(game, game->texture[4], "./images/enemy.xpm", &img);
	return (1);
}

int	init_texture(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->texture = (int **)malloc(sizeof(int *) * 7);
	if (!game->texture)
		return (0);
	while (i < 7)
	{
		game->texture[i] = (int *)malloc(sizeof(int) * (TEXHEIGHT * TEXWIDTH));
		if (!game->texture[i])
			return (0);
		i++;
	}
	i = 0;
	while (i < 7)
	{
		j = -1;
		while (++j < TEXHEIGHT * TEXWIDTH)
			game->texture[i][j] = 0;
		i++;
	}
	load_tex_enemy_and_sprite(game);
	return (1);
}

void	init_game(t_game *game)
{
	game->mlx = 0;
	game->win = 0;
	game->map_width = 0;
	game->map_height = 0;
}

void	init_valid(t_valid *valid)
{
	valid->valid_ea = 0;
	valid->valid_no = 0;
	valid->valid_we = 0;
	valid->valid_so = 0;
	valid->valid_c = 0;
	valid->valid_f = 0;
}
