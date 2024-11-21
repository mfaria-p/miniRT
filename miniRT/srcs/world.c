/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:48:27 by ecorona-          #+#    #+#             */
/*   Updated: 2024/11/21 13:44:04 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// world as static var in main?

volatile t_world	*world_init(volatile t_world *world)
{
	world->ray_origin = (t_vector){0, 0, 0};
	world->objects = NULL;
	world->light = (t_light_source){(t_vector){0, 0, 0}, 0, (t_vector){0, 0, 0}};
	world->img = NULL;
	world->camera = (t_camera){0};
	world->scene = NULL;
	world->tmp = (t_vector){0, 0, 0};
	return (world);
}

volatile t_world	*world_object_add(volatile t_world *world, t_object *object)
{
	t_list	*new_object;

	new_object = malloc(sizeof(t_list));
	new_object->content = object;
	new_object->next = world->objects;
	world->objects = new_object;
	return (world);
}

void	world_destroy(volatile t_world *world)
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
	clean_scene(world->scene);
	clean_data(&world->scene->data);
}
