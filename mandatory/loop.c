/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:38:59 by juahn             #+#    #+#             */
/*   Updated: 2022/05/07 11:24:13 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

int	able_to_move(t_game *game, int deg)
{
	t_vec	fv;

	fv = vec_add(game->p.pos, vec_mul(vec_rot(game->p.dir, deg), 0.2));
	if (game->map[(int)fv.y][(int)fv.x] != '0')
		return (0);
	return (1);
}

void	apply_key_input(t_game *game)
{
	if (game->key.w && able_to_move(game, 0))
		game->p.pos = vec_add(game->p.pos,
				vec_mul(vec_rot(game->p.dir, 0), 0.05));
	if (game->key.a && able_to_move(game, 90))
		game->p.pos = vec_add(game->p.pos,
				vec_mul(vec_rot(game->p.dir, 90), 0.05));
	if (game->key.s && able_to_move(game, 180))
		game->p.pos = vec_add(game->p.pos,
				vec_mul(vec_rot(game->p.dir, 180), 0.05));
	if (game->key.d && able_to_move(game, 270))
		game->p.pos = vec_add(game->p.pos,
				vec_mul(vec_rot(game->p.dir, 270), 0.05));
	if (game->key.al)
	{
		game->p.dir = vec_rot(game->p.dir, 1);
		game->p.plane = vec_rot(game->p.plane, 1);
	}
	if (game->key.ar)
	{
		game->p.dir = vec_rot(game->p.dir, -1);
		game->p.plane = vec_rot(game->p.plane, -1);
	}
}

int	main_loop(t_game *game)
{
	apply_key_input(game);
	draw_3d_map(game);
	if (game->map_flag)
		draw_2d_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
