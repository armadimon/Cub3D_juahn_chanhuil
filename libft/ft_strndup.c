/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:08:53 by juahn             #+#    #+#             */
/*   Updated: 2022/04/14 01:36:46 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *src, size_t n)
{
	char			*dest;
	unsigned int	src_len;
	unsigned int	i;

	i = 0;
	src_len = ft_strlen(src);
	if (src_len < n)
		n = src_len;
	dest = (char *)malloc(n + 1);
	if (!dest)
		return (0);
	if (dest)
	{
		while (i < n)
		{
			dest[i] = src[i];
			i++;
		}
	}
	dest[i] = '\0';
	return (dest);
}
