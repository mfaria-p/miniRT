/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:13:18 by ecorona-          #+#    #+#             */
/*   Updated: 2024/10/17 23:12:46 by ecorona-         ###   ########.fr       */
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

static double	sqr(double x)
{
	return (x * x);
}

t_roots	ray_object_intersect(t_ray ray, t_object object)
{
	t_shape		shape;
	double		a;
	double		b;
	double		c;

	shape = object.shape;
	ray.origin = vector_subtract(ray.origin, object.translation);
	ray.direction = vector_rotate(ray.direction, object.rotation.axis, -object.rotation.angle);
	a = shape.parameters.coefficients.x * (sqr(shape.shear.matrix[0][0] * shape.scale) + sqr(shape.shear.matrix[0][1] * ray.direction.y) + sqr(shape.shear.matrix[0][2] * ray.direction.z) + 2 * shape.scale * (shape.shear.matrix[0][0] * shape.shear.matrix[0][1] * ray.direction.x * ray.direction.y + shape.shear.matrix[0][0] * shape.shear.matrix[0][2] * ray.direction.x * ray.direction.z + shape.shear.matrix[0][1] * shape.shear.matrix[0][2] * ray.direction.y * ray.direction.z));
	a += shape.parameters.coefficients.y * (sqr(shape.shear.matrix[1][1] * shape.scale) + sqr(shape.shear.matrix[1][0] * ray.direction.x) + sqr(shape.shear.matrix[1][2] * ray.direction.z) + 2 * shape.scale * (shape.shear.matrix[1][1] * shape.shear.matrix[1][0] * ray.direction.x * ray.direction.y + shape.shear.matrix[1][1] * shape.shear.matrix[1][2] * ray.direction.y * ray.direction.z + shape.shear.matrix[1][0] * shape.shear.matrix[1][2] * ray.direction.x * ray.direction.z));
	a += shape.parameters.coefficients.z * (sqr(shape.shear.matrix[2][2] * shape.scale) + sqr(shape.shear.matrix[2][0] * ray.direction.x) + sqr(shape.shear.matrix[2][1] * ray.direction.y) + 2 * shape.scale * (shape.shear.matrix[2][2] * shape.shear.matrix[2][0] * ray.direction.x * ray.direction.z + shape.shear.matrix[2][2] * shape.shear.matrix[2][1] * ray.direction.y * ray.direction.z + shape.shear.matrix[2][0] * shape.shear.matrix[2][1] * ray.direction.x * ray.direction.y));
	b = 2 * shape.parameters.coefficients.x * (sqr(shape.shear.matrix[0][0] * shape.scale) * ray.direction.x * (ray.origin.x - shape.parameters.shift.x) + sqr(shape.shear.matrix[0][1]) * ray.direction.y * ray.origin.y + sqr(shape.shear.matrix[0][2]) * ray.direction.z * ray.origin.z + 2 * shape.scale * (shape.shear.matrix[0][0] * shape.shear.matrix[0][1] * ((ray.origin.x - shape.parameters.shift.x) * ray.direction.y + ray.origin.y * ray.direction.x) + shape.shear.matrix[0][0] * shape.shear.matrix[0][2] * ((ray.origin.x - shape.parameters.shift.x) * ray.direction.z + ray.origin.z * ray.direction.x) + shape.shear.matrix[0][1] * shape.shear.matrix[0][2] * (ray.origin.y * ray.direction.z + ray.origin.z * ray.direction.y)));
	b += 2 * shape.parameters.coefficients.y * (sqr(shape.shear.matrix[1][1] * shape.scale) * ray.direction.y * (ray.origin.y - shape.parameters.shift.y) + sqr(shape.shear.matrix[1][0]) * ray.direction.x * ray.origin.x + sqr(shape.shear.matrix[1][2]) * ray.direction.z * ray.origin.z + 2 * shape.scale * (shape.shear.matrix[1][1] * shape.shear.matrix[1][0] * ((ray.origin.y - shape.parameters.shift.y) * ray.direction.x + ray.origin.x * ray.direction.y) + shape.shear.matrix[1][1] * shape.shear.matrix[1][2] * ((ray.origin.y - shape.parameters.shift.y) * ray.direction.z + ray.origin.z * ray.direction.y) + shape.shear.matrix[1][0] * shape.shear.matrix[1][2] * (ray.origin.x * ray.direction.z + ray.origin.z * ray.direction.x)));
	b += 2 * shape.parameters.coefficients.z * (sqr(shape.shear.matrix[2][2] * shape.scale) * ray.direction.z * (ray.origin.z - shape.parameters.shift.z) + sqr(shape.shear.matrix[2][0]) * ray.direction.x * ray.origin.x + sqr(shape.shear.matrix[2][1]) * ray.direction.y * ray.origin.y + 2 * shape.scale * (shape.shear.matrix[2][2] * shape.shear.matrix[2][0] * ((ray.origin.z - shape.parameters.shift.z) * ray.direction.x + ray.origin.x * ray.direction.z) + shape.shear.matrix[2][2] * shape.shear.matrix[2][1] * ((ray.origin.z - shape.parameters.shift.z) * ray.direction.y + ray.origin.y * ray.direction.z) + shape.shear.matrix[2][0] * shape.shear.matrix[2][1] * (ray.origin.x * ray.direction.y + ray.origin.y * ray.direction.x)));
	c = shape.parameters.coefficients.x * (sqr(shape.shear.matrix[0][0] * shape.scale * (ray.origin.x - shape.parameters.shift.x)) + sqr(shape.shear.matrix[0][1] * ray.origin.y) + sqr(shape.shear.matrix[0][2] * ray.origin.z) + 2 * shape.scale * (shape.shear.matrix[0][0] * shape.shear.matrix[0][1] * (ray.origin.x - shape.parameters.shift.x) * ray.origin.y + shape.shear.matrix[0][0] * shape.shear.matrix[0][2] * (ray.origin.x - shape.parameters.shift.x) * ray.origin.z + shape.shear.matrix[0][1] * shape.shear.matrix[0][2] * ray.origin.y * ray.origin.z));
	c += shape.parameters.coefficients.y * (sqr(shape.shear.matrix[1][1] * shape.scale * (ray.origin.y - shape.parameters.shift.y)) + sqr(shape.shear.matrix[1][0] * ray.origin.x) + sqr(shape.shear.matrix[1][2] * ray.origin.z) + 2 * shape.scale * (shape.shear.matrix[1][1] * shape.shear.matrix[1][0] * (ray.origin.y - shape.parameters.shift.y) * ray.origin.x + shape.shear.matrix[1][1] * shape.shear.matrix[1][2] * (ray.origin.y - shape.parameters.shift.y) * ray.origin.z + shape.shear.matrix[1][0] * shape.shear.matrix[1][2] * ray.origin.x * ray.origin.z));
	c += shape.parameters.coefficients.z * (sqr(shape.shear.matrix[2][2] * shape.scale * (ray.origin.z - shape.parameters.shift.z)) + sqr(shape.shear.matrix[2][0] * ray.origin.x) + sqr(shape.shear.matrix[2][1] * ray.origin.y) + 2 * shape.scale * (shape.shear.matrix[2][2] * shape.shear.matrix[2][0] * (ray.origin.z - shape.parameters.shift.z) * ray.origin.x + shape.shear.matrix[2][2] * shape.shear.matrix[2][1] * (ray.origin.z - shape.parameters.shift.z) * ray.origin.y + shape.shear.matrix[2][0] * shape.shear.matrix[2][1] * ray.origin.x * ray.origin.y));
	c -= sqr(shape.parameters.constant);
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
