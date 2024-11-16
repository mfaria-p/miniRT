/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:48:27 by ecorona-          #+#    #+#             */
/*   Updated: 2024/11/09 13:26:28 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// world as static var in main?

t_world	*world_init(t_world *world)
{
	world->ray_origin = (t_vector){0, 0, 0};
	world->objects = NULL;
	return (world);
}

t_world	*world_object_add(t_world *world, t_object *object)
{
	t_list	*new_object;

	new_object = malloc(sizeof(t_list));
	new_object->content = object;
	new_object->next = world->objects;
	world->objects = new_object;
	return (world);
}

void	world_destroy(t_world *world)
{
	void	*tmp;

	while (world->objects)
	{
		tmp = world->objects->next;
		if (world->objects->content)
			free(world->objects->content);
		free(world->objects);
		world->objects = tmp;
	}
}
