/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceiling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 18:09:29 by juahn             #+#    #+#             */
/*   Updated: 2022/05/06 18:16:03 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game.h"

int	fill_floor_color(t_game *game)
{
	int	color;

	color = 0x010000 * game->map_data.F_red;
	color += 0x000100 * game->map_data.F_green;
	color += 0x000001 * game->map_data.F_blue;
	return (color);
}

int	fill_ceiling_color(t_game *game)
{
	int	color;

	color = 0x010000 * game->map_data.C_red;
	color += 0x000100 * game->map_data.C_green;
	color += 0x000001 * game->map_data.C_blue;
	return (color);
}
