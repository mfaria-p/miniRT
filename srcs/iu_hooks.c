/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:19:32 by mfaria-p          #+#    #+#             */
/*   Updated: 2025/01/24 14:25:33 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mouse_press_hook(int button, int x, int y, void *param)
{
	t_world	*w;
	int		cursor[2];

	w = (t_world *)param;
	if (button == 1)
	{
		if (w->selected_obj)
		{
			mlx_mouse_get_pos(w->img->mlx, w->img->win, cursor, cursor + 1);
			w->dir_rot = (t_vec){cursor[0], cursor[1], 0};
		}
		else
			w->dir_rot = (t_vec){w->cam.hsize / 2, w->cam.vsize / 2, 0};
		mlx_loop_hook(w->img->mlx, scene_rotate, param);
	}
	else if (button == 3)
	{
		w->selected_light = 0;
		w->selected_obj = obj_select(w, x, y);
		mlx_loop_hook(w->img->mlx, animate, param);
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
		world->dir_move = cam.axis;
	else if (keycode == XK_S)
	{
		world->dir_move = cam.axis;
		world->dir_move = vec_scalar_prod(-1, world->dir_move);
	}
	else if (keycode == XK_D)
		world->dir_move = cam.right;
	else if (keycode == XK_A)
	{
		world->dir_move = cam.right;
		world->dir_move = vec_scalar_prod(-1, world->dir_move);
	}
	else if (keycode == XK_SPACE)
		world->dir_move = cam.up;
	else if (keycode == XK_SHIFT)
	{
		world->dir_move = cam.up;
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
		world->selected_light = 1;
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
