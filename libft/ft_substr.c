/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:22:22 by juahn             #+#    #+#             */
/*   Updated: 2022/04/14 01:43:01 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;

	if (!s || start < 0)
		return (0);
	if (len >= ft_strlen(s))
		len = ft_strlen(s);
	sub_str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!sub_str)
		return (0);
	if (ft_strlen(s) < start)
		return (sub_str);
	while (start--)
		s++;
	ft_strlcpy(sub_str, s, len + 1);
	return (sub_str);
}
