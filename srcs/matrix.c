/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:16:40 by ecorona-          #+#    #+#             */
/*   Updated: 2024/08/11 17:43:42 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"

// return ((t_matrix){{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}});
t_matrix	matrix_identity(void)
{
	t_matrix	aux;
	int			i;
	int			j;

	i = 0;
	while (i < MATRIX_LINE_SIZE)
	{
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

// return ((t_matrix){{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}});
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

t_matrix	matrix_scalar_product(float a, t_matrix m)
{
	int			i;
	t_matrix	aux;

	aux = m;
	i = 0;
	while (i < MATRIX_SIZE)
	{
		((float *)aux.matrix)[i] *= a;
		i++;
	}
	return (aux);
}

t_matrix	matrix_add(t_matrix a, t_matrix b)
{
	int			i;
	t_matrix	aux;

	i = 0;
	while (i < MATRIX_SIZE)
	{
		((float *)aux.matrix)[i] = ((float *)a.matrix)[i] + ((float *)b.matrix)[i];
		i++;
	}
	return (aux);
}

t_matrix	matrix_subtract(t_matrix a, t_matrix b)
{
	int			i;
	t_matrix	aux;

	i = 0;
	while (i < MATRIX_SIZE)
	{
		((float *)aux.matrix)[i] = ((float *)a.matrix)[i] - ((float *)b.matrix)[i];
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

	aux = (t_vector){0, 0, 0};
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

float	matrix_determinant(t_matrix a)
{
	float	*aux;
	float	det;

	aux = (float *)a.matrix;
	det = aux[0] * aux[4] * aux[8] - aux[2] * aux[4] * aux[6];
	det += aux[3] * aux[7] * aux[2] - aux[5] * aux[7] * aux[0];
	det += aux[6] * aux[1] * aux[5] - aux[8] * aux[1] * aux[3];
	return (det);
}

t_matrix	matrix_cofactor(t_matrix a)
{
	t_matrix	aux;
	float		*cof;
	int			i;

	cof = (float *)((t_matrix){{{1, -1, 1}, {-1, 1, -1}, {1, -1, 1}}}.matrix);
	i = 0;
	while (i < MATRIX_SIZE)
	{
		((float *)aux.matrix)[i] = cof[i] * ((float *)a.matrix)[i];
		i++;
	}
	return (aux);
}

static float	matrix_minor_aux(t_matrix a, int row, int col)
{
	double	minor;
	int		r[2];
	int		c[2];
	int		temp;

	r[0] = (row + 1) % MATRIX_LINE_SIZE;
	r[1] = (row + 2) % MATRIX_LINE_SIZE;
	c[0] = (col + 1) % MATRIX_LINE_SIZE;
	c[1] = (col + 2) % MATRIX_LINE_SIZE;
	temp = c[0];
	c[0] = (temp < c[1]) * temp + (temp > c[1]) * c[1];
	c[1] = (temp > c[1]) * temp + (temp < c[1]) * c[1];
	temp = r[0];
	r[0] = (temp < r[1]) * temp + (temp > r[1]) * r[1];
	r[1] = (temp > r[1]) * temp + (temp < r[1]) * r[1];
	minor = a.matrix[r[0]][c[0]] * a.matrix[r[1]][c[1]];
	minor -= a.matrix[r[0]][c[1]] * a.matrix[r[1]][c[0]];
	return ((float)minor);
}

t_matrix	matrix_minor(t_matrix a)
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
			aux.matrix[i][j] = matrix_minor_aux(a, i, j);
			j++;
		}
		i++;
	}
	return (aux);
}

// implementing the logic again rather then relying of other function
//   is an opportunity for a faster calculation
t_matrix	matrix_adjoint(t_matrix a)
{
	return (matrix_transpose(matrix_cofactor(matrix_minor(a))));
}

t_matrix	matrix_inverse(t_matrix a)
{
	float	det;

	det = matrix_determinant(a);
	if (float_equals(det, 0))
		return ((t_matrix){{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}});
	return (matrix_scalar_product(1 / det, matrix_adjoint(a)));
}
