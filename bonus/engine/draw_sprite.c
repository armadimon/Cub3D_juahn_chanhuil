/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 19:29:14 by juahn             #+#    #+#             */
/*   Updated: 2022/05/10 16:08:46 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game_bonus.h"

typedef struct		s_pair
{
	double	first;
	int		second;
}					t_pair;

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;

	for (int i = 0; i < amount; i++)
	{
		for (int j = 0; j < amount - 1; j++)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
		}
	}
}

void	sortSprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;

	//std::vector<std::pair<double, int>> sprites(amount);
	sprites = (t_pair*)malloc(sizeof(t_pair) * amount);
	for (int i = 0; i < amount; i++)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	sort_order(sprites, amount);
	//std::sort(sprites.begin(), sprites.end());
	for (int i = 0; i < amount; i++)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
	free(sprites);
}

int	get_texnum(t_game *game)
{
	if (game->cnt >= 0 && game->cnt < 33)
		return (4);
	if (game->cnt >= 33 && game->cnt < 66)
		return (5);
	if (game->cnt >= 66 && game->cnt < 100)
		return (6);
	return (4);
}

int	 draw_sprite(t_game *game)
{
	int		spriteOrder[game->r.sp_cnt];
	double	spriteDistance[game->r.sp_cnt];
	//SPRITE CASTING
    //sort sprites from far to close
    for(int i = 0; i < game->r.sp_cnt; i++)
    {
		spriteOrder[i] = i;
		spriteDistance[i] = vec_len(vec_sub(game->p.pos, game->sp[i].pos));
	}
    sortSprites(spriteOrder, spriteDistance, game->r.sp_cnt);

    for(int i = 0; i < game->r.sp_cnt; i++)
    {
		t_vec	sprite = vec_sub(game->sp[spriteOrder[i]].pos, game->p.pos);
		double	len = vec_dot(sprite, game->p.dir);
		int		screenx = (int)((WIDTH / 2) * (1 + vec_dot(sprite, vec_norm(game->p.plane)) / len));

		if (vec_dot(vec_norm(sprite), game->p.dir) < vec_dot(game->p.dir, vec_rot(game->p.dir, 60)))
			continue ;
		int spritesize = abs((int)(HEIGHT / len));

		for(int col = -spritesize / 2 + screenx; col < spritesize / 2 + screenx; col++)
		{
			int texX = (int)(256 * (col - (-spritesize / 2 + screenx)) * TEXWIDTH / spritesize) / 256;
        	if (col >= 0 && col < WIDTH && len < game->r.z_buffer[col])
				for (int y = -spritesize / 2 + HEIGHT / 2; y < spritesize / 2 + HEIGHT / 2; y++) //for every pixel of the current stripe
				{
					if (y < 0 || y >= HEIGHT)
						continue ;
					int d = (y) * 256 - HEIGHT * 128 + spritesize * 128; //256 and 128 factors to avoid floats
					int texY = ((d * TEXHEIGHT) / spritesize) / 256;
					int color = game->texture[get_texnum(game)][TEXWIDTH * texY + texX]; //get current color from the texture
						if (color != 0x980088)
						game->img.data[y * WIDTH + col] = color; //paint pixel if it isn't black, black is the invisible color
				}
		}
    }
	return (1);
}