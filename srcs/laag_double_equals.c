/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   laag_double_equals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:08:45 by ecorona-          #+#    #+#             */
/*   Updated: 2024/12/12 15:13:42 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"

int	double_equals(double x, double y)
{
	return (((x - y) < EPSILON) && ((x - y) > -EPSILON));
}

// yaw pitch roll to quaternion
t_vec	vec_rotate_euler(t_vec u, t_vec euler)
{
	t_quat	p;
	t_quat	q;

	q.k = sin(euler.z / 2) * cos(euler.y / 2) * cos(euler.x / 2) - \
		cos(euler.z / 2) * sin(euler.y / 2) * sin(euler.x / 2);
	q.i = cos(euler.z / 2) * sin(euler.y / 2) * cos(euler.x / 2) + \
		sin(euler.z / 2) * cos(euler.y / 2) * sin(euler.x / 2);
	q.j = cos(euler.z / 2) * cos(euler.y / 2) * sin(euler.x / 2) - \
		sin(euler.z / 2) * sin(euler.y / 2) * cos(euler.x / 2);
	q.w = cos(euler.z / 2) * cos(euler.y / 2) * cos(euler.x / 2) + \
		sin(euler.z / 2) * sin(euler.y / 2) * sin(euler.x / 2);
	p = (t_quat){0, u.x, u.y, u.z};
	p = quat_prod(quat_prod(quat_inverse(q), p), q);
	return ((t_vec){p.i, p.j, p.k});
}
