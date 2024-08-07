/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   laag.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:29:50 by ecorona-          #+#    #+#             */
/*   Updated: 2024/08/07 15:27:47 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAAG_H
# define LAAG_H

#include "minirt.h"

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

#endif
