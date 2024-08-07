/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:52:23 by ecorona-          #+#    #+#             */
/*   Updated: 2024/08/07 15:34:01 by ecorona-         ###   ########.fr       */
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
	//ACT
	//ASSERT
	_ft_assert(true);
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
