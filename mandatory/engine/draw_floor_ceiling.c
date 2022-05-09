/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceiling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 18:09:29 by juahn             #+#    #+#             */
/*   Updated: 2022/05/07 11:26:08 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"

int	fill_floor_color(t_game *game)
{
	int	color;

	color = 0x010000 * game->map_data.f_red;
	color += 0x000100 * game->map_data.f_green;
	color += 0x000001 * game->map_data.f_blue;
	return (color);
}

int	fill_ceiling_color(t_game *game)
{
	int	color;

	color = 0x010000 * game->map_data.c_red;
	color += 0x000100 * game->map_data.c_green;
	color += 0x000001 * game->map_data.c_blue;
	return (color);
}
