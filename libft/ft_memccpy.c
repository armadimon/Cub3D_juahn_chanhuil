/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 17:32:39 by juahn             #+#    #+#             */
/*   Updated: 2021/05/05 17:32:43 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*casted_dest;
	unsigned const char	*casted_src;

	if (dst == 0 && src == 0)
		return (0);
	casted_dest = dst;
	casted_src = src;
	while (n-- > 0)
	{
		if (*casted_src == (unsigned char)c)
		{
			*casted_dest = *casted_src;
			return (++casted_dest);
		}
		*casted_dest = *casted_src;
		casted_dest++;
		casted_src++;
	}
	return (0);
}
