/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:59:01 by ecorona-          #+#    #+#             */
/*   Updated: 2024/11/05 22:10:50 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*object_sphere_create(t_vector xyz, t_vector rgb, double d)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	obj->shape = (t_shape){SPHERE, (t_vector){1, 1, 1}, {-1, 1}, 1, (double)1 / d};
	obj->material.color = rgb;
	obj->material.shine = 1;
	obj->material.ambient = 1;
	obj->material.diffuse = 1;
	obj->material.specular = 1;
	obj->translation = xyz;
	obj->rotation.axis = (t_vector){0, 0, 0};
	obj->rotation.angle = 0;
	return (obj);
}

t_object	*object_cylinder_create(t_vector xyz, t_vector rgb, t_vector axis, double d, double h)
{
	t_object	*obj;

	// (void)axis;
	// (void)h;
	obj = malloc(sizeof(t_object));
	obj->shape = (t_shape){CYLINDER, (t_vector){1, 1, 0}, {-h / 2, h / 2}, 1, (double)1 / d};
	obj->material.color = rgb;
	obj->material.shine = 1;
	obj->material.ambient = 1;
	obj->material.diffuse = 1;
	obj->material.specular = 1;
	obj->translation = xyz;
	obj->rotation.axis = vector_cross_product(axis, (t_vector){0, 0, 1});
	obj->rotation.angle = acos(vector_cosine(axis, (t_vector){0, 0, 1}));
	return (obj);
}

t_object	*object_plane_create(t_vector xyz, t_vector rgb, t_vector axis)
{
	t_object	*obj;

	// (void)axis;
	obj = malloc(sizeof(t_object));
	obj->shape = (t_shape){PLANE, axis, {0, 0}, 0, 0};
	obj->material.color = rgb;
	obj->material.shine = 1;
	obj->material.ambient = 1;
	obj->material.diffuse = 1;
	obj->material.specular = 1;
	obj->translation = xyz;
	obj->rotation.axis = vector_cross_product(axis, (t_vector){0, 0, 1});
	obj->rotation.angle = acos(vector_cosine(axis, (t_vector){0, 0, 1}));
	return (obj);
}

t_object	*object_cone_create(t_vector xyz, t_vector rgb, t_vector axis, double d, double h)
{
	t_object	*obj;

	// (void)axis;
	obj = malloc(sizeof(t_object));
	obj->shape = (t_shape){CONE, (t_vector){1, 1, -d}, {-h, 0}, 0, 1};
	obj->material.color = rgb;
	obj->material.shine = 1;
	obj->material.ambient = 1;
	obj->material.diffuse = 1;
	obj->material.specular = 1;
	obj->translation = xyz;
	obj->rotation.axis = vector_cross_product(axis, (t_vector){0, 0, 1});
	obj->rotation.angle = acos(vector_cosine(axis, (t_vector){0, 0, 1}));
	return (obj);
}
