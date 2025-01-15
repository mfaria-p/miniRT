/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:58:18 by ecorona-          #+#    #+#             */
/*   Updated: 2025/01/15 16:16:53 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_roots	ray_sphere_intersect(t_ray ray, t_obj *obj)
{
	double	a;
	double	b;
	double	c;

	a = vec_dot_prod(ray.dir, ray.dir);
	b = 2 * vec_dot_prod(ray.origin, ray.dir);
	c = vec_dot_prod(ray.origin, ray.origin) - obj->shape.sradius;
	return (quadratic_roots(a, b, c));
}

t_roots	ray_cylinder_intersect(t_ray ray, t_obj *obj)
{
	double	abc[3];
	t_ray	tmp;
	t_roots	r;
	t_vec	p;

	tmp = ray;
	ray.origin.z = 0;
	ray.dir.z = 0;
	abc[0] = vec_dot_prod(ray.dir, ray.dir);
	abc[1] = 2 * vec_dot_prod(ray.origin, ray.dir);
	abc[2] = vec_dot_prod(ray.origin, ray.origin) - obj->shape.sradius;
	r = quadratic_roots(abc[0], abc[1], abc[2]);
	if (r.count == 2)
	{
		p = ray_position(tmp, r.x2);
		if (fabs(p.z) > obj->shape.height)
			r.count--;
	}
	if (r.count == 1)
	{
		p = ray_position(tmp, r.x1);
		if (fabs(p.z) > obj->shape.height)
			r.count--;
	}
	return (r);
}

t_roots	ray_plane_intersect(t_ray ray)
{
	return ((t_roots){1, -ray.origin.z / ray.dir.z, 0});
}

t_roots	ray_obj_intersect(t_ray ray, t_obj *obj)
{
	ray.origin = vec_subtract(ray.origin, obj->translation);
	ray.origin = mat_vec_prod(mat_inverse(obj->rmat), ray.origin);
	ray.dir = mat_vec_prod(mat_inverse(obj->rmat), ray.dir);
	if (obj->shape.type == SPHERE)
		return (ray_sphere_intersect(ray, obj));
	else if (obj->shape.type == CYLINDER)
		return (ray_cylinder_intersect(ray, obj));
	else if (obj->shape.type == PLANE)
		return (ray_plane_intersect(ray));
	return ((t_roots){0, 0, 0});
}

t_touches	*ray_world_hits(t_touches *is, t_ray ray, t_world *world)
{
	t_roots	xs;
	t_list	*objs;

	objs = world->objs;
	while (objs)
	{
		xs = ray_obj_intersect(ray, (t_obj *)objs->content);
		is = touches_roots_add(is, xs, objs->content);
		objs = objs->next;
	}
	return (is);
}
