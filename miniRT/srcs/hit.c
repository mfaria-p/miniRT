/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:39:41 by ecorona-          #+#    #+#             */
/*   Updated: 2024/11/07 21:45:05 by ecorona-         ###   ########.fr       */
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
	t_light_source	*light;
	t_list			*node;
	t_vector		c_acc;
	t_phong			c;

	material = hit.i.obj->material;
	c_acc = (t_vector){0, 0, 0};
	node = world->lights;
	while (node)
	{
		light = node->content;
		c = lighting(material, *light, hit.point, hit.eyev, hit.normal);
		c.ambient.x = c.ambient.x * light->color.x;
		c.ambient.y = c.ambient.y * light->color.y;
		c.ambient.z = c.ambient.z * light->color.z;
		c.diffuse.x = c.diffuse.x * light->color.x;
		c.diffuse.y = c.diffuse.y * light->color.y;
		c.diffuse.z = c.diffuse.z * light->color.z;
		c.specular.x = c.specular.x * light->color.x;
		c.specular.y = c.specular.y * light->color.y;
		c.specular.z = c.specular.z * light->color.z;
		c_acc.x += c.ambient.x + c.diffuse.x + c.diffuse.x;
		c_acc.y += c.ambient.y + c.diffuse.y + c.diffuse.y;
		c_acc.z += c.ambient.z + c.diffuse.z + c.diffuse.z;
		node = node->next;
	}
	return (c_acc);
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
