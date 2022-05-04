/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:23:21 by chanhuil          #+#    #+#             */
/*   Updated: 2022/05/04 15:11:46 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vector.h"

double	facos(t_vec v)
{
	if (-vec_norm(v).y < 0)
		return (-acos(vec_norm(v).x));
	return (acos(vec_norm(v).x));
}

double	fasin(t_vec v)
{
	if (vec_norm(v).x < 0)
		return (PI - asin(-vec_norm(v).y));
	return (asin(-vec_norm(v).y));
}

t_vec	vec_rot(t_vec v, int degree)
{
	return (vec_new(cos(facos(v) + (PI / 180 * degree)) * vec_len(v),
			-sin(fasin(v) + (PI / 180 * degree)) * vec_len(v)));
}

void	vec_print(t_vec v)
{
	printf("(%f, %f)\n", v.x, v.y);
}
