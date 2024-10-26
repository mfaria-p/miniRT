/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:07:22 by ecorona-          #+#    #+#             */
/*   Updated: 2024/10/26 18:41:59 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	create_sphere(void)
{
	t_shape	ret = {SPHERE, (t_vector){1, 1, 1}, {-1, 1}, 1, 1};

	return (ret);
}

t_shape	create_cylinder(void)
{
	t_shape	ret = {CYLINDER, (t_vector){1, 1, 0}, {-1, 1}, 1, 1};

	return (ret);
}

t_shape	create_cone(void)
{
	t_shape	ret = {CONE, (t_vector){1, 1, -1}, {-1, 0}, 0, 1};

	return (ret);
}

// circle normal = {0, 0, 1}

t_vector	normal_at(t_vector p, t_object object)
{
	t_shape		shape;
	t_vector	normal;

	shape = object.shape;
	p = vector_subtract(p, object.translation);
	p = vector_rotate(p, object.rotation.axis, -object.rotation.angle);
	normal.x = 2 * shape.scale * shape.coefficients.x * p.x;
	normal.y = 2 * shape.scale * shape.coefficients.y * p.y;
	normal.z = 2 * shape.scale * shape.coefficients.z * p.z;
	normal = vector_add(p, object.translation);
	normal = vector_rotate(p, object.rotation.axis, object.rotation.angle);
	normal = vector_normalize(normal);
	return (normal);
}
