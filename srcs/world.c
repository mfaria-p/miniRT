/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:48:27 by ecorona-          #+#    #+#             */
/*   Updated: 2024/12/03 15:32:08 by mfaria-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// world as static var in main?

t_world	*world_init(t_world *world)
{
	world->ray_origin = (t_vec){0, 0, 0};
	world->objs = NULL;
	world->light = (t_spotlight){(t_vec){0, 0, 0}, 0, (t_vec){0, 0, 0}};
	world->img = NULL;
	world->cam = (t_cam){0};
	world->scene = NULL;
	world->dir_rot = (t_vec){0, 0, 0};
	world->dir_move = (t_vec){0, 0, 0};
	world->selected_obj = NULL;
	world->selected_light = 0;
	return (world);
}

t_world	*world_obj_add(t_world *world, t_obj *obj)
{
	t_list	*new_obj;

	new_obj = malloc(sizeof(t_list));
	new_obj->content = obj;
	new_obj->next = world->objs;
	world->objs = new_obj;
	return (world);
}

void	world_destroy(t_world *world)
{
	void	*tmp;

	while (world->objs)
	{
		tmp = world->objs->next;
		if (world->objs->content)
			free(world->objs->content);
		free(world->objs);
		world->objs = tmp;
	}
	clean_scene(world->scene);
	clean_data(&world->scene->data);
}
