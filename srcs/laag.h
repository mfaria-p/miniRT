/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   laag.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:29:50 by ecorona-          #+#    #+#             */
/*   Updated: 2024/08/07 19:56:18 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAAG_H
# define LAAG_H

# include <math.h>

# define EPSILON 1e-10

typedef unsigned char	t_uint8;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct s_matrix
{
	t_uint8	rows;
	t_uint8	cols;
	float	*data;
}	t_matrix;

typedef struct s_quaternion
{
	float	w;
	float	i;
	float	j;
	float	k;
}	t_quaternion;

int			float_equals(float x, float y);
int			vector_equals(t_vector u, t_vector v);
t_vector	vector_scalar_product(float n, t_vector u);
t_vector	vector_add(t_vector u, t_vector v);
t_vector	vector_subtract(t_vector u, t_vector v);
float		vector_dot_product(t_vector u, t_vector v);
float		vector_magnitude(t_vector u);
float		vector_distance(t_vector u, t_vector v);
t_vector	vector_normalize(t_vector u);

#endif
