/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:38:59 by juahn             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/05/10 12:21:59 by juahn            ###   ########.fr       */
=======
/*   Updated: 2022/05/09 18:44:39 by juahn            ###   ########.fr       */
>>>>>>> 4e81942d7905bbcea4bb9997d3a8e3aecce0134d
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
	int	sign;
	
	sign = 0;
<<<<<<< HEAD
	if (game->key.o == 1)
	{
		mlx_mouse_hide();
		if (game->key.o_delay++ < 5)
=======
	if (game->key.m == 1)
	{
		mlx_mouse_hide();
		if (game->key.m_delay++ < 5)
>>>>>>> 4e81942d7905bbcea4bb9997d3a8e3aecce0134d
			mlx_mouse_move(game->win, WIDTH / 2, HEIGHT / 2);
		else
		{
			mlx_mouse_get_pos(game->win, &x, &y);
			if (x < WIDTH / 2)
				sign = 1;
			if (x > WIDTH / 2)
				sign = -1;
			game->p.dir = vec_rot(game->p.dir, sign);
			game->p.plane = vec_rot(game->p.plane, sign);
			mlx_mouse_move(game->win, WIDTH / 2, HEIGHT / 2);
		}
	}
	else
	{
		mlx_mouse_show();
<<<<<<< HEAD
		game->key.o_delay = 0;
=======
		game->key.m_delay = 0;
>>>>>>> 4e81942d7905bbcea4bb9997d3a8e3aecce0134d
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
	while (i < game->dr_cnt)
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
	door_status_check(game);
	apply_key_input(game);
	apply_mouse_input(game);
	draw_3d_map(game);
	if (game->map_flag)
		draw_2d_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
