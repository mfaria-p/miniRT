/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:59:01 by ecorona-          #+#    #+#             */
/*   Updated: 2024/11/06 19:16:24 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*object_sphere_create(t_vector xyz, t_vector rgb, double d)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	obj->shape = (t_shape){SPHERE, (t_vector){1, 1, 1}, 0, (d * d) / 4, d};
	obj->material.color = rgb;
	obj->material.shine = 1;
	obj->material.ambient = 1;
	obj->material.diffuse = 1;
	obj->material.specular = 1;
	obj->translation = xyz;
	obj->rotation.axis = (t_vector){0, 0, 0};
	obj->rotation.angle = 0;
	obj->axis = (t_vector){0, 0, 0};
	return (obj);
}

t_object	*object_cylinder_create(t_vector xyz, t_vector rgb, t_vector axis, double d, double h)
{
	t_object	*obj;

	// (void)axis;
	// (void)h;
	obj = malloc(sizeof(t_object));
	obj->shape = (t_shape){CYLINDER, (t_vector){1, 1, 0}, h, (d * d) / 4, d};
	obj->material.color = rgb;
	obj->material.shine = 1;
	obj->material.ambient = 1;
	obj->material.diffuse = 1;
	obj->material.specular = 1;
	obj->translation = xyz;
	obj->axis = axis;
	obj->rotation.axis = vector_cross_product(obj->axis, (t_vector){0, 0, 1});
	obj->rotation.angle = acos(vector_cosine(obj->axis, (t_vector){0, 0, 1}));
	/*obj->rotation.axis = (t_vector){1, 0, 0};*/
	/*obj->rotation.angle = M_PI / 2 - 0.2;*/
	return (obj);
}

t_object	*object_plane_create(t_vector xyz, t_vector rgb, t_vector axis)
{
	t_object	*obj;

	// (void)axis;
	obj = malloc(sizeof(t_object));
	obj->shape = (t_shape){PLANE, axis, 0, 0, 0};
	obj->material.color = rgb;
	obj->material.shine = 1;
	obj->material.ambient = 1;
	obj->material.diffuse = 1;
	obj->material.specular = 1;
	obj->translation = xyz;
	obj->axis = axis;
	obj->rotation.axis = vector_cross_product(obj->axis, (t_vector){0, 0, 1});
	obj->rotation.angle = acos(vector_cosine(obj->axis, (t_vector){0, 0, 1}));
	return (obj);
}

t_object	*object_cone_create(t_vector xyz, t_vector rgb, t_vector axis, double d, double h)
{
	t_object	*obj;

	// (void)axis;
	obj = malloc(sizeof(t_object));
	obj->shape = (t_shape){CONE, (t_vector){1, 1, -(d * d) / 4}, h, 0, d};
	obj->material.color = rgb;
	obj->material.shine = 1;
	obj->material.ambient = 1;
	obj->material.diffuse = 1;
	obj->material.specular = 1;
	obj->translation = xyz;
	obj->axis = axis;
	obj->rotation.axis = vector_cross_product(obj->axis, (t_vector){0, 0, 1});
	obj->rotation.angle = acos(vector_cosine(obj->axis, (t_vector){0, 0, 1}));
	return (obj);
}

t_object	*object_height_new(t_object *obj, double height)
{
	if (obj->shape.type == CONE || obj->shape.type == CYLINDER)
		obj->shape.height = height;
	return (obj);
}

t_object	*object_coord_new(t_object *obj, t_vector coord)
{
	obj->translation = coord;
	return (obj);
}

t_object	*object_rot_new(t_object *obj, t_vector axis, double angle)
{
	obj->rotation.axis = axis;
	obj->rotation.angle = angle;
	return (obj);
}

t_object	*object_coef_new(t_object *obj, t_vector new_coef)
{
	obj->shape.coefficients = new_coef;
	return (obj);
}

t_object	*object_translate(t_object *obj, t_vector direction, double shift)
{
	obj->translation.x = obj->translation.x + shift * direction.x;
	obj->translation.y = obj->translation.y + shift * direction.y;
	obj->translation.z = obj->translation.z + shift * direction.z;
	return (obj);
}

t_object	*object_rotate(t_object *obj, t_vector axis, double angle)
{
	obj->axis = vector_rotate(obj->axis, axis, angle);
	obj->rotation.axis = vector_cross_product(obj->axis, (t_vector){0, 0, 1});
	obj->rotation.angle = acos(vector_cosine(obj->axis, (t_vector){0, 0, 1}));
	return (obj);
}

t_object	*object_scale(t_object *obj, double scale)
{
	if (obj->shape.type == PLANE)
		return (obj);
	obj->shape.scale *= scale;
	if(obj->shape.type == CONE)
		obj->shape.coefficients.z *= scale;
	else  if(obj->shape.type == SPHERE || obj->shape.type == CYLINDER)
		obj->shape.constant *= scale;
	return (obj);
}
