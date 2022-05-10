/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_one_col.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 18:13:02 by juahn             #+#    #+#             */
/*   Updated: 2022/05/10 13:21:38 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game_bonus.h"

int	check_wall_dir(t_game *game, t_vec ray)
{
	int	tex_num;

	if (game->r.door_flag >= 1)
		return (7);
	tex_num = 0;
	if (game->side == 1)
	{
		if (ray.y >= 0)
			tex_num = 0;
		else
			tex_num = 1;
	}
	else
	{
		if (ray.x >= 0)
			tex_num = 2;
		else
			tex_num = 3;
	}
	return (tex_num);
}

void	draw_texture_2(t_game *game, int tex_x, double tex_pos, double step)
{
	int	i;
	int	tex_y;
	int	color;

	i = 0;
	while (i < HEIGHT)
	{
		if (i < game->r.wall_start)
			game->img.data[i * WIDTH + game->r.x] = fill_ceiling_color(game);
		else if (i < game->r.wall_end)
		{
			tex_y = (int)tex_pos;
			tex_pos += step;
			color = game->texture[check_wall_dir(game, game->ray)]
			[TEXHEIGHT * tex_y + tex_x];
			if (color != 0x980088)
				game->img.data[i * WIDTH + game->r.x] = color;
		}
		else
			game->img.data[i * WIDTH + game->r.x] = fill_floor_color(game);
		i++;
	}
}

double	calc_wall_x(t_game *game, double len, t_vec ray)
{
	double	wall_x;

	if (game->side == 0)
		wall_x = game->p.pos.y + len * ray.y;
	else
		wall_x = game->p.pos.x + len * ray.x;
	wall_x -= floor((wall_x));
	if (game->r.door_flag > 0)
	{
		wall_x = wall_x - ((double)(game->door[game->r.door_flag - 1].open_rate) / 100);
		wall_x = fabs(wall_x);
	}
	return (wall_x);
}

void	draw_texture(t_game *game, t_vec ray, double len)
{
	int		tex_x;
	double	tex_pos;
	double	step;

	tex_x = (int)(calc_wall_x(game, len, ray) * (double)(TEXWIDTH));
	step = 1.0 * TEXHEIGHT / game->r.length;
	tex_pos = (game->r.wall_start - HEIGHT / 2 + game->r.length / 2) * step;
	draw_texture_2(game, tex_x, tex_pos, step);
}

void	draw_one_column(t_game *game, int x, double len, t_vec ray)
{
	game->ray = ray;
	game->r.length = (int)((HEIGHT / 2) / len * 1.35);
	game->r.wall_start = HEIGHT / 2 + (int)(-game->r.length / 2);
	game->r.wall_end = HEIGHT / 2 + (int)(game->r.length / 2);
	game->r.x = x;
	if (game->r.wall_start < 0)
		game->r.wall_start = 0;
	if (game->r.wall_end >= HEIGHT)
		game->r.wall_end = HEIGHT - 1;
	draw_texture(game, game->ray, len);
}
