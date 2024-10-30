/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:31:34 by ecorona-          #+#    #+#             */
/*   Updated: 2024/10/30 13:33:48 by ecorona-         ###   ########.fr       */
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

	float			pixel_size = (float)WALL_SIZE / CANVAS_PIXEL;
	float			half = (float)WALL_SIZE / 2;
	t_shape			sphere = create_cylinder();
	sphere.scale = 1;
	/*sphere.shear.matrix[0][1] = 2;*/
	t_object		object = {sphere, {{252./255, 15./255, 192./255}, 1, 1, 1, 50}, {0, 0, 10}, {{.1, 1, .3}, 0}};
	t_light_source	light = {{-1, 1, -1}, 1};
	t_light_source	light2 = {{10, -10, 10}, .2};
	float			world_y;
	float			world_x;
	t_vector		position;
	t_ray			ray;
	t_roots			xs[4];
	t_vector		point;
	t_vector		normal;
	t_vector		eyev;

	ray.origin = (t_vector){0, 0, -5};
	float angle = 0;
	/*float xsh[2] = {.2, 0};*/
	/*object.transformation = matrix_product(matrix_shear(xsh, NULL, NULL), object.transformation);*/
	/*object.transformation = matrix_product(matrix_scale(.1, 1, 1), object.transformation);*/
	while (1)
	{
		/*light.origin = vector_rotate(light.origin, (t_vector){0, 1, 0}, angle);*/
		object.rotation.angle = angle;
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
				float	minx;
				xs[1] = ray_object_intersect(ray, object);
				xs[2] = ray_circle_intersect(ray, object, -object.shape.scale);
				xs[3] = ray_circle_intersect(ray, object, object.shape.scale);
				minx = -1;
				t_vector	colors[3] = {{255,0,0}, {0,255,0}, {0,0,255}};
				if (xs[1].count > 0) {
					minx = xs[1].x1;
					object.material.color = colors[0];
				}
				if (xs[1].count == 2 && (xs[1].x2 < minx || minx < 0)) {
					minx = xs[1].x2;
					object.material.color = colors[0];
				}
				if (xs[2].count > 0 && (xs[2].x1 < minx || minx < 0)) {
					minx = xs[2].x1;
					object.material.color = colors[1];
				}
				if (xs[3].count > 0 && (xs[3].x1 < minx || minx < 0)) {
					minx = xs[3].x1;
					object.material.color = colors[2];
				}
				if (minx >= 0)
				{
					point = ray_position(ray, minx);
					normal = normal_at(point, object);
					eyev = vector_scalar_product(-1, ray.direction);
					t_vector	color = lighting(object.material, light, point, eyev, normal);
					color = vector_add(color, lighting(object.material, light2, point, eyev, normal));
					my_mlx_pixel_put(&img, x, y, color_rgb(color));
				}
			}
		}
		angle += .1;
		/*if (angle >= 8 * M_PI)*/
		/*	break;*/
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
