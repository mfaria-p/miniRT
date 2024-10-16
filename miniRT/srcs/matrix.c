/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:16:40 by ecorona-          #+#    #+#             */
/*   Updated: 2024/10/16 12:16:29 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// THESE FUNCTIOS SUCK:
// matrix_sub
// matrix_nil
// matrix_det_aux
// matrix_minor
// matrix_vector_product
// matrix_cofactor
//
// improve:
// matrix_scalar_product
// ray_sphere_intersect
// DO BETTER

#include "laag.h"

// return ((t_matrix){{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}}});
t_matrix	matrix_identity(void)
{
	t_matrix	aux;
	int			i;
	int			j;

	i = 0;
	while (i < MATRIX_LINE_SIZE)
	{
		j = 0;
		while (j < MATRIX_LINE_SIZE)
		{
			if (i == j)
				aux.matrix[i][j] = 1;
			else
				aux.matrix[i][j] = 0;
			j++;
		}
		i++;
	}
	return (aux);
}

// return ((t_matrix){{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}});
t_matrix	matrix_nil(void)
{
	t_matrix	aux;
	int			i;

	i = 0;
	while (i < MATRIX_SIZE)
		((double *)aux.matrix)[i++] = 0;
	return (aux);
}

int	matrix_equals(t_matrix a, t_matrix b)
{
	int		i;

	i = 0;
	while (double_equals(((double *)a.matrix)[i], ((double *)b.matrix)[i]))
		if (++i == MATRIX_SIZE)
			return (1);
	return (0);
}

t_matrix	matrix_scalar_product(double a, t_matrix m)
{
	int			i;
	t_matrix	aux;

	aux = m;
	i = 0;
	while (i < MATRIX_SIZE)
	{
		((double *)aux.matrix)[i] *= a;
		i++;
	}
	return (aux);
}

t_matrix	matrix_product(t_matrix a, t_matrix b)
{
	int			row;
	int			col;
	int			idx;
	t_matrix	aux;

	aux = matrix_nil();
	row = 0;
	while (row < MATRIX_LINE_SIZE)
	{
		col = 0;
		while (col < MATRIX_LINE_SIZE)
		{
			idx = 0;
			while (idx < MATRIX_LINE_SIZE)
			{
				aux.matrix[row][col] += a.matrix[row][idx] * b.matrix[idx][col]; 
				idx++;
			}
			col++;
		}
		row++;
	}
	return (aux);
}

t_vector	matrix_vector_product(t_matrix a, t_vector u)
{
	int			i;
	int			j;
	t_vector	aux;

	aux = (t_vector){0, 0, 0, 0};
	i = 0;
	while (i < MATRIX_LINE_SIZE)
	{
		j = 0;
		while (j < MATRIX_LINE_SIZE)
		{
			((double *)&aux)[i] += a.matrix[i][j] * ((double *)&u)[j];
			j++;
		}
		i++;
	}
	return (aux);
}

t_matrix	matrix_transpose(t_matrix a)
{
	int			i;
	int			j;
	t_matrix	aux;

	i = 0;
	while (i < MATRIX_LINE_SIZE)
	{
		j = 0;
		while (j < MATRIX_LINE_SIZE)
		{
			aux.matrix[i][j] = a.matrix[j][i];
			j++;
		}
		i++;
	}
	return (aux);
}

static t_submatrix	matrix_sub(t_submatrix a, int row, int col)
{
	int			idx[4];
	t_submatrix	aux;

	aux.m = matrix_nil();
	aux.size = a.size - 1;
	idx[0] = 0;
	idx[2] = 0;
	while (idx[0] < a.size)
	{
		if (idx[0] == row)
			idx[0]++;
		idx[1] = 0;
		idx[3] = 0;
		while (idx[1] < a.size)
		{
			if (idx[1] == col)
				idx[1]++;
			aux.m.matrix[idx[2]][idx[3]] = a.m.matrix[idx[0]][idx[1]];
			idx[1]++;
			idx[3]++;
		}
		idx[0]++;
		idx[2]++;
	}
	return (aux);
}

static double	matrix_det_aux(t_submatrix a)
{
	int		i;
	int		c;
	double	det;

	det = 0;
	i = 0;
	if (a.size == 2)
		return (a.m.matrix[0][0] * a.m.matrix[1][1] - a.m.matrix[0][1] * a.m.matrix[1][0]);
	c = 1;
	while (i < a.size)
	{
		c = -c;
		if (((double *)a.m.matrix)[i])
			det += ((double *)a.m.matrix)[i] * c * matrix_det_aux(matrix_sub(a, 0, i));
		i++;
	}
	return (det);
}

double	matrix_determinant(t_matrix a)
{
	return (matrix_det_aux((t_submatrix){a, MATRIX_LINE_SIZE}));
}

t_matrix	matrix_cofactor(t_matrix a)
{
	t_matrix	aux;
	double		*cof;
	int			i;

	cof = (double *)((t_matrix){{{1, -1, 1, -1}, {-1, 1, -1, 1}, {1, -1, 1, -1}, {-1, 1, -1, 1}}}.matrix);
	i = 0;
	while (i < MATRIX_SIZE)
	{
		((double *)aux.matrix)[i] = cof[i] * ((double *)a.matrix)[i];
		i++;
	}
	return (aux);
}

t_matrix	matrix_minor(t_matrix a)
{
	t_matrix	ret;
	t_submatrix	aux;
	int			row;
	int			col;

	ret = matrix_nil();
	aux = (t_submatrix){a, MATRIX_LINE_SIZE};
	row = 0;
	while (row < MATRIX_LINE_SIZE)
	{
		col = 0;
		while (col < MATRIX_LINE_SIZE)
		{
			ret.matrix[row][col] = -matrix_det_aux(matrix_sub(aux, row, col));
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
	return (matrix_transpose(matrix_cofactor(matrix_minor(a))));
}

t_matrix	matrix_inverse(t_matrix a)
{
	double	det;

	det = matrix_determinant(a);
	if (double_equals(det, 0))
		return ((t_matrix){{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}});
	return (matrix_scalar_product(1 / det, matrix_adjoint(a)));
}
