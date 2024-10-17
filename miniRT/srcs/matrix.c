/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:16:40 by ecorona-          #+#    #+#             */
/*   Updated: 2024/10/17 15:34:45 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// THESE FUNCTIOS SUCK:
// matrix_sub
// matrix_nil
// matrix_det_ret
// matrix_minor
// matrix_vector_product
// matrix_cofactor
//
// improve:
// matrix_scalar_product
// ray_sphere_intersect
// DO BETTER

#include "laag.h"

int	matrix_equals(t_matrix a, t_matrix b)
{
	int	i;

	i = 0;
	while (double_equals(((double *)a.matrix)[i], ((double *)b.matrix)[i]))
		if (++i == MATRIX_SIZE)
			return (1);
	return (0);
}

t_matrix	matrix_add(t_matrix a, t_matrix b)
{
	int			i;
	t_matrix	ret;

	i = 0;
	while (i < MATRIX_SIZE)
		((double *)ret.matrix)[i] = ((double *)a.matrix)[i] + ((double *)b.matrix)[i];
	return (ret);
}

t_matrix	matrix_subtract(t_matrix a, t_matrix b)
{
	int			i;
	t_matrix	ret;

	i = 0;
	while (i < MATRIX_SIZE)
		((double *)ret.matrix)[i] = ((double *)a.matrix)[i] - ((double *)b.matrix)[i];
	return (ret);
}

t_matrix	matrix_scalar_product(double a, t_matrix m)
{
	int			i;
	t_matrix	ret;

	ret = m;
	i = 0;
	while (i < MATRIX_SIZE)
	{
		((double *)ret.matrix)[i] *= a;
		i++;
	}
	return (ret);
}

t_matrix	matrix_product(t_matrix a, t_matrix b)
{
	int			row;
	int			col;
	int			idx;
	t_matrix	ret;

	ret = ((t_matrix){{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}});
	row = 0;
	while (row < MATRIX_LINE_SIZE)
	{
		col = 0;
		while (col < MATRIX_LINE_SIZE)
		{
			idx = 0;
			while (idx < MATRIX_LINE_SIZE)
			{
				ret.matrix[row][col] += a.matrix[row][idx] * b.matrix[idx][col]; 
				idx++;
			}
			col++;
		}
		row++;
	}
	return (ret);
}

t_vector	matrix_vector_product(t_matrix a, t_vector u)
{
	int			i;
	int			j;
	t_vector	ret;

	ret = (t_vector){0, 0, 0};
	i = 0;
	while (i < MATRIX_LINE_SIZE)
	{
		j = 0;
		while (j < MATRIX_LINE_SIZE)
		{
			((double *)&ret)[i] += a.matrix[i][j] * ((double *)&u)[j];
			j++;
		}
		i++;
	}
	return (ret);
}

t_matrix	matrix_transpose(t_matrix a)
{
	int			i;
	int			j;
	t_matrix	ret;

	i = 0;
	while (i < MATRIX_LINE_SIZE)
	{
		j = 0;
		while (j < MATRIX_LINE_SIZE)
		{
			ret.matrix[i][j] = a.matrix[j][i];
			j++;
		}
		i++;
	}
	return (ret);
}

double	matrix_determinant(t_matrix a)
{
	double	det;

	det = a.matrix[0][0] * a.matrix[1][1] * a.matrix[2][2];
	det += a.matrix[1][0] * a.matrix[2][1] * a.matrix[0][2];
	det += a.matrix[2][0] * a.matrix[0][1] * a.matrix[1][2];
	det -= a.matrix[0][0] * a.matrix[2][1] * a.matrix[1][2];
	det -= a.matrix[1][0] * a.matrix[0][1] * a.matrix[2][2];
	det -= a.matrix[2][0] * a.matrix[1][1] * a.matrix[0][2];
	return (det);
}

t_matrix	matrix_cofactor(t_matrix a)
{
	t_matrix	ret;
	double		*cof;
	int			i;

	cof = (double *)((t_matrix){{{1, -1, 1}, {-1, 1, -1}, {1, -1, 1}}}).matrix;
	i = 0;
	while (i < MATRIX_SIZE)
	{
		((double *)ret.matrix)[i] = cof[i] * ((double *)a.matrix)[i];
		i++;
	}
	return (ret);
}

static double	matrix_minor_aux(t_matrix a, int row, int col)
{
	double	det;
	int		i[2];
	int		j[2];
	
	i[0] = (row + 1) % MATRIX_LINE_SIZE;
	i[1] = (row + 2) % MATRIX_LINE_SIZE;
	j[0] = (col + 1) % MATRIX_LINE_SIZE;
	j[1] = (col + 2) % MATRIX_LINE_SIZE;
	det = a.matrix[i[0]][j[0]] * a.matrix[i[1]][j[1]];
	det -= a.matrix[i[0]][j[1]] * a.matrix[i[1]][j[0]];
	return (det);
}

t_matrix	matrix_minor(t_matrix a)
{
	t_matrix	ret;
	int			row;
	int			col;

	ret = ((t_matrix){{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}});
	row = 0;
	while (row < MATRIX_LINE_SIZE)
	{
		col = 0;
		while (col < MATRIX_LINE_SIZE)
		{
			ret.matrix[row][col] = matrix_minor_aux(a, row, col);
			col++;
		}
		row++;
	}
	return (ret);
}

// implementing the logic again rather then relying of other function
//   is an opportunity for a faster calculation
t_matrix	matrix_adjoint(t_matrix a)
{
	return (matrix_transpose(matrix_minor(a)));
}

t_matrix	matrix_inverse(t_matrix a)
{
	double	det;

	det = matrix_determinant(a);
	if (double_equals(det, 0))
		return ((t_matrix){{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}});
	return (matrix_scalar_product(1 / det, matrix_adjoint(a)));
}
