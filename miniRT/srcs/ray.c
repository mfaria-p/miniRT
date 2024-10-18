/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:13:18 by ecorona-          #+#    #+#             */
/*   Updated: 2024/10/18 12:29:44 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"
#include "minirt.h"

t_vector	ray_position(t_ray ray, float t)
{
	return (vector_add(ray.origin, vector_scalar_product(t, ray.direction)));
}

t_roots	quadratic_roots(float a, float b, float c)
{
	float	delta;
	float	x1;
	float	x2;

	if (a == 0)
		return ((t_roots){0, 0, 0});
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return ((t_roots){0, 0, 0});
	else if (delta == 0)
	{
		x1 = -b / (2 * a);
		return ((t_roots){1, x1, x1});
	}
	x1 = (-b - sqrtf(delta)) / (2 * a);
	x2 = (-b + sqrtf(delta)) / (2 * a);
	return ((t_roots){2, x1, x2});
}

t_roots	ray_object_intersect(t_ray ray, t_object object)
{
	t_shape		shape;
	double		a;
	double		b;
	double		c;
	t_vector	h;
	t_vector	i;
	t_vector	ii;

	shape = object.shape;
	ray.origin = vector_subtract(ray.origin, object.translation);
	ray.origin = vector_rotate(ray.origin, object.rotation.axis, -object.rotation.angle);
	ray.direction = vector_rotate(ray.direction, object.rotation.axis, -object.rotation.angle);
	h.x = vector_dot_product(ray.direction, (t_vector){shape.scale * shape.shear.matrix[0][0], shape.shear.matrix[0][1], shape.shear.matrix[0][2]});
	h.y = vector_dot_product(ray.direction, (t_vector){shape.shear.matrix[1][0], shape.scale * shape.shear.matrix[1][1], shape.shear.matrix[1][2]});
	h.z = vector_dot_product(ray.direction, (t_vector){shape.shear.matrix[2][0], shape.shear.matrix[2][1], shape.scale * shape.shear.matrix[2][2]});
	i.x = shape.scale * (ray.origin.x - shape.parameters.shift.x) * shape.shear.matrix[0][0];
	i.y = shape.scale * (ray.origin.y - shape.parameters.shift.y) * shape.shear.matrix[1][1];
	i.z = shape.scale * (ray.origin.z - shape.parameters.shift.z) * shape.shear.matrix[2][2];
	ii.x = ray.origin.y * shape.shear.matrix[0][1] + ray.origin.z * shape.shear.matrix[0][2];
	ii.y = ray.origin.x * shape.shear.matrix[1][0] + ray.origin.z * shape.shear.matrix[1][2];
	ii.z = ray.origin.x * shape.shear.matrix[2][0] + ray.origin.y * shape.shear.matrix[2][1];
	a = vector_dot_product(shape.parameters.coefficients, (t_vector){h.x * h.x, h.y * h.y, h.z * h.z});
	b = 2 * vector_dot_product(shape.parameters.coefficients, (t_vector){(i.x + ii.x) * h.x + i.x * ii.x, (i.y + ii.y) * h.y + i.y * ii.y, (i.z + ii.z) * h.z + i.z * ii.z});
	c = vector_dot_product(shape.parameters.coefficients, (t_vector){i.x * i.x + ii.x * ii.x, i.y * i.y + ii.y * ii.y, i.z * i.z + ii.z * ii.z});
	c -= shape.parameters.constant;
	return (quadratic_roots(a, b, c));
}

// OUTDATED:
// Ray
// | ray := {O, D}
// |   where
// |     O := vector representing ray's origin
// |     D := vector representing ray's direction
//
// Sphere
// | sphere := {C, r}
// |   where
// |     C := vector representing sphere's center
// |     r := sphere's radius
//
// Intersection
// | O + kD = C + R
// |   where
// |     k := scalar
// |     R := vector of arbitrary direction and magnitude ||R|| = r
// |       then
// |         ray `intersects` sphere if a real number satifies equation
//
// solve system S to find k:
//  S := 1. O + kD = C + R
//       2. ||R|| = r
// 
// working:
//  S => a*k^2 + b*k + c = 0
//    where
//      a = ||D||^2
//      b = 2*(D.H)
//      c = ||H||^2 - r^2
// 
// working:
//  S => k = (-b+sqrt(b^2 -4ac))/(2*a) or (-b-sqrt(b^2 -4ac))/(2*a)
