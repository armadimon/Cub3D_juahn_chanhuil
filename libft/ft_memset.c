/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:18:48 by juahn             #+#    #+#             */
/*   Updated: 2021/05/05 15:07:52 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			index;
	unsigned char	*ori_ptr;

	index = 0;
	ori_ptr = (unsigned char *)b;
	while (index < len)
	{
		*(unsigned char *)b = (unsigned char)c;
		b++;
		index++;
	}
	return (ori_ptr);
}
