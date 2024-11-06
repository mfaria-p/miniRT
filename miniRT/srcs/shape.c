/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:07:22 by ecorona-          #+#    #+#             */
/*   Updated: 2024/11/06 09:32:21 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	shape_sphere_create(void)
{
	t_shape	ret = {SPHERE, (t_vector){1, 1, 1}, 0, 1, 1};

	return (ret);
}

t_shape	shape_cylinder_create(void)
{
	t_shape	ret = {CYLINDER, (t_vector){1, 1, 0}, 1, 1, 1};

	return (ret);
}

t_shape	shape_plane_create(void)
{
	t_shape	ret = {PLANE, (t_vector){0, 0, 1}, 0, 0, 1};

	return (ret);
}

t_shape	shape_cone_create(void)
{
	t_shape	ret = {CONE, (t_vector){1, 1, -1}, 1, 0, 1};

	return (ret);
}

t_shape	*shape_scale(t_shape *shape, double scale)
{
	shape->scale = (double)1 / scale;
	if (shape->type == SPHERE || shape->type == CYLINDER)
		shape->constant = (double)1 / shape->scale;
	else if (shape->type ==	CONE)
		shape->coefficients.z = -(double)1 / shape->scale;
	else if (shape->type == PLANE)
		shape->scale = 1;
	return (shape);
}

// circle normal = {0, 0, 1}

t_vector	normal_at(t_vector p, t_object object)
{
	t_shape		shape;
	t_vector	normal;

	if (object.shape.type == PLANE)
		return (object.shape.coefficients);
	shape = object.shape;
	p = vector_subtract(p, object.translation);
	p = vector_rotate(p, object.rotation.axis, -object.rotation.angle);
	normal.x = 2 * shape.coefficients.x * p.x;
	normal.y = 2 * shape.coefficients.y * p.y;
	normal.z = 2 * shape.coefficients.z * p.z;
	normal = vector_add(p, object.translation);
	normal = vector_rotate(p, object.rotation.axis, object.rotation.angle);
	normal = vector_normalize(normal);
	return (normal);
}
