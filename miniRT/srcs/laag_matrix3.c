/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:12:47 by ecorona-          #+#    #+#             */
/*   Updated: 2024/12/03 20:13:24 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"

static double	mat_minor_aux(t_mat a, int row, int col)
{
	double	det;
	int		i[2];
	int		j[2];

	i[0] = (row + 1) % MATRIX_LINE_SIZE;
	i[1] = (row + 2) % MATRIX_LINE_SIZE;
	j[0] = (col + 1) % MATRIX_LINE_SIZE;
	j[1] = (col + 2) % MATRIX_LINE_SIZE;
	det = a.mat[i[0]][j[0]] * a.mat[i[1]][j[1]];
	det -= a.mat[i[0]][j[1]] * a.mat[i[1]][j[0]];
	return (det);
}

t_mat	mat_minor(t_mat a)
{
	t_mat	ret;
	int		row;
	int		col;

	ret = ((t_mat){{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}});
	row = 0;
	while (row < MATRIX_LINE_SIZE)
	{
		col = 0;
		while (col < MATRIX_LINE_SIZE)
		{
			ret.mat[row][col] = mat_minor_aux(a, row, col);
			col++;
		}
		row++;
	}
	return (ret);
}

// implementing the logic again rather then relying of other function
//   is an opportunity for a faster calculation
t_mat	mat_adjoint(t_mat a)
{
	return (mat_transpose(mat_minor(a)));
}

t_mat	mat_inverse(t_mat a)
{
	double	det;

	det = mat_determinant(a);
	if (double_equals(det, 0))
		return ((t_mat){{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}});
	return (mat_scalar_prod(1 / det, mat_adjoint(a)));
}
