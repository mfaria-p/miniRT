/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:07:22 by ecorona-          #+#    #+#             */
/*   Updated: 2024/12/03 20:19:26 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	shape_sphere_create(void)
{
	t_shape	ret;

	ret = (t_shape){SPHERE, (t_vec){1, 1, 1}, 0, 1, 1};
	return (ret);
}

t_shape	shape_cylinder_create(void)
{
	t_shape	ret;

	ret = (t_shape){CYLINDER, (t_vec){1, 1, 0}, 1, 1, 1};
	return (ret);
}

t_shape	shape_plane_create(void)
{
	t_shape	ret;

	ret = (t_shape){PLANE, (t_vec){0, 0, 1}, 0, 0, 1};
	return (ret);
}

t_shape	shape_cone_create(void)
{
	t_shape	ret;

	ret = (t_shape){CONE, (t_vec){1, 1, -1}, 1, 0, 1};
	return (ret);
}

t_shape	*shape_scale(t_shape *shape, double scale)
{
	shape->scale = (double)1 / scale;
	if (shape->type == SPHERE || shape->type == CYLINDER)
		shape->constant = (double)1 / shape->scale;
	else if (shape->type == CONE)
		shape->coef.z = -(double)1 / shape->scale;
	else if (shape->type == PLANE)
		shape->scale = 1;
	return (shape);
}
