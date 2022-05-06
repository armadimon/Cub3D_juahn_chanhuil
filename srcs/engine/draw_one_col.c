#include "../../include/game.h"

int		check_wall_dir(t_game *game, t_vec ray)
{
	int tex_num = 0;
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

void	draw_texture_2(t_game *game, t_vec ray, int tex_x)
{
	int i;
	int	tex_y;
	int	color;

	i = 0;
	while (i < HEIGHT)
	{
			if (i < game->r.wall_start)
				game->img.data[i * WIDTH + game->r.x] = 0x010000 * game->map_data.C_red + 0x000100 * game->map_data.C_green + 0x000001 * game->map_data.C_blue;
			else if (i < game->r.wall_end)
			{
				tex_y = (int)(game->r.tex_pos) & (texHeight - 1);
				game->r.tex_pos += game->r.step;
				color = game->texture[check_wall_dir(game, ray)][texHeight * tex_y + tex_x];
				game->img.data[i * WIDTH + game->r.x] = color;
			}
			else
				game->img.data[i * WIDTH + game->r.x] = 0x010000 * game->map_data.F_red + 0x000100 * game->map_data.F_green + 0x000001 * game->map_data.F_blue;
		i++;
	}
}

double	calc_wall_x(t_game *game, double len, t_vec ray)
{
	double wall_x;

    if (game->side == 0)
		wall_x = game->p.pos.y + len * ray.y;
    else
		wall_x = game->p.pos.x + len * ray.x;
	wall_x -= floor((wall_x));
	return (wall_x);
}

void	draw_texture(t_game *game, t_vec ray, double len)
{
	int		tex_x;

	tex_x =(int)(calc_wall_x(game, len, ray) * (double)(texWidth));
	if ((game->side == 0 && ray.x > 0) || (game->side == 1 && ray.y < 0))
		tex_x = texWidth - tex_x - 1;
	game->r.step = 1.0 * texHeight / game->r.length;
	game->r.tex_pos = (game->r.wall_start - HEIGHT / 2 + game->r.length / 2) * game->r.step;
	draw_texture_2(game, ray, tex_x);
}

void	draw_one_column(t_game *game, int x, double len, t_vec ray)
{
	game->r.length = (int)((HEIGHT / 2)/ len * 1.35);
	game->r.wall_start = HEIGHT / 2 + (int)(-game->r.length / 2);
	game->r.wall_end = HEIGHT / 2 + (int)(game->r.length / 2);
	game->r.x = x;
	if (game->r.wall_start < 0)
		game->r.wall_start = 0;
	if (game->r.wall_end >= HEIGHT)
		game->r.wall_end = HEIGHT - 1;
	draw_texture(game, ray, len);
}