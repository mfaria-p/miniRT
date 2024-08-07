/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:52:23 by ecorona-          #+#    #+#             */
/*   Updated: 2024/08/07 15:38:02 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	vector_equals_00(void);

int	tests_run = 0;
suite	tests = {
					vector_equals_00,
					NULL
				};

int	vector_equals_00(void)
{
	//ARRANGE
	t_vector	u = {1, 2, 3};
	t_vector	v = {1, 2, 1};

	//ACT
	//ASSERT
	_ft_assert(vector_equals(u,v));

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

	result = unit_test_suite(tests);
	if (result == 0)
		printf(GREEN"PASSED\n");
	printf(DFLT"Tests run: %d\n", tests_run);

	return (result);
}
