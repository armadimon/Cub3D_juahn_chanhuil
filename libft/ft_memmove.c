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

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*temp;
	unsigned const char	*casted_src;

	if (dst == 0 && src == 0)
		return (0);
	temp = dst;
	casted_src = src;
	if (dst <= src)
	{
		while (n-- > 0)
			*temp++ = *casted_src++;
	}
	else
	{
		temp += n;
		casted_src += n;
		while (n-- > 0)
			*--temp = *--casted_src;
	}
	return (dst);
}
