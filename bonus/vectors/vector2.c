/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:23:21 by chanhuil          #+#    #+#             */
/*   Updated: 2022/05/04 15:11:50 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vector.h"

t_vec	vec_norm(t_vec v)
{
	return (vec_mul(v, 1 / vec_len(v)));
}

double	vec_len(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

double	vec_dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

int	vec_equal(t_vec v1, t_vec v2)
{
	if (v1.x == v2.x && v1.y == v2.y)
		return (1);
	return (0);
}
