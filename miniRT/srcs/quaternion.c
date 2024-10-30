/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:37:34 by ecorona-          #+#    #+#             */
/*   Updated: 2024/10/30 13:21:08 by ecorona-         ###   ########.fr       */
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

double	quaternion_smagnitude(t_quaternion q)
{
	return (q.w * q.w + q.i * q.i + q.j * q.j + q.k * q.k);
}

t_quaternion	quaternion_conjugate(t_quaternion q)
{
	return ((t_quaternion){q.w, -q.i, -q.j, -q.k});
}

t_quaternion	quaternion_scalar_product(double a, t_quaternion q)
{
	return ((t_quaternion){a * q.w, a * q.i, a * q.j, a * q.k});
}

t_quaternion	quaternion_inverse(t_quaternion q)
{
	double			a;

	/*a = quaternion_smagnitude(q);*/
	a = q.w * q.w + q.i * q.i + q.j * q.j + q.k * q.k;
	a = 1 / a;
	if (a == 0)
		return ((t_quaternion){0, 0, 0, 0});
	q = (t_quaternion){q.w, -q.i, -q.j, -q.k};
	q = (t_quaternion){a * q.w, a * q.i, a * q.j, a * q.k};
	return (q);
	/*return (quaternion_scalar_product(1 / a, quaternion_conjugate(q)));*/
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
	double			a;
	t_vector		u;
	t_vector		v;
	t_vector		uv;

	u = (t_vector){q.i, q.j, q.k};
	v = (t_vector){p.i, p.j, p.k};
	uv = vector_cross_product(u, v);
	/*a = (q.w * p.w) - vector_dot_product(u, v);*/
	a = (q.w * p.w) - (u.x * v.x + u.y * v.y + u.z * v.z);
	/*u = vector_scalar_product(p.w, u);*/
	u = (t_vector){p.w * u.x, p.w * u.y, p.w * u.z};
	/*v = vector_scalar_product(q.w, v);*/
	v = (t_vector){q.w * v.x, q.w * v.y, q.w * v.z};
	/*uv = vector_add(vector_add(uv, u), v);*/
	uv = (t_vector){u.x + uv.x, u.y + uv.y, u.z + uv.z};
	uv = (t_vector){v.x + uv.x, v.y + uv.y, v.z + uv.z};
	return ((t_quaternion){a, uv.x, uv.y, uv.z});
}
