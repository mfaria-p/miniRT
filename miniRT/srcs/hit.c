/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:39:41 by ecorona-          #+#    #+#             */
/*   Updated: 2024/11/09 13:30:39 by ecorona-         ###   ########.fr       */
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

t_vector	shade_hit(t_world *world, t_hit hit)
{
	t_material		material;
	t_light_source	light;
	t_phong			phong;
	t_vector		color;

	material = hit.i.obj->material;
	light = world->light;
	phong = lighting(material, light, hit.point, hit.eyev, hit.normal);
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
	t_vector			color;

	color = (t_vector){0, 0, 0};
	intersections_init(&is);
	ray_world_intersect(&is, ray, world);
	if (is.hit)
		color = shade_hit(world, hit(*is.hit, ray));
	free(is.is);
	return (color);
}
