/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:07:22 by ecorona-          #+#    #+#             */
/*   Updated: 2025/01/13 16:30:44 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	shape_sphere_create(void)
{
	t_shape	ret;

	ret = (t_shape){SPHERE, 0, 1, 1};
	return (ret);
}

t_shape	shape_cylinder_create(void)
{
	t_shape	ret;

	ret = (t_shape){CYLINDER, 1, 1, 1};
	return (ret);
}

t_shape	shape_plane_create(void)
{
	t_shape	ret;

	ret = (t_shape){PLANE, 0, 0, 0};
	return (ret);
}

t_shape	*shape_scale(t_shape *shape, double scale)
{
	if (shape->type == PLANE)
		shape->scale = 1;
	else
		shape->scale = scale;
	return (shape);
}
