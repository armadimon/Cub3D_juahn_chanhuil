/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcho <hcho@42seoul.student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 16:58:18 by juahn             #+#    #+#             */
/*   Updated: 2022/04/14 17:59:26 by hcho             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_atoi(const char *str)
{
	long long	num;
	int			sign;

	num = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (num * sign >= LLONG_MAX / 10
			|| num * sign < LLONG_MIN / 10)
			return (255);
		else if (sign == -1 && num == LLONG_MAX / 10 && *str == '8')
			return (0);
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (sign * num);
}
