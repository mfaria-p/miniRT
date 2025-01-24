/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:16:30 by ecorona-          #+#    #+#             */
/*   Updated: 2025/01/24 14:38:59 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*obj_sphere_create(t_sphere s)
{
	t_shape	shape;
	t_obj	*obj;

	shape.type = SPHERE;
	shape.height = 0;
	shape.sradius = (s.diameter * s.diameter) / 4;
	shape.scale = 1;
	obj = malloc(sizeof(t_obj));
	obj->shape = shape;
	obj->material.color = (t_vec){s.color.r, s.color.g, s.color.b};
	obj->material.color = vec_scalar_prod(1 / 255.0, obj->material.color);
	obj->material.shine = 1;
	obj->material.amb = 1;
	obj->material.dif = 1;
	obj->material.spec = 1;
	obj->translation = (t_vec){s.x, s.y, s.z};
	obj->rmat = (t_mat){{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	obj->axis = (t_vec){0, 0, 1};
	return (obj);
}

t_obj	*obj_cylinder_create(t_cylinder c)
{
	t_shape	shape;
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	shape.type = CYLINDER;
	shape.height = c.height;
	shape.sradius = (c.diameter * c.diameter) / 4;
	shape.scale = 1;
	obj->shape = shape;
	obj->material.color = (t_vec){c.color.r, c.color.g, c.color.b};
	obj->material.color = vec_scalar_prod(1 / 255.0, obj->material.color);
	obj->material.shine = 1;
	obj->material.amb = 1;
	obj->material.dif = 1;
	obj->material.spec = 1;
	obj->translation = (t_vec){c.x, c.y, c.z};
	obj->axis = (t_vec){c.dx, c.dy, c.dz};
	obj->rmat = mat_rot_vec2vec((t_vec){0, 0, 1}, obj->axis);
	return (obj);
}

t_obj	*obj_plane_create(t_plane p)
{
	t_shape	shape;
	t_obj	*obj;

	shape.type = PLANE;
	shape.height = 0;
	shape.sradius = 0;
	shape.scale = 0;
	obj = malloc(sizeof(t_obj));
	obj->shape = shape;
	obj->material.color = (t_vec){p.color.r, p.color.g, p.color.b};
	obj->material.color = vec_scalar_prod(1 / 255.0, obj->material.color);
	obj->material.shine = 1;
	obj->material.amb = 1;
	obj->material.dif = 1;
	obj->material.spec = 1;
	obj->translation = (t_vec){p.x, p.y, p.z};
	obj->axis = (t_vec){p.dx, p.dy, p.dz};
	obj->rmat = mat_rot_vec2vec((t_vec){0, 0, 1}, obj->axis);
	return (obj);
}

t_vec	normal_at(t_vec p, t_obj obj)
{
	t_vec	normal;

	if (obj.shape.type == PLANE)
		return (obj.axis);
	p = vec_subtract(p, obj.translation);
	if (obj.shape.type == SPHERE)
		normal = p;
	else if (obj.shape.type == CYLINDER)
	{
		p = mat_vec_prod(mat_inverse(obj.rmat), p);
		normal = p;
		normal.z = 0;
		normal = mat_vec_prod(obj.rmat, p);
	}
	normal = vec_normalize(normal);
	return (normal);
}
