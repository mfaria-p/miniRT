/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:07:22 by ecorona-          #+#    #+#             */
/*   Updated: 2024/10/18 20:53:52 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*typedef struct s_shape*/
/*{*/
/*	const struct	s_parameters*/
/*	{*/
/*		e_shape_type	type;*/
/*		t_vector		coefficients;*/
/*		t_vector		shift;*/
/*		double			constant;*/
/*	}					parameters;*/
/*	double				scale;*/
/*	t_matrix			transform;*/
/*}	t_shape;*/

t_shape	create_sphere(void)
{
	t_shape	ret = {{SPHERE, (t_vector){1,1,1}, (t_vector){0,0,0}, 1}, 1, (t_matrix){{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}}};

	return (ret);
}

t_shape	create_cylinder(void)
{
	t_shape	ret = {{CONE, (t_vector){1,1,0}, (t_vector){0,0,0}, 1}, 1, (t_matrix){{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}}};

	return (ret);
}

t_shape	create_cone(void)
{
	t_shape	ret = {{CONE, (t_vector){1,1,-1}, (t_vector){0,0,-1}, 0}, 1, (t_matrix){{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}}};

	return (ret);
}

t_vector	normal_at(t_vector p, t_object object)
{
	t_shape		shape;
	t_vector	normal;
	t_vector	aux;
	t_vector	n_xyz[3];

	shape = object.shape;
	p = vector_subtract(p, object.translation);
	p = vector_rotate(p, object.rotation.axis, -object.rotation.angle);
	aux = (t_vector){
		shape.parameters.coefficients.x * (shape.shear.matrix[0][0] * shape.scale * (p.x - shape.parameters.shift.x) + shape.shear.matrix[0][1] * p.y + shape.shear.matrix[0][2] * p.z),
		shape.parameters.coefficients.y * (shape.shear.matrix[1][0] * p.x + shape.shear.matrix[1][1] * shape.scale * (p.y - shape.parameters.shift.y) + shape.shear.matrix[1][2] * p.z),
		shape.parameters.coefficients.z * (shape.shear.matrix[2][0] * p.x + shape.shear.matrix[2][1] * p.y + shape.shear.matrix[2][2] * shape.scale * (p.z - shape.parameters.shift.z))
	};
	n_xyz[0] = (t_vector){shape.shear.matrix[0][0] * shape.scale, shape.shear.matrix[1][0], shape.shear.matrix[2][0]};
	n_xyz[1] = (t_vector){shape.shear.matrix[0][1], shape.shear.matrix[1][1] * shape.scale, shape.shear.matrix[2][1]};
	n_xyz[2] = (t_vector){shape.shear.matrix[0][2], shape.shear.matrix[1][2], shape.shear.matrix[2][2] * shape.scale};
	normal.x = 2 * vector_dot_product(n_xyz[0], aux);
	normal.y = 2 * vector_dot_product(n_xyz[1], aux);
	normal.z = 2 * vector_dot_product(n_xyz[2], aux);
	normal = vector_normalize(normal);
	return (normal);
}
