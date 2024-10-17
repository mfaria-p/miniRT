/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   laag.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:29:50 by ecorona-          #+#    #+#             */
/*   Updated: 2024/10/17 15:38:06 by ecorona-         ###   ########.fr       */
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

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_matrix
{
	double	matrix[MATRIX_LINE_SIZE][MATRIX_LINE_SIZE];
}	t_matrix;

typedef struct s_quaternion
{
	double	w;
	double	i;
	double	j;
	double	k;
}	t_quaternion;

/* ************************************************************************** */
// vector.c
int				double_equals(double x, double y);
int				vector_equals(t_vector u, t_vector v);
t_vector		vector_scalar_product(double n, t_vector u);
t_vector		vector_add(t_vector u, t_vector v);
t_vector		vector_subtract(t_vector u, t_vector v);
double			vector_dot_product(t_vector u, t_vector v);
double			vector_magnitude(t_vector u);
double			vector_distance(t_vector u, t_vector v);
t_vector		vector_normalize(t_vector u);
t_vector		vector_cross_product(t_vector u, t_vector v);
double			vector_cosine(t_vector u, t_vector v);
double			vector_scalar_projection(t_vector u, t_vector v);
t_vector		vector_projection(t_vector u, t_vector v);
t_vector		vector_plane_projection(t_vector u, t_vector n);
t_vector		vector_rotate(t_vector u, t_vector ax, double rad);

/* ************************************************************************** */
// quaternion.c
double			quaternion_smagnitude(t_quaternion q);
t_quaternion	quaternion_conjugate(t_quaternion q);
t_quaternion	quaternion_scalar_product(double a, t_quaternion q);
t_quaternion	quaternion_inverse(t_quaternion q);
t_quaternion	quaternion_product(t_quaternion q, t_quaternion p);

/* ************************************************************************** */
// matrix.c
t_matrix		matrix_identity(void);
int				matrix_equals(t_matrix a, t_matrix b);
t_matrix		matrix_add(t_matrix a, t_matrix b);
t_matrix		matrix_subtract(t_matrix a, t_matrix b);
t_matrix		matrix_scalar_product(double a, t_matrix m);
t_matrix		matrix_product(t_matrix a, t_matrix b);
t_vector		matrix_vector_product(t_matrix a, t_vector u);
t_matrix		matrix_transpose(t_matrix a);
double			matrix_determinant(t_matrix a);
t_matrix		matrix_cofactor(t_matrix a);
t_matrix		matrix_minor(t_matrix a);
t_matrix		matrix_adjoint(t_matrix a);
t_matrix		matrix_inverse(t_matrix a);

#endif
