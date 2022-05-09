/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:22:21 by juahn             #+#    #+#             */
/*   Updated: 2022/05/07 11:26:08 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"

int	check_id(t_valid *valid, char *str)
{
	if (ft_strstr(str, "NO") && valid->valid_no == 0)
		valid->valid_no = 1;
	else if (ft_strstr(str, "SO") && valid->valid_so == 0)
		valid->valid_so = 1;
	else if (ft_strstr(str, "WE") && valid->valid_we == 0)
		valid->valid_we = 1;
	else if (ft_strstr(str, "EA") && valid->valid_ea == 0)
		valid->valid_ea = 1;
	else if (ft_strstr(str, "F") && valid->valid_f == 0)
		valid->valid_f = 1;
	else if (ft_strstr(str, "C") && valid->valid_c == 0)
		valid->valid_c = 1;
	else
		return (0);
	return (1);
}

int	check_id_rule(char **buf)
{
	int	i;

	i = 0;
	while (buf[i])
		i++;
	if (i == 2)
		return (1);
	return (0);
}

int	is_color_id(char **buf)
{
	if (ft_strstr(buf[0], "F") && ft_strcmp(buf[0], "F")
		&& check_id_rule(buf))
		return (1);
	if (ft_strstr(buf[0], "C") && ft_strcmp(buf[0], "C")
		&& check_id_rule(buf))
		return (2);
	return (0);
}

int	get_map_contents(t_game *game, char **buf, t_valid *valid)
{
	t_img	img;
	int		ret;

	ret = 0;
	if (!check_id(valid, buf[0]))
		return (ret);
	if (ft_strstr(buf[0], "NO") && ft_strcmp(buf[0], "NO")
		&& check_id_rule(buf))
		ret = load_image(game, game->texture[0], buf[1], &img);
	else if (ft_strstr(buf[0], "SO") && ft_strcmp(buf[0], "SO")
		&& check_id_rule(buf))
		ret = load_image(game, game->texture[1], buf[1], &img);
	else if (ft_strstr(buf[0], "WE") && ft_strcmp(buf[0], "WE")
		&& check_id_rule(buf))
		ret = load_image(game, game->texture[2], buf[1], &img);
	else if (ft_strstr(buf[0], "EA") && ft_strcmp(buf[0], "EA")
		&& check_id_rule(buf))
		ret = load_image(game, game->texture[3], buf[1], &img);
	else if (is_color_id(buf) == 1)
		ret = set_f_c_color(game, buf[1], 0);
	else if (is_color_id(buf) == 2)
		ret = set_f_c_color(game, buf[1], 1);
	else
		return (0);
	return (ret);
}
