/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3D_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 19:29:14 by juahn             #+#    #+#             */
/*   Updated: 2022/05/07 15:52:03 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"

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

double	get_hitpoint(t_game *game, t_vec ray, t_vec count, double len)
{
	t_vec	delta;
	t_vec	step;
	t_vec	side;

	delta = get_delta(ray);
	side = get_side(game);
	get_ray_value(&delta, &step, &side, ray);
	while (1)
	{
		if (game->map[(int)count.y][(int)count.x] == '2')
		{
			// if (count.x + step.y / 2 < 1)
			// {
				if (side.x < side.y)
				{
					if (game->map[(int)count.y][(int)(count.x + step.x)] != '2')
					{
					game->side = 0;
					side.x -= (delta.x / 2);
					return (fabs(side.x));
					}
					if (game->map[(int)count.y][(int)(count.x + step.x/ 2)] == '2')
					{
						printf("check : fab [%f]\n", fabs(side.x));
					game->side = 0;
					side.x -= (delta.x / 2);
					return (fabs(side.x));
					}
				}
				else
				{
					if (game->map[(int)(count.y +step.y)][(int)(count.x)] != '2')
					{					
					game->side = 1;
					side.y -= (delta.y / 2);
					return (fabs(side.y));
					}
					if (game->map[(int)(count.y +step.y/ 2)][(int)(count.x)] == '2')
					{					
					game->side = 1;
					side.y += (delta.y / 2);
					return (fabs(side.y));
					}
				}
		}
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
		if (game->map[(int)count.y][(int)count.x] == '1')
			break ;
	}
	return (len);
}

void	draw_3d_map(t_game *game)
{
	int		i;
	t_vec	ray;
	t_vec	hp;
	double	len;

	i = -1;
	while (++i < WIDTH)
	{
		ray = vec_add(game->p.dir, vec_mul(game->p.plane, 2 * i
					/ (double)(WIDTH) - 1));
		hp = vec_mul(vec_norm(ray), get_hitpoint(game, ray,
					vec_new((int)game->p.pos.x, (int)game->p.pos.y), 1.0));
		len = vec_len(hp) / vec_len(ray);
		draw_one_column(game, i, len, ray);
	}
}
