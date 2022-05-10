/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhuil <chanhuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:23:21 by chanhuil          #+#    #+#             */
/*   Updated: 2022/05/04 16:00:24 by chanhuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vector.h"

double	vec_angle(t_vec v)
{
	if (-vec_norm(v).y < 0)
		return (-acos(vec_norm(v).x));
	return (acos(vec_norm(v).x));
}

t_vec	vec_rot(t_vec v, int degree)
{
	return (vec_new(cos(vec_angle(v) + (PI / 180 * degree)) * vec_len(v),
			-sin(vec_angle(v) + (PI / 180 * degree)) * vec_len(v)));
}

t_vec	vec_mrot(t_vec v, int degree)
{
	return (vec_new(cos(vec_angle(v) + (PI / 1800 * degree)) * vec_len(v),
			-sin(vec_angle(v) + (PI / 1800 * degree)) * vec_len(v)));
}

void	vec_print(t_vec v)
{
	printf("(%f, %f)\n", v.x, v.y);
}
