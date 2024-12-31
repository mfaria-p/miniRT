/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:37:34 by ecorona-          #+#    #+#             */
/*   Updated: 2024/12/03 19:28:43 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"

// Quaternion
// | quat Q := w + ai + bj + ck = {w,a,b,c}
// |   where
// |     w,a,b,c := real numbers
// |     i,j,k   := basis elements
// |       then
// |         w       := scalar part of Q
// |         {a,b,c} := vec part of Q

double	quat_smagnitude(t_quat q)
{
	return (q.w * q.w + q.i * q.i + q.j * q.j + q.k * q.k);
}

t_quat	quat_conjugate(t_quat q)
{
	return ((t_quat){q.w, -q.i, -q.j, -q.k});
}

t_quat	quat_scalar_prod(double a, t_quat q)
{
	return ((t_quat){a * q.w, a * q.i, a * q.j, a * q.k});
}

/*a = quat_smagnitude(q);*/
t_quat	quat_inverse(t_quat q)
{
	double	a;

	a = q.w * q.w + q.i * q.i + q.j * q.j + q.k * q.k;
	a = 1 / a;
	if (a == 0)
		return ((t_quat){0, 0, 0, 0});
	q = (t_quat){q.w, -q.i, -q.j, -q.k};
	q = (t_quat){a * q.w, a * q.i, a * q.j, a * q.k};
	return (q);
}
/*return (quat_scalar_prod(1 / a, quat_conjugate(q)));*/

// Quaternion Product
// | quat q = a + u
// | quat p = b + v
// |   where
// |     a,b := scalar parts of q and p
// |     u,v := vec parts of q and p
// |       then
// |         qp = (ab) + (uv) = (a*b - u.v) + (a*v + b*v + uxv)
t_quat	quat_prod(t_quat q, t_quat p)
{
	double	a;
	t_vec	u;
	t_vec	v;
	t_vec	uv;

	u = (t_vec){q.i, q.j, q.k};
	v = (t_vec){p.i, p.j, p.k};
	uv = vec_cross_prod(u, v);
	a = (q.w * p.w) - (u.x * v.x + u.y * v.y + u.z * v.z);
	u = (t_vec){p.w * u.x, p.w * u.y, p.w * u.z};
	v = (t_vec){q.w * v.x, q.w * v.y, q.w * v.z};
	uv = (t_vec){u.x + uv.x, u.y + uv.y, u.z + uv.z};
	uv = (t_vec){v.x + uv.x, v.y + uv.y, v.z + uv.z};
	return ((t_quat){a, uv.x, uv.y, uv.z});
}
