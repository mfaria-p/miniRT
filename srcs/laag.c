/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   laag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:32:51 by ecorona-          #+#    #+#             */
/*   Updated: 2024/08/07 17:13:22 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"

#define VECTOR_NIL (t_vector){0, 0, 0}

int	vector_equals(t_vector u, t_vector v)
{
	return (u.x == v.x && u.y == v.y && u.z == v.z);
}

t_vector	vector_scalar_product(float n, t_vector u)
{
	return ((t_vector){n * u.x, n * u.y, n * u.z});
}

t_vector	vector_add(t_vector u, t_vector v)
{
	return ((t_vector){u.x + v.x, u.y + v.y, u.z + v.z});
}

t_vector	vector_subtract(t_vector u, t_vector v)
{
	return (vector_add(u, vector_scalar_product(-1, v)));
}

float	vector_dot_product(t_vector u, t_vector v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

float	vector_magnitude(t_vector u)
{
	return (sqrt(fabs(vector_dot_product(u,u))));
}

float	vector_distance(t_vector u, t_vector v)
{
	return (vector_magnitude(vector_subtract(u, v)));
}

t_vector	vector_normalize(t_vector u)
{
	if (vector_equals(u, VECTOR_NIL))
		return (VECTOR_NIL);
	return (vector_scalar_product(1 / vector_magnitude(u), u));
}
