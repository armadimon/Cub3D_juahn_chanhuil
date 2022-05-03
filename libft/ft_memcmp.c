/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 17:32:39 by juahn             #+#    #+#             */
/*   Updated: 2022/04/14 02:11:12 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char		*casted_s1;
	unsigned char		*casted_s2;
	size_t				index;

	casted_s1 = (unsigned char *)s1;
	casted_s2 = (unsigned char *)s2;
	index = 0;
	while (index++ < n)
	{
		if (*casted_s1 != *casted_s2)
			return (*casted_s1 - *casted_s2);
		casted_s1++;
		casted_s2++;
	}
	return (0);
}
