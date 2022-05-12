/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:36:06 by juahn             #+#    #+#             */
/*   Updated: 2022/05/10 22:09:57 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game_bonus.h"

int	load_tex_door_and_sprite(t_game *game)
{
	t_img	img;

	if (!load_image(game, game->texture[4], "./images/enemy1.xpm", &img))
		return (0);
	if (!load_image(game, game->texture[5], "./images/enemy2.xpm", &img))
		return (0);
	if (!load_image(game, game->texture[6], "./images/enemy3.xpm", &img))
		return (0);
	if (!load_image(game, game->texture[7], "./images/Door.xpm", &img))
		return (0);
	return (1);
}

int	init_texture(t_game *game)
{
	int	i;
	int	j;

	game->texture = (int **)malloc(sizeof(int *) * 7);
	if (!game->texture)
		return (0);
	i = -1;
	while (++i < 8)
	{
		game->texture[i] = (int *)malloc(sizeof(int) * (TEXHEIGHT * TEXWIDTH));
		if (!game->texture[i])
			return (0);
	}
	i = -1;
	while (++i < 8)
	{
		j = -1;
		while (++j < TEXHEIGHT * TEXWIDTH)
			game->texture[i][j] = 0;
	}
	if (!load_tex_door_and_sprite(game))
		return (0);
	return (1);
}
