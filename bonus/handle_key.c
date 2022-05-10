/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:37:47 by juahn             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/05/10 02:46:19 by juahn            ###   ########.fr       */
=======
/*   Updated: 2022/05/09 17:55:17 by juahn            ###   ########.fr       */
>>>>>>> 4e81942d7905bbcea4bb9997d3a8e3aecce0134d
/*                                                                            */
/* ************************************************************************** */

#include "../include/game_bonus.h"

int	key_press_exit(t_game *game)
{
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	exit (0);
}

int	user_move(int key, t_game *game)
{
	if (key == K_ESC)
		key_press_exit(game);
	if (key == K_M && game->map_flag == 0)
		game->map_flag = 1;
	else if (key == K_M && game->map_flag == 1)
		game->map_flag = 0;
	else if (key == K_W)
		game->key.w = 1;
	else if (key == K_A)
		game->key.a = 1;
	else if (key == K_S)
		game->key.s = 1;
	else if (key == K_D)
		game->key.d = 1;
	else if (key == K_E)
		cast_ray_and_check_door(game);
	else if (key == K_AR_L)
		game->key.al = 1;
	else if (key == K_AR_R)
		game->key.ar = 1;
	else if (key == K_O)
	{
<<<<<<< HEAD
		game->key.o ^= 1;
		game->key.o_delay = 0;
=======
		game->key.m ^= 1;
		game->key.m_delay = 0;
>>>>>>> 4e81942d7905bbcea4bb9997d3a8e3aecce0134d
	}
	return (0);
}

int	user_stop(int key, t_game *game)
{
	if (key == K_W)
		game->key.w = 0;
	else if (key == K_A)
		game->key.a = 0;
	else if (key == K_S)
		game->key.s = 0;
	else if (key == K_D)
		game->key.d = 0;
	else if (key == K_AR_L)
		game->key.al = 0;
	else if (key == K_AR_R)
		game->key.ar = 0;
	return (0);
}
