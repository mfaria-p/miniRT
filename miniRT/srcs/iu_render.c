/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:01:10 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/12/03 17:26:19 by mfaria-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	quit(void *param)
{
	volatile t_world	*world;

	world = (t_world *)param;
	mlx_do_key_autorepeaton(world->img->mlx);
	mlx_loop_end(world->img->mlx);
	world_destroy(world);
	exit(EXIT_SUCCESS);
}

int	scene_rotate(void *param)
{
	t_world		*world;
	void		*img;
	t_vector	v;
	t_vector	axis;
	int			mouse_pos[2];

	world = (t_world *)param;
	img = world->img->img;
	(void)img;
	mlx_mouse_get_pos(world->img->mlx, world->img->win, mouse_pos, mouse_pos
		+ 1);
	v = (t_vector){mouse_pos[0], mouse_pos[1], 0};
	axis = (t_vector){-world->direction_rot.y + mouse_pos[1],
		-world->direction_rot.x + mouse_pos[0], 0};
	axis = vector_rotate(axis, world->camera.rotation.axis,
			world->camera.rotation.angle);
	if (world->selected_object == NULL)
		camera_rotate(&world->camera, axis,
			-vector_distance(world->direction_rot, v) * ROT_FACTOR);
	else if (world->selected_object->shape.type != SPHERE)
		object_rotate(world->selected_object, axis,
			-vector_distance(world->direction_rot, v) * ROT_FACTOR);
	render(world->img, &world->camera, world);
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
	render(world->img, &world->camera, world);
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
		light_translate(&world->light, world->direction_move, MOVE_FACTOR);
	else if (world->selected_object == NULL)
		camera_translate((t_camera *)&world->camera, world->direction_move,
			MOVE_FACTOR);
	else
		object_translate(world->selected_object, world->direction_move,
			MOVE_FACTOR);
	render(world->img, &world->camera, world);
	mlx_clear_window(world->img->mlx, world->img->win);
	mlx_put_image_to_window(world->img->mlx, world->img->win, world->img->img,
		0, 0);
	return (0);
}

void	render_scene(t_scenehe *scene, volatile t_world *world)
{
	t_light_source	light;
	static t_camera	camera;
	t_object		*object;
	int				i;
	t_sphere		*sphere;
	t_plane			*plane;
	t_cylinder		*cylinder;
	t_img			img;

	printf("Initializing ambient light");
	world->ambient = vector_scalar_product(scene->ambient.ratio,
			(t_vector){scene->ambient.color.r / 255.0, scene->ambient.color.g
			/ 255.0, scene->ambient.color.b / 255.0});
	printf("Initializing light source\n");
	light = light_init((t_vector){scene->light.x, scene->light.y,
			scene->light.z}, (t_vector){scene->light.color.r / 255.0,
			scene->light.color.g / 255.0, scene->light.color.b / 255.0},
			scene->light.brightness);
	world->light = light;
	printf("Initializing camera\n");
	camera = init_camera2(scene);
	world->camera = camera;
	printf("Adding spheres to the world\n");
	i = 0;
	while (i < scene->sphere_count)
	{
		sphere = &scene->spheres[i];
		object = object_sphere_create((t_vector){sphere->x, sphere->y,
				sphere->z}, (t_vector){sphere->color.r / 255.0, sphere->color.g
				/ 255.0, sphere->color.b / 255.0}, sphere->diameter);
		world_object_add(world, object);
		i++;
	}
	printf("Adding planes to the world\n");
	i = 0;
	while (i < scene->plane_count)
	{
		plane = &scene->planes[i];
		object = object_plane_create((t_vector){plane->x, plane->y, plane->z},
				(t_vector){plane->color.r / 255.0, plane->color.g / 255.0,
				plane->color.b / 255.0}, (t_vector){plane->orient_x,
				plane->orient_y, plane->orient_z});
		world_object_add(world, object);
		i++;
	}
	printf("Adding cylinders to the world\n");
	i = 0;
	while (i < scene->cylinder_count)
	{
		cylinder = &scene->cylinders[i];
		object = object_cylinder_create((t_vector){cylinder->x, cylinder->y,
				cylinder->z}, (t_vector){cylinder->color.r / 255.0,
				cylinder->color.g / 255.0, cylinder->color.b / 255.0},
				(t_vector){cylinder->orient_x, cylinder->orient_y,
				cylinder->orient_z}, cylinder->diameter, cylinder->height);
		world_object_add(world, object);
		i++;
	}
	img = img_init(&scene->data);
	world->img = &img;
	printf("Rendering scene with %d spheres, %d planes, %d cylinders\n",
		scene->sphere_count, scene->plane_count, scene->cylinder_count);
	printf("scene2.img: %p\n", (void *)&img);
	printf("camera: %p\n", (void *)&camera);
	printf("world: %p\n", (void *)world);
	printf("Starting render function\n");
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
	render(&img, &camera, world);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_do_key_autorepeaton(world->img->mlx);
	mlx_loop(world->img->mlx);
	quit((void *)world);
	exit(EXIT_SUCCESS);
}
