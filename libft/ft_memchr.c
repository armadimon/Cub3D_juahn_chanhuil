/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 17:32:39 by juahn             #+#    #+#             */
/*   Updated: 2021/05/05 17:32:43 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		*casted_s;
	size_t				index;

	casted_s = (unsigned char *)s;
	index = 0;
	while (index++ < n)
	{
		if (*casted_s == (unsigned char)c)
			return (casted_s);
		casted_s++;
	}
	return (0);
}
