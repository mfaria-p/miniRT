/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_scene_parser2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:31:47 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/12/02 23:33:00 by mfaria-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambient(const char *line, t_scenehe *scene)
{
	line++;
	skip_spaces(&line);
	scene->ambient.ratio = parse_float(&line);
	if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
		ft_error("Ambient lighting ratio out of range [0.0, 1.0]", scene,
			EXIT_FAILURE);
	skip_spaces(&line);
	parse_color(&line, &scene->ambient.color, scene);
}

void	parse_camera(const char *line, t_scenehe *scene)
{
	printf("Parsing camera\n");
	line++;
	skip_spaces(&line);
	scene->camera.x = parse_float(&line);
	line++;
	scene->camera.y = parse_float(&line);
	line++;
	scene->camera.z = parse_float(&line);
	skip_spaces(&line);
	scene->camera.orient_x = parse_float(&line);
	line++;
	scene->camera.orient_y = parse_float(&line);
	line++;
	scene->camera.orient_z = parse_float(&line);
	if (scene->camera.orient_x < -1.0 || scene->camera.orient_x > 1.0
		|| scene->camera.orient_y < -1.0 || scene->camera.orient_y > 1.0
		|| scene->camera.orient_z < -1.0 || scene->camera.orient_z > 1.0)
		ft_error("Camera orientation values out of range [-1.0, 1.0]", scene,
			EXIT_FAILURE);
	skip_spaces(&line);
	scene->camera.fov = parse_float(&line);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
		ft_error("Camera FOV out of range [0, 180]", scene, EXIT_FAILURE);
}

void	parse_light(const char *line, t_scenehe *scene)
{
	line++;
	skip_spaces(&line);
	scene->light.x = parse_float(&line);
	line++;
	scene->light.y = parse_float(&line);
	line++;
	scene->light.z = parse_float(&line);
	skip_spaces(&line);
	scene->light.brightness = parse_float(&line);
	if (scene->light.brightness < 0.0 || scene->light.brightness > 1.0)
		ft_error("Light brightness out of range [0.0, 1.0]", scene,
			EXIT_FAILURE);
	skip_spaces(&line);
	parse_color(&line, &scene->light.color, scene);
}
