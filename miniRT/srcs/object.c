/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:59:01 by ecorona-          #+#    #+#             */
/*   Updated: 2024/12/03 20:19:23 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*obj_translate(t_obj *obj, t_vec dir, double shift)
{
	obj->translation.x = obj->translation.x + shift * dir.x;
	obj->translation.y = obj->translation.y + shift * dir.y;
	obj->translation.z = obj->translation.z + shift * dir.z;
	return (obj);
}

t_obj	*obj_rotate(t_obj *obj, t_vec axis, double angle)
{
	obj->axis = vec_rotate(obj->axis, axis, angle);
	obj->rotation.axis = vec_cross_prod(obj->axis, (t_vec){0, 0, 1});
	obj->rotation.angle = acos(vec_cosine(obj->axis, (t_vec){0, 0, 1}));
	return (obj);
}

t_obj	*obj_scale(t_obj *obj, double scale)
{
	if (obj->shape.type == PLANE)
		return (obj);
	obj->shape.scale *= scale;
	if (obj->shape.type == CONE)
		obj->shape.coef.z *= scale;
	else if (obj->shape.type == SPHERE || obj->shape.type == CYLINDER)
		obj->shape.constant *= scale;
	return (obj);
}

t_obj	*obj_select(t_world *world, int x, int y)
{
	t_ray		ray;
	t_touches	is;
	t_obj		*selected;
	t_vec		point;

	selected = NULL;
	ray.origin = world->cam.origin;
	point = vec_normalize(world->cam.axis);
	point = vec_add(point, vec_scalar_prod((x - world->cam.hsize / 2) * world->cam.pixel_size / world->cam.scale, vec_normalize(vec_rotate(vec_scalar_prod(-1, world->cam.left), world->cam.rotation.axis, world->cam.rotation.angle))));
	point = vec_add(point, vec_scalar_prod((y - world->cam.vsize / 2) * world->cam.pixel_size / world->cam.scale, vec_normalize(vec_rotate(vec_scalar_prod(-1, world->cam.up), world->cam.rotation.axis, world->cam.rotation.angle))));
	ray.dir = vec_normalize(point);
	touches_init(&is);
	ray_world_hits(&is, ray, world);
	if (is.hit)
		selected = is.hit->obj;
	free(is.is);
	return (selected);
}

t_vec	normal_at(t_vec p, t_obj obj)
{
	t_shape	shape;
	t_vec	normal;

	if (obj.shape.type == PLANE)
		return (obj.shape.coef);
	shape = obj.shape;
	p = vec_subtract(p, obj.translation);
	p = vec_rotate(p, obj.rotation.axis, -obj.rotation.angle);
	normal.x = 2 * shape.coef.x * p.x;
	normal.y = 2 * shape.coef.y * p.y;
	normal.z = 2 * shape.coef.z * p.z;
	normal = vec_add(p, obj.translation);
	normal = vec_rotate(p, obj.rotation.axis, obj.rotation.angle);
	normal = vec_normalize(normal);
	return (normal);
}
