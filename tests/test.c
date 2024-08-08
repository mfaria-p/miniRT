/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:52:23 by ecorona-          #+#    #+#             */
/*   Updated: 2024/08/08 23:37:29 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	float_equals_00(void);
int	float_equals_01(void);
int	float_equals_02(void);
int	float_equals_03(void);
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
int	matrix_add_00(void);
int	matrix_subtract_00(void);
int	matrix_product_00(void);
int	matrix_product_01(void);
int	matrix_product_02(void);
int	matrix_vector_product_00(void);
int	matrix_vector_product_01(void);
int	matrix_vector_product_02(void);
int	matrix_vector_product_03(void);

int	tests_run = 0;
suite	tests_laag = {
					float_equals_00, float_equals_01, float_equals_02, float_equals_03,
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
					matrix_add_00,
					matrix_subtract_00,
					matrix_product_00, matrix_product_01, matrix_product_02,
					matrix_vector_product_00, matrix_vector_product_01, matrix_vector_product_02, matrix_vector_product_03,
					NULL
				};

t_vector	vector_print(t_vector v)
{
	printf("%f\t", v.x);
	printf("%f\t", v.y);
	printf("%f\t", v.z);
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
		if (i % 3 == 0)
			printf("\n");
		printf("%f\t", ((float *)m.matrix)[i]);
	}
	printf("\n");
	return (m);
}

int	float_equals_00(void)
{
	_ft_assert(float_equals(0, 1e-11));
	return (SUCCESS);
}

int	float_equals_01(void)
{
	_ft_assert(!float_equals(0, 1));
	return (SUCCESS);
}

int	float_equals_02(void)
{
	_ft_assert(!float_equals(1.001, 1.002));
	return (SUCCESS);
}

int	float_equals_03(void)
{
	_ft_assert(float_equals(1.00000000000000001, 1.00000000000000002));
	return (SUCCESS);
}

int	vector_equals_00(void)
{
	t_vector	u = {1, 8, 9};

	_ft_assert(vector_equals(u,u));
	return (SUCCESS);
}

int	vector_equals_01(void)
{
	t_vector	u = {1, 2, 3};
	t_vector	v = {1, 2, 1};

	_ft_assert(!vector_equals(u,v));
	return (SUCCESS);
}

int	vector_scalar_product_00(void)
{
	t_vector	u = {3, 54, 2};
	int			n = 7;
	t_vector	result = {n * 3, n * 54, n * 2};

	_ft_assert(vector_equals(vector_scalar_product(n, u), result));
	return (SUCCESS);
}

int	vector_scalar_product_01(void)
{
	t_vector	u = {3, 54, 2};
	int			n = 1;

	_ft_assert(vector_equals(vector_scalar_product(n, u), u));
	return (SUCCESS);
}

int	vector_scalar_product_02(void)
{
	t_vector	u = {3, 54, 2};
	int			n = 0;

	_ft_assert(vector_equals(vector_scalar_product(n, u), (t_vector){0, 0, 0}));
	return (SUCCESS);
}

int	vector_add_00(void)
{
	t_vector	u = {1, 3, 5};
	t_vector	v = {5, 3, 1};

	_ft_assert(vector_equals(vector_add(u, v), (t_vector){6, 6, 6}));
	return (SUCCESS);
}

int	vector_add_01(void)
{
	t_vector	u = {-1, 3, -5};
	t_vector	v = {5, 3, 1};

	_ft_assert(vector_equals(vector_add(u, v), (t_vector){4, 6, -4}));
	return (SUCCESS);
}

int	vector_subtract_00(void)
{
	t_vector	u = {-1, 3, -5};
	t_vector	v = {5, 3, 1};

	_ft_assert(vector_equals(vector_subtract(u, v), (t_vector){-6, 0, -6}));
	return (SUCCESS);
}

int	vector_subtract_01(void)
{
	t_vector	u = {-1, 3, -5};

	_ft_assert(vector_equals(vector_subtract(u, u), (t_vector){0, 0, 0}));
	return (SUCCESS);
}

int	vector_dot_product_00(void)
{
	t_vector	u = {-1, 3, -5};

	_ft_assert(vector_dot_product(u, u) == 35);
	return (SUCCESS);
}

int	vector_dot_product_01(void)
{
	t_vector	u = {1, 10, 2};
	t_vector	v = {1, 10, 9};

	_ft_assert(vector_dot_product(u, v) == 119);
	return (SUCCESS);
}

int	vector_magnitude_00(void)
{
	t_vector	u = {1, 1, 1};

	_ft_assert(float_equals(vector_magnitude(u), sqrt(3)));
	return (SUCCESS);
}

int	vector_magnitude_01(void)
{
	t_vector u = {0, 0, 0};

	_ft_assert(float_equals(vector_magnitude(u), 0));
	return (SUCCESS);
}

int	vector_distance_00(void)
{
	t_vector	u = {0, 0, 0};
	t_vector	v = {0, 1, 1};

	_ft_assert(float_equals(vector_distance(u, v), sqrt(2)));
	return (SUCCESS);
}

int	vector_distance_01(void)
{
	t_vector	u = {1, 0, 2};

	_ft_assert(float_equals(vector_distance(u, u),0));
	return (SUCCESS);
}

int	vector_normalize_00(void)
{
	t_vector	u = {0, 0, 0};
	
	_ft_assert(vector_equals(vector_normalize(u), (t_vector){0, 0, 0}));
	return (SUCCESS);
}

int	vector_normalize_01(void)
{
	t_vector	u = {1, 1, 1};
	
	_ft_assert(vector_equals(vector_normalize(u), (t_vector){1 / sqrt(3), 1 / sqrt(3), 1 / sqrt(3)}));
	return (SUCCESS);
}

int	vector_cross_product_00(void)
{
	t_vector	u = {1, 2, 3};
	t_vector	v = {8, .5, 10};

	_ft_assert(vector_equals(vector_cross_product(u, v), (t_vector){18.5, 14, -15.5}));
	return (SUCCESS);
}

int	vector_cross_product_01(void)
{
	t_vector	u = {0, 0, 0};
	t_vector	v = {6, 7, 3};

	_ft_assert(vector_equals(vector_cross_product(u, v), (t_vector){0, 0, 0}));
	return (SUCCESS);
}

int	vector_cosine_00(void)
{
	t_vector	u = {0, 0, 0};

	_ft_assert(float_equals(vector_cosine(u, u), 0));
	return (SUCCESS);
}

int	vector_cosine_01(void)
{
	t_vector	u = {1, 1, 0};
	t_vector	v = {0, 1, 0};

	_ft_assert(float_equals(vector_cosine(u, v), .5 * sqrt(2)));
	return (SUCCESS);
}

int	vector_scalar_projection_00(void)
{
	t_vector	u = {1, 3, 1};
	t_vector	v = {0, .5, 0};

	_ft_assert(float_equals(vector_scalar_projection(u, v), 3));
	return (SUCCESS);
}

int	vector_scalar_projection_01(void)
{
	t_vector	u = {1, 3, 1};
	t_vector	v = {0, .5, 0};

	_ft_assert(float_equals(vector_scalar_projection(v, u), 0.452267016866645));
	return (SUCCESS);
}

int	vector_projection_00(void)
{
	t_vector	u = {0, 0, 0};
	t_vector	v = {0, 0, 0};

	_ft_assert(vector_equals(vector_projection(u, v), (t_vector){0, 0, 0}));
	return (SUCCESS);
}

int	vector_projection_01(void)
{
	t_vector	u = {1, 3, 5};
	t_vector	v = {0, 0, 0};

	_ft_assert(vector_equals(vector_projection(u, v), (t_vector){0, 0, 0}));
	return (SUCCESS);
}

int	vector_projection_02(void)
{
	t_vector	u = {1, 3, 5};
	t_vector	v = {0, 0, .1};

	_ft_assert(vector_equals(vector_projection(u, v), (t_vector){0, 0, 5}));
	return (SUCCESS);
}

int	vector_plane_projection_00(void)
{
	t_vector	u = {1, 3, 5};
	t_vector	n = {0, 1, 0};

	_ft_assert(vector_equals(vector_plane_projection(u, n), (t_vector){1, 0, 5}));
	return (SUCCESS);
}

int	vector_plane_projection_01(void)
{
	t_vector	u = {1, 3, 5};
	t_vector	n = {0, .5, 2};

	_ft_assert(vector_equals(vector_plane_projection(u, n), (t_vector){1, 1.64705882353, -0.41176470588}));
	return (SUCCESS);
}

int	vector_rotate_00(void)
{
	t_vector	u = {1, 1, 1};
	t_vector	ax = {-1, 1, 0};

	_ft_assert(vector_equals(vector_rotate(u, ax, M_PI), (t_vector){-1, -1, -1}));
	return (SUCCESS);
}

int	matrix_equals_00(void)
{
	t_matrix	m = {{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}};

	_ft_assert(matrix_equals(m, m));
	return (SUCCESS);
}

int	matrix_equals_01(void)
{
	t_matrix	m = {{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}};
	t_matrix	n = {{{1, 1, 1}, {1, 1, 1}, {1, 3, 1}}};

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
	t_matrix	m = {{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}};
	t_matrix	n = {{{3, 3, 3}, {3, 3, 3}, {3, 3, 3}}};

	_ft_assert(matrix_equals(matrix_scalar_product(3, m), n));
	return (SUCCESS);
}

int	matrix_add_00(void)
{
	t_matrix	m = {{{1, 1, -1}, {.1, .5, 1.9}, {100, 0, 0}}};
	t_matrix	n = {{{-1, 1, -1}, {-.2, .5, -1.9}, {0, 0, -100}}};
	t_matrix	w = {{{0, 2, -2}, {-.1, 1, 0}, {100, 0, -100}}};

	_ft_assert(matrix_equals(matrix_add(m, n), w));
	return (SUCCESS);
}

int	matrix_subtract_00(void)
{
	t_matrix	m = {{{1, 1, -1}, {.1, .5, 1.9}, {100, 0, 0}}};
	t_matrix	n = {{{-1, 1, -1}, {-.2, .5, -1.9}, {0, 0, -100}}};
	t_matrix	w = {{{2, 0, 0}, {.3, 0, 3.8}, {100, 0, 100}}};

	_ft_assert(matrix_equals(matrix_subtract(m, n), w));
	return (SUCCESS);
}

int	matrix_product_00(void)
{
	t_matrix	m = {{{1, 1, -1}, {.1, .5, 1.9}, {100, 0, 0}}};
	t_matrix	n = {{{-1, 1, -1}, {-.2, .5, -1.9}, {0, 0, -100}}};
	t_matrix	w = {{{-1.2, 1.5, 97.1}, {-.2, .35, -191.05}, {-100, 100, -100}}};

	_ft_assert(matrix_equals(matrix_product(m, n), w));
	return (SUCCESS);
}

int	matrix_product_01(void)
{
	t_matrix	m = {{{-1.2, 1.5, 97.1}, {-.2, .35, -191.05}, {-100, 100, -100}}};

	_ft_assert(matrix_equals(matrix_product(matrix_identity(), m), m));
	return (SUCCESS);
}

int	matrix_product_02(void)
{
	t_matrix	m = {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}};
	t_matrix	n = {{{-1.2, 1.5, 97.1}, {-.2, .35, -191.05}, {-100, 100, -100}}};

	_ft_assert(matrix_equals(matrix_product(m, n), m));
	return (SUCCESS);
}

int	matrix_vector_product_00(void)
{
	t_vector	u = {.655, 0, 101};

	_ft_assert(vector_equals(matrix_vector_product(matrix_identity(), u), u));
	return (SUCCESS);
}

int	matrix_vector_product_01(void)
{
	t_matrix	m = {{{1, 1, -1}, {.1, .5, 1.9}, {100, 0, 0}}};
	t_vector	u = {.655, 0, 101};
	t_vector	v = {-100.345, 191.9655, 65.5};

	_ft_assert(vector_equals(matrix_vector_product(m, u), v));
	return (SUCCESS);
}

int	matrix_vector_product_02(void)
{
	t_matrix	m = {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}};
	t_vector	u = {.655, 0, 101};
	t_vector	v = {0, 0, 0};

	_ft_assert(vector_equals(matrix_vector_product(m, u), v));
	return (SUCCESS);
}

int	matrix_vector_product_03(void)
{
	t_matrix	m = {{{1, 1, -1}, {.1, .5, 1.9}, {100, 0, 0}}};
	t_vector	u = {0, 0, 0};
	t_vector	v = {0, 0, 0};

	_ft_assert(vector_equals(matrix_vector_product(m, u), v));
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

	result = unit_test_suite(tests_laag);
	if (result == 0)
		printf(GREEN"PASSED\n");
	printf(DFLT"Tests run: %d\n", tests_run);

	return (result);
}
