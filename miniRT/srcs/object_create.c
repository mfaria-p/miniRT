/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:16:30 by ecorona-          #+#    #+#             */
/*   Updated: 2024/12/03 20:16:35 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*obj_sphere_create(t_vec xyz, t_vec rgb, double d)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	obj->shape = (t_shape){SPHERE, (t_vec){1, 1, 1}, 0, (d * d) / 4, d};
	obj->material.color = rgb;
	obj->material.shine = 1;
	obj->material.amb = 1;
	obj->material.dif = 1;
	obj->material.spec = 1;
	obj->translation = xyz;
	obj->rotation.axis = (t_vec){0, 0, 0};
	obj->rotation.angle = 0;
	obj->axis = (t_vec){0, 0, 0};
	return (obj);
}

t_obj	*obj_cylinder_create(t_vec xyz, t_vec rgb, t_vec axis, double d, double h)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	obj->shape = (t_shape){CYLINDER, (t_vec){1, 1, 0}, h, (d * d) / 4, d};
	obj->material.color = rgb;
	obj->material.shine = 1;
	obj->material.amb = 1;
	obj->material.dif = 1;
	obj->material.spec = 1;
	obj->translation = xyz;
	obj->axis = axis;
	obj->rotation.axis = vec_cross_prod(obj->axis, (t_vec){0, 0, 1});
	obj->rotation.angle = acos(vec_cosine(obj->axis, (t_vec){0, 0, 1}));
	return (obj);
}

t_obj	*obj_plane_create(t_vec xyz, t_vec rgb, t_vec axis)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	obj->shape = (t_shape){PLANE, axis, 0, 0, 0};
	obj->material.color = rgb;
	obj->material.shine = 1;
	obj->material.amb = 1;
	obj->material.dif = 1;
	obj->material.spec = 1;
	obj->translation = xyz;
	obj->axis = axis;
	obj->rotation.axis = vec_cross_prod(obj->axis, (t_vec){0, 0, 1});
	obj->rotation.angle = acos(vec_cosine(obj->axis, (t_vec){0, 0, 1}));
	return (obj);
}

t_obj	*obj_cone_create(t_vec xyz, t_vec rgb, t_vec axis, double d, double h)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	obj->shape = (t_shape){CONE, (t_vec){1, 1, -(d * d) / 4}, h, 0, d};
	obj->material.color = rgb;
	obj->material.shine = 1;
	obj->material.amb = 1;
	obj->material.dif = 1;
	obj->material.spec = 1;
	obj->translation = xyz;
	obj->axis = axis;
	obj->rotation.axis = vec_cross_prod(obj->axis, (t_vec){0, 0, 1});
	obj->rotation.angle = acos(vec_cosine(obj->axis, (t_vec){0, 0, 1}));
	return (obj);
}
