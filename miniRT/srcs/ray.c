/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:13:18 by ecorona-          #+#    #+#             */
/*   Updated: 2024/10/17 21:37:05 by ecorona-         ###   ########.fr       */
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

t_roots	ray_shape_intersect(t_ray ray, t_object object)
{
	t_shape		shape;
	t_vector	aux;
	double		a;
	double		b;
	double		c;

	shape = object.shape;
	ray.origin = vector_subtract(ray.origin, object.translation);
	ray.direction = vector_rotate(ray.direction, object.rotation.axis, -object.rotation.angle);
	// a b c ? check notebook
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
