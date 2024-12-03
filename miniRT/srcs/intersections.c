/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:09:12 by ecorona-          #+#    #+#             */
/*   Updated: 2024/12/03 19:20:57 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_touches	*touches_realloc(t_touches *is)
{
	t_touch	*new_is;
	size_t	i;

	new_is = ft_calloc((is->size + INTERSECTION_BUFFER_STEP), sizeof(t_touch));
	if (is->size > 0)
	{
		i = 0;
		while (i < is->size)
		{
			new_is[i].t = is->is[i].t;
			new_is[i].obj = is->is[i].obj;
			i++;
		}
		free(is->is);
	}
	is->is = new_is;
	return (is);
}

static t_touches	*touches_add(t_touches *is, double t, t_obj *obj)
{
	if (is->size % INTERSECTION_BUFFER_STEP == 0)
		touches_realloc(is);
	if (t >= 0 && (!is->hit || t < is->hit->t))
		is->hit = (is->is + is->size);
	is->is[is->size].t = t;
	is->is[is->size].obj = obj;
	is->size++;
	return (is);
}

t_touches	*touches_roots_add(t_touches *is, t_roots xs, t_obj *obj)
{
	if (xs.count > 0)
		touches_add(is, xs.x1, obj);
	if (xs.count > 1)
		touches_add(is, xs.x2, obj);
	return (is);
}

t_touches	*touches_init(t_touches *is)
{
	is->hit = NULL;
	is->size = 0;
	is->is = NULL;
	return (is);
}
