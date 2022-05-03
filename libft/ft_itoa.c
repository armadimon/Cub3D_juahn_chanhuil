/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 16:58:18 by juahn             #+#    #+#             */
/*   Updated: 2022/04/14 01:34:30 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*ft_itoa_pos(int n)
{
	int		cnt;
	int		ori;
	char	*str;

	cnt = 1;
	ori = n;
	while (n >= 10)
	{
		n = n / 10;
		cnt++;
	}
	str = (char *)malloc(cnt + 1);
	if (!str)
		return (0);
	str += cnt;
	*(str--) = 0;
	while (ori)
	{
		*str = ori % 10 + '0';
		ori /= 10;
		str--;
	}
	str++;
	return (str);
}

static char	*ft_itoa_neg(int n)
{
	int		cnt;
	int		ori;
	char	*str;

	cnt = 1;
	ori = n;
	while (n <= -10)
	{
		n = n / 10;
		cnt++;
	}
	cnt++;
	str = (char *)malloc(cnt + 1);
	if (!str)
		return (0);
	*str = '-';
	str += cnt;
	*(str--) = 0;
	while (ori)
	{
		*str = -(ori % 10) + '0';
		ori /= 10;
		str--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;

	if (n < 0)
		str = ft_itoa_neg(n);
	else if (n > 0)
		str = ft_itoa_pos(n);
	else
	{
		str = (char *)malloc(2);
		if (!str)
			return (0);
		*(str++) = '0';
		*(str--) = 0;
		return (str);
	}
	return (str);
}
