/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:32:51 by ecorona-          #+#    #+#             */
/*   Updated: 2024/12/03 20:10:29 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"

int	vec_equals(t_vec u, t_vec v)
{
	int		result;

	result = 1;
	result = result && (((u.x - v.x) < EPSILON) && ((u.x - v.x) > -EPSILON));
	result = result && (((u.y - v.y) < EPSILON) && ((u.y - v.y) > -EPSILON));
	result = result && (((u.z - v.z) < EPSILON) && ((u.z - v.z) > -EPSILON));
	return (result);
}

t_vec	vec_elem_prod(t_vec v, t_vec u)
{
	return ((t_vec){v.x * u.x, v.y * u.y, v.z * u.z});
}

t_vec	vec_scalar_prod(double a, t_vec u)
{
	return ((t_vec){a * u.x, a * u.y, a * u.z});
}

t_vec	vec_add(t_vec u, t_vec v)
{
	return ((t_vec){u.x + v.x, u.y + v.y, u.z + v.z});
}

t_vec	vec_subtract(t_vec u, t_vec v)
{
	return ((t_vec){u.x - v.x, u.y - v.y, u.z - v.z});
}
