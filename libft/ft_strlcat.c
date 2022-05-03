/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:05:33 by juahn             #+#    #+#             */
/*   Updated: 2021/04/05 14:11:56 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char const *src, size_t size)
{
	size_t	i;
	size_t	tem_i;

	i = 0;
	tem_i = 0;
	while (dest[i] && i < size)
		i++;
	while (src[tem_i] && (i + tem_i + 1) < size)
	{
		dest[i + tem_i] = src[tem_i];
		tem_i++;
	}
	if (i < size)
		dest[i + tem_i] = '\0';
	return (i + ft_strlen(src));
}
