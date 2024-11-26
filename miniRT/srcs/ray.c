/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:13:18 by ecorona-          #+#    #+#             */
/*   Updated: 2024/11/21 13:45:49 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	ray_position(t_ray ray, double t)
{
	return (vector_add(ray.origin, vector_scalar_product(t, ray.direction)));
}

t_roots	quadratic_roots(double a, double b, double c)
{
	double	delta;
	double	x1;
	double	x2;

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

t_roots	ray_circle_intersect(t_ray ray, t_object object, double z)
{
	double		t;
	double		r;
	t_vector	p;

	r = (double)1 / object.shape.scale;
	ray.origin = vector_subtract(ray.origin, object.translation);
	ray.origin = vector_rotate(ray.origin, object.rotation.axis, -object.rotation.angle);
	ray.direction = vector_rotate(ray.direction, object.rotation.axis, -object.rotation.angle);
	t = (z - ray.origin.z) / ray.direction.z;
	p = ray_position(ray, t);
	return ((t_roots){(p.x * p.x + p.y * p.y) < (r * r), t, t});
}

t_roots	ray_plane_intersect(t_ray ray, t_object object, double z)
{
	double		t;

	ray.origin = vector_subtract(ray.origin, object.translation);
	ray.origin = vector_rotate(ray.origin, object.rotation.axis, -object.rotation.angle);
	ray.direction = vector_rotate(ray.direction, object.rotation.axis, -object.rotation.angle);
	t = (z - ray.origin.z) / ray.direction.z;
	return ((t_roots){1, t, t});
}

t_roots	ray_object_intersect(t_ray ray, t_object object)
{
	t_shape		shape;
	double		abc[3];
	t_roots		xs;
	t_vector	p;

	shape = object.shape;
	if (shape.type == PLANE)
		return (ray_plane_intersect(ray, object, 0));
	ray.origin = vector_subtract(ray.origin, object.translation);
	ray.origin = vector_rotate(ray.origin, object.rotation.axis, -object.rotation.angle);
	ray.direction = vector_rotate(ray.direction, object.rotation.axis, -object.rotation.angle);
	abc[0] = vector_dot_product(shape.coefficients, (t_vector){ray.direction.x * ray.direction.x, ray.direction.y * ray.direction.y, ray.direction.z * ray.direction.z});
	abc[1] = vector_dot_product(shape.coefficients, (t_vector){ray.origin.x * ray.direction.x, ray.origin.y * ray.direction.y, ray.origin.z * ray.direction.z});
	abc[1] *= 2;
	abc[2] = vector_dot_product(shape.coefficients, (t_vector){ray.origin.x * ray.origin.x, ray.origin.y * ray.origin.y, ray.origin.z * ray.origin.z});
	abc[2] -= shape.constant;
	xs = quadratic_roots(abc[0], abc[1], abc[2]);
	p = ray_position(ray, xs.x1);
	if (object.shape.height > 0 && (p.z > object.shape.height || p.z < 0))
		xs.x1 = -1;
	p = ray_position(ray, xs.x2);
	if (object.shape.height > 0 && (p.z > object.shape.height || p.z < 0))
		xs.x2 = -1;
	return (xs);
}

t_intersections	*ray_world_intersect(t_intersections *is, t_ray ray, volatile t_world *world)
{
	t_roots	xs;
	t_list	*obj;

	obj = world->objects;
	while (obj)
	{
		xs = ray_object_intersect(ray, *(t_object *)obj->content);
		is = intersections_roots_add(is, xs, obj->content);
		obj = obj->next;
	}
	return (is);
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
