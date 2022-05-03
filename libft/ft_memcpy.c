/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 17:32:39 by juahn             #+#    #+#             */
/*   Updated: 2021/05/17 15:27:25 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*casted_dest;
	unsigned const char	*casted_src;

	casted_dest = dest;
	casted_src = src;
	if (casted_dest == 0 && casted_src == 0)
		return (0);
	while (n-- > 0)
	{
		*casted_dest = *casted_src;
		casted_dest++;
		casted_src++;
	}
	return (dest);
}
