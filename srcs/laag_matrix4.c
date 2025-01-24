/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   laag_matrix4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:29:45 by ecorona-          #+#    #+#             */
/*   Updated: 2025/01/22 10:08:03 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"

static t_mat	mat_rotate_x(t_mat m, double a)
{
	const t_mat	rm = {{{1, 0, 0}, {0, cos(a), -sin(a)}, {0, sin(a), cos(a)}}};

	return (mat_prod(m, rm));
}

static t_mat	mat_rotate_y(t_mat m, double a)
{
	const t_mat	rm = {{{cos(a), 0, sin(a)}, {0, 1, 0}, {-sin(a), 0, cos(a)}}};

	return (mat_prod(m, rm));
}

static t_mat	mat_rotate_z(t_mat m, double a)
{
	const t_mat	rm = {{{cos(a), -sin(a), 0}, {sin(a), cos(a), 0}, {0, 0, 1}}};

	return (mat_prod(m, rm));
}

t_mat	mat_rotate_euler(t_mat m, t_vec euler)
{
	m = mat_rotate_x(m, euler.x);
	m = mat_rotate_y(m, euler.y);
	m = mat_rotate_z(m, euler.z);
	return (m);
}

t_mat	mat_rot_vec2vec(t_vec u, t_vec v)
{
	t_vec	cp;
	double	c;
	t_mat	mcp;
	t_mat	smcp;
	t_mat	rot;

	rot = (t_mat){{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	cp = vec_cross_prod(u, v);
	c = vec_dot_prod(u, v);
	if (c == -1)
		return (rot);
	mcp = (t_mat){{{0, -cp.z, cp.y}, {cp.z, 0, -cp.x}, {-cp.y, cp.x, 0}}};
	smcp = mat_prod(mcp, mcp);
	smcp = mat_scalar_prod(1 / (1 + c), smcp);
	rot = mat_add(rot, mcp);
	rot = mat_add(rot, smcp);
	return (rot);
}
