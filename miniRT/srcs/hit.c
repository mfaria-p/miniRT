/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:39:41 by ecorona-          #+#    #+#             */
/*   Updated: 2024/12/03 19:21:21 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	hit(t_touch touch, t_ray ray)
{
	t_hit	hit;
	t_vec	n;
	t_vec	e;

	hit.i = touch;
	hit.point = ray_position(ray, touch.t);
	n = normal_at(hit.point, *touch.obj);
	e = vec_scalar_prod(-1, ray.dir);
	if (n.x * e.x + n.y * e.y + n.z * e.z < 0)
	{
		hit.is_inside = 1;
		n = (t_vec){-n.x, -n.y, -n.z};
	}
	else
		hit.is_inside = 0;
	hit.normal = n;
	hit.eyev = e;
	return (hit);
}

static int	is_shadowed(t_vec p, t_vec n, t_world *world)
{
	t_ray		ray;
	t_touches	is;
	int			shadow;

	shadow = 0;
	p = (t_vec){p.x + .2 * n.x, p.y + .2 * n.y, p.z + .2 * n.z};
	ray.origin = p;
	ray.dir = vec_subtract(world->light.origin, p);
	ray.dir = vec_normalize(ray.dir);
	touches_init(&is);
	ray_world_hits(&is, ray, world);
	if (is.hit)
		shadow = 1;
	free(is.is);
	return (shadow);
}

t_vec	shade_hit(t_world *world, t_hit hit)
{
	t_material	material;
	t_spotlight	light;
	t_phong		phong;
	t_vec		color;
	int			shadow;

	material = hit.i.obj->material;
	light = world->light;
	shadow = is_shadowed(hit.point, hit.normal, world);
	phong = lighting(material, light, hit.point, hit.eyev, hit.normal, shadow);
	phong.amb = world->amb;
	phong.amb = vec_scalar_prod(material.amb, phong.amb);
	color.x = material.color.x * phong.amb.x + phong.dif.x + phong.spec.x;
	color.y = material.color.y * phong.amb.y + phong.dif.y + phong.spec.y;
	color.z = material.color.z * phong.amb.z + phong.dif.z + phong.spec.z;
	color.x *= light.color.x;
	color.y *= light.color.y;
	color.z *= light.color.z;
	return (color);
}

t_vec	color_at(t_world *world, t_ray ray)
{
	t_touches	is;
	t_vec		color;

	color = (t_vec){0, 0, 0};
	touches_init(&is);
	ray_world_hits(&is, ray, world);
	if (is.hit)
		color = shade_hit(world, hit(*is.hit, ray));
	free(is.is);
	return (color);
}
