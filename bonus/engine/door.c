/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:24:30 by juahn             #+#    #+#             */
/*   Updated: 2022/05/10 21:12:24 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game_bonus.h"

void	open_close_door(t_game *game, int y, int x)
{
	int	i;

	i = 0;
	while (i < game->r.dr_cnt)
	{
		if (game->door[i].pos.x == x && game->door[i].pos.y == y
			&& game->door[i].flag == 0)
			game->door[i].flag = 1;
		if (game->door[i].pos.x == x && game->door[i].pos.y == y
			&& game->door[i].flag == 2)
			game->door[i].flag = 3;
		i++;
	}
}

void	cast_ray_i_x(t_game *game, double m, t_vec ray_dir)
{
	float	temp_y;
	int		x;
	int		i;

	i = -1;
	x = game->p.pos.x * TILE_SIZE;
	temp_y = game->p.pos.y * TILE_SIZE;
	while (++i < 40)
	{
		if (temp_y / TILE_SIZE < 0 || temp_y / TILE_SIZE > game->map_height)
			return ;
		if (x / TILE_SIZE < 0 || x / TILE_SIZE > game->map_width)
			return ;
		if (game->map[(int)temp_y / TILE_SIZE][x / TILE_SIZE] == '2')
			open_close_door(game, (int)temp_y / TILE_SIZE, x / TILE_SIZE);
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

void	cast_ray_i_y(t_game *game, double m, t_vec ray_dir)
{
	float	temp_x;
	int		y;
	int		i;

	i = -1;
	temp_x = game->p.pos.x * TILE_SIZE;
	y = game->p.pos.y * TILE_SIZE;
	while (++i < 40)
	{
		if (temp_x / TILE_SIZE < 0 || temp_x / TILE_SIZE > game->map_width)
			return ;
		if (y / TILE_SIZE < 0 || y / TILE_SIZE > game->map_height)
			return ;
		if (game->map[y / TILE_SIZE][(int)temp_x / TILE_SIZE] == '2')
			open_close_door(game, y / TILE_SIZE, (int)temp_x / TILE_SIZE);
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

void	cast_ray_and_check_door(t_game *game)
{
	double	camera_x;
	t_vec	ray_dir;
	double	m;

	if (game->map[(int)game->p.pos.y][(int)game->p.pos.x] == '2')
		return ;
	camera_x = 2 * (WIDTH / 2) / (double)(game->map_width * TILE_SIZE) - 1;
	ray_dir = vec_add(game->p.dir, vec_mul(game->p.plane, camera_x));
	m = tan(vec_angle(ray_dir));
	if (m <= 1.0f && m >= -1.0f)
		cast_ray_i_x(game, m, ray_dir);
	else
		cast_ray_i_y(game, 1 / m, ray_dir);
}
