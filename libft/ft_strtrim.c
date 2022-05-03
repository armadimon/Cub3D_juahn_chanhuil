/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 19:59:34 by juahn             #+#    #+#             */
/*   Updated: 2022/05/03 16:00:14 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;
	unsigned int	set_len;
	char			*temp;

	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1);
	set_len = ft_strlen(set);
	while (s1[start] && ft_memchr(set, s1[start], set_len))
		start++;
	if (start == end)
		return ((char *)ft_calloc(1, 1));
	while (s1[end - 1] && ft_memchr(set, s1[end - 1], set_len))
		end--;
	temp = (char *)malloc(end - start + 1);
	if (!temp)
		return (0);
	ft_strlcpy(temp, s1 + start, end - start + 1);
	return (temp);
}
