/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:19:10 by ecorona-          #+#    #+#             */
/*   Updated: 2024/11/18 15:23:18 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "laag.h"
#include "minirt.h"
#include <stdio.h>

#define MOVE_FACTOR .001

int	color_rgb(t_vector color);

// mlx callback
// to exit program
int	quit(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	mlx_loop_end(scene->mlx_ptr);
	mlx_destroy_image(scene->mlx_ptr, scene->img->img);
	mlx_destroy_window(scene->mlx_ptr, scene->mlx_win);
	mlx_destroy_display(scene->mlx_ptr);
	free(scene->mlx_ptr);
	// free_scene(scene);
	exit(EXIT_SUCCESS);
}

// mlx (loop) callback
// render scene
int	animate(void *param)
{
	t_scene		*scene;
	t_img		*img;

	scene = (t_scene *)param;
	img = scene->img;
	scene->img->img = mlx_new_image(scene->mlx_ptr, scene->camera->hsize, scene->camera->vsize);
	scene->img->addr = mlx_get_data_addr(scene->img->img, &scene->img->bpp, &scene->img->len, &scene->img->endian);
	render(scene->img, scene->camera, scene->world);
	mlx_clear_window(scene->mlx_ptr, scene->mlx_win);
	mlx_put_image_to_window(scene->mlx_ptr, scene->mlx_win, scene->img->img, 0, 0);
	mlx_destroy_image(scene->mlx_ptr, img->img);
	return (0);
}

// mlx (loop) callback
// move camera around
int	scene_shift(void *param)
{
	t_scene		*scene;
	t_img		*img;
	t_vector	v;
	int			mouse_pos[2];

	scene = (t_scene *)param;
	img = scene->img;
	scene->img->img = mlx_new_image(scene->mlx_ptr, scene->camera->hsize, scene->camera->vsize);
	scene->img->addr = mlx_get_data_addr(scene->img->img, &scene->img->bpp, &scene->img->len, &scene->img->endian);
	mlx_mouse_get_pos(scene->mlx_ptr, scene->mlx_win, mouse_pos, mouse_pos + 1);
	v = (t_vector){mouse_pos[0], mouse_pos[1], 0};
	scene->camera->origin.x -= (v.x - scene->tmp.x) * MOVE_FACTOR;
	scene->camera->origin.y += (v.y - scene->tmp.y) * MOVE_FACTOR;
	render(scene->img, scene->camera, scene->world);
	mlx_clear_window(scene->mlx_ptr, scene->mlx_win);
	mlx_put_image_to_window(scene->mlx_ptr, scene->mlx_win, scene->img->img, 0, 0);
	mlx_destroy_image(scene->mlx_ptr, img->img);
	return (0);
}

// mlx (hook) callback
// mouse press button hook
int	mouse_press_hook(int button, int x, int y, void *param)
{
	t_scene	*scene;
	// const int	mouse_left_click = 1;
	// const int	mouse_right_click = 3;
	// n tenho certeza (4,5):
	// const int	mouse_wheel_down = 4;
	// const int	mouse_wheel_up = 5;
	// const int	mouse_wheel_click = 2;

	scene = (t_scene *)param;
	// if (button == 1)
	// {
	// 	scene->origin = (t_vector){x, y, 0};
	// 	mlx_loop_hook(win->mlx_ptr, scene_rot, param);
	// }
	if (button == 1)
	{
		scene->tmp = (t_vector){x, y, 0};
		mlx_loop_hook(scene->mlx_ptr, scene_shift, param);
	}
	// else if (button == 4 && scene->perspective)
	// 	scene->cam->origin.z -= scene->cam->zoom_factor;
	// else if (button == 5 && scene->perspective)
	// 	scene->cam->origin.z += scene->cam->zoom_factor;
	return (0);
}

// mlx (hook) callback
// mouse release button hook
int	mouse_release_hook(int button, int x, int y, void *param)
{
	t_scene	*scene;

	(void)x;
	(void)y;
	scene = (t_scene *)param;
	// if (button == 1 || button == 3)
	if (button == 1)
	{
		// scene->tmp = (t_vector){x, y, 0};
		mlx_loop_hook(scene->mlx_ptr, animate, param);
	}
	return (0);
}

int	main(void)
{
	void		*mlx_ptr;
	void		*mlx_win;
	t_img		img;

	// initialize camera
	static t_camera	camera;
	camera_init(&camera);
	camera_rescale(&camera, 5);

	// initialize mlx things
	mlx_ptr = mlx_init();
	// mlx_get_screen_size(mlx_ptr, &w, &h);
	mlx_win = mlx_new_window(mlx_ptr, camera.hsize, camera.vsize, "Hello World!");
	img.img = mlx_new_image(mlx_ptr, camera.hsize, camera.vsize);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.endian);

	// initialize world
	static t_world	world;
	world_init(&world);

	// initialize light example
	t_light_source light;
	light = light_init((t_vector){0, 0, -.3}, (t_vector){1, 1, 1}, 1);
	world.light = light;

	// initialize objects examples
	t_object		*object;
	object = object_sphere_create((t_vector){0, 0, 2}, (t_vector){1, .2, .2}, .8);
	// object_coord_new(object, (t_vector){0, 0, 2});
	// object_translate(object, (t_vector){1, 0 ,0}, -.5);
	world_object_add(&world, object);
	object = object_cone_create((t_vector){.5, -.25, 2}, (t_vector){0, .4, .5}, (t_vector){0, 1, 0}, .5, .5);
	world_object_add(&world, object);
	object = object_plane_create((t_vector){0, 0, 10}, (t_vector){.3, .8, .7}, (t_vector){0, 0, 1});
	world_object_add(&world, object);

	// initialize scene
	t_scene scene;
	scene.camera = &camera;
	scene.world = &world;
	scene.img = &img;
	scene.mlx_ptr = mlx_ptr;
	scene.mlx_win = mlx_win;

	// set mlx hooks
	mlx_do_key_autorepeatoff(mlx_ptr);
	// mlx_hook(mlx_win, DestroyNotify, StructureNotifyMask, quit, (void *)&scene);
	mlx_hook(mlx_win, ButtonPress, ButtonPressMask, mouse_press_hook, (void *)&scene);
	mlx_hook(mlx_win, ButtonRelease, ButtonReleaseMask, mouse_release_hook, (void *)&scene);
	// mlx_key_hook(mlx_win, key_hook, (void *)scene);
	scene.tmp = (t_vector){0, 0, 0};
	mlx_loop_hook(mlx_ptr, animate, (void *)&scene);
	mlx_do_key_autorepeaton(mlx_ptr);
	mlx_loop(mlx_ptr);

	render(&img, &camera, &world);


	// mlx_put_image_to_window(mlx_ptr, mlx_win, img.img, 0, 0);
	// mlx_loop(mlx_ptr);
	world_destroy(&world);
	mlx_clear_window(mlx_ptr, mlx_win);
	mlx_destroy_image(mlx_ptr, img.img);
	free(scene.img->img);
	mlx_destroy_window(mlx_ptr, mlx_win);
	mlx_destroy_display(mlx_ptr);
	return (0);
}
