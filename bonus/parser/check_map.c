/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 19:23:40 by juahn             #+#    #+#             */
/*   Updated: 2022/05/10 12:21:20 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game_bonus.h"

t_vec	get_direction(char c)
{
	if (c == 'N')
		return (vec_new(0, -1));
	else if (c == 'S')
		return (vec_new(0, 1));
	else if (c == 'E')
		return (vec_new(1, 0));
	else if (c == 'W')
		return (vec_new(-1, 0));
	return (vec_new(0, 0));
}

int	check_space(t_game *game, int i, int j)
{
	if (i == 0 || j == 0 || !game->map[i + 1] || !game->map[i][j + 1])
		return (0);
	if (game->map[i][j - 1] == ' ' || game->map[i][j + 1] == ' ')
		return (0);
	if ((int)ft_strlen(game->map[i - 1]) <= j || game->map[i - 1][j] == ' ')
		return (0);
	if ((int)ft_strlen(game->map[i + 1]) <= j || game->map[i + 1][j] == ' ')
		return (0);
	return (1);
}

int	check_char(char c)
{
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W'
		&& c != ' ' && c != '0' && c != '1' && c!= '2')
		return (0);
	return (1);
}

int	check_map_2(t_game *game, int i, int j, int *isinited)
{
	while (game->map[i][++j])
	{
		if (!check_char(game->map[i][j]))
			return (0);
		if (game->map[i][j] == '0' && !check_space(game, i, j))
			return (0);
		if (game->map[i][j] == 'N' || game->map[i][j] == 'S' ||
			game->map[i][j] == 'E' || game->map[i][j] == 'W')
		{
			if (*isinited)
				return (0);
			game->p.dir = get_direction(game->map[i][j]);
			game->map[i][j] = '0';
			*isinited = 1;
		}
		else
			continue ;
		game->p.pos = vec_new(j + 0.5, i + 0.5);
	}
	return (1);
}

int	check_door_and_sprite(t_game *game)
{
	int i;
	int j;
	int	sp_cnt;
	int	dr_cnt;

	i = -1;
	sp_cnt = 0;
	dr_cnt = 0;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == '2')
				dr_cnt++;
			if (game->map[i][j] == 'P')
				sp_cnt++;
		}
	}
	game->door = malloc(sizeof(t_door) * dr_cnt);
	game->dr_cnt = dr_cnt;
	i = -1;
	sp_cnt = 0;
	dr_cnt = 0;
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
			if (game->map[i][j] == 'P')
				sp_cnt++;
		}
	}
	return (1);
}

int	check_map(t_game *game)
{
	int	i;
	int	isinited;

	isinited = 0;
	if (!check_door_and_sprite(game))
		return (0);
	i = -1;
	while (game->map[++i])
	{
		if (!check_map_2(game, i, -1, &isinited))
			return (0);
	}
	if (game->p.pos.x < 0 || game->p.pos.y < 0)
		return (0);
	game->screen_height = game->map_height * TILE_SIZE;
	game->screen_width = game->map_width * TILE_SIZE;
	game->p.plane = vec_rot(game->p.dir, -90);
	return (1);
}
