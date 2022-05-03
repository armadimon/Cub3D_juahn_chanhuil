/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:24:53 by juahn             #+#    #+#             */
/*   Updated: 2021/04/14 17:27:41 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**count_str_nb(const char *str, char c)
{
	int		cnt;
	int		i;
	char	**strs;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			cnt++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	strs = (char **)ft_calloc(cnt + 1, sizeof(char *));
	if (!strs)
		return (NULL);
	return (strs);
}

static void	ft_strcpy_for_split(char *dst, const char *from, const char *until)
{
	while (from < until)
		*(dst++) = *(from++);
	*dst = 0;
}

static void	ft_free_strs(char **strs, size_t index)
{
	size_t	i;

	i = 0;
	while (i < index)
		free(strs[i++]);
	free(strs);
}

static char	**ft_alloc_str(char const *str, char **strs, char c)
{
	long long	i;
	const char	*ori;

	i = 0;
	while (*str)
	{
		if (!(*str == c))
		{
			ori = str;
			while (*str && *str != c)
				str++;
			strs[i] = (char *)ft_calloc(str - ori + 1, sizeof(char));
			if (!strs[i])
				ft_free_strs(strs, i);
			ft_strcpy_for_split(strs[i++], ori, str);
		}
		else
			str++;
	}
	return (strs);
}

char	**ft_split(char const *str, char c)
{
	char	**strs;

	if (!str)
		return (0);
	strs = count_str_nb(str, c);
	if (!strs)
		return (0);
	strs = ft_alloc_str(str, strs, c);
	if (!strs)
		return (0);
	return (strs);
}
