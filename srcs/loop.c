#include "../include/game.h"

int		draw_texture(t_game *game)
{
	int i = 0;
	int j = 0;
	while (i < texHeight)
	{
		j = 0;
		while (j < texWidth)
		{
			game->img.data[i * texHeight * COLS  + j] = game->texture[1][i * texHeight + j];
			j++;
		}
		i++;
	}
	return (0);
}

void	get_ray_value(t_vec *delta, t_vec *step, t_vec *side, t_vec ray)
{
	if (ray.x < 0)
	{
		step->x = -1;
		side->x = 1 - side->x;
	}
	else
		step->x = 1;
	if (ray.y < 0)
	{
		step->y = -1;
		side->y = 1 - side->y;
	}
	else
		step->y = 1;
	side->x *= delta->x;
	side->y *= delta->y;
}

double	get_hitpoint(t_game *game, t_vec ray)
{
	t_vec	delta;
	t_vec	step;
	t_vec	side;
	int		count[2];
	double	len;

	delta = vec_new(1 / cos(vec_angle(ray)), 1 / sin(vec_angle(ray)));
	side = vec_new(game->p.pos.x - (int)(game->p.pos.x),
			game->p.pos.y - (int)(game->p.pos.y));
	get_ray_value(&delta, &step, &side, ray);
	while (1)
	{
		if (side.x < side.y)
		{
			len = side.x;
			side.x += delta.x;
			count[0] += step.x;
		}
		else
		{
			len = side.y;
			side.y += delta.y;
			count[1] += step.y;
		}
		if (game->map[count[1]][count[0]] == '1')
			return (len);
	}
}

void	draw_one_column(t_game *game, int x, double len)
{
	int	wall_start;
	int	wall_end;

	wall_start = 480 / 2 - 2 / len;
	wall_end = 480 / 2 + 2 / len;

	for (int i=0;i<480;i++)
	{
		if (i < wall_start)
			game->img.data[i * 480 + x] = 0xaaaaff;
		else if (i < wall_end)
			game->img.data[i * 480 + x] = 0x00ff00;
		else
			game->img.data[i * 480 + x] = 0x000000;
	}
}

void	draw_3D_map(t_game *game)
{
	int		i;
	t_vec	ray;
	t_vec	hp;
	double	len;

	i = -1;
	while (++i < 640)
	{
		ray = vec_add(game->p.dir, vec_mul(game->p.plane, 2.0 * i / 640 - 1));
		hp = vec_mul(vec_norm(ray), get_hitpoint(game, ray));
		len = vec_len(hp) / vec_len(ray) - 1;
		draw_one_column(game, i, len);
	}
}

int		main_loop(t_game *game)
{
	init_img(game);
	// draw_texture(game);
	// draw_2D_map(game);
	draw_3D_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
