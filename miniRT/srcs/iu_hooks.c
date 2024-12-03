/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:19:32 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/12/03 17:26:28 by mfaria-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mouse_press_hook(int button, int x, int y, void *param)
{
	volatile t_world	*world;

	(void)x;
	(void)y;
	world = (volatile t_world *)param;
	if (button == 1)
	{
		world->direction_rot = (t_vector){world->camera.hsize / 2,
			world->camera.vsize / 2, 0};
		mlx_loop_hook(world->img->mlx, scene_rotate, param);
	}
	else if (button == 3)
	{
		world->selected_light = 0;
		world->selected_object = object_select(world, x, y);
		mlx_loop_hook(world->img->mlx, animate, param);
	}
	return (0);
}

int	mouse_release_hook(int button, int x, int y, void *param)
{
	t_world	*world;

	(void)button;
	(void)x;
	(void)y;
	world = (t_world *)param;
	mlx_loop_hook(world->img->mlx, animate, param);
	return (0);
}

int	key_press_hook(int keycode, void *param)
{
	volatile t_world	*world;
	t_camera			camera;
	t_object			*object;

	world = (volatile t_world *)param;
	camera = (t_camera)world->camera;
	object = (t_object *)world->selected_object;
	if (keycode == XK_ESCAPE)
		quit(param);
	if (keycode == XK_W)
	{
		world->direction_move = camera.axis;
		mlx_loop_hook(world->img->mlx, scene_translate, param);
	}
	if (keycode == XK_S)
	{
		world->direction_move = vector_scalar_product(-1, camera.axis);
		mlx_loop_hook(world->img->mlx, scene_translate, param);
	}
	if (keycode == XK_A)
	{
		world->direction_move = vector_rotate(camera.left, camera.rotation.axis,
				camera.rotation.angle);
		mlx_loop_hook(world->img->mlx, scene_translate, param);
	}
	if (keycode == XK_D)
	{
		world->direction_move = vector_rotate(camera.left, camera.rotation.axis,
				camera.rotation.angle);
		world->direction_move = vector_scalar_product(-1,
				world->direction_move);
		mlx_loop_hook(world->img->mlx, scene_translate, param);
	}
	if (keycode == XK_SPACE)
	{
		world->direction_move = vector_rotate(camera.up, camera.rotation.axis,
				camera.rotation.angle);
		mlx_loop_hook(world->img->mlx, scene_translate, param);
	}
	if (keycode == XK_SHIFT)
	{
		world->direction_move = vector_rotate(camera.up, camera.rotation.axis,
				camera.rotation.angle);
		world->direction_move = vector_scalar_product(-1,
				world->direction_move);
		mlx_loop_hook(world->img->mlx, scene_translate, param);
	}
	if (object != NULL)
	{
		if (keycode == XK_UP)
		{
			printf("Scaling up\n");
			object_scale(object, 1.2);
		}
		if (keycode == XK_DOWN)
		{
			printf("Scaling down\n");
			if (object->shape.scale > 0.1)
				object_scale(object, 0.833);
		}
	}
	if (keycode == XK_C)
	{
		world->selected_light = 0;
		world->selected_object = NULL;
	}
	if (keycode == XK_L)
	{
		printf("Selecting light\n");
		world->selected_light = 1;
	}
	if (keycode == XK_R)
	{
		world->camera.scale = 3 - (((int)world->camera.scale + 2) % 3);
	}
	return (0);
}

int	key_release_hook(int keycode, void *param)
{
	volatile t_world	*world;

	(void)world;
	world = (volatile t_world *)param;
	if (keycode == XK_W || keycode == XK_S || keycode == XK_A || keycode == XK_D
		|| keycode == XK_SPACE || keycode == XK_SHIFT || keycode == XK_UP
		|| keycode == XK_DOWN || keycode == XK_R)
		mlx_loop_hook(world->img->mlx, animate, param);
	return (0);
}
