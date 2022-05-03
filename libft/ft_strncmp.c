/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:13:12 by juahn             #+#    #+#             */
/*   Updated: 2022/04/14 01:42:31 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	len;

	if (ft_strlen(s1) >= ft_strlen(s2))
		len = ft_strlen(s1);
	if (ft_strlen(s2) > ft_strlen(s1))
		len = ft_strlen(s2);
	if (ft_strlen(s1) == 0 && ft_strlen(s2))
		return (0);
	i = 0;
	while (i < len && i < n)
	{
		if (s1[i] == s2[i])
		{
			i++;
			continue ;
		}
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
