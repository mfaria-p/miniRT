/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:31:34 by ecorona-          #+#    #+#             */
/*   Updated: 2024/11/09 20:27:35 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"
#include "minirt.h"

#define CANVAS_PIXEL 500
#define WALL_Z 10
#define WALL_SIZE 7

int	color_rgb(t_vector color);

int	main(void) { return (0); }

/*int	main(void)*/
/*{*/
/*	void		*mlx_ptr;*/
/*	void		*mlx_win;*/
/*	t_img		img;*/
/**/
/*	mlx_ptr = mlx_init();*/
/*	// mlx_get_screen_size(mlx_ptr, &w, &h);*/
/*	mlx_win = mlx_new_window(mlx_ptr, CANVAS_PIXEL, CANVAS_PIXEL, "Hello World!");*/
/*	img.img = mlx_new_image(mlx_ptr, CANVAS_PIXEL, CANVAS_PIXEL);*/
/*	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.endian);*/
/**/
/*	float			pixel_size = (float)WALL_SIZE / CANVAS_PIXEL;*/
/*	float			half = (float)WALL_SIZE / 2;*/
/*	t_sphere		shape = {{0, 0, 0, 1}, 1};*/
/*	t_object		sphere = {SPHERE, &shape, {{53./255, 33./255, 0, 1}, .5, 1, 1, 10}};*/
/*	t_light_source	light = {{-10, 10, -10, 1}, 1};*/
/*	float			world_y;*/
/*	float			world_x;*/
/*	t_vector		position;*/
/*	t_ray			ray;*/
/*	t_roots			xs;*/
/*	t_vector		point;*/
/*	t_vector		normal;*/
/*	t_vector		eyev;*/
/**/
/*	ray.origin = (t_vector){0, 0, -5, 1};*/
/*	for (int y = 0; y < CANVAS_PIXEL; y++)*/
/*	{*/
/*		world_y = half - pixel_size * y;*/
/*		for (int x = 0; x < CANVAS_PIXEL; x++)*/
/*		{*/
/*			world_x = -half + pixel_size * x;*/
/*			position = (t_vector){world_x, world_y, WALL_Z, 1};*/
/*			ray.direction = vector_normalize(vector_subtract(position, ray.origin));*/
/*			xs = ray_sphere_intersect(ray, *(t_sphere  *)sphere.shape);*/
/*			if (xs.count > 0)*/
/*			{*/
/*				float	minx = (xs.x1 < xs.x2) * xs.x1 + (xs.x2 < xs.x1) * xs.x2;*/
/*				point = ray_position(ray, minx);*/
/*				normal = vector_normalize(vector_subtract(point, (*(t_sphere *)sphere.shape).origin));*/
/*				eyev = vector_scalar_product(-1, ray.direction);*/
/*				t_vector	color = lighting(sphere.material, light, point, eyev, normal);*/
/*				my_mlx_pixel_put(&img, x, y, color_rgb(color));*/
/*			}*/
/*		}*/
/*	}*/
/**/
/*	mlx_put_image_to_window(mlx_ptr, mlx_win, img.img, 0, 0);*/
/*	mlx_loop(mlx_ptr);*/
/*	return (0);*/
/*}*/

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

t_img	*my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
	return (img);
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
