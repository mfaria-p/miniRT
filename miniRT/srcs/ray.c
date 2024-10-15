/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:13:18 by ecorona-          #+#    #+#             */
/*   Updated: 2024/10/15 23:22:10 by ecorona-         ###   ########.fr       */
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
t_roots	ray_sphere_intersect(t_ray ray, t_object sphere)
{
	t_sphere	shape;
	t_vector	aux;
	float		a;
	float		b;
	float		c;

	shape = *(t_sphere *)sphere.shape;
	ray.direction = matrix_vector_product(matrix_inverse(sphere.transformation), ray.direction);
	ray.origin = matrix_vector_product(matrix_inverse(sphere.transformation), ray.origin);
	aux = vector_subtract(ray.origin, shape.origin);
	a = vector_dot_product(ray.direction, ray.direction);
	b = 2 * vector_dot_product(ray.direction, aux);
	c = vector_dot_product(aux, aux) - shape.r * shape.r;
	return (quadratic_roots(a, b, c));
}
