/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:05:33 by juahn             #+#    #+#             */
/*   Updated: 2022/04/14 01:43:19 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	s_len;

	s_len = ft_strlen((char *)s);
	s += s_len;
	while (s_len-- >= 0)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s--;
	}
	return (0);
}
