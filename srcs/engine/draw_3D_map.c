#include "../../include/game.h"

void	get_ray_value(t_vec *delta, t_vec *step, t_vec *side, t_vec ray)
{
	if (ray.x >=0)
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

double	get_hitpoint(t_game *game, t_vec ray)
{
	t_vec	delta;
	t_vec	step;
	t_vec	side;
	t_vec	count;
	double	len;

	count = vec_new((int)game->p.pos.x, (int)game->p.pos.y);
	delta = vec_new(fabs(1 / cos(vec_angle(ray))), fabs(1 / sin(vec_angle(ray))));
	side = vec_new(game->p.pos.x - (int)(game->p.pos.x),
			game->p.pos.y - (int)(game->p.pos.y));
	get_ray_value(&delta, &step, &side, ray);
	len = 1;
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
		if (game->map[(int)count.y][(int)count.x] == '1')
			break ;
	}
	return (len);
}

void	draw_3D_map(t_game *game)
{
	int		i;
	t_vec	ray;
	t_vec	hp;
	double	len;

	i = -1;
	while (++i < WIDTH)
	{
		ray = vec_add(game->p.dir, vec_mul(game->p.plane, 2 * i / (double)(WIDTH) - 1));
		hp = vec_mul(vec_norm(ray), get_hitpoint(game, ray));
		len = vec_len(hp) / vec_len(ray);
		draw_one_column(game, i, len, ray);
	}
}
