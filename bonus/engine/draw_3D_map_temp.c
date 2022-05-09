/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3D_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 19:29:14 by juahn             #+#    #+#             */
/*   Updated: 2022/05/09 17:31:18 by juahn            ###   ########.fr       */
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

double	get_hitpoint(t_game *game, t_vec ray, t_vec count, double len, int cnt)
{
	t_vec	delta;
	t_vec	step;
	t_vec	side;

	delta = get_delta(ray);
	side = get_side(game);
	get_ray_value(&delta, &step, &side, ray);
	while (1)
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
		if (game->map[(int)count.y][(int)count.x] == '2')
		{
			double map_x2=count.x;
			double map_y2=count.y;
			// if (game->p.pos.x < count.x)
			// 	map_x2 -= 1;
			// if (game->p.pos.y > count.y)
			// 	map_y2 += 1;
		
			double adj=1;
			double ray_mult=1;
			if (game->side == 1)
			{
				adj= map_y2 - game->p.pos.y;
				ray_mult = adj / ray.y;
			}
			else
			{
				adj=(map_x2 - game->p.pos.x) + 1;
				ray_mult = adj / ray.x;
			}
			double rxe2 = game->p.pos.x+ray.x*ray_mult;
			double rye2 = game->p.pos.y+ray.y*ray_mult;
		
			double true_delta_x=sqrt(1+(ray.y*ray.y)/(ray.x*ray.x));
			double true_delta_y=sqrt(1+(ray.x*ray.x)/(ray.y*ray.y));
		
			// if (fabs(ray.x) < 0.01)
			// true_delta_x=100;
			// if (fabs(ray.y) < 0.01)
			// true_delta_y=100;
			if (game->side == 0)
			{
				double true_y_step=sqrt(true_delta_x*true_delta_x-1);
				double half_step_in_y=rye2+(step.y *true_y_step)/2;
				if ((floor(half_step_in_y) == count.y) && ((half_step_in_y - count.y) > ((double)(cnt)) / 100))
						break ;
			}
			else
			{
				double true_x_step=sqrt(true_delta_y*true_delta_y-1);
				double half_step_in_x=rxe2+(step.x*true_x_step)/2;
				if ((floor(half_step_in_x) == count.x) && (half_step_in_x-count.x > ((double)(cnt)) / 100))
						break ;
			}
		}
		if (game->map[(int)count.y][(int)count.x] == '1')
			break ;
	}
	if (game->side == 0)
	{
		if (game->map[(int)count.y][(int)count.x] == '2')
			count.x += step.x / 2;
		len = (count.x - game->p.pos.x + (1 - step.x) / 2) / ray.x;
	}
	else
	{
		if (game->map[(int)count.y][(int)count.x] == '2')
			count.y += step.y / 2;
		len = (count.y - game->p.pos.y + (1 - step.y) / 2) / ray.y;
	}
	return (len);
}

void	draw_3d_map(t_game *game)
{
	int		i;
	t_vec	ray;
	// t_vec	hp;
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
		// hp = vec_mul(vec_norm(ray), get_hitpoint(game, ray,
		// 			vec_new((int)game->p.pos.x, (int)game->p.pos.y), 1.0));
		// len = vec_len(hp) / vec_len(ray);
		len = get_hitpoint(game, ray, vec_new((int)game->p.pos.x, (int)game->p.pos.y), 1.0 , cnt);
		draw_one_column(game, i, len, ray);
	}
}
