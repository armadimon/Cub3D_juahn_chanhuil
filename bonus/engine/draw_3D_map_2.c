/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3D_map_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 19:29:14 by juahn             #+#    #+#             */
/*   Updated: 2022/05/10 22:08:40 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game_bonus.h"

double	get_door_cnt(t_game *game, t_vec count)
{
	int	i;

	i = 0;
	while (game->door[i].pos.x)
	{
		if ((int)count.x == (int)game->door[i].pos.x
			&& (int)count.y == (int)game->door[i].pos.y)
		{
			game->r.door_flag = i + 1;
			return ((double)game->door[i].open_rate);
		}
		i++;
	}
	return (0.0);
}

int	check_door_hitted(t_game *game, t_vec count, t_vec ray, double *len)
{
	t_vec	delta;
	t_vec	hp;

	hp = vec_add(game->p.pos, vec_mul(ray, *len / vec_len(ray)));
	if (game->side == 0)
	{
		delta = vec_mul(ray, fabs(0.5 / cos(vec_angle(ray))) / vec_len(ray));
		if (vec_add(hp, delta).y < (count.y) + get_door_cnt(game, count)
			/ 100.0 && vec_add(hp, delta).y > count.y)
		{
			*len += vec_len(delta);
			return (1);
		}
	}
	else
	{
		delta = vec_mul(ray, fabs(0.5 / sin(vec_angle(ray))) / vec_len(ray));
		if (vec_add(hp, delta).x < (count.x) + get_door_cnt(game, count)
			/ 100.0 && vec_add(hp, delta).x > count.x)
		{
			*len += vec_len(delta);
			return (1);
		}
	}
	return (0);
}

int	check_hitted(t_game *game, t_vec count, double *len, t_vec ray)
{
	if (game->map[(int)count.y][(int)count.x] == '2')
	{
		if (check_door_hitted(game, count, ray, len))
			return (0);
		game->r.door_flag = 0;
	}
	else if (game->map[(int)count.y][(int)count.x] == '1')
		return (0);
	return (1);
}
