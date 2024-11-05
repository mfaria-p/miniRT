/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:31:34 by ecorona-          #+#    #+#             */
/*   Updated: 2024/11/04 20:41:07 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "laag.h"
#include "minirt.h"

#define CANVAS_PIXEL 500
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
	t_shape			sphere = create_sphere();
	t_object		object = {sphere, {{252./255, 15./255, 192./255}, .1, .5, .8, 50}, {-2, -2, 10}, {{0, 0, 0}, 0}};
	shape_scale(&sphere, .5);
	t_object		object2 = {sphere, {{252./255, 15./255, 192./255}, .1, .5, .8, 50}, {2, 2, 10}, {{0, 0, 0}, 0}};
	t_object		plane1 = {sphere, {{1, 0, 0}, .1, .5, .8, 50}, {0, 0, 0}, {{0, 1, 0}, M_PI / 4}};
	t_object		plane2 = {sphere, {{1, 0, 0}, .1, .5, .8, 50}, {0, 0, 0}, {{0, 1, 0}, M_PI / 4}};
	t_object		plane3 = {sphere, {{1, 0, 0}, .1, .5, .8, 50}, {0, 0, 0}, {{1, 0, 0}, M_PI / 2}};
	t_object		planes[3] = {plane1, plane2, plane3};
	t_light_source	light = {{-10, 10, -10}, 1};
	double			world_y;
	double			world_x;
	t_vector		position;
	t_ray			ray;
	t_roots			xs;
	t_vector		point;
	t_vector		normal;
	t_vector		eyev;

	ray.origin = (t_vector){0, 0, -5};
	// double angle = (double)M_PI / 2;
	// double scale = 1;
	// double scale_inc = 0;
	while (42)
	{
		// object.rotation.angle = angle;
		// shape_scale(&object.shape, scale);
		mlx_put_image_to_window(mlx_ptr, mlx_win, img.img, 0, 0);
		mlx_destroy_image(mlx_ptr, img.img);
		img.img = mlx_new_image(mlx_ptr, CANVAS_PIXEL, CANVAS_PIXEL);
		for (int y = 0; y < CANVAS_PIXEL; y++)
		{
			world_y = half - pixel_size * y;
			for (int x = 0; x < CANVAS_PIXEL; x++)
			{
				world_x = -half + pixel_size * x;
				position = (t_vector){world_x, world_y, WALL_Z};
				ray.direction = vector_normalize(vector_subtract(position, ray.origin));
				double	minx;
				t_roots xss[3];
				xs = ray_object_intersect(ray, object);
				if (xs.count > 0)
				{
					minx = (xs.x1 <= xs.x2) * xs.x1 + (xs.x2 < xs.x1) * xs.x2;
					point = ray_position(ray, minx);
					normal = normal_at(point, object);
					eyev = vector_scalar_product(-1, ray.direction);
					t_vector	color = lighting(object.material, light, point, eyev, normal);
					my_mlx_pixel_put(&img, x, y, color_rgb(color));
				}
				xs = ray_object_intersect(ray, object2);
				if (xs.count > 0)
				{
					minx = (xs.x1 <= xs.x2) * xs.x1 + (xs.x2 < xs.x1) * xs.x2;
					point = ray_position(ray, minx);
					normal = normal_at(point, object2);
					eyev = vector_scalar_product(-1, ray.direction);
					t_vector	color = lighting(object.material, light, point, eyev, normal);
					my_mlx_pixel_put(&img, x, y, color_rgb(color));
				}
				xss[0] = ray_plane_intersect(ray, planes[0], 0);
				// xss[1] = ray_plane_intersect(ray, planes[1], 0);
				// xss[2] = ray_plane_intersect(ray, planes[2], 0);
				// minx = -1;
				// if (xss[0].x1 <= xss[1].x1 && xss[0].x1 <= xss[2].x1) {
				// 	if (xss[0].count > 0)
				// 		minx = xss[0].x1;
				// }
				// else if (xss[1].x1 <= xss[0].x1 && xss[1].x1 <= xss[2].x1) {
				// 	if (xss[1].count > 0)
				// 		minx = xss[1].x1;
				// }
				// else if (xss[2].x1 <= xss[1].x1 && xss[2].x1 <= xss[0].x1) {
				// 	if (xss[2].count > 0)
				// 		minx = xss[2].x1;
				// }
				minx = xss[0].x1;
				if (minx > 0)
				{
					point = ray_position(ray, minx);
					normal = normal_at(point, object);
					eyev = vector_scalar_product(-1, ray.direction);
					t_vector	color = lighting(object.material, light, point, eyev, normal);
					my_mlx_pixel_put(&img, x, y, color_rgb(color));
				}
			}
		}
		// scale += scale_inc;
		// angle += .1;
		// if (angle >= 8 * M_PI)
		// 	break;
		// if (scale >= 2 || scale <= .5)
		// 	scale_inc = -scale_inc;
		mlx_clear_window(mlx_ptr, mlx_win);
	}

	mlx_put_image_to_window(mlx_ptr, mlx_win, img.img, 0, 0);
	/*mlx_loop(mlx_ptr);*/
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
