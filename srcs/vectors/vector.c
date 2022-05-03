/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhuil <chanhuil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:23:21 by chanhuil          #+#    #+#             */
/*   Updated: 2022/05/03 16:58:19 by chanhuil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec	vec_new(double x, double y)
{
	t_vec	v;

	v.x = x;
	v.y = y;
	return (v);
}

t_vec	vec_zero(void)
{
	t_vec	v;

	v.x = 0;
	v.y = 0;
	return (v);
}

t_vec	vec_add(t_vec v1, t_vec v2)
{
	return (vec_new(v1.x + v2.x, v1.y + v2.y));
}

t_vec	vec_sub(t_vec v1, t_vec v2)
{
	return (vec_new(v1.x - v2.x, v1.y - v2.y));
}

t_vec	vec_mul(t_vec v, double n)
{
	return (vec_new(v.x * n, v.y * n));
}
