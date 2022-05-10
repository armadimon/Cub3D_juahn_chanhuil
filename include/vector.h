/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:23:36 by chanhuil          #+#    #+#             */
/*   Updated: 2022/05/09 16:45:50 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdio.h>
# include <math.h>

# define PI 3.14159265358979323846

typedef struct t_vec
{
	double	x;
	double	y;
}			t_vec;

t_vec	vec_new(double x, double y);
t_vec	vec_zero(void);
t_vec	vec_add(t_vec v1, t_vec v2);
t_vec	vec_sub(t_vec v1, t_vec v2);
t_vec	vec_mul(t_vec v, double n);
t_vec	vec_norm(t_vec v);
double	vec_len(t_vec v);
double	vec_dot(t_vec v1, t_vec v2);
int		vec_equal(t_vec v1, t_vec v2);

double	vec_angle(t_vec v);
t_vec	vec_rot(t_vec v, int degree);
t_vec	vec_mrot(t_vec v, int degree);

void	vec_print(t_vec v);

#endif