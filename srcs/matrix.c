/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:16:40 by ecorona-          #+#    #+#             */
/*   Updated: 2024/08/08 23:27:52 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"

t_matrix	matrix_identity(void)
{
	return ((t_matrix){{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}});
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

	aux = (t_matrix){{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}};
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
	t_vector	aux;

	aux.x = a.matrix[0][0] * u.x + a.matrix[0][1] * u.y + a.matrix[0][2] * u.z;
	aux.y = a.matrix[1][0] * u.x + a.matrix[1][1] * u.y + a.matrix[1][2] * u.z;
	aux.z = a.matrix[2][0] * u.x + a.matrix[2][1] * u.y + a.matrix[2][2] * u.z;
	return (aux);
}
