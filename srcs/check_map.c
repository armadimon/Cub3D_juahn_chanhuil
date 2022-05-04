#include "../include/game.h"

int	check_map(t_game *game)
{
	int i;
	int j;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == 'N')
				game->p.dir = vec_new(0 , -1);
			else if (game->map[i][j] == 'S')
				game->p.dir = vec_new(0 , 1);
			else if (game->map[i][j] == 'E')
				game->p.dir = vec_new(1 , 0);
			else if (game->map[i][j] == 'W')
				game->p.dir = vec_new(-1 , 0);
			else
				continue ;
			game->p.pos = vec_new(j + 0.5, i + 0.5);
		}
	}
	game->p.plane = vec_rot(game->p.dir, -90);
	return (1);
}