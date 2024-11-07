/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:31:34 by ecorona-          #+#    #+#             */
/*   Updated: 2024/11/07 16:00:17 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"
#include "minirt.h"

#define CANVAS_PIXEL 100
#define WALL_Z 10
#define WALL_SIZE 7

int	color_rgb(t_vector color);

int	main(void)
{
	void		*mlx_ptr;
	void		*mlx_win;
	t_img		img;

	ft_memset(&img, 0, sizeof(img));
	mlx_ptr = mlx_init();
	// mlx_get_screen_size(mlx_ptr, &w, &h);
	mlx_win = mlx_new_window(mlx_ptr, CANVAS_PIXEL, CANVAS_PIXEL, "Hello World!");
	img.img = mlx_new_image(mlx_ptr, CANVAS_PIXEL, CANVAS_PIXEL);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.endian);

	double			pixel_size = (double)WALL_SIZE / CANVAS_PIXEL;
	double			half = (double)WALL_SIZE / 2;
	double			world_y;
	double			world_x;
	t_vector		position;
	t_ray			ray;


	static t_world	world;
	world_init(&world);

	t_light_source *light;
	light = light_create((t_vector){10, 1, -10}, (t_vector){1, 0, 0}, 1);
	world_light_add(&world, light);

	t_object		*object;
	object = object_sphere_create((t_vector){0, .4, -.4}, (t_vector){.9, .4, .5}, .5);
	object_coord_new(object, (t_vector){0, 0, 0});
	object_translate(object, (t_vector){1, 0 ,0}, -.5);
	world_object_add(&world, object);
	object = object_cylinder_create((t_vector){0, -.25, 0}, (t_vector){.9, .4, .5}, (t_vector){0, 1, 0}, .5, .5);
	object_translate(object, (t_vector){1, 0 ,0}, .5);
	world_object_add(&world, object);


	ray.origin = (t_vector){0, 0, -5};
	for (int y = 0; y < CANVAS_PIXEL; y++)
	{
		world_y = half - pixel_size * y;
		for (int x = 0; x < CANVAS_PIXEL; x++)
		{
			world_x = -half + pixel_size * x;
			position = (t_vector){world_x, world_y, WALL_Z};
			ray.direction = vector_normalize(vector_subtract(position, ray.origin));
			my_mlx_pixel_put(&img, x, y, color_rgb(color_at(&world, ray)));
		}
	}

	mlx_put_image_to_window(mlx_ptr, mlx_win, img.img, 0, 0);
	mlx_loop(mlx_ptr);
	world_destroy(&world);
	mlx_clear_window(mlx_ptr, mlx_win);
	mlx_destroy_image(mlx_ptr, img.img);
	mlx_destroy_window(mlx_ptr, mlx_win);
	mlx_destroy_display(mlx_ptr);
	return (0);
}

t_proj	tick(t_env env, t_proj proj)
{
	t_proj	new_proj;

	new_proj.position = vector_add(proj.position, proj.velocity);
	new_proj.velocity = vector_add(vector_add(proj.velocity, env.gravity), env.wind);
	return (new_proj);
}

t_vector	to_canvapos(t_vector u, int h)
{
	t_vector	v;

	v.x = u.x;
	v.y = h - u.y;
	v.z = u.z;
	return (v);
}

int	v_inbound(t_vector u, int w, int h)
{
	return (u.x >= 0 && u.x < w && u.y >= 0 && u.y < h);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	put_vector(t_img *img, t_vector u, int color)
{
	my_mlx_pixel_put(img, u.x, u.y, color);
}

int	color_rgb(t_vector color)
{
	int	r;
	int	g;
	int	b;

	r = 0xFF * color.x;
	g = 0xFF * color.y;
	b = 0xFF * color.z;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return (r << 16 | g << 8 | b);
	return (0xFF << 24 | r << 16 | g << 8 | b);
}

int	argb(t_uint8 a, t_uint8 r, t_uint8 g, t_uint8 b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}
