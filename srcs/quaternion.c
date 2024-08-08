/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:37:34 by ecorona-          #+#    #+#             */
/*   Updated: 2024/08/08 14:43:44 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"

// Quaternion
// | quaternion Q := w + ai + bj + ck = {w,a,b,c}
// |   where
// |     w,a,b,c := real numbers
// |     i,j,k   := basis elements
// |       then
// |         w       := scalar part of Q
// |         {a,b,c} := vector part of Q

float	quaternion_smagnitude(t_quaternion q)
{
	return (q.w * q.w + q.i * q.i + q.j * q.j + q.k * q.k);
}

t_quaternion	quaternion_conjugate(t_quaternion q)
{
	return ((t_quaternion){q.w, -q.i, -q.j, -q.k});
}

t_quaternion	quaternion_scalar_product(float a, t_quaternion q)
{
	return ((t_quaternion){a * q.w, a * q.i, a * q.j, a * q.k});
}

t_quaternion	quaternion_inverse(t_quaternion q)
{
	float	aux;

	aux = quaternion_smagnitude(q);
	if (aux == 0)
		return ((t_quaternion){0, 0, 0, 0});
	return (quaternion_scalar_product(1 / aux, quaternion_conjugate(q)));
}

// Quaternion Product
// | quaternion q = a + u
// | quaternion p = b + v
// |   where
// |     a,b := scalar parts of q and p
// |     u,v := vector parts of q and p
// |       then
// |         qp = (ab) + (uv) = (a*b - u.v) + (a*v + b*v + uxv)
t_quaternion	quaternion_product(t_quaternion q, t_quaternion p)
{
	float			a;
	t_vector		u;
	t_vector		v;
	t_vector		uv;

	u = (t_vector){q.i, q.j, q.k};
	v = (t_vector){p.i, p.j, p.k};
	uv = vector_cross_product(u, v);
	a = (q.w * p.w) - vector_dot_product(u, v);
	u = vector_scalar_product(p.w, u);
	v = vector_scalar_product(q.w, v);
	uv = vector_add(vector_add(uv, u), v);
	return ((t_quaternion){a, uv.x, uv.y, uv.z});
}
