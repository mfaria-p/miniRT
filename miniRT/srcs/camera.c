/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:42:15 by ecorona-          #+#    #+#             */
/*   Updated: 2024/11/09 20:44:49 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

t_camera	*camera_init(t_camera *camera)
{
	double	half_view;
	double	aspect;

	camera->axis = (t_vector){0, 1, 0};
	camera->scale = 2;
	camera->hsize = CANVAS_PIXEL;
	camera->vsize = CANVAS_PIXEL;
	camera->fov = M_PI / 2;
	camera->origin = (t_vector){0, 0, 0};
	camera->rotation.axis = (t_vector){0, 0, 0};
	camera->rotation.angle = 0;
	half_view = tan(camera->fov / 2);
	aspect = (double)camera->hsize / camera->vsize;
	if (camera->hsize > camera->vsize)
	{
		camera->half_width = half_view;
		camera->half_height = (half_view / aspect);
	}
	else
	{
		camera->half_width = (half_view * aspect);
		camera->half_height = half_view;
	}
	camera->pixel_size = (camera->half_width * camera->scale * 2) / camera->hsize;
	return (camera);
}

t_camera	*camera_rescale(t_camera *camera, double new_scale)
{
	camera->pixel_size /= camera->scale;
	camera->scale = new_scale;
	camera->pixel_size *= camera->scale;
	return (camera);
}

t_camera	*camera_coord_new(t_camera *camera, t_vector coord)
{
	camera->origin = coord;
	return (camera);
}

t_camera	*camera_rot_new(t_camera *camera, t_vector axis, double angle)
{
	camera->rotation.axis = axis;
	camera->rotation.angle = angle;
	return (camera);
}

t_camera	*camera_translate(t_camera *camera, t_vector direction, double shift)
{
	camera->origin.x = camera->origin.x + shift * direction.x;
	camera->origin.y = camera->origin.y + shift * direction.y;
	camera->origin.z = camera->origin.z + shift * direction.z;
	return (camera);
}

t_camera	*camera_rotate(t_camera *camera, t_vector axis, double angle)
{
	camera->axis = vector_rotate(camera->axis, axis, angle);
	camera->rotation.axis = vector_cross_product(camera->axis, (t_vector){0, 1, 0});
	camera->rotation.angle = acos(vector_cosine(camera->axis, (t_vector){0, 1, 0}));
	return (camera);
}

t_ray	ray_for_pixel(t_camera *camera, int x, int y)
{
	double		x_offset;
	double		y_offset;
	double		world_x;
	double		world_y;
	t_vector	pixel;
	t_ray		ray;

	x_offset = ((double)x + .5) * camera->pixel_size;
	y_offset = ((double)y + .5) * camera->pixel_size;
	world_x = -camera->half_width + x_offset;
	world_y = camera->half_width - y_offset;
	pixel = (t_vector){world_x, world_y, 1};
	pixel = vector_subtract(pixel, camera->origin);
	pixel = vector_rotate(pixel, camera->rotation.axis, -camera->rotation.angle);
	ray.origin = camera->origin;
	ray.direction = vector_normalize(vector_subtract(pixel, ray.origin));
	return (ray);
}

t_img	*my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
	return (img);
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

int	color_argb(t_uint8 a, t_uint8 r, t_uint8 g, t_uint8 b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

void print_camera(const t_camera *camera) {
    if (!camera) {
        printf("Camera is NULL\n");
        return;
    }

    printf("Camera values:\n");
    printf("  Scale: %f\n", camera->scale);
    printf("  HSize: %f\n", camera->hsize);
    printf("  VSize: %f\n", camera->vsize);
    printf("  Pixel Size: %f\n", camera->pixel_size);
    printf("  Half Width: %f\n", camera->half_width);
    printf("  Half Height: %f\n", camera->half_height);
    printf("  Rotation Axis: (%f, %f, %f)\n", camera->rotation.axis.x, camera->rotation.axis.y, camera->rotation.axis.z);
    printf("  Rotation Angle: %f\n", camera->rotation.angle);
    printf("  Origin: (%f, %f, %f)\n", camera->origin.x, camera->origin.y, camera->origin.z);
    printf("  Axis: (%f, %f, %f)\n", camera->axis.x, camera->axis.y, camera->axis.z);
    printf("  FOV: %f\n", camera->fov);
}

void print_img(const t_img *img) {
    if (!img) {
        printf("Image is NULL\n");
        return;
    }

    printf("Image values:\n");
    printf("  Image Pointer: %p\n", img->img);
    printf("  Address: %p\n", img->addr);
    printf("  Bits Per Pixel: %d\n", img->bpp);
    printf("  Line Length: %d\n", img->len);
    printf("  Endian: %d\n", img->endian);
}

t_img	*render(t_img *img, t_camera *camera, t_world *world)
{
	printf("img: %p, camera: %p, world: %p\n", (void *)img, (void *)camera, (void *)world);
	print_img(img);
	print_camera(camera);
	//ver tudo do world e td dentro da light
	printf("world->objects: %p\n", (void *)world->objects);
	printf("world->light: %p\n", (void *)&world->light);
	//t_ray	ray; QUANDO TIRO ESTE RAY FUNCEMINA WHYYYYY
	printf("boop");
	int		x;
	int		y;
	int		xx;
	int		yy;
	//int		color;

	printf("boop");
	y = 0;
	printf("boop");
	while (y < camera->vsize / camera->scale)
	{
		x = 0;
		while (x < camera->hsize / camera->scale)
		{
			//ray = ray_for_pixel(camera, x, y);
			//color = color_rgb(color_at(world, ray));
			yy = y * camera->scale;
			while (yy < y * camera->scale + camera->scale)
			{
				xx = x * camera->scale;
				while (xx < x * camera->scale + camera->scale)
				{
					//my_mlx_pixel_put(img, xx, yy, color);
					xx++;
				}
				yy++;
			}
			x++;
		}
		y++;
	}
	return (img);
}
