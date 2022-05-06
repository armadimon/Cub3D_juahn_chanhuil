/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:13:12 by juahn             #+#    #+#             */
/*   Updated: 2022/05/06 15:01:00 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	len_s1;
	int	len_s2;
	int	i;

	i = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (len_s1 != len_s2)
		return (0);
	while (i < len_s2)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}
