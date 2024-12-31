/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:01:10 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/12/12 10:36:09 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_scaling(int keycode, t_obj *obj)
{
	if (keycode == XK_UP)
		obj_scale(obj, 1.2);
	else if (keycode == XK_DOWN)
	{
		if (obj->shape.scale > 0.1)
			obj_scale(obj, 0.833);
	}
	else if (keycode == XK_RIGHT)
		obj_new_height(obj, obj->shape.height + 0.1);
	else if (keycode == XK_LEFT)
	{
		if (obj->shape.height > 0.5)
			obj_new_height(obj, obj->shape.height - 0.1);
	}
}

static void	render_scene_aux(t_scenehe *scene, t_world *world)
{
	int		i;
	t_obj	*obj;

	i = 0;
	while (i < scene->sphere_count)
	{
		obj = obj_sphere_create(scene->spheres[i]);
		world_obj_add(world, obj);
		i++;
	}
	i = 0;
	while (i < scene->plane_count)
	{
		obj = obj_plane_create(scene->planes[i]);
		world_obj_add(world, obj);
		i++;
	}
	i = 0;
	while (i < scene->cylinder_count)
	{
		obj = obj_cylinder_create(scene->cylinders[i]);
		world_obj_add(world, obj);
		i++;
	}
}

static void	render_hook_aux(t_world *world)
{
	mlx_do_key_autorepeatoff(world->img->mlx);
	mlx_hook(world->img->win, DestroyNotify, StructureNotifyMask, quit,
		(void *)world);
	mlx_hook(world->img->win, ButtonPress, ButtonPressMask, mouse_press_hook,
		(void *)world);
	mlx_hook(world->img->win, ButtonRelease, ButtonReleaseMask,
		mouse_release_hook, (void *)world);
	mlx_hook(world->img->win, KeyPress, KeyPressMask, key_press_hook,
		(void *)world);
	mlx_hook(world->img->win, KeyRelease, KeyReleaseMask, key_release_hook,
		(void *)world);
}

void	render_scene(t_scenehe *scene, t_world *world)
{
	t_spotlight		light;
	static t_cam	cam;
	t_img			img;
	t_vec			color;

	color = (t_vec){scene->amb.color.r, scene->amb.color.g, scene->amb.color.b};
	color = vec_scalar_prod(1 / 255.0, color);
	world->amb = vec_scalar_prod(scene->amb.ratio, color);
	light = light_init(scene->light);
	world->light = light;
	cam = cam_init(scene);
	world->cam = cam;
	render_scene_aux(scene, world);
	img = img_init(&scene->data);
	world->img = &img;
	world->scene = scene;
	render_hook_aux(world);
	render(&img, &cam, world);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_do_key_autorepeaton(world->img->mlx);
	mlx_loop(world->img->mlx);
	quit((void *)world);
	exit(EXIT_SUCCESS);
}
