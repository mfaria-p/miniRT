/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_scene_parser2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:31:47 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/12/03 17:50:40 by mfaria-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_amb(const char *line, t_scenehe *scene)
{
	line++;
	skip_spaces(&line);
	scene->amb.ratio = parse_float(&line, 1, 0.0);
	if (scene->amb.ratio < 0.0 || scene->amb.ratio > 1.0)
		ft_error("Ambient lighting ratio out of range [0.0, 1.0]", scene,
			EXIT_FAILURE);
	skip_spaces(&line);
	parse_color(&line, &scene->amb.color, scene);
}

void	parse_cam(const char *line, t_scenehe *scene)
{
	printf("Parsing cam\n");
	line++;
	skip_spaces(&line);
	scene->cam.x = parse_float(&line, 1, 0.0);
	line++;
	scene->cam.y = parse_float(&line, 1, 0.0);
	line++;
	scene->cam.z = parse_float(&line, 1, 0.0);
	skip_spaces(&line);
	scene->cam.orient_x = parse_float(&line, 1, 0.0);
	line++;
	scene->cam.orient_y = parse_float(&line, 1, 0.0);
	line++;
	scene->cam.orient_z = parse_float(&line, 1, 0.0);
	if (scene->cam.orient_x < -1.0 || scene->cam.orient_x > 1.0
		|| scene->cam.orient_y < -1.0 || scene->cam.orient_y > 1.0
		|| scene->cam.orient_z < -1.0 || scene->cam.orient_z > 1.0)
		ft_error("Camera orientation values out of range [-1.0, 1.0]", scene,
			EXIT_FAILURE);
	skip_spaces(&line);
	scene->cam.fov = parse_float(&line, 1, 0.0);
	if (scene->cam.fov < 0 || scene->cam.fov > 180)
		ft_error("Camera FOV out of range [0, 180]", scene, EXIT_FAILURE);
}

void	parse_light(const char *line, t_scenehe *scene)
{
	line++;
	skip_spaces(&line);
	scene->light.x = parse_float(&line, 1, 0.0);
	line++;
	scene->light.y = parse_float(&line, 1, 0.0);
	line++;
	scene->light.z = parse_float(&line, 1, 0.0);
	skip_spaces(&line);
	scene->light.brightness = parse_float(&line, 1, 0.0);
	if (scene->light.brightness < 0.0 || scene->light.brightness > 1.0)
		ft_error("Light brightness out of range [0.0, 1.0]", scene,
			EXIT_FAILURE);
	skip_spaces(&line);
	parse_color(&line, &scene->light.color, scene);
}
