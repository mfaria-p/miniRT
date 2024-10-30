/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:32:51 by ecorona-          #+#    #+#             */
/*   Updated: 2024/10/30 13:28:39 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"

int	double_equals(double x, double y)
{
	return (fabs(x - y) < EPSILON);
}

int	vector_equals(t_vector u, t_vector v)
{
	return (double_equals(u.x, v.x) && double_equals(u.y, v.y) && double_equals(u.z, v.z));
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
	return (vector_add(u, vector_scalar_product(-1, v)));
}

double	vector_dot_product(t_vector u, t_vector v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

double	vector_magnitude(t_vector u)
{
	return (sqrtf(vector_dot_product(u, u)));
}

double	vector_distance(t_vector u, t_vector v)
{
	return (vector_magnitude(vector_subtract(u, v)));
}

t_vector	vector_normalize(t_vector u)
{
	if (vector_equals(u, (t_vector){0, 0, 0}))
		return ((t_vector){0, 0, 0});
	return (vector_scalar_product(1 / vector_magnitude(u), u));
}

t_vector	vector_cross_product(t_vector u, t_vector v)
{
	return ((t_vector){u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x});
}

double	vector_cosine(t_vector u, t_vector v)
{
	return (vector_dot_product(vector_normalize(u), vector_normalize(v)));
}

// project u onto v
double	vector_scalar_projection(t_vector u, t_vector v)
{
	return (vector_dot_product(u, vector_normalize(v)));
}

// project u onto v
t_vector	vector_projection(t_vector u, t_vector v)
{
	t_vector	aux;

	aux = vector_normalize(v);
	return (vector_scalar_product(vector_dot_product(u, aux), aux));
}

// project u onto plane defined by normal n
t_vector	vector_plane_projection(t_vector u, t_vector n)
{
	return (vector_subtract(u, vector_projection(u, n)));
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
