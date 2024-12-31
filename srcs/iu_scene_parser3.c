/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_scene_parser3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:11:30 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/12/12 11:02:03 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_position(const char **line, t_cylinder *cylinder)
{
	cylinder->x = parse_float(line, 1, 0.0);
	(*line)++;
	cylinder->y = parse_float(line, 1, 0.0);
	(*line)++;
	cylinder->z = parse_float(line, 1, 0.0);
}

void	parse_cylinder(const char *line, t_scenehe *scene)
{
	t_cylinder	cylinder;

	line += 2;
	skip_spaces(&line);
	parse_position(&line, &cylinder);
	skip_spaces(&line);
	parse_orientation(&line, &cylinder, scene);
	skip_spaces(&line);
	cylinder.diameter = parse_float(&line, 1, 0.0);
	if (cylinder.diameter <= 0.0)
		ft_error("Cylinder: Diameter must be positive", scene, EXIT_FAILURE);
	skip_spaces(&line);
	cylinder.height = parse_float(&line, 1, 0.0);
	if (cylinder.height <= 0.0)
		ft_error("Cylinder: Height must be positive", scene, EXIT_FAILURE);
	skip_spaces(&line);
	parse_color(&line, &cylinder.color, scene);
	scene->cylinders = ft_realloc(scene->cylinders, sizeof(t_cylinder), \
			(scene->cylinder_count + 1));
	scene->cylinders[scene->cylinder_count++] = cylinder;
}
