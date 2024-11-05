/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:09:12 by ecorona-          #+#    #+#             */
/*   Updated: 2024/11/05 21:06:36 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_intersections *intersections_realloc(t_intersections *is)
{
	t_intersection	*new_is;
	size_t			i;

	new_is = ft_calloc((is->size + INTERSECTION_BUFFER_STEP), sizeof(t_intersection));
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

static t_intersections	*intersections_add(t_intersections *is, double t, t_object *obj)
{
	if (is->size % INTERSECTION_BUFFER_STEP == 0)
		intersections_realloc(is);
	if (t >= 0 && (!is->hit || t < is->hit->t))
		is->hit = (is->is + is->size);
	is->is[is->size].t = t;
	is->is[is->size].obj = obj;
	is->size++;
	return (is);
}

t_intersections	*intersections_roots_add(t_intersections *is, t_roots xs, t_object *obj)
{
	if (xs.count > 0)
		intersections_add(is, xs.x1, obj);
	if (xs.count > 1)
		intersections_add(is, xs.x2, obj);
	return (is);
}

t_intersections	*intersections_init(t_intersections *is)
{
	is->hit = NULL;
	is->size = 0;
	is->is = NULL;
	return (is);
}
