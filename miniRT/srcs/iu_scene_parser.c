/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_scene_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:12:33 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/12/04 16:12:44 by mfaria-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_orientation(const char **line, t_cylinder *cylinder,
		t_scenehe *scene)
{
	cylinder->orient_x = parse_float(line, 1, 0.0);
	(*line)++;
	cylinder->orient_y = parse_float(line, 1, 0.0);
	(*line)++;
	cylinder->orient_z = parse_float(line, 1, 0.0);
	if (cylinder->orient_x < -1.0 || cylinder->orient_x > 1.0
		|| cylinder->orient_y < -1.0 || cylinder->orient_y > 1.0
		|| cylinder->orient_z < -1.0 || cylinder->orient_z > 1.0)
		ft_error("Cylinder orientation values out of range [-1.0, 1.0]", scene,
			EXIT_FAILURE);
}

char	*cleanline(char *line, t_scenehe *scene)
{
	size_t	len;
	char	*clean_line;

	len = strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	clean_line = (char *)malloc(len + 1);
	if (!clean_line)
		ft_error("Memory allocation failed", scene, EXIT_FAILURE);
	ft_memcpy(clean_line, line, len);
	clean_line[len] = '\0';
	return (clean_line);
}

void	check_element_type(char *clean_line, t_scenehe *scene)
{
	if (clean_line[0] == 'A')
		check_amb(clean_line, scene);
	else if (clean_line[0] == 'C')
		check_cam(clean_line, scene);
	else if (clean_line[0] == 'L')
		check_light(clean_line, scene);
	else if (ft_strncmp(clean_line, "sp", 2) == 0)
		check_sphere(clean_line, scene);
	else if (ft_strncmp(clean_line, "pl", 2) == 0)
		check_plane(clean_line, scene);
	else if (ft_strncmp(clean_line, "cy", 2) == 0)
		check_cylinder(clean_line, scene);
	else
		ft_error("Invalid element", scene, EXIT_FAILURE);
}

void	process_line(char *line, t_scenehe *scene)
{
	char	*clean_line;

	clean_line = cleanline(line, scene);
	if (scene->line)
	{
		free(scene->line);
		scene->line = NULL;
	}
	scene->line = clean_line;
	check_element_type(clean_line, scene);
	if (scene->line)
	{
		free(scene->line);
		scene->line = NULL;
	}
}

void	parse_scene(const char *filename, t_scenehe *scene)
{
	scene->data.fd = open(filename, O_RDONLY);
	if (scene->data.fd < 0)
		ft_error("Failed to open file", scene, EXIT_FAILURE);
	while (1)
	{
		scene->line = get_next_line(scene->data.fd);
		if (scene->line == NULL)
			break ;
		if (scene->line[0] == '\n')
		{
			free(scene->line);
			scene->line = NULL;
			continue ;
		}
		process_line(scene->line, scene);
		if (scene->line)
		{
			free(scene->line);
			scene->line = NULL;
		}
	}
	close(scene->data.fd);
	is_invalid_file(scene);
}
