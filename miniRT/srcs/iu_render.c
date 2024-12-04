/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:01:10 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/12/04 19:29:56 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_scaling(int keycode, t_obj *object)
{
	if (keycode == XK_UP)
	{
		printf("Scaling up\n");
		obj_scale(object, 1.2);
	}
	else if (keycode == XK_DOWN)
	{
		printf("Scaling down\n");
		if (object->shape.scale > 0.1)
			obj_scale(object, 0.833);
	}
}

int	scene_rotate(void *param)
{
	t_world		*world;
	void		*img;
	t_vec		v;
	t_vec		axis;
	int			mouse_pos[2];

	world = (t_world *)param;
	img = world->img->img;
	(void)img;
	mlx_mouse_get_pos(world->img->mlx, world->img->win, mouse_pos, mouse_pos
		+ 1);
	v = (t_vec){mouse_pos[0], mouse_pos[1], 0};
	axis = (t_vec){-world->dir_rot.y + mouse_pos[1],
		-world->dir_rot.x + mouse_pos[0], 0};
	axis = vec_rotate(axis, world->cam.rotation.axis,
			world->cam.rotation.angle);
	if (world->selected_obj == NULL)
		cam_rotate((t_cam *)&world->cam, axis,
			-vec_distance(world->dir_rot, v) * ROT_FACTOR);
	else if (world->selected_obj->shape.type != SPHERE)
		obj_rotate(world->selected_obj, axis,
			-vec_distance(world->dir_rot, v) * ROT_FACTOR);
	render(world->img, (t_cam *)&world->cam, world);
	mlx_clear_window(world->img->mlx, world->img->win);
	mlx_put_image_to_window(world->img->mlx, world->img->win, world->img->img,
		0, 0);
	return (0);
}

int	animate(void *param)
{
	t_world	*world;
	void	*img;

	world = (t_world *)param;
	img = world->img->img;
	(void)img;
	render(world->img, (t_cam *)&world->cam, world);
	mlx_clear_window(world->img->mlx, world->img->win);
	mlx_put_image_to_window(world->img->mlx, world->img->win, world->img->img,
		0, 0);
	return (0);
}

int	scene_translate(void *param)
{
	t_world	*world;
	void	*img;

	world = (t_world *)param;
	img = world->img->img;
	(void)img;
	if (world->selected_light)
		light_translate((t_spotlight *)&world->light, world->dir_move, MOVE_FACTOR);
	else if (world->selected_obj == NULL)
		cam_translate((t_cam *)&world->cam, world->dir_move,
			MOVE_FACTOR);
	else
		obj_translate(world->selected_obj, world->dir_move,
			MOVE_FACTOR);
	render(world->img, (t_cam *)&world->cam, world);
	mlx_clear_window(world->img->mlx, world->img->win);
	mlx_put_image_to_window(world->img->mlx, world->img->win, world->img->img,
		0, 0);
	return (0);
}

void	render_scene(t_scenehe *scene, t_world *world)
{
	t_spotlight		light;
	static t_cam	cam;
	t_obj			*obj;
	int				i;
	t_sphere		*sphere;
	t_plane			*plane;
	t_cylinder		*cylinder;
	t_img			img;

	world->amb = vec_scalar_prod(scene->amb.ratio,
			(t_vec){scene->amb.color.r / 255.0, scene->amb.color.g
			/ 255.0, scene->amb.color.b / 255.0});
	light = light_init((t_vec){scene->light.x, scene->light.y,
			scene->light.z}, (t_vec){scene->light.color.r / 255.0,
			scene->light.color.g / 255.0, scene->light.color.b / 255.0},
			scene->light.brightness);
	world->light = light;
	cam = cam_init(scene);
	world->cam = cam;
	i = 0;
	while (i < scene->sphere_count)
	{
		sphere = &scene->spheres[i];
		obj = obj_sphere_create((t_vec){sphere->x, sphere->y,
				sphere->z}, (t_vec){sphere->color.r / 255.0, sphere->color.g
				/ 255.0, sphere->color.b / 255.0}, sphere->diameter);
		world_obj_add(world, obj);
		i++;
	}
	i = 0;
	while (i < scene->plane_count)
	{
		plane = &scene->planes[i];
		obj = obj_plane_create((t_vec){plane->x, plane->y, plane->z},
				(t_vec){plane->color.r / 255.0, plane->color.g / 255.0,
				plane->color.b / 255.0}, (t_vec){plane->orient_x,
				plane->orient_y, plane->orient_z});
		world_obj_add(world, obj);
		i++;
	}
	i = 0;
	while (i < scene->cylinder_count)
	{
		cylinder = &scene->cylinders[i];
		obj = obj_cylinder_create((t_vec){cylinder->x, cylinder->y,
				cylinder->z}, (t_vec){cylinder->color.r / 255.0,
				cylinder->color.g / 255.0, cylinder->color.b / 255.0},
				(t_vec){cylinder->orient_x, cylinder->orient_y,
				cylinder->orient_z}, cylinder->diameter, cylinder->height);
		world_obj_add(world, obj);
		i++;
	}
	img = img_init(&scene->data);
	world->img = &img;
	world->scene = scene;
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
	render(&img, &cam, world);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_do_key_autorepeaton(world->img->mlx);
	mlx_loop(world->img->mlx);
	quit((void *)world);
	exit(EXIT_SUCCESS);
}
