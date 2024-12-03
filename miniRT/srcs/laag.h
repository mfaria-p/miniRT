/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   laag.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:29:50 by ecorona-          #+#    #+#             */
/*   Updated: 2024/12/03 19:42:47 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAAG_H
# define LAAG_H

# include <math.h>
# include <stdlib.h>

// maximum absolute difference where doubles are considered equal
# define EPSILON 1e-4
# define MATRIX_SIZE 9
# define MATRIX_LINE_SIZE 3
# define VECTOR_SIZE 3

typedef unsigned char	t_uint8;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_mat
{
	double	mat[MATRIX_LINE_SIZE][MATRIX_LINE_SIZE];
}	t_mat;

typedef struct s_quat
{
	double	w;
	double	i;
	double	j;
	double	k;
}	t_quat;

/* ************************************************************************** */
// vec.c
int		double_equals(double x, double y);
int		vec_equals(t_vec u, t_vec v);
t_vec	vec_elem_prod(t_vec v, t_vec u);
t_vec	vec_scalar_prod(double n, t_vec u);
t_vec	vec_add(t_vec u, t_vec v);
t_vec	vec_subtract(t_vec u, t_vec v);
double	vec_dot_prod(t_vec u, t_vec v);
double	vec_magnitude(t_vec u);
double	vec_distance(t_vec u, t_vec v);
t_vec	vec_normalize(t_vec u);
t_vec	vec_cross_prod(t_vec u, t_vec v);
double	vec_cosine(t_vec u, t_vec v);
double	vec_scalar_projection(t_vec u, t_vec v);
t_vec	vec_projection(t_vec u, t_vec v);
t_vec	vec_plane_projection(t_vec u, t_vec n);
t_vec	vec_rotate(t_vec u, t_vec ax, double rad);

/* ************************************************************************** */
// quat.c
double	quat_smagnitude(t_quat q);
t_quat	quat_conjugate(t_quat q);
t_quat	quat_scalar_prod(double a, t_quat q);
t_quat	quat_inverse(t_quat q);
t_quat	quat_prod(t_quat q, t_quat p);

/* ************************************************************************** */
// mat.c
t_mat	mat_identity(void);
int		mat_equals(t_mat a, t_mat b);
t_mat	mat_add(t_mat a, t_mat b);
t_mat	mat_subtract(t_mat a, t_mat b);
t_mat	mat_scalar_prod(double a, t_mat m);
t_mat	mat_prod(t_mat a, t_mat b);
t_vec	mat_vec_prod(t_mat a, t_vec u);
t_mat	mat_transpose(t_mat a);
double	mat_determinant(t_mat a);
t_mat	mat_cofactor(t_mat a);
t_mat	mat_minor(t_mat a);
t_mat	mat_adjoint(t_mat a);
t_mat	mat_inverse(t_mat a);

#endif
