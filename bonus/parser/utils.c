/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:33:36 by juahn             #+#    #+#             */
/*   Updated: 2022/05/09 14:00:47 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game_bonus.h"

void	free_strs(char **strs)
{
	int	i;

	i = -1;
	if (strs)
	{
		while (strs[++i])
			free(strs[i]);
		free(strs);
	}
}
