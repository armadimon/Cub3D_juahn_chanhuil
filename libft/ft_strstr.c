/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:05:33 by juahn             #+#    #+#             */
/*   Updated: 2022/05/11 23:11:47 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!big)
		return (0);
	if (ft_strlen(big) < ft_strlen(little))
		return (0);
	if (!ft_strlen(little))
		return ((char *)big);
	while (big[i])
	{
		while (little[j] == big[i + j])
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (0);
}
