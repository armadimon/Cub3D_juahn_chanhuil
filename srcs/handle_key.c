/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:37:47 by juahn             #+#    #+#             */
/*   Updated: 2022/05/06 18:16:54 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

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
		game->key.W = 1;
	else if (key == K_A)
		game->key.A = 1;
	else if (key == K_S)
		game->key.S = 1;
	else if (key == K_D)
		game->key.D = 1;
	else if (key == K_AR_L)
		game->key.AL = 1;
	else if (key == K_AR_R)
		game->key.AR = 1;
	return (0);
}

int	user_stop(int key, t_game *game)
{
	if (key == K_W)
		game->key.W = 0;
	else if (key == K_A)
		game->key.A = 0;
	else if (key == K_S)
		game->key.S = 0;
	else if (key == K_D)
		game->key.D = 0;
	else if (key == K_AR_L)
		game->key.AL = 0;
	else if (key == K_AR_R)
		game->key.AR = 0;
	return (0);
}
