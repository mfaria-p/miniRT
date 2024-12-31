/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:12:06 by ecorona-          #+#    #+#             */
/*   Updated: 2024/12/03 20:13:26 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"

t_vec	mat_vec_prod(t_mat a, t_vec u)
{
	int		i;
	int		j;
	t_vec	ret;

	ret = (t_vec){0, 0, 0};
	i = 0;
	while (i < MATRIX_LINE_SIZE)
	{
		j = 0;
		while (j < MATRIX_LINE_SIZE)
		{
			((double *)&ret)[i] += a.mat[i][j] * ((double *)&u)[j];
			j++;
		}
		i++;
	}
	return (ret);
}

t_mat	mat_transpose(t_mat a)
{
	int		i;
	int		j;
	t_mat	ret;

	i = 0;
	while (i < MATRIX_LINE_SIZE)
	{
		j = 0;
		while (j < MATRIX_LINE_SIZE)
		{
			ret.mat[i][j] = a.mat[j][i];
			j++;
		}
		i++;
	}
	return (ret);
}

double	mat_determinant(t_mat a)
{
	double	det;

	det = a.mat[0][0] * a.mat[1][1] * a.mat[2][2];
	det += a.mat[1][0] * a.mat[2][1] * a.mat[0][2];
	det += a.mat[2][0] * a.mat[0][1] * a.mat[1][2];
	det -= a.mat[0][0] * a.mat[2][1] * a.mat[1][2];
	det -= a.mat[1][0] * a.mat[0][1] * a.mat[2][2];
	det -= a.mat[2][0] * a.mat[1][1] * a.mat[0][2];
	return (det);
}

t_mat	mat_cofactor(t_mat a)
{
	t_mat	ret;
	double	*cof;
	int		i;

	cof = (double *)((t_mat){{{1, -1, 1}, {-1, 1, -1}, {1, -1, 1}}}).mat;
	i = 0;
	while (i < MATRIX_SIZE)
	{
		((double *)ret.mat)[i] = cof[i] * ((double *)a.mat)[i];
		i++;
	}
	return (ret);
}
