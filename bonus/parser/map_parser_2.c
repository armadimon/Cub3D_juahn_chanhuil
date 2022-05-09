/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 20:08:55 by juahn             #+#    #+#             */
/*   Updated: 2022/05/09 14:00:47 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game_bonus.h"

int	check_map_contents(t_game *game, t_valid *valid)
{
	if (valid->valid_ea == 0 || valid->valid_no == 0
		|| valid->valid_so == 0 || valid->valid_we == 0)
		return (0);
	if (game->map_data.c_red < 0 || game->map_data.c_red > 255)
		return (0);
	if (game->map_data.c_green < 0 || game->map_data.c_green > 255)
		return (0);
	if (game->map_data.c_blue < 0 || game->map_data.c_blue > 255)
		return (0);
	if (game->map_data.f_red < 0 || game->map_data.f_red > 255)
		return (0);
	if (game->map_data.f_green < 0 || game->map_data.f_green > 255)
		return (0);
	if (game->map_data.f_blue < 0 || game->map_data.f_blue > 255)
		return (0);
	return (1);
}

int	parse_map(t_game *game, t_list *map_list)
{
	t_list	*temp;
	t_valid	valid;
	char	**buf;
	int		ret;

	ret = 1;
	temp = map_list;
	init_valid(&valid);
	while (temp && ret)
	{
		if (temp->content == NULL)
			temp = temp->next;
		if (check_map_contents(game, &valid))
			return (get_map_arr(game, temp));
		buf = ft_split((char *)temp->content, ' ');
		if (buf)
			ret = get_map_contents(game, buf, &valid);
		free_strs(buf);
		temp = temp->next;
	}
	if (!ret || !check_map_contents(game, &valid) || !game->map)
		return (0);
	return (1);
}
