/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:05:34 by mfaria-p          #+#    #+#             */
/*   Updated: 2025/01/24 14:24:26 by ecorona-         ###   ########.fr       */
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

t_cam	cam_init(t_scenehe *scene)
{
	t_cam	cam;

	cam.axis = (t_vec){scene->cam.dx, scene->cam.dy, scene->cam.dz};
	cam.rmat = mat_rot_vec2vec((t_vec){0, 0, 1}, cam.axis);
	cam.right = mat_vec_prod(cam.rmat, (t_vec){1, 0, 0});
	cam.up = mat_vec_prod(cam.rmat, (t_vec){0, 1, 0});
	cam.scale = 3;
	cam.hsize = CANVAS_PIXEL;
	cam.vsize = CANVAS_PIXEL;
	cam.fov = scene->cam.fov * (M_PI / 180.0);
	cam.origin = (t_vec){scene->cam.x, scene->cam.y, scene->cam.z};
	if (cam.hsize > cam.vsize)
	{
		cam.half_width = tan(cam.fov / 2);
		cam.half_height = tan(cam.fov / 2) / ((double)cam.hsize / cam.vsize);
	}
	else
	{
		cam.half_width = tan(cam.fov / 2) * ((double)cam.hsize / cam.vsize);
		cam.half_height = tan(cam.fov / 2);
	}
	cam.pixel_size = (cam.half_width * cam.scale * 2) / cam.hsize;
	return (cam);
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
	scene->amb.ratio = 0.0;
	scene->amb.color = (t_color){0, 0, 0};
	scene->cam = (t_camhe){0};
	scene->light = (t_light){0};
	scene->spheres = NULL;
	scene->sphere_count = 0;
	scene->planes = NULL;
	scene->plane_count = 0;
	scene->cylinders = NULL;
	scene->cylinder_count = 0;
	scene->cam_count = 0;
	scene->light_count = 0;
	scene->amb_count = 0;
}
