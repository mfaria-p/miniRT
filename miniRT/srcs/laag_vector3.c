/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:10:19 by ecorona-          #+#    #+#             */
/*   Updated: 2024/12/03 20:10:28 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"

double	vec_cosine(t_vec u, t_vec v)
{
	u = vec_normalize(u);
	v = vec_normalize(v);
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

// project u onto v
double	vec_scalar_projection(t_vec u, t_vec v)
{
	v = vec_normalize(v);
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

// project u onto v
t_vec	vec_projection(t_vec u, t_vec v)
{
	t_vec	aux;
	double	dot;

	aux = vec_normalize(v);
	dot = u.x * aux.x + u.y * aux.y + u.z * aux.z;
	return ((t_vec){dot * aux.x, dot * aux.y, dot * aux.z});
}

// project u onto plane defined by normal n
t_vec	vec_plane_projection(t_vec u, t_vec n)
{
	t_vec	aux;
	double	dot;

	aux = vec_normalize(n);
	dot = u.x * aux.x + u.y * aux.y + u.z * aux.z;
	aux = ((t_vec){dot * aux.x, dot * aux.y, dot * aux.z});
	return ((t_vec){u.x - aux.x, u.y - aux.y, u.z - aux.z});
}

// Axis-Angle Rotation
// | {r,x,y,z} := axis-angle rotation
// |   where
// |     r       := real number representing angle [radians]
// |     {x,y,z} := unit vec representing axis
//
// Quaternion Rotation
// | q := quat rotation
// |   where
// |     {r,x,y,z} := axis-angle rotation
// |     q         = {cos(r/2), sin(r/2)*x, sin(r/2)*y, sin(r/2)*z}
//
// 3D Rotation from Quaternion
// | v := rotation of {a,b,c} r [radians] around {x,y,z}
// |   then
// |     v = vec part of p'
// |       where
// |         p' := q^(-1) * p * q
// |           where
// |             p      := {0,a,b,c}
// |             q      := quat rotation of {r,x,y,z} axis-angle rotation
// |             q^(-1) := inverse of q
//
// rotate u rad degrees [radians] around axis ax
t_vec	vec_rotate(t_vec u, t_vec ax, double rad)
{
	double	aux;
	t_quat	p;
	t_quat	q;

	aux = sin(rad / 2);
	ax = vec_scalar_prod(aux, vec_normalize(ax));
	q = (t_quat){1 - (aux * aux), ax.x, ax.y, ax.z};
	p = (t_quat){0, u.x, u.y, u.z};
	p = quat_prod(quat_prod(quat_inverse(q), p), q);
	return ((t_vec){p.i, p.j, p.k});
}
