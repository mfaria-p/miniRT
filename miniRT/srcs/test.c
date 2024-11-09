/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:19:10 by ecorona-          #+#    #+#             */
/*   Updated: 2024/11/09 17:16:55 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "laag.h"
#include "minirt.h"

int	color_rgb(t_vector color);

int	main(void)
{
	void		*mlx_ptr;
	void		*mlx_win;
	t_img		img;

	static t_camera	camera;
	camera_init(&camera);
	/*camera_rotate(&camera, (t_vector){0, 0, 0}, 0);*/
	camera_translate(&camera, (t_vector){0, 0, 1}, .1);
	camera_rotate(&camera, (t_vector){0, 0, 1}, M_PI / 4);
	camera_rescale(&camera, 5);

	ft_memset(&img, 0, sizeof(img)); mlx_ptr = mlx_init();
	// mlx_get_screen_size(mlx_ptr, &w, &h);
	mlx_win = mlx_new_window(mlx_ptr, camera.hsize, camera.vsize, "Hello World!");
	img.img = mlx_new_image(mlx_ptr, camera.hsize, camera.vsize);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.endian);

	static t_world	world;
	world_init(&world);

	t_light_source light;
	light = light_create((t_vector){10, 0, -1}, (t_vector){.9, .8, .2}, 1);
	world.light = light;

	t_object		*object;
	object = object_sphere_create((t_vector){-.5, 0, 0}, (t_vector){1, 1, 1}, .8);
	object_coord_new(object, (t_vector){0, 0, 2});
	object_translate(object, (t_vector){1, 0 ,0}, -.5);
	world_object_add(&world, object);
	object = object_cylinder_create((t_vector){0, -.25, 0}, (t_vector){0, .4, .5}, (t_vector){0, 1, 0}, .5, .5);
	object_coord_new(object, (t_vector){0, 0, 2});
	object_translate(object, (t_vector){1, 0 ,0}, .5);
	world_object_add(&world, object);

	render(&img, &camera, &world);


	mlx_put_image_to_window(mlx_ptr, mlx_win, img.img, 0, 0);
	mlx_loop(mlx_ptr);
	world_destroy(&world);
	mlx_clear_window(mlx_ptr, mlx_win);
	mlx_destroy_image(mlx_ptr, img.img);
	mlx_destroy_window(mlx_ptr, mlx_win);
	mlx_destroy_display(mlx_ptr);
	return (0);
}
