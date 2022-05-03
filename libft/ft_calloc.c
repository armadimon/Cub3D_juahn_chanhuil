/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:48:53 by juahn             #+#    #+#             */
/*   Updated: 2022/04/14 01:36:21 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	void	*ori_ptr;
	void	*ptr;

	ptr = (void *)malloc(number * size);
	if (!ptr)
		return (0);
	ori_ptr = ptr;
	ft_bzero(ptr, number * size);
	return (ori_ptr);
}
