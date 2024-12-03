/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:05:34 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/12/03 17:30:14 by mfaria-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_img	img_init(t_data *data)
{
	t_img	img;

	img.win = data->win_ptr;
	img.mlx = data->mlx_ptr;
	img.img = data->img_ptr;
	img.addr = data->img_data;
	img.bpp = data->bpp;
	img.len = data->size_line;
	img.endian = data->endian;
	return (img);
}

t_camera	init_camera2(t_scenehe *scene)
{
	t_camera	camera;
	double		half_view;
	double		aspect;

	camera.axis = (t_vector){scene->camera.orient_x, scene->camera.orient_y,
		scene->camera.orient_z};
	camera.left = vector_cross_product(camera.axis, (t_vector){0, 1, 0});
	camera.up = vector_cross_product(camera.left, camera.axis);
	camera.scale = 3;
	camera.hsize = CANVAS_PIXEL;
	camera.vsize = CANVAS_PIXEL;
	camera.fov = scene->camera.fov * (M_PI / 180.0);
	camera.origin = (t_vector){scene->camera.x, scene->camera.y,
		scene->camera.z};
	camera.rotation.axis = vector_cross_product(camera.axis, (t_vector){0, 0,
			1});
	camera.rotation.angle = acos(vector_cosine(camera.axis, (t_vector){0, 0,
				1}));
	half_view = tan(camera.fov / 2);
	aspect = (double)camera.hsize / camera.vsize;
	if (camera.hsize > camera.vsize)
	{
		camera.half_width = half_view;
		camera.half_height = half_view / aspect;
	}
	else
	{
		camera.half_width = half_view * aspect;
		camera.half_height = half_view;
	}
	camera.pixel_size = (camera.half_width * camera.scale * 2) / camera.hsize;
	return (camera);
}

void	init_scene(t_scenehe *scene)
{
	scene->data.mlx_ptr = NULL;
	scene->data.win_ptr = NULL;
	scene->data.img_ptr = NULL;
	scene->data.img_data = NULL;
	scene->line = NULL;
	scene->params = NULL;
	scene->data.bpp = 0;
	scene->data.size_line = 0;
	scene->data.endian = 0;
	scene->data.fd = 0;
	scene->ambient.ratio = 0.0;
	scene->ambient.color = (t_color){0, 0, 0};
	scene->camera = (t_camerahe){0};
	scene->light = (t_light){0};
	scene->spheres = NULL;
	scene->sphere_count = 0;
	scene->planes = NULL;
	scene->plane_count = 0;
	scene->cylinders = NULL;
	scene->cylinder_count = 0;
	scene->camera_count = 0;
	scene->light_count = 0;
	scene->ambient_count = 0;
}
