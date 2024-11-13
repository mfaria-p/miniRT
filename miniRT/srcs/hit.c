/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:39:41 by ecorona-          #+#    #+#             */
/*   Updated: 2024/11/10 00:14:50 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	hit(t_intersection intersection, t_ray ray)
{
	t_hit		hit;
	t_vector	n;
	t_vector	e;

	hit.i = intersection;
	hit.point = ray_position(ray, intersection.t);
	n = normal_at(hit.point, *intersection.obj);
	e = vector_scalar_product(-1, ray.direction);
	if (n.x * e.x + n.y * e.y + n.z * e.z < 0)
	{
		hit.is_inside = 1;
		n = (t_vector){-n.x, -n.y, -n.z};
	}
	else
		hit.is_inside = 0;
	hit.normal = n;
	hit.eyev = e;
	return (hit);
}

static int	is_shadowed(t_vector p, t_vector n, t_world *world)
{
	t_ray			ray;
	t_intersections	is;
	int				shadow;

	shadow = 0;
	p = (t_vector){p.x + .2 * n.x, p.y + .2 * n.y, p.z + .2 * n.z};
	ray.origin = p;
	ray.direction = vector_subtract(world->light.origin, p);
	ray.direction = vector_normalize(ray.direction);
	intersections_init(&is);
	ray_world_intersect(&is, ray, world);
	if (is.hit)
		shadow = 1;
	free(is.is);
	return (shadow);
}

t_vector	shade_hit(t_world *world, t_hit hit)
{
	t_material		material;
	t_light_source	light;
	t_phong			phong;
	t_vector		color;
	int				shadow;

	material = hit.i.obj->material;
	light = world->light;
	shadow = is_shadowed(hit.point, hit.normal, world);
	phong = lighting(material, light, hit.point, hit.eyev, hit.normal, shadow);
	color.x = phong.ambient.x + phong.diffuse.x + phong.specular.x;
	color.y = phong.ambient.y + phong.diffuse.y + phong.specular.y;
	color.z = phong.ambient.z + phong.diffuse.z + phong.specular.z;
	color.x *= light.color.x;
	color.y *= light.color.y;
	color.z *= light.color.z;
	return (color);
}

t_vector	color_at(t_world *world, t_ray ray)
{
	t_intersections	is;
	t_vector		color;

	color = (t_vector){0, 0, 0};
	intersections_init(&is);
	ray_world_intersect(&is, ray, world);
	if (is.hit)
		color = shade_hit(world, hit(*is.hit, ray));
	free(is.is);
	return (color);
}
