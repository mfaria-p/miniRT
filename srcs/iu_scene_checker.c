/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_scene_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:48:11 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/12/12 10:46:02 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_sphere(const char *line, t_scenehe *scene)
{
	char	**params;

	params = ft_split(line, ' ');
	if (array_length(params) != 4)
	{
		free_array(params);
		ft_error("Sphere: Invalid number of parameters", scene, EXIT_FAILURE);
	}
	check_vec(&params, scene, 1);
	if (!is_float(params[2]))
	{
		free_array(params);
		ft_error("Sphere: Diameter must be float", scene, EXIT_FAILURE);
	}
	check_colors(&params, scene, 3);
	free_array(params);
	parse_sphere(line, scene);
}

void	check_plane(const char *line, t_scenehe *scene)
{
	char	**params;

	params = ft_split(line, ' ');
	if (array_length(params) != 4)
	{
		free_array(params);
		ft_error("Plane: Invalid number of parameters", scene, EXIT_FAILURE);
	}
	check_vec(&params, scene, 1);
	check_vec(&params, scene, 2);
	check_colors(&params, scene, 3);
	free_array(params);
	parse_plane(line, scene);
}

void	check_cylinder(const char *line, t_scenehe *scene)
{
	char		**params;

	params = ft_split(line, ' ');
	if (array_length(params) != 6)
	{
		free_array(params);
		ft_error("Cylinder: Invalid number of parameters", scene, EXIT_FAILURE);
	}
	check_vec(&params, scene, 1);
	check_vec(&params, scene, 2);
	if (!is_float(params[3]))
	{
		free_array(params);
		ft_error("Cylinder: Diameter must be float", scene, EXIT_FAILURE);
	}
	if (!is_float(params[4]))
	{
		free_array(params);
		ft_error("Cylinder: Height must be float", scene, EXIT_FAILURE);
	}
	check_colors(&params, scene, 5);
	free_array(params);
	parse_cylinder(line, scene);
}

void	check_vec(char ***str, t_scenehe *scene, int j)
{
	int		i;
	char	**nbrs;

	i = 0;
	nbrs = ft_split((*str)[j], ',');
	if (!nbrs)
	{
		free_array(*str);
		ft_error("check_vec: Memory allocation failed", scene, EXIT_FAILURE);
	}
	while (nbrs[i])
	{
		if (!is_float(nbrs[i]))
		{
			free_arrays(str, nbrs);
			ft_error("All parameters must be numbers", scene, EXIT_FAILURE);
		}
		i++;
	}
	if (array_length(nbrs) != 3)
	{
		free_arrays(str, nbrs);
		ft_error("Must input x,y,z axis", scene, EXIT_FAILURE);
	}
	free_array(nbrs);
}

void	check_colors(char ***str, t_scenehe *scene, int j)
{
	int		i;
	char	**nbrs;

	i = -1;
	nbrs = ft_split((*str)[j], ',');
	while (nbrs && nbrs[++i])
	{
		if (is_int(nbrs[i]) == 0)
		{
			free_array(*str);
			free_array(nbrs);
			ft_error("RGB colors must be int", scene, EXIT_FAILURE);
		}
	}
	if (array_length(nbrs) != 3)
	{
		free_array(*str);
		free_array(nbrs);
		ft_error("Must input 3 integers for RGB colors", scene, EXIT_FAILURE);
	}
	free_array(nbrs);
}
