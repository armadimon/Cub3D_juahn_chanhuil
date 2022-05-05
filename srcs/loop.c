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
	int		count[2];
	double	len;

	count[0] = (int)game->p.pos.x;
	count[1] = (int)game->p.pos.y;
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
			count[0] += step.x;
			game->side = 0;
		}
		else
		{
			len = fabs(side.y);
			side.y += delta.y;
			count[1] += step.y;
			game->side = 1;
		}
		if (game->map[count[1]][count[0]] == '1')
			break ;
	}
	return (len);
}

void	draw_one_column(t_game *game, int x, double len, t_vec ray)
{
	int	wall_start;
	int	wall_end;
	int length;

	length = (int)((HEIGHT / 2)/ len);
	wall_start = HEIGHT / 2 + (int)(-length / 2);
	if (wall_start < 0)
		wall_start = 0;
	wall_end = HEIGHT / 2 + (int)(length / 2);
	if (wall_end >= HEIGHT)
		wall_end = HEIGHT - 1;
 	double wallX; //where exactly the wall was hit
      if (game->side == 0) wallX = game->p.pos.y + len * ray.y;
      else           wallX = game->p.pos.x + len * ray.x;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = (int)(wallX * (double)(texWidth));
      if(game->side == 0 && ray.x > 0) texX = texWidth - texX - 1;
      if(game->side == 1 && ray.y < 0) texX = texWidth - texX - 1;

 	double step = 1.0 * texHeight / length;
      // Starting texture coordinate
      double texPos = (wall_start - HEIGHT / 2 + length / 2) * step;
      for(int y = wall_start; y<wall_end; y++)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow

      }

	for (int i=0;i<HEIGHT;i++)
	{
		if (i < wall_start)
			game->img.data[i * WIDTH + x] = 0xaaaaff;
		else if (i < wall_end)
		{
		    int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			int color = game->texture[0][texHeight * texY + texX];
			game->img.data[i * WIDTH + x] = color;
		}
		else
			game->img.data[i * WIDTH + x] = 0x000000;
	}
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

int		main_loop(t_game *game)
{
	// draw_texture(game);
	draw_3D_map(game);
	if (game->map_flag)
		draw_2D_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
