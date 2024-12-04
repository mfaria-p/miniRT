/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:19:32 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/12/03 20:04:11 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mouse_press_hook(int button, int x, int y, void *param)
{
	t_world	*world;

	(void)x;
	(void)y;
	world = (t_world *)param;
	if (button == 1)
	{
		world->dir_rot = (t_vec){world->cam.hsize / 2,
			world->cam.vsize / 2, 0};
		mlx_loop_hook(world->img->mlx, scene_rotate, param);
	}
	else if (button == 3)
	{
		world->selected_light = 0;
		world->selected_obj = obj_select(world, x, y);
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
	t_world	*world;
	t_cam	cam;
	t_obj	*obj;

	world = (t_world *)param;
	cam = (t_cam)world->cam;
	obj = (t_obj *)world->selected_obj;
	if (keycode == XK_ESCAPE)
		quit(param);
	if (keycode == XK_W)
	{
		world->dir_move = cam.axis;
		mlx_loop_hook(world->img->mlx, scene_translate, param);
	}
	if (keycode == XK_S)
	{
		world->dir_move = vec_scalar_prod(-1, cam.axis);
		mlx_loop_hook(world->img->mlx, scene_translate, param);
	}
	if (keycode == XK_A)
	{
		world->dir_move = vec_rotate(cam.left, cam.rotation.axis,
				cam.rotation.angle);
		mlx_loop_hook(world->img->mlx, scene_translate, param);
	}
	if (keycode == XK_D)
	{
		world->dir_move = vec_rotate(cam.left, cam.rotation.axis,
				cam.rotation.angle);
		world->dir_move = vec_scalar_prod(-1,
				world->dir_move);
		mlx_loop_hook(world->img->mlx, scene_translate, param);
	}
	if (keycode == XK_SPACE)
	{
		world->dir_move = vec_rotate(cam.up, cam.rotation.axis,
				cam.rotation.angle);
		mlx_loop_hook(world->img->mlx, scene_translate, param);
	}
	if (keycode == XK_SHIFT)
	{
		world->dir_move = vec_rotate(cam.up, cam.rotation.axis,
				cam.rotation.angle);
		world->dir_move = vec_scalar_prod(-1,
				world->dir_move);
		mlx_loop_hook(world->img->mlx, scene_translate, param);
	}
	if (obj != NULL)
	{
		if (keycode == XK_UP)
		{
			printf("Scaling up\n");
			obj_scale(obj, 1.2);
		}
		if (keycode == XK_DOWN)
		{
			printf("Scaling down\n");
			if (obj->shape.scale > 0.1)
				obj_scale(obj, 0.833);
		}
	}
	if (keycode == XK_C)
	{
		world->selected_light = 0;
		world->selected_obj = NULL;
	}
	if (keycode == XK_L)
	{
		printf("Selecting light\n");
		world->selected_light = 1;
	}
	if (keycode == XK_R)
	{
		world->cam.scale = 3 - (((int)world->cam.scale + 2) % 3);
	}
	return (0);
}

int	key_release_hook(int keycode, void *param)
{
	t_world	*world;

	(void)world;
	world = (t_world *)param;
	if (keycode == XK_W || keycode == XK_S || keycode == XK_A || keycode == XK_D
		|| keycode == XK_SPACE || keycode == XK_SHIFT || keycode == XK_UP
		|| keycode == XK_DOWN || keycode == XK_R)
		mlx_loop_hook(world->img->mlx, animate, param);
	return (0);
}
