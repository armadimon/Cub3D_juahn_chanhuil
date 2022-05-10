/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2D_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:26:11 by juahn             #+#    #+#             */
/*   Updated: 2022/05/10 15:36:02 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game_bonus.h"

int	color_ch(int oriy, int y)
{
	int	distance;

	distance = abs(y - oriy);
	distance /= 100;
	distance = 255 - distance / 5;
	if (distance < 0)
		return (0x000000);
	return (0x010000 * (distance));
}

int	check_tile(t_game *game, int y, int x)
{
	int i;

	i = 0;
	if (game->map[y][x] == '1' || game->map[y][x] == ' ' || game->map[y][x] == '3')
		return (0);
	if (game->map[y][x] == '2')
	{
		while (i < game->r.dr_cnt)
		{
			if (game->door[i].pos.x == x && game->door[i].pos.y == y)
			{
				if (game->door[i].open_rate == 100)
					return (0);
				else
					return (1);
			}
			i++;
		}
	}
	return (1);
}

void	draw_ray_i_x(t_game *game, double m, t_vec ray_dir)
{
	float	temp_y;
	int		x;

	x = game->p.pos.x * TILE_SIZE;
	temp_y = game->p.pos.y * TILE_SIZE;
	while (1)
	{
		if (temp_y / TILE_SIZE < 0 || temp_y / TILE_SIZE > game->map_height)
			return ;
		if (x / TILE_SIZE < 0 || x / TILE_SIZE > game->map_width)
			return ;
		if (!check_tile(game, (int)temp_y / TILE_SIZE, x / TILE_SIZE))
			break ;
		game->img.data[(((int)temp_y / 4) * (WIDTH)) + x / 4]
			= color_ch((int)(game->p.pos.x * TILE_SIZE * 100), x * 100);
		if (ray_dir.x < 0)
			x--;
		else
			x++;
		if (ray_dir.y < 0)
			temp_y -= fabs(m);
		else
			temp_y += fabs(m);
	}	
}

void	draw_ray_i_y(t_game *game, double m, t_vec ray_dir)
{
	float	temp_x;
	int		y;

	temp_x = game->p.pos.x * TILE_SIZE;
	y = game->p.pos.y * TILE_SIZE;
	while (1)
	{
		if (temp_x / TILE_SIZE < 0 || temp_x / TILE_SIZE > game->map_width)
			return ;
		if (y / TILE_SIZE < 0 || y / TILE_SIZE > game->map_height)
			return ;
		if (!check_tile(game, y / TILE_SIZE, (int)temp_x / TILE_SIZE))
			break ;
		game->img.data[(y / 4) * (WIDTH) + (int)(temp_x / 4)]
			= color_ch((int)(game->p.pos.y * TILE_SIZE * 100), y * 100);
		if (ray_dir.x < 0)
			temp_x -= fabs(m);
		else
			temp_x += fabs(m);
		if (ray_dir.y < 0)
			y--;
		else
			y++;
	}	
}

void	draw_ray(t_game *game, int w)
{
	double	camera_x;
	t_vec	ray_dir;
	double	m;

	camera_x = 2 * w / (double)(game->map_width * TILE_SIZE) - 1;
	ray_dir = vec_add(game->p.dir, vec_mul(game->p.plane, camera_x));
	m = tan(vec_angle(ray_dir));
	if (m <= 1.0f && m >= -1.0f)
		draw_ray_i_x(game, m, ray_dir);
	else
		draw_ray_i_y(game, 1 / m, ray_dir);
}
