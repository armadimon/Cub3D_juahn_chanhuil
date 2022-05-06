/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2D_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:24:30 by juahn             #+#    #+#             */
/*   Updated: 2022/05/06 20:23:40 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"

void	draw_rectangle(t_game *game, int x, int y)
{
	int	i;
	int	j;

	x *= TILE_SIZE / 4;
	y *= TILE_SIZE / 4;
	i = 0;
	while (i < TILE_SIZE / 4)
	{
		j = 0;
		while (j < TILE_SIZE / 4)
		{
			game->img.data[(y + i) * (WIDTH) + x + j] = 0xFFFFFF;
			j++;
		}
		i++;
	}
}

void	draw_background(t_game *game, int x, int y)
{
	int	i;
	int	j;

	x *= TILE_SIZE / 4;
	y *= TILE_SIZE / 4;
	i = 0;
	while (i < TILE_SIZE / 4)
	{
		j = 0;
		while (j < TILE_SIZE / 4)
		{
			game->img.data[(y + i) * (WIDTH) + x + j] = 0x000000;
			j++;
		}
		i++;
	}
}

void	draw_rectangles(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == '1')
				draw_rectangle(game, j, i);
			if (game->map[i][j] == '0')
				draw_background(game, j, i);
			j++;
		}
		i++;
	}
}

void	draw_2d_map(t_game *game)
{
	int	w;

	draw_rectangles(game);
	w = 0;
	while (w < game->screen_width)
	{
		draw_ray(game, w);
		w++;
	}
}
