/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:10:00 by ecorona-          #+#    #+#             */
/*   Updated: 2024/12/03 20:10:06 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"

double	vec_dot_prod(t_vec u, t_vec v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

double	vec_magnitude(t_vec u)
{
	return (sqrtf(u.x * u.x + u.y * u.y + u.z * u.z));
}

double	vec_distance(t_vec u, t_vec v)
{
	t_vec	a;

	a = (t_vec){u.x - v.x, u.y - v.y, u.z - v.z};
	return (sqrtf(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vec	vec_normalize(t_vec u)
{
	t_vec	nil;
	double	imag;
	int		res;

	nil = (t_vec){0, 0, 0};
	res = 1;
	res = res && (((u.x - nil.x) < EPSILON) && ((u.x - nil.x) > -EPSILON));
	res = res && (((u.y - nil.y) < EPSILON) && ((u.y - nil.y) > -EPSILON));
	res = res && (((u.z - nil.z) < EPSILON) && ((u.z - nil.z) > -EPSILON));
	if (res)
		return ((t_vec){0, 0, 0});
	imag = 1 / sqrtf(u.x * u.x + u.y * u.y + u.z * u.z);
	return ((t_vec){imag * u.x, imag * u.y, imag * u.z});
}

t_vec	vec_cross_prod(t_vec u, t_vec v)
{
	return ((t_vec){u.y * v.z - u.z * v.y, \
		u.z * v.x - u.x * v.z, \
		u.x * v.y - u.y * v.x});
}
