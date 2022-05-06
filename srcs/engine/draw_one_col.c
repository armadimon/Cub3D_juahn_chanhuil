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

void	draw_one_column(t_game *game, int x, double len, t_vec ray)
{
	int	wall_start;
	int	wall_end;
	int length;

	length = (int)((HEIGHT / 2)/ len * 1.35);
	wall_start = HEIGHT / 2 + (int)(-length / 2);
	wall_end = HEIGHT / 2 + (int)(length / 2);
	if (wall_start < 0)
		wall_start = 0;
	if (wall_end >= HEIGHT)
		wall_end = HEIGHT - 1;
 	double wallX;
    if (game->side == 0)
		wallX = game->p.pos.y + len * ray.y;
    else
		wallX = game->p.pos.x + len * ray.x;
    wallX -= floor((wallX));
    int texX = (int)(wallX * (double)(texWidth));
	if ((game->side == 0 && ray.x > 0) || (game->side == 1 && ray.y < 0))
		texX = texWidth - texX - 1;
 	double step = 1.0 * texHeight / length;
    double texPos = (wall_start - HEIGHT / 2 + length / 2) * step;
	for (int i=0;i<HEIGHT;i++)
	{
		if (i < wall_start)
			game->img.data[i * WIDTH + x] = 0x010000 * game->map_data.C_red + 0x000100 * game->map_data.C_green + 0x000001 * game->map_data.C_blue;
		else if (i < wall_end)
		{
		    int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			int color = game->texture[check_wall_dir(game, ray)][texHeight * texY + texX];
			game->img.data[i * WIDTH + x] = color;
		}
		else
			game->img.data[i * WIDTH + x] = 0x010000 * game->map_data.F_red + 0x000100 * game->map_data.F_green + 0x000001 * game->map_data.F_blue;
	}
}