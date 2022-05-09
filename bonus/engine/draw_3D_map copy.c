/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3D_map copy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhuil <chanhuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 19:29:14 by juahn             #+#    #+#             */
/*   Updated: 2022/05/09 16:19:49 by chanhuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game_bonus.h"

void	get_ray_value(t_vec *delta, t_vec *step, t_vec *side, t_vec ray)
{
	if (ray.x >= 0)
	{
		step->x = 1;
		side->x = 1 - side->x;
	}
	else
		step->x = -1;
	if (ray.y >= 0)
	{
		step->y = 1;
		side->y = 1 - side->y;
	}
	else
		step->y = -1;
	side->x *= delta->x;
	side->y *= delta->y;
}

t_vec	get_delta(t_vec ray)
{
	return (vec_new(fabs(1 / cos(vec_angle(ray))),
			fabs(1 / sin(vec_angle(ray)))));
}

t_vec	get_side(t_game *game)
{
	return (vec_new(game->p.pos.x - (int)(game->p.pos.x),
		game->p.pos.y - (int)(game->p.pos.y)));
}

int	check_hitted(t_game *game, char c, double *len, t_vec ray, int cnt)
{
	t_vec	delta;
	t_vec	hp;
	
	hp = vec_add(vec_add(game->p.pos, ray), vec_mul(ray, *len / vec_len(ray)));
	if (c == '2')
	{
		if (game->side == 0)
		{
			delta = vec_mul(ray, fabs(2 / cos(vec_angle(ray))) / vec_len(ray));
			if (vec_add(hp, delta).y < (int)hp.y + cnt / 100)
			{
				*len += vec_len(delta);
				return (0);
			}
		}
		else
		{
			delta = vec_mul(ray, fabs(2 / sin(vec_angle(ray))) / vec_len(ray));
			if (vec_add(hp, delta).x < (int)hp.x + cnt / 100)
			{
				*len += vec_len(delta);
				return (0);
			}
		}
	}
	else if (c == '1')
		return (0);
	return (1);
}

double	get_hitpoint(t_game *game, t_vec ray, t_vec count, double len, int cnt)
{
	t_vec	delta;
	t_vec	step;
	t_vec	side;

	delta = get_delta(ray);
	side = get_side(game);
	get_ray_value(&delta, &step, &side, ray);
	while (check_hitted(game, game->map[(int)count.y][(int)count.x], &len, ray, cnt))
	{
		if (side.x < side.y)
		{
			len = fabs(side.x);
			side.x += delta.x;
			count.x += step.x;
			game->side = 0;
		}
		else
		{
			len = fabs(side.y);
			side.y += delta.y;
			count.y += step.y;
			game->side = 1;
		}
	}
	return (len);
}

void	draw_3d_map(t_game *game)
{
	int		i;
	t_vec	ray;
	t_vec	hp;
	double	len;
	static int cnt;

	cnt++;
	if (cnt > 100)
		cnt = 0;
	i = -1;
	while (++i < WIDTH)
	{
		ray = vec_add(game->p.dir, vec_mul(game->p.plane, 2 * i
					/ (double)(WIDTH) - 1));
		hp = vec_mul(vec_norm(ray), get_hitpoint(game, ray,
		 			vec_new((int)game->p.pos.x, (int)game->p.pos.y), 1.0, cnt));
		len = vec_len(hp) / vec_len(ray);
		draw_one_column(game, i, len, ray);
	}
}
