/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_scene_checker2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:27:58 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/12/02 23:28:41 by mfaria-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_ambient(const char *line, t_scenehe *scene)
{
	char	**params;

	scene->ambient_count++;
	if (scene->ambient_count > 1)
	{
		ft_error("You cannot declare more than one Ambient", scene,
			EXIT_FAILURE);
	}
	params = ft_split(line, ' ');
	if (array_length(params) != 3)
	{
		free_array(params);
		ft_error("Invalid number of parameters for ambient element", scene,
			EXIT_FAILURE);
	}
	if (!is_float(params[1]))
	{
		free_array(params);
		ft_error("Ambient lighting ratio must be a float number", scene,
			EXIT_FAILURE);
	}
	check_colors(&params, scene, 2);
	free_array(params);
	parse_ambient(line, scene);
}

void	check_camera(const char *line, t_scenehe *scene)
{
	char	**params;

	scene->camera_count++;
	if (scene->camera_count > 1)
	{
		ft_error("You cannot declare more than one Camera", scene,
			EXIT_FAILURE);
	}
	params = ft_split(line, ' ');
	if (array_length(params) != 4)
	{
		free_array(params);
		ft_error("Invalid number of parameters for camera element", scene,
			EXIT_FAILURE);
	}
	check_vector(&params, scene, 1);
	check_vector(&params, scene, 2);
	if (!is_float(params[3]))
	{
		free_array(params);
		ft_error("Camera FOV must be a float number", scene, EXIT_FAILURE);
	}
	free_array(params);
	parse_camera(line, scene);
}

void	check_light(const char *line, t_scenehe *scene)
{
	char	**params;

	scene->light_count++;
	if (scene->light_count > 1)
	{
		ft_error("You cannot declare more than one Light", scene, EXIT_FAILURE);
	}
	params = ft_split(line, ' ');
	if (array_length(params) != 4)
	{
		free_array(params);
		ft_error("Invalid number of parameters for Light element", scene,
			EXIT_FAILURE);
	}
	check_vector(&params, scene, 1);
	if (!is_float(params[2]))
	{
		free_array(params);
		ft_error("Light brightness ratio must be a float number", scene,
			EXIT_FAILURE);
	}
	check_colors(&params, scene, 3);
	free_array(params);
	parse_light(line, scene);
}

