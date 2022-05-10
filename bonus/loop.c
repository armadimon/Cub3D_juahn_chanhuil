/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:38:59 by juahn             #+#    #+#             */
/*   Updated: 2022/05/10 15:09:03 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game_bonus.h"

int	able_to_move(t_game *game, int deg)
{
	int		i;
	t_vec	fv;

	i = -1;
	fv = vec_add(game->p.pos, vec_mul(vec_rot(game->p.dir, deg), 0.2));
	if (game->map[(int)fv.y][(int)fv.x] == '0')
		return (1);
	if (game->map[(int)fv.y][(int)fv.x] == '2')
	{
		while (++i < game->r.dr_cnt)
		{
			if (vec_equal(game->door[i].pos, vec_new((int)fv.x, (int)fv.y))
				&& game->door[i].flag == 0)
				return (1);
		}
	}
	return (0);
}

void	apply_mouse_input(t_game *game)
{
	int	x;
	int	y;
	if (game->key.o == 1)
	{
		mlx_mouse_hide();
		if (game->key.o_delay++ < 5)
			mlx_mouse_move(game->win, WIDTH / 2, HEIGHT / 2);
		else
		{
			mlx_mouse_get_pos(game->win, &x, &y);
			game->p.dir = vec_mrot(game->p.dir, -(2.0 * x / WIDTH - 1) * 160);
			game->p.plane = vec_mrot(game->p.plane, -(2.0 * x / WIDTH - 1) * 160);
			mlx_mouse_move(game->win, WIDTH / 2, HEIGHT / 2);
		}
	}
	else
	{
		mlx_mouse_show();
		game->key.o_delay = 0;
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

void	door_status_check(t_game *game)
{
	int i;

	i = 0;
	while (i < game->r.dr_cnt)
	{
		if (game->door[i].flag == 1)
		{
			game->door[i].open_rate++;
			if (game->door[i].open_rate > 100)
			{
				game->door[i].open_rate = 100;
				game->door[i].flag = 2;
			}
		}
		if (game->door[i].flag == 3)
		{
			game->door[i].open_rate--;
			if (game->door[i].open_rate <= 0)
			{
				game->door[i].open_rate = 0;
				game->door[i].flag = 0;
			}
		}
		i++;
	}
}

int	main_loop(t_game *game)
{
	game->cnt++;
	if (game->cnt > 100)
		game->cnt = 0;
	door_status_check(game);
	apply_key_input(game);
	apply_mouse_input(game);
	draw_3d_map(game);
	draw_sprite(game);
	if (game->map_flag)
		draw_2d_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
