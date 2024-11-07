/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:48:27 by ecorona-          #+#    #+#             */
/*   Updated: 2024/11/07 15:29:31 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// world as static var in main?

t_world	*world_init(t_world *world)
{
	world->objects = NULL;
	world->lights = NULL;
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

t_world	*world_light_add(t_world *world, t_light_source *light)
{
	t_list	*new_light;

	new_light = malloc(sizeof(t_list));
	new_light->content = light;
	new_light->next = world->lights;
	world->lights = new_light;
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
	while (world->lights)
	{
		tmp = world->lights->next;
		if (world->lights->content)
			free(world->lights->content);
		free(world->lights);
		world->lights = tmp;
	}
}
