/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:16:40 by ecorona-          #+#    #+#             */
/*   Updated: 2024/10/15 14:28:21 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (i < MATRIX_LINE_SIZE)
		((float *)aux.matrix)[i++] = 0;
	return (aux);
}

int	matrix_equals(t_matrix a, t_matrix b)
{
	int		i;

	i = 0;
	while (float_equals(((float *)a.matrix)[i], ((float *)b.matrix)[i]))
		if (++i == MATRIX_SIZE)
			return (1);
	return (0);
}

/*t_matrix	matrix_scalar_product(float a, t_matrix m)*/
/*{*/
/*	int			i;*/
/*	t_matrix	aux;*/
/**/
/*	aux = m;*/
/*	i = 0;*/
/*	while (i < MATRIX_SIZE)*/
/*	{*/
/*		((float *)aux.matrix)[i] *= a;*/
/*		i++;*/
/*	}*/
/*	return (aux);*/
/*}*/

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

	aux = (t_vector){0, 0, 0, 1};
	i = 0;
	while (i < MATRIX_LINE_SIZE)
	{
		j = 0;
		while (j < MATRIX_LINE_SIZE)
		{
			((float *)&aux)[j] += a.matrix[i][j] * ((float *)&u)[j];
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

// submatrix -> minor -> cofactor -> determinant -> adjoint -> inverse
static t_submatrix	matrix_sub(t_submatrix a, int row, int col)
{
	int			idx[4];
	t_submatrix	ret;

	ret.m = matrix_nil();
	ret.size = a.size - 1;
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
			ret.m.matrix[idx[2]][idx[3]] = a.m.matrix[idx[0]][idx[1]];
			idx[1]++;
			idx[3]++;
		}
		idx[0]++;
		idx[2]++;
	}
	return (ret);
}

static int	matrix_cof(int row, int col)
{
	int	c;

	if (row % 2 == 0)
		c = 1;
	else
		c = -1;
	if (col % 2 == 1)
		c = -c;
	return (c);
}
// det(R^4) = sumprodut(e_i, cofactor(e_i)) for one line
static float	matrix_det_aux(t_submatrix a)
{
	int		i;
	int		row;
	int		col;
	float	det;

	det = 0;
	i = 0;
	if (a.size == 2)
		return (a.m.matrix[0][0] * a.m.matrix[1][1] - a.m.matrix[0][1] * a.m.matrix[1][0]);
	while (i < a.size)
	{
		row = i / MATRIX_LINE_SIZE;
		col = i % MATRIX_LINE_SIZE;
		det += ((float *)a.m.matrix)[i] * matrix_cof(row, col) * matrix_det_aux(matrix_sub((t_submatrix){a.m, a.size - 1}, row, col));
		i++;
	}
	return (det);
}

float	matrix_determinant(t_matrix a)
{
	return (matrix_det_aux((t_submatrix){a, MATRIX_LINE_SIZE}));
}

// implementing the logic again rather then relying of other function
//   is an opportunity for a faster calculation
/*t_matrix	matrix_adjoint(t_matrix a)*/
/*{*/
/*	return (matrix_transpose(matrix_cofactor(matrix_minor(a))));*/
/*}*/
/**/
/*t_matrix	matrix_inverse(t_matrix a)*/
/*{*/
/*	float	det;*/
/**/
/*	det = matrix_determinant(a);*/
/*	if (float_equals(det, 0))*/
/*		return ((t_matrix){{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}});*/
/*	return (matrix_scalar_product(1 / det, matrix_adjoint(a)));*/
/*}*/
