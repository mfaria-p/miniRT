/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:51:14 by ecorona-          #+#    #+#             */
/*   Updated: 2024/10/15 23:09:32 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	matrix_tranlate(float x, float y, float z)
{
	return ((t_matrix){{{0, 0, 0, x}, {0, 0, 0, y}, {0, 0, 0, z}, {0, 0, 0, 1}}});
}

t_matrix	matrix_scale(float x, float y, float z)
{
	return ((t_matrix){{{x, 0, 0, 0}, {0, y, 0, 0}, {0, 0, z, 0}, {0, 0, 0, 1}}});
}

t_matrix	matrix_shear(float x[2], float y[2], float z[2])
{
	return ((t_matrix){{{1, x[0], x[1], 0}, {y[0], 0, y[1], 0}, {z[0], z[1], 0, 0}, {0, 0, 0, 1}}});
}

t_matrix	matrix_rotate(float x, float y, float z)
{
	t_matrix	aux_x;
	t_matrix	aux_y;
	t_matrix	aux_z;

	aux_x = (t_matrix){{{1, 0, 0, 0}, {0, cosf(x), -sinf(x), 0}, {0, sinf(x), cosf(x), 0}, {0, 0, 0, 1}}};
	aux_y = (t_matrix){{{cosf(y), 0, sinf(y), 0}, {0, 1, 0, 0}, {-sinf(y), 0, cosf(y), 0}, {0, 0, 0, 1}}};
	aux_z = (t_matrix){{{cosf(z), -sinf(z), 0, 0}, {sinf(z), cosf(z), 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
	return (matrix_product(aux_z, matrix_product(aux_y, aux_x)));
}
