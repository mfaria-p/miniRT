/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:29:50 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/12/03 17:29:51 by mfaria-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	clean_data(t_data *data)
{
	if (!data)
		return ;
	if (data->img_ptr)
	{
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	}
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->img_ptr = NULL;
}

// Clean up `t_scenehe` resources, including dynamically allocated arrays
void	clean_scene(t_scenehe *scene)
{
	if (!scene)
		return ;
	if (scene->line)
	{
		free(scene->line);
		scene->line = NULL;
	}
	if (scene->params)
	{
		free_array(scene->params);
		scene->params = NULL;
	}
	if (scene->spheres)
	{
		free(scene->spheres);
		scene->spheres = NULL;
	}
	if (scene->planes)
	{
		free(scene->planes);
		scene->planes = NULL;
	}
	if (scene->cylinders)
	{
		free(scene->cylinders);
		scene->cylinders = NULL;
	}
	scene->sphere_count = 0;
	scene->plane_count = 0;
	scene->cylinder_count = 0;
	scene->camera_count = 0;
	scene->light_count = 0;
	scene->ambient_count = 0;
}

int	ft_error(char *str, t_scenehe *scene, int e)
{
	clean_data(&scene->data);
	clean_scene(scene);
	if (e == EXIT_SUCCESS)
		exit(EXIT_SUCCESS);
	ft_printf("Error: %s\n", str);
	exit(EXIT_FAILURE);
}

void	is_invalid_file(t_scenehe *scene)
{
	if (!scene->ambient_count)
		ft_error("Missing Ambient element", scene, EXIT_FAILURE);
	if (!scene->camera_count)
		ft_error("Missing Camera element", scene, EXIT_FAILURE);
	if (!scene->light_count)
		ft_error("Missing Light element", scene, EXIT_FAILURE);
}
