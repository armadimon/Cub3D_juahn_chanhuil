/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_F_C_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:24:12 by juahn             #+#    #+#             */
/*   Updated: 2022/05/06 15:24:13 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"

int	check_valid_color(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (!ft_isdigit(buf[i]))
			return (0);
		i++;
	}
	return (1);
}

int	set_F_C_color(t_game *game, char *str, int flag)
{
	char	**buf;
	int		i;

	i = 0;
	buf = ft_split(str, ',');
	while (buf[i])
	{
		if (!check_valid_color(buf[i]) || i > 2)
			return (0);
		if (i == 0 && flag == 0)
			game->map_data.F_red = ft_atoi(buf[i]);
		else if (i == 1 && flag == 0)
			game->map_data.F_green = ft_atoi(buf[i]);
		else if (i == 2 && flag == 0)
			game->map_data.F_blue = ft_atoi(buf[i]);
		if (i == 0 && flag == 1)
			game->map_data.C_red = ft_atoi(buf[i]);
		else if (i == 1 && flag == 1)
			game->map_data.C_green = ft_atoi(buf[i]);
		else if (i == 2 && flag == 1)
			game->map_data.C_blue = ft_atoi(buf[i]);
		i++;
	}
	return (1);
}
