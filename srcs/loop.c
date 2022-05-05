#include "../include/game.h"

// int		draw_texture(t_game *game)
// {
// 	int i = 0;
// 	int j = 0;
// 	while (i < texHeight)
// 	{
// 		j = 0;
// 		while (j < texWidth)
// 		{
// 			game->img.data[i * texHeight * COLS  + j] = game->texture[1][i * texHeight + j];
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

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

	count[0] = (int)game->p.pos.x;
	count[1] = (int)game->p.pos.y;
	delta = vec_new(fabs(1 / cos(vec_angle(ray))), fabs(1 / sin(vec_angle(ray))));
	side = vec_new(game->p.pos.x - (int)(game->p.pos.x),
			game->p.pos.y - (int)(game->p.pos.y));
	get_ray_value(&delta, &step, &side, ray);
	while (1)
	{
		if (side.x < side.y)
		{
			len = fabs(side.x);
			side.x += delta.x;
			count[0] += step.x;
		}
		else
		{
			len = fabs(side.y);
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
	int length;

	length = (int)(HEIGHT / len);
	wall_start = HEIGHT / 2 + (int)(-length / 2);
	// if (wall_start < 0)
	// 	wall_start = 0;
	wall_end = HEIGHT / 2 + (int)(length / 2);
	// if (wall_end >= len)
	// 	wall_end = len - 1;
	for (int i=0;i<HEIGHT;i++)
	{
		if (i < wall_start)
			game->img.data[i * WIDTH + x] = 0xaaaaff;
		else if (i < wall_end)
			game->img.data[i * WIDTH + x] = 0x00ff00;
		else
			game->img.data[i * WIDTH + x] = 0x000000;
	}
}

double temp(t_game *game, int i)
{
	char **temp_map = game->map;
			double cameraX = 2 * i / (double)WIDTH - 1;
		double rayDirX = game->p.dir.x + game->p.plane.x * cameraX;
		double rayDirY = game->p.dir.y + game->p.plane.y * cameraX;
		
		int mapX = (int)game->p.pos.x;
		int mapY = (int)game->p.pos.y;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		
		 //length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->p.pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->p.pos.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->p.pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->p.pos.y) * deltaDistY;
		}

		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (mapX < 0 || mapX > game->map_width ||
				mapY < 0 || mapY > game->map_height)
				return (0);
			if (temp_map[mapY][mapX] == '1' || temp_map[mapY][mapX] == ' ')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - game->p.pos.x + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - game->p.pos.y + (1 - stepY) / 2) / rayDirY;

		return (perpWallDist);

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
		ray = vec_add(game->p.dir, vec_mul(game->p.plane, 2.0 * i / WIDTH - 1));
		hp = vec_mul(vec_norm(ray), get_hitpoint(game, ray));
		len = vec_len(hp) / vec_len(ray) - 1;
	// printf("perp : %f\n", len);
		// len = temp(game, i);
		draw_one_column(game, i, len);
	}
}

int		main_loop(t_game *game)
{
	// draw_texture(game);
	draw_3D_map(game);
	if (game->map_flag)
		draw_2D_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
