/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:20:35 by juahn             #+#    #+#             */
/*   Updated: 2022/04/14 02:10:02 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (!ft_strlen(little))
		return ((char *)big);
	if (ft_strlen(big) < len)
		len = ft_strlen(big);
	while (i < len)
	{
		j = 0;
		while ((little[j] == big[i + j]) && i + j < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (0);
}
