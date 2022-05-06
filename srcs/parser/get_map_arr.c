/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:05:41 by juahn             #+#    #+#             */
/*   Updated: 2022/05/06 15:06:08 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"

int	cpy_map_2(t_game *game, t_list *map_list, int row, int col)
{
	int		i;
	int		j;
	char	*buf;

	i = -1;
	while (++i < row)
	{
		j = -1;
		buf = map_list->content;
		if (!buf)
			return (0);
		while ((++j < col) && buf[j])
			game->map[i][j] = buf[j];
		map_list = map_list->next;
	}
	return (1);
}

int	cpy_map(t_game *game, t_list *map_list, int row, int col)
{
	int	i;
	int	j;

	i = 0;
	while (i < row)
	{
		j = -1;
		game->map[i] = (char *)malloc(sizeof(char) * col + 1);
		if (!game->map[i])
			return (0);
		while (++j < col)
			game->map[i][j] = ' ';
		game->map[i][j] = '\0';
		i++;
	}
	game->map[i] = NULL;
	if (!cpy_map_2(game, map_list, row, col))
		return (0);
	return (1);
}

int	get_map_arr(t_game *game, t_list *map_list)
{
	t_list	*temp;
	int		row;
	int		col;

	temp = map_list;
	row = 0;
	col = 0;
	while (temp)
	{
		row++;
		if (col < (int)ft_strlen((char *)temp->content))
			col = ft_strlen((char *)temp->content);
		temp = temp->next;
	}
	game->map_width = col;
	game->map_height = row;
	game->map = (char **)malloc(sizeof(char *) * (row + 1));
	cpy_map(game, map_list, row, col);
	return (1);
}
