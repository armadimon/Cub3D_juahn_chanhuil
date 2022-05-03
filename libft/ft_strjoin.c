/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:22:22 by juahn             #+#    #+#             */
/*   Updated: 2022/03/30 03:41:32 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		index;

	if (!s1 || !s2)
		return (NULL);
	result = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (result)
	{
		index = 0;
		while (*s1)
		{
			result[index++] = *s1;
			s1++;
		}
		while (*s2)
		{
			result[index++] = *s2;
			s2++;
		}
		result[index] = '\0';
	}
	return (result);
}
