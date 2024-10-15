/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:52:23 by ecorona-          #+#    #+#             */
/*   Updated: 2024/10/15 23:42:54 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	double_equals_00(void);
int	double_equals_01(void);
int	double_equals_02(void);
int	double_equals_03(void);
int	vector_equals_00(void);
int	vector_equals_01(void);
int	vector_scalar_product_00(void);
int	vector_scalar_product_01(void);
int	vector_scalar_product_02(void);
int	vector_add_00(void);
int	vector_add_01(void);
int	vector_subtract_00(void);
int	vector_subtract_01(void);
int	vector_dot_product_00(void);
int	vector_dot_product_01(void);
int	vector_magnitude_00(void);
int	vector_magnitude_01(void);
int	vector_distance_00(void);
int	vector_distance_01(void);
int	vector_normalize_00(void);
int	vector_normalize_01(void);
int	vector_cross_product_00(void);
int	vector_cross_product_01(void);
int	vector_cosine_00(void);
int	vector_cosine_01(void);
int	vector_scalar_projection_00(void);
int	vector_scalar_projection_01(void);
int	vector_projection_00(void);
int	vector_projection_01(void);
int	vector_projection_02(void);
int	vector_plane_projection_00(void);
int	vector_plane_projection_01(void);
int	vector_rotate_00(void);
int	matrix_equals_00(void);
int	matrix_equals_01(void);
int	matrix_equals_02(void);
int	matrix_scalar_product_00(void);
int	matrix_product_00(void);
int	matrix_product_01(void);
int	matrix_product_02(void);
int	matrix_vector_product_00(void);
int	matrix_vector_product_01(void);
int	matrix_vector_product_02(void);
int	matrix_vector_product_03(void);
int	matrix_transpose_00(void);
int	matrix_transpose_01(void);
int	matrix_transpose_02(void);
int	matrix_determinant_00(void);
int	matrix_determinant_01(void);
int	matrix_determinant_02(void);
int	matrix_determinant_03(void);
int	matrix_cofactor_00(void);
int	matrix_minor_00(void);
int	matrix_adjoint_00(void);
int	matrix_inverse_00(void);
int	matrix_inverse_01(void);
int	matrix_inverse_02(void);
int	quadratic_roots_00(void);
int	quadratic_roots_01(void);
int	quadratic_roots_02(void);
int	quadratic_roots_03(void);
int	quadratic_roots_04(void);
int	ray_position_00(void);
int	ray_position_01(void);
int	ray_position_02(void);
int	ray_sphere_intersect_00(void);
int	ray_sphere_intersect_01(void);
int	ray_sphere_intersect_02(void);
int	ray_sphere_intersect_03(void);
int	ray_sphere_intersect_04(void);

int	tests_run = 0;
suite	tests_laag = {
					double_equals_00, double_equals_01, double_equals_02, double_equals_03,
					vector_equals_00, vector_equals_01,
					vector_scalar_product_00, vector_scalar_product_01, vector_scalar_product_02,
					vector_add_00, vector_add_01,
					vector_subtract_00, vector_subtract_01,
					vector_dot_product_00, vector_dot_product_01,
					vector_magnitude_00, vector_magnitude_01,
					vector_distance_00, vector_distance_01,
					vector_normalize_00, vector_normalize_01,
					vector_cross_product_00, vector_cross_product_01,
					vector_cosine_00, vector_cosine_01,
					vector_scalar_projection_00, vector_scalar_projection_01,
					vector_projection_00, vector_projection_01, vector_projection_02,
					vector_plane_projection_00, vector_plane_projection_01,
					vector_rotate_00,
					matrix_equals_00, matrix_equals_01, matrix_equals_02,
					matrix_scalar_product_00,
					matrix_product_00, matrix_product_01, matrix_product_02,
					matrix_vector_product_00, matrix_vector_product_01, matrix_vector_product_02, matrix_vector_product_03,
					matrix_transpose_00, matrix_transpose_01, matrix_transpose_02,
					matrix_determinant_00, matrix_determinant_01, matrix_determinant_02, matrix_determinant_03,
					matrix_cofactor_00,
					matrix_minor_00,
					matrix_adjoint_00,
					matrix_inverse_00, matrix_inverse_01, matrix_inverse_02,
					NULL
				};

suite	tests_ray = {
					quadratic_roots_00, quadratic_roots_01, quadratic_roots_02, quadratic_roots_03, quadratic_roots_04,
					ray_position_00, ray_position_01, ray_position_02,
					ray_sphere_intersect_00, ray_sphere_intersect_01, ray_sphere_intersect_02, ray_sphere_intersect_03, ray_sphere_intersect_04,
					NULL
				};

t_vector	vector_print(t_vector v)
{
	printf("%f\t", v.x);
	printf("%f\t", v.y);
	printf("%f\t", v.z);
	printf("%f\t", v.w);
	printf("\n");
	return (v);
}

t_quaternion	quaternion_print(t_quaternion q)
{
	printf("%f\t", q.w);
	printf("%f\t", q.i);
	printf("%f\t", q.j);
	printf("%f\t", q.k);
	printf("\n");
	return (q);
}

t_matrix	matrix_print(t_matrix	m)
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		if (i % MATRIX_LINE_SIZE == 0)
			printf("\n");
		printf("%f\t", ((double *)m.matrix)[i]);
	}
	printf("\n");
	return (m);
}

int	double_equals_00(void)
{
	_ft_assert(double_equals(0, 1e-11));
	return (SUCCESS);
}

int	double_equals_01(void)
{
	_ft_assert(!double_equals(0, 1));
	return (SUCCESS);
}

int	double_equals_02(void)
{
	_ft_assert(!double_equals(1.001, 1.002));
	return (SUCCESS);
}

int	double_equals_03(void)
{
	_ft_assert(double_equals(1.00000000000000001, 1.00000000000000002));
	return (SUCCESS);
}

int	vector_equals_00(void)
{
	t_vector	u = {1, 8, 9, 1};

	_ft_assert(vector_equals(u,u));
	return (SUCCESS);
}

int	vector_equals_01(void)
{
	t_vector	u = {1, 2, 3, 1};
	t_vector	v = {1, 2, 1, 1};

	_ft_assert(!vector_equals(u,v));
	return (SUCCESS);
}

int	vector_scalar_product_00(void)
{
	t_vector	u = {3, 54, 2, 1};
	int			n = 7;
	t_vector	result = {n * 3, n * 54, n * 2, 1};

	_ft_assert(vector_equals(vector_scalar_product(n, u), result));
	return (SUCCESS);
}

int	vector_scalar_product_01(void)
{
	t_vector	u = {3, 54, 2, 1};
	int			n = 1;

	_ft_assert(vector_equals(vector_scalar_product(n, u), u));
	return (SUCCESS);
}

int	vector_scalar_product_02(void)
{
	t_vector	u = {3, 54, 2, 1};
	int			n = 0;

	_ft_assert(vector_equals(vector_scalar_product(n, u), (t_vector){0, 0, 0, 1}));
	return (SUCCESS);
}

int	vector_add_00(void)
{
	t_vector	u = {1, 3, 5, 1};
	t_vector	v = {5, 3, 1, 1};

	_ft_assert(vector_equals(vector_add(u, v), (t_vector){6, 6, 6, 1}));
	return (SUCCESS);
}

int	vector_add_01(void)
{
	t_vector	u = {-1, 3, -5, 1};
	t_vector	v = {5, 3, 1, 1};

	_ft_assert(vector_equals(vector_add(u, v), (t_vector){4, 6, -4, 1}));
	return (SUCCESS);
}

int	vector_subtract_00(void)
{
	t_vector	u = {-1, 3, -5, 1};
	t_vector	v = {5, 3, 1, 1};

	_ft_assert(vector_equals(vector_subtract(u, v), (t_vector){-6, 0, -6, 1}));
	return (SUCCESS);
}

int	vector_subtract_01(void)
{
	t_vector	u = {-1, 3, -5, 1};

	_ft_assert(vector_equals(vector_subtract(u, u), (t_vector){0, 0, 0, 1}));
	return (SUCCESS);
}

int	vector_dot_product_00(void)
{
	t_vector	u = {-1, 3, -5, 1};

	_ft_assert(vector_dot_product(u, u) == 35);
	return (SUCCESS);
}

int	vector_dot_product_01(void)
{
	t_vector	u = {1, 10, 2, 1};
	t_vector	v = {1, 10, 9, 1};

	_ft_assert(vector_dot_product(u, v) == 119);
	return (SUCCESS);
}

int	vector_magnitude_00(void)
{
	t_vector	u = {1, 1, 1, 1};

	_ft_assert(double_equals(vector_magnitude(u), sqrt(3)));
	return (SUCCESS);
}

int	vector_magnitude_01(void)
{
	t_vector u = {0, 0, 0, 1};

	_ft_assert(double_equals(vector_magnitude(u), 0));
	return (SUCCESS);
}

int	vector_distance_00(void)
{
	t_vector	u = {0, 0, 0, 1};
	t_vector	v = {0, 1, 1, 1};

	_ft_assert(double_equals(vector_distance(u, v), sqrt(2)));
	return (SUCCESS);
}

int	vector_distance_01(void)
{
	t_vector	u = {1, 0, 2, 1};

	_ft_assert(double_equals(vector_distance(u, u),0));
	return (SUCCESS);
}

int	vector_normalize_00(void)
{
	t_vector	u = {0, 0, 0, 1};
	
	_ft_assert(vector_equals(vector_normalize(u), (t_vector){0, 0, 0, 1}));
	return (SUCCESS);
}

int	vector_normalize_01(void)
{
	t_vector	u = {1, 1, 1, 1};
	
	_ft_assert(vector_equals(vector_normalize(u), (t_vector){1 / sqrt(3), 1 / sqrt(3), 1 / sqrt(3), 1}));
	return (SUCCESS);
}

int	vector_cross_product_00(void)
{
	t_vector	u = {1, 2, 3, 1};
	t_vector	v = {8, .5, 10, 1};

	_ft_assert(vector_equals(vector_cross_product(u, v), (t_vector){18.5, 14, -15.5, 1}));
	return (SUCCESS);
}

int	vector_cross_product_01(void)
{
	t_vector	u = {0, 0, 0, 1};
	t_vector	v = {6, 7, 3, 1};

	_ft_assert(vector_equals(vector_cross_product(u, v), (t_vector){0, 0, 0, 1}));
	return (SUCCESS);
}

int	vector_cosine_00(void)
{
	t_vector	u = {0, 0, 0, 1};

	_ft_assert(double_equals(vector_cosine(u, u), 0));
	return (SUCCESS);
}

int	vector_cosine_01(void)
{
	t_vector	u = {1, 1, 0, 1};
	t_vector	v = {0, 1, 0, 1};

	_ft_assert(double_equals(vector_cosine(u, v), .5 * sqrt(2)));
	return (SUCCESS);
}

int	vector_scalar_projection_00(void)
{
	t_vector	u = {1, 3, 1, 1};
	t_vector	v = {0, .5, 0, 1};

	_ft_assert(double_equals(vector_scalar_projection(u, v), 3));
	return (SUCCESS);
}

int	vector_scalar_projection_01(void)
{
	t_vector	u = {1, 3, 1, 1};
	t_vector	v = {0, .5, 0, 1};

	_ft_assert(double_equals(vector_scalar_projection(v, u), 0.452267016866645));
	return (SUCCESS);
}

int	vector_projection_00(void)
{
	t_vector	u = {0, 0, 0, 1};
	t_vector	v = {0, 0, 0, 1};

	_ft_assert(vector_equals(vector_projection(u, v), (t_vector){0, 0, 0, 1}));
	return (SUCCESS);
}

int	vector_projection_01(void)
{
	t_vector	u = {1, 3, 5, 1};
	t_vector	v = {0, 0, 0, 1};

	_ft_assert(vector_equals(vector_projection(u, v), (t_vector){0, 0, 0, 1}));
	return (SUCCESS);
}

int	vector_projection_02(void)
{
	t_vector	u = {1, 3, 5, 1};
	t_vector	v = {0, 0, .1, 1};

	_ft_assert(vector_equals(vector_projection(u, v), (t_vector){0, 0, 5, 1}));
	return (SUCCESS);
}

int	vector_plane_projection_00(void)
{
	t_vector	u = {1, 3, 5, 1};
	t_vector	n = {0, 1, 0, 1};

	_ft_assert(vector_equals(vector_plane_projection(u, n), (t_vector){1, 0, 5, 1}));
	return (SUCCESS);
}

int	vector_plane_projection_01(void)
{
	t_vector	u = {1, 3, 5, 1};
	t_vector	n = {0, .5, 2, 1};

	_ft_assert(vector_equals(vector_plane_projection(u, n), (t_vector){1, 1.64705882353, -0.41176470588, 1}));
	return (SUCCESS);
}

int	vector_rotate_00(void)
{
	t_vector	u = {1, 1, 1, 1};
	t_vector	ax = {-1, 1, 0, 1};

	_ft_assert(vector_equals(vector_rotate(u, ax, M_PI), (t_vector){-1, -1, -1, 1}));
	return (SUCCESS);
}

int	matrix_equals_00(void)
{
	t_matrix	m = {{{1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}}};

	_ft_assert(matrix_equals(m, m));
	return (SUCCESS);
}

int	matrix_equals_01(void)
{
	t_matrix	m = {{{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {0, 0, 0, 1}}};
	t_matrix	n = {{{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 3, 1, 1}, {0, 0, 0, 1}}};

	_ft_assert(!matrix_equals(m, n));
	return (SUCCESS);
}

int	matrix_equals_02(void)
{
	_ft_assert(matrix_equals(matrix_identity(), matrix_identity()));
	return (SUCCESS);
}

int	matrix_scalar_product_00(void)
{
	t_matrix	m = {{{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {0, 0, 0, 1}}};
	t_matrix	n = {{{3, 3, 3, 3}, {3, 3, 3, 3}, {3, 3, 3, 3}, {0, 0, 0, 3}}};

	_ft_assert(matrix_equals(matrix_scalar_product(3, m), n));
	return (SUCCESS);
}

int	matrix_product_00(void)
{
	t_matrix	m = {{{1, 1, -1, 1}, {.1, .5, 1.9, 2}, {100, 0, 0, 1}, {0, 0, 0, 1}}};
	t_matrix	n = {{{-1, 1, -1, 1}, {-.2, .5, -1.9, 2}, {0, 0, -100, 1}, {0, 0, 0, 1}}};
	t_matrix	w = {{{-1.2, 1.5, 97.1, 3}, {-.2, .35, -191.05, 5}, {-100, 100, -100, 101}, {0, 0, 0, 1}}};

	_ft_assert(matrix_equals(matrix_product(m, n), w));
	return (SUCCESS);
}

int	matrix_product_01(void)
{
	t_matrix	m = {{{-1.2, 1.5, 97.1, 1}, {-.2, .35, -191.05, 1}, {-100, 100, -100, 1}, {0, 0, 0, 1}}};

	_ft_assert(matrix_equals(matrix_product(matrix_identity(), m), m));
	return (SUCCESS);
}

int	matrix_product_02(void)
{
	t_matrix	m = {{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 1}}};
	t_matrix	n = {{{-1.2, 1.5, 97.1, 1}, {-.2, .35, -191.05, 1}, {-100, 100, -100, 1}, {0, 0, 0, 1}}};

	_ft_assert(matrix_equals(matrix_product(m, n), m));
	return (SUCCESS);
}

int	matrix_vector_product_00(void)
{
	t_vector	u = {.655, 0, 101, 1};

	_ft_assert(vector_equals(matrix_vector_product(matrix_identity(), u), u));
	return (SUCCESS);
}

int	matrix_vector_product_01(void)
{
	t_matrix	m = {{{1, 1, -1, 1}, {.1, .5, 1.9, 1}, {100, 0, 0, 1}, {0, 0, 0, 1}}};
	t_vector	u = {.655, 0, 101, 1};
	t_vector	v = {-99.345, 192.9655, 66.5, 1};

	_ft_assert(vector_equals(matrix_vector_product(m, u), v));
	return (SUCCESS);
}

int	matrix_vector_product_02(void)
{
	t_matrix	m = {{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 1}}};
	t_vector	u = {.655, 0, 101, 1};
	t_vector	v = {0, 0, 0, 1};

	_ft_assert(vector_equals(matrix_vector_product(m, u), v));
	return (SUCCESS);
}

int	matrix_vector_product_03(void)
{
	t_matrix	m = {{{1, 1, -1, 1}, {.1, .5, 1.9, 1}, {100, 0, 0, 1}, {0, 0, 0, 1}}};
	t_vector	u = {0, 0, 0, 1};
	t_vector	v = {1, 1, 1, 1};

	_ft_assert(vector_equals(matrix_vector_product(m, u), v));
	return (SUCCESS);
}

int	matrix_transpose_00(void)
{
	_ft_assert(matrix_equals(matrix_transpose(matrix_identity()), matrix_identity()));
	return (SUCCESS);
}

int	matrix_transpose_01(void)
{
	t_matrix	m = {{{1, 2, 3, 1}, {4, 5, 6, 1}, {7, 8, 9, 1}, {0, 0, 0, 1}}};
	t_matrix	n = {{{1, 4, 7, 0}, {2, 5, 8, 0}, {3, 6, 9, 0}, {1, 1, 1, 1}}};

	_ft_assert(matrix_equals(matrix_transpose(m), n));
	return (SUCCESS);
}

int	matrix_transpose_02(void)
{
	t_matrix	m = {{{1, 2, 3, 1}, {4, 5, 6, 1}, {7, 8, 9, 1}, {0, 0, 0, 1}}};
	t_matrix	n = {{{1, 4, 7, 0}, {2, 5, 8, 0}, {3, 6, 9, 0}, {1, 1, 1, 1}}};

	_ft_assert(matrix_equals(matrix_transpose(n), m));
	return (SUCCESS);
}

int	matrix_determinant_00(void)
{
	t_matrix	m = {{{3, .7, 7, 1}, {12, .1, 1, 1}, {3, 3, -4, 1}, {0, 0, 0, 1}}};

	_ft_assert(double_equals(matrix_determinant(m), 275.4));
	return (SUCCESS);
}

int	matrix_determinant_01(void)
{
	t_matrix	m = {{{0, 0, 0, 0}, {12, .1, 1, 1}, {3, 3, -4, 1}, {2, 2, 2, 2}}};

	_ft_assert(double_equals(matrix_determinant(m), 0));
	return (SUCCESS);
}

int	matrix_determinant_02(void)
{
	t_matrix	m = {{{0, 3, 4, 1}, {0, .1, 1, 2}, {0, 3, -4, 1}, {0, 0, 0, 1}}};

	_ft_assert(double_equals(matrix_determinant(m), 0));
	return (SUCCESS);
}

int	matrix_determinant_03(void)
{
	t_matrix	m = {{{1, 0, 3, 1}, {0, .1, 1, 1}, {-3, -3, 0, 1}, {0, 0, 0, 1}}};

	_ft_assert(double_equals(matrix_determinant(m), 3.9));
	return (SUCCESS);
}

int	matrix_cofactor_00(void)
{
	t_matrix	m = {{{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}}};
	t_matrix	n = {{{1, -1, 1, -1}, {-1, 1, -1, 1}, {1, -1, 1, -1}, {-1, 1, -1, 1}}};

	_ft_assert(matrix_equals(matrix_cofactor(m), n));
	return (SUCCESS);
}

int	matrix_minor_00(void)
{
	t_matrix	m = {{{-1.2, 1.5, 97.1, 1}, {.2, .35, -191.05, 1}, {-100, 100, -100, 1}, {0, 0, 0, 1}}};
	t_matrix	n = {{{19070, -19125, 55, 0}, {-9860, 9830, 30, 0}, {-320.56, 209.84, -.72, 0}, {28609.44, -28745.16, 24.28, 11144}}};

	_ft_assert(matrix_equals(matrix_minor(m), n));
	return (SUCCESS);
}

int	matrix_adjoint_00(void)
{
	t_matrix	m = {{{-1.2, 1.5, 97.1, 1}, {.2, .35, -191.05, 1}, {-100, 100, -100, 1}, {0, 0, 0, 1}}};
	t_matrix	n = {{{19070, 9860, -320.56, -28609.44}, {19125, 9830, -209.84, -28745.16}, {55, -30, -.72, -24.28}, {0, 0, 0, 11144}}};

	_ft_assert(matrix_equals(matrix_adjoint(m), n));
	return (SUCCESS);
}

int	matrix_inverse_00(void)
{
	t_matrix	m = {{{-1.2, 1.5, 97.1, 1}, {-.2, .35, -191.05, 1}, {-100, 100, -100, 1}, {0, 0, 0, 1}}};
	t_matrix	n = {{{2.64861, 1.36944, -.04452, -3.97353}, {2.65069, 1.36527, -.03453, -3.98143}, {.00208, -.00416, -.00001, .0021}, {0, 0, 0, 1}}};

	_ft_assert(matrix_equals(matrix_inverse(m), n));
	return (SUCCESS);
}

int	matrix_inverse_01(void)
{
	t_matrix	m = {{{2.64861, 1.36944, -.04452, 1}, {2.65069, 1.36527, -.03453, 1}, {.00208, -.00416, -.00001, 1}, {0, 0, 0, 1}}};

	_ft_assert(matrix_equals(matrix_product(matrix_inverse(m), m), matrix_identity()));
	return (SUCCESS);
}

int	matrix_inverse_02(void)
{
	t_matrix	m = {{{0, 1, -.04, 1}, {2.6, 1.3, 0, 1}, {.002, 0, -.2, 1}, {0, 0, 0, 1}}};
	t_matrix	n = {{{-.49990, .38454, .09998, .01538}, {.99980, .00015, -.19996, -.79999}, {-.004999, .00385, -4.999, 5.00015}, {0, 0, 0, 1}}};

	_ft_assert(matrix_equals(matrix_inverse(m), n));
	return (SUCCESS);
}

int	quadratic_roots_00(void)
{
	t_roots	xs;

	xs = quadratic_roots(0, 2, 2);
	_ft_assert(xs.count == 0);
	return (SUCCESS);
}

int	quadratic_roots_01(void)
{
	t_roots	xs;

	xs = quadratic_roots(4.5, 3, 7);
	_ft_assert(xs.count == 0);
	return (SUCCESS);
}

int	quadratic_roots_02(void)
{
	t_roots	xs;

	xs = quadratic_roots(4.5, 3, 0);
	_ft_assert(xs.count == 2 && double_equals(xs.x1, -.66666) && double_equals(xs.x2, 0));
	return (SUCCESS);
}

int	quadratic_roots_03(void)
{
	t_roots	xs;

	xs = quadratic_roots(4.5, 10, 2);
	_ft_assert(xs.count == 2 && double_equals(xs.x1, -2) && double_equals(xs.x2, -.22222));
	return (SUCCESS);
}

int	quadratic_roots_04(void)
{
	t_roots	xs;

	xs = quadratic_roots(1, 0, 0);
	_ft_assert(xs.count == 1 && double_equals(xs.x1, 0) && double_equals(xs.x2, 0));
	return (SUCCESS);
}

int	ray_position_00(void)
{
	t_ray	ray = {{2, 3, 4, 1}, {1, 0, 0, 1}};

	_ft_assert(vector_equals(ray_position(ray, 0), ray.origin));
	return (SUCCESS);
}

int	ray_position_01(void)
{
	t_ray	ray = {{2, 3, 4, 1}, {1, 0, 0, 1}};

	_ft_assert(vector_equals(ray_position(ray, 1), (t_vector){3, 3, 4, 1}));
	return (SUCCESS);
}

int	ray_position_02(void)
{
	t_ray	ray = {{2, 3, 4, 1}, {1, 0, 0, 1}};

	_ft_assert(vector_equals(ray_position(ray, 2.5), (t_vector){4.5, 3, 4, 1}));
	return (SUCCESS);
}

int	ray_sphere_intersect_00(void)
{
	t_ray		ray = {{0, 0, -5, 1}, {0, 0, 1, 1}};
	t_sphere	shape = {{0, 0, 0, 1}, 1};
	t_object	sphere = {SPHERE, &shape, {{0, 0, 0, 1}, 0, 0, 0, 0}, matrix_identity()};
	t_roots		xs;

	xs = ray_sphere_intersect(ray, sphere);
	_ft_assert(xs.count == 2 && double_equals(xs.x1, 4) && double_equals(xs.x2, 6));
	return (SUCCESS);
}

int	ray_sphere_intersect_01(void)
{
	t_ray		ray = {{0, 1, -5, 1}, {0, 0, 1, 1}};
	t_sphere	shape = {{0, 0, 0, 1}, 1};
	t_object	sphere = {SPHERE, &shape, {{0, 0, 0, 1}, 0, 0, 0, 0}, matrix_identity()};
	t_roots		xs;

	xs = ray_sphere_intersect(ray, sphere);
	_ft_assert(xs.count == 1 && double_equals(xs.x1, 5) && double_equals(xs.x2, 5));
	return (SUCCESS);
}

int	ray_sphere_intersect_02(void)
{
	t_ray		ray = {{0, 2, -5, 1}, {0, 0, 1, 1}};
	t_sphere	shape = {{0, 0, 0, 1}, 1};
	t_object	sphere = {SPHERE, &shape, {{0, 0, 0, 1}, 0, 0, 0, 0}, matrix_identity()};
	t_roots		xs;

	xs = ray_sphere_intersect(ray, sphere);
	_ft_assert(xs.count == 0);
	return (SUCCESS);
}

int	ray_sphere_intersect_03(void)
{
	t_ray		ray = {{0, 0, 0, 1}, {0, 0, 1, 1}};
	t_sphere	shape = {{0, 0, 0, 1}, 1};
	t_object	sphere = {SPHERE, &shape, {{0, 0, 0, 1}, 0, 0, 0, 0}, matrix_identity()};
	t_roots		xs;

	xs = ray_sphere_intersect(ray, sphere);
	_ft_assert(xs.count == 2 && double_equals(xs.x1, -1) && double_equals(xs.x2, 1));
	return (SUCCESS);
}

int	ray_sphere_intersect_04(void)
{
	t_ray		ray = {{0, 0, 5, 1}, {0, 0, 1, 1}};
	t_sphere	shape = {{0, 0, 0, 1}, 1};
	t_object	sphere = {SPHERE, &shape, {{0, 0, 0, 1}, 0, 0, 0, 0}, matrix_identity()};
	t_roots		xs;

	xs = ray_sphere_intersect(ray, sphere);
	_ft_assert(xs.count == 2 && double_equals(xs.x1, -6) && double_equals(xs.x2, -4));
	return (SUCCESS);
}

int	unit_test_suite(suite tests)
{
	while (*tests)
		_ft_verify((*(tests++)));
	return (SUCCESS);
}

int	main(void)
{
	int	result;

	result = 0;
	result += unit_test_suite(tests_laag);
	result += unit_test_suite(tests_ray);
	if (result == 0)
		printf(GREEN"PASSED\n");
	printf(DFLT"Tests run: %d\n", tests_run);

	return (result);
}
