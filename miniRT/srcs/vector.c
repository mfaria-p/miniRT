/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:32:51 by ecorona-          #+#    #+#             */
/*   Updated: 2024/10/30 15:03:37 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"

int	double_equals(double x, double y)
{
	return (((x - y) < EPSILON) && ((x - y) > -EPSILON));
}

int	vector_equals(t_vector u, t_vector v)
{
	int		result;

	result = 1;
	result = result && (((u.x - v.x) < EPSILON) && ((u.x - v.x) > -EPSILON));
	result = result && (((u.y - v.y) < EPSILON) && ((u.y - v.y) > -EPSILON));
	result = result && (((u.z - v.z) < EPSILON) && ((u.z - v.z) > -EPSILON));
	return (result);
}

t_vector	vector_scalar_product(double a, t_vector u)
{
	return ((t_vector){a * u.x, a * u.y, a * u.z});
}

t_vector	vector_add(t_vector u, t_vector v)
{
	return ((t_vector){u.x + v.x, u.y + v.y, u.z + v.z});
}

t_vector	vector_subtract(t_vector u, t_vector v)
{
	return ((t_vector){u.x - v.x, u.y - v.y, u.z - v.z});
}

double	vector_dot_product(t_vector u, t_vector v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

double	vector_magnitude(t_vector u)
{
	return (sqrtf(u.x * u.x + u.y * u.y + u.z * u.z));
}

double	vector_distance(t_vector u, t_vector v)
{
	t_vector	a;

	a = (t_vector){u.x - v.x, u.y - v.y, u.z - v.z};
	return (sqrtf(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vector	vector_normalize(t_vector u)
{
	t_vector	nil;
	double		imag;
	int			res;

	nil = (t_vector){0, 0, 0};
	res = 1;
	res = res && (((u.x - nil.x) < EPSILON) && ((u.x - nil.x) > -EPSILON));
	res = res && (((u.y - nil.y) < EPSILON) && ((u.y - nil.y) > -EPSILON));
	res = res && (((u.z - nil.z) < EPSILON) && ((u.z - nil.z) > -EPSILON));
	if (res)
		return ((t_vector){0, 0, 0});
	imag = 1 / sqrtf(u.x * u.x + u.y * u.y + u.z * u.z);
	return ((t_vector){imag * u.x, imag * u.y, imag * u.z});
}

t_vector	vector_cross_product(t_vector u, t_vector v)
{
	return ((t_vector){u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x});
}

double	vector_cosine(t_vector u, t_vector v)
{
	u = vector_normalize(u);
	v = vector_normalize(v);
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

// project u onto v
double	vector_scalar_projection(t_vector u, t_vector v)
{
	v = vector_normalize(v);
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

// project u onto v
t_vector	vector_projection(t_vector u, t_vector v)
{
	t_vector	aux;
	double		dot;

	aux = vector_normalize(v);
	dot = u.x * aux.x + u.y * aux.y + u.z * aux.z;
	return ((t_vector){dot * aux.x, dot * aux.y, dot * aux.z});
}

// project u onto plane defined by normal n
t_vector	vector_plane_projection(t_vector u, t_vector n)
{
	t_vector	aux;
	double		dot;

	aux = vector_normalize(n);
	dot = u.x * aux.x + u.y * aux.y + u.z * aux.z;
	aux = ((t_vector){dot * aux.x, dot * aux.y, dot * aux.z});
	return ((t_vector){u.x - aux.x, u.y - aux.y, u.z - aux.z});
}

// Axis-Angle Rotation
// | {r,x,y,z} := axis-angle rotation
// |   where
// |     r       := real number representing angle [radians]
// |     {x,y,z} := unit vector representing axis
//
// Quaternion Rotation
// | q := quaternion rotation
// |   where
// |     {r,x,y,z} := axis-angle rotation
// |     q         = {cos(r/2), sin(r/2)*x, sin(r/2)*y, sin(r/2)*z}
//
// 3D Rotation from Quaternion
// | v := rotation of {a,b,c} r [radians] around {x,y,z}
// |   then
// |     v = vector part of p'
// |       where
// |         p' := q^(-1) * p * q
// |           where
// |             p      := {0,a,b,c}
// |             q      := quaternion rotation of {r,x,y,z} axis-angle rotation
// |             q^(-1) := inverse of q
//
// rotate u rad degrees [radians] around axis ax
t_vector	vector_rotate(t_vector u, t_vector ax, double rad)
{
	double			aux;
	t_quaternion	p;
	t_quaternion	q;

	aux = sinf(rad / 2);
	ax = vector_scalar_product(aux, vector_normalize(ax));
	q = (t_quaternion){1 - (aux * aux), ax.x, ax.y, ax.z};
	p = (t_quaternion){0, u.x, u.y, u.z};
	p = quaternion_product(quaternion_product(quaternion_inverse(q), p), q);
	return ((t_vector){p.i, p.j, p.k});
}
