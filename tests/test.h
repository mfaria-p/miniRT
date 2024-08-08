/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:30:36 by ecorona-          #+#    #+#             */
/*   Updated: 2024/08/08 15:04:33 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include "minirt.h"

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define DFLT "\033[0m"

# define FAILURE 1
# define SUCCESS 0

# define _ft_FAIL() printf(RED"KO"DFLT": %s() line %i\n", __func__, __LINE__)
# define _ft_PASS() printf(GREEN"OK"DFLT": %s() line %i\n", __func__, __LINE__)
# define _ft_assert(test) do {if (!(test)){ _ft_FAIL(); return (FAILURE);} else{ _ft_PASS();}} while (0)
# define _ft_verify(test) do { int r=test(); tests_run++; if (r) return (r);} while (0)

typedef int(*unit_test)(void);
typedef unit_test suite[];

#endif
