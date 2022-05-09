/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhuil <chanhuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:38:59 by juahn             #+#    #+#             */
/*   Updated: 2022/05/09 17:53:55 by chanhuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game_bonus.h"

int	able_to_move(t_game *game, int deg)
{
	t_vec	fv;

	fv = vec_add(game->p.pos, vec_mul(vec_rot(game->p.dir, deg), 0.2));
	if (game->map[(int)fv.y][(int)fv.x] != '0')
		return (0);
	return (1);
}

void	apply_mouse_input(t_game *game)
{
	int	x;
	int	y;
	
	if (game->key.m == 1)
	{
		mlx_mouse_hide();
		if (game->key.m_delay < 5)
			game->key.m_delay++;
		else
		{
			mlx_mouse_get_pos(game->win, &x, &y);
			game->p.dir = vec_rot(game->p.dir, (x * 2 / game->screen_width - 1) * 45);
			game->p.plane = vec_rot(game->p.plane, (x * 2 / game->screen_width - 1) * 45);
			mlx_mouse_move(game->win, game->screen_width / 2, game->screen_height / 2);
		}
	}
	else
	{
		mlx_mouse_show();
		game->key.m_delay = 0;
	}
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
	apply_mouse_input(game);
	draw_3d_map(game);
	if (game->map_flag)
		draw_2d_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
