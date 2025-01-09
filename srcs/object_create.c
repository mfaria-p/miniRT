/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:16:30 by ecorona-          #+#    #+#             */
/*   Updated: 2025/01/09 17:51:51 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*obj_sphere_create(t_sphere s)
{
	t_shape	shape;
	t_obj	*obj;

	shape.type = SPHERE;
	shape.coef = (t_vec){1, 1, 1};
	shape.height = 0;
	shape.constant = (s.diameter * s.diameter) / 4;
	shape.scale = s.diameter;
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
	obj->axis = (t_vec){0, 0, 0};
	return (obj);
}

t_obj	*obj_cylinder_create(t_cylinder c)
{
	t_shape	shape;
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	shape.type = CYLINDER;
	shape.coef = (t_vec){1, 1, 0};
	shape.height = c.height;
	shape.constant = (c.diameter * c.diameter) / 4;
	shape.scale = c.diameter;
	obj->shape = shape;
	obj->material.color = (t_vec){c.color.r, c.color.g, c.color.b};
	obj->material.color = vec_scalar_prod(1 / 255.0, obj->material.color);
	obj->material.shine = 1;
	obj->material.amb = 1;
	obj->material.dif = 1;
	obj->material.spec = 1;
	obj->translation = (t_vec){c.x, c.y, c.z};
	obj->axis = (t_vec){c.dx, c.dy, c.dz};
	obj->rmat = (t_mat){{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	obj->rmat = mat_rotate_euler(obj->rmat, \
							  vec_scalar_prod(M_PI / 2, obj->axis));
	return (obj);
}

t_obj	*obj_plane_create(t_plane p)
{
	t_shape	shape;
	t_obj	*obj;

	shape.type = PLANE;
	shape.coef = (t_vec){p.dx, p.dy, p.dz};
	shape.height = 0;
	shape.constant = 0;
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
	obj->axis = shape.coef;
	obj->rmat = (t_mat){{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	obj->rmat = mat_rotate_euler(obj->rmat, \
							  vec_scalar_prod(M_PI / 2, obj->axis));
	return (obj);
}

t_vec	normal_at(t_vec p, t_obj obj)
{
	t_shape	shape;
	t_vec	normal;

	if (obj.shape.type == PLANE)
		return (obj.shape.coef);
	shape = obj.shape;
	p = vec_subtract(p, obj.translation);
	p = mat_vec_prod(obj.rmat, p);
	normal.x = 2 * shape.coef.x * p.x;
	normal.y = 2 * shape.coef.y * p.y;
	normal.z = 2 * shape.coef.z * p.z;
	normal = vec_add(p, obj.translation);
	normal = mat_vec_prod(obj.rmat, p);
	normal = vec_normalize(normal);
	return (normal);
}
