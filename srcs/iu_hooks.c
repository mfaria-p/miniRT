/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:19:32 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/12/12 15:26:09 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mouse_press_hook(int button, int x, int y, void *param)
{
	t_world	*world;

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

void	handle_movement(int keycode, t_world *world, t_cam cam)
{
	if (keycode == XK_W)
		world->dir_move = vec_rotate_euler(cam.axis, cam.euler);
	else if (keycode == XK_S)
	{
		world->dir_move = vec_rotate_euler(cam.axis, cam.euler);
		world->dir_move = vec_scalar_prod(-1, world->dir_move);
	}
	else if (keycode == XK_A)
		world->dir_move = vec_rotate_euler(cam.left, cam.euler);
	else if (keycode == XK_D)
	{
		world->dir_move = vec_rotate_euler(cam.left, cam.euler);
		world->dir_move = vec_scalar_prod(-1, world->dir_move);
	}
	else if (keycode == XK_SPACE)
		world->dir_move = vec_rotate_euler(cam.up, cam.euler);
	else if (keycode == XK_SHIFT)
	{
		world->dir_move = vec_rotate_euler(cam.up, cam.euler);
		world->dir_move = vec_scalar_prod(-1, world->dir_move);
	}
	else
		return ;
	mlx_loop_hook(world->img->mlx, scene_translate, (void *)world);
}

int	key_press_hook(int keycode, void *param)
{
	t_world	*world;
	t_cam	cam;
	t_obj	*obj;

	world = (t_world *)param;
	cam = world->cam;
	obj = world->selected_obj;
	if (keycode == XK_ESCAPE)
		quit(param);
	handle_movement(keycode, world, cam);
	if (obj != NULL)
		handle_scaling(keycode, obj);
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
		world->cam.scale = 3 - (((int)world->cam.scale + 2) % 3);
	return (0);
}

int	key_release_hook(int keycode, void *param)
{
	t_world	*world;

	(void)keycode;
	world = (t_world *)param;
	mlx_loop_hook(world->img->mlx, animate, param);
	return (0);
}
