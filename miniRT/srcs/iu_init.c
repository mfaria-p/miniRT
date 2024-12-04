/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:05:34 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/12/03 21:50:50 by mfaria-p         ###   ########.fr       */
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

t_camera	init_camera2(t_scenehe *s)
{
	t_camera	c;

	c.axis = (t_vector){s->camera.orient_x, s->camera.orient_y,
		s->camera.orient_z};
	c.left = vector_cross_product(c.axis, (t_vector){0, 1, 0});
	c.up = vector_cross_product(c.left, c.axis);
	c.scale = 3;
	c.hsize = CANVAS_PIXEL;
	c.vsize = CANVAS_PIXEL;
	c.fov = s->camera.fov * (M_PI / 180.0);
	c.origin = (t_vector){s->camera.x, s->camera.y, s->camera.z};
	c.rotation.axis = vector_cross_product(c.axis, (t_vector){0, 0, 1});
	c.rotation.angle = acos(vector_cosine(c.axis, (t_vector){0, 0, 1}));
	if (c.hsize > c.vsize)
	{
		c.half_width = tan(c.fov / 2);
		c.half_height = tan(c.fov / 2) / ((double)c.hsize / c.vsize);
	}
	else
	{
		c.half_width = tan(c.fov / 2) * ((double)c.hsize / c.vsize);
		c.half_height = tan(c.fov / 2);
	}
	c.pixel_size = (c.half_width * c.scale * 2) / c.hsize;
	return (c);
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
