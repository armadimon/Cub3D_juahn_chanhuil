/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2D_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:26:11 by juahn             #+#    #+#             */
/*   Updated: 2022/05/06 16:30:12 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"

void	draw_ray_i_x(t_game *game, double m, t_vec ray_dir)
{
	float	temp_y;
	int		color = 0xFF0000;
	int		x;

	x = game->p.pos.x * TILE_SIZE;
	temp_y = game->p.pos.y * TILE_SIZE;
	while (1)
	{
		if (temp_y / TILE_SIZE < 0 || temp_y / TILE_SIZE > game->map_height)
			return ;
		if (x / TILE_SIZE < 0 || x / TILE_SIZE > game->map_width)
			return ;
		if (game->map[(int)temp_y / TILE_SIZE][x / TILE_SIZE] == '1' ||
			game->map[(int)temp_y / TILE_SIZE][x / TILE_SIZE] == ' ')
			break ;
		game->img.data[(((int)temp_y / 4) * (WIDTH)) + x / 4] = color;
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
	int		color = 0xFF0000;

	temp_x = game->p.pos.x * TILE_SIZE;
	y = game->p.pos.y * TILE_SIZE;
	while (1)
	{
		if (temp_x / TILE_SIZE < 0 || temp_x / TILE_SIZE > game->map_width)
			return ;
		if (y / TILE_SIZE < 0 || y / TILE_SIZE > game->map_height)
			return ;
		if (game->map[y / TILE_SIZE][(int)temp_x / TILE_SIZE] == '1' ||
			game->map[y / TILE_SIZE][(int)temp_x / TILE_SIZE] == ' ')
			break ;
		game->img.data[(y / 4) * (WIDTH) + (int)(temp_x / 4)] = color;
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
