/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhuil <chanhuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 19:29:14 by juahn             #+#    #+#             */
/*   Updated: 2022/05/12 09:50:28 by chanhuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game_bonus.h"

void	sort_sprites(t_game *game)
{
	int			i;
	int			sorted;
	t_sprite	temp;

	i = -1;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		while (++i < game->r.sp_cnt - 1)
		{
			if (vec_len(vec_sub(game->sp[i].pos, game->p.pos))
				< vec_len(vec_sub(game->sp[i + 1].pos, game->p.pos)))
			{
				temp = game->sp[i];
				game->sp[i] = game->sp[i + 1];
				game->sp[i + 1] = temp;
				sorted = 0;
			}
		}
	}
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

void	render_sprite(t_game *game, double len, int sp_x, int size)
{
	int	tex_x;
	int	tex_y;
	int	i;
	int	j;

	size = (int)(HEIGHT / len);
	i = -size / 2 + sp_x - 1;
	while (++i < size / 2 + sp_x)
	{
		if (i < 0 || i >= WIDTH || len >= game->r.z_buffer[i])
			continue ;
		tex_x = (int)(256 * (i - (-size / 2 + sp_x)) * TEXWIDTH / size) / 256;
		j = -size / 2 + HEIGHT / 2 - 1;
		while (++j < size / 2 + HEIGHT / 2)
		{
			if (j < 0 || j >= HEIGHT)
				continue ;
			tex_y = ((int)(j * 256 - HEIGHT * 128 + size * 128))
				* TEXHEIGHT / size / 256;
			if (game->texture[get_texnum(game)]
				[TEXWIDTH * tex_y + tex_x] != 0x980088)
				game->img.data[j * WIDTH + i]
					= game->texture[get_texnum(game)][TEXWIDTH * tex_y + tex_x];
		}
	}
}

int	draw_sprite(t_game *game)
{
	int		i;
	t_vec	sprite;
	double	len;
	int		sp_x;

	sort_sprites(game);
	i = -1;
	while (++i < game->r.sp_cnt)
	{
		sprite = vec_sub(game->sp[i].pos, game->p.pos);
		len = vec_dot(sprite, game->p.dir);
		sp_x = (int)((WIDTH / 2) * (1 + vec_dot(sprite,
						vec_norm(game->p.plane)) / len));
		if (vec_dot(vec_norm(sprite), game->p.dir)
			< vec_dot(game->p.dir, vec_rot(game->p.dir, 60)))
			continue ;
		render_sprite(game, len, sp_x, 0);
	}
	return (1);
}
