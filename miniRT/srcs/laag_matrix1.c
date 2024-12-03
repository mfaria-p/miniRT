/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:16:40 by ecorona-          #+#    #+#             */
/*   Updated: 2024/12/03 20:13:11 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"

int	mat_equals(t_mat a, t_mat b)
{
	int	i;

	i = 0;
	while (double_equals(((double *)a.mat)[i], ((double *)b.mat)[i]))
		if (++i == MATRIX_SIZE)
			return (1);
	return (0);
}

t_mat	mat_add(t_mat a, t_mat b)
{
	int		i;
	t_mat	ret;

	i = 0;
	while (i < MATRIX_SIZE)
		((double *)ret.mat)[i] = ((double *)a.mat)[i] + ((double *)b.mat)[i];
	return (ret);
}

t_mat	mat_subtract(t_mat a, t_mat b)
{
	int		i;
	t_mat	ret;

	i = 0;
	while (i < MATRIX_SIZE)
		((double *)ret.mat)[i] = ((double *)a.mat)[i] - ((double *)b.mat)[i];
	return (ret);
}

t_mat	mat_scalar_prod(double a, t_mat m)
{
	int		i;
	t_mat	ret;

	ret = m;
	i = 0;
	while (i < MATRIX_SIZE)
	{
		((double *)ret.mat)[i] *= a;
		i++;
	}
	return (ret);
}

t_mat	mat_prod(t_mat a, t_mat b)
{
	int		row;
	int		col;
	int		idx;
	t_mat	ret;

	ret = ((t_mat){{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}});
	row = 0;
	while (row < MATRIX_LINE_SIZE)
	{
		col = 0;
		while (col < MATRIX_LINE_SIZE)
		{
			idx = 0;
			while (idx < MATRIX_LINE_SIZE)
			{
				ret.mat[row][col] += a.mat[row][idx] * b.mat[idx][col];
				idx++;
			}
			col++;
		}
		row++;
	}
	return (ret);
}
