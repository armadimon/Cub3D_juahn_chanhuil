/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:24:30 by juahn             #+#    #+#             */
/*   Updated: 2022/05/09 16:54:15 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game_bonus.h"

void	cast_ray_and_check_door(t_game *game)
{
	t_vec	ray;
	// int		map_x;
			ray = vec_add(game->p.dir, vec_mul(game->p.plane, 2 * (WIDTH / 2)
					/ (double)(WIDTH) - 1));
	// if (ray.x > 0)
		// game->map;
	// return (0);
}