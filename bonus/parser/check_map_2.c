/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 19:23:40 by juahn             #+#    #+#             */
/*   Updated: 2022/05/10 21:22:49 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game_bonus.h"

int	check_door_and_sprite_2(t_game *game, int dr_cnt, int sp_cnt)
{
	int	i;
	int	j;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == '2')
			{
				game->door[dr_cnt].pos = vec_new(j, i);
				game->door[dr_cnt].open_rate = 100.0;
				game->door[dr_cnt].flag = 2;
				dr_cnt++;
			}
			if (game->map[i][j] == '3')
			{
				game->sp[sp_cnt].pos = vec_new(j + 0.5, i + 0.5);
				sp_cnt++;
			}
		}
	}
	return (1);
}

int	check_door_and_sprite(t_game *game, int dr_cnt, int sp_cnt)
{
	int	i;
	int	j;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == '2')
				dr_cnt++;
			if (game->map[i][j] == '3')
				sp_cnt++;
		}
	}
	game->door = (t_door *)malloc(sizeof(t_door) * dr_cnt);
	if (!game->door)
		return (0);
	game->sp = (t_sprite *)malloc(sizeof(t_sprite) * sp_cnt);
	if (!game->sp)
		return (0);
	game->r.dr_cnt = dr_cnt;
	game->r.sp_cnt = sp_cnt;
	check_door_and_sprite_2(game, 0, 0);
	return (1);
}
