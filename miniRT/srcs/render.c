/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 20:43:05 by ecorona-          #+#    #+#             */
/*   Updated: 2024/11/04 20:44:55 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	world_hits(t_world *world)
{
	t_objects	*obj;

	obj = world->objects;
	while (obj)
	{
		ray_object_intersect(obj);
	}
}
