/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:53:16 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/12/03 16:53:17 by mfaria-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	open_window(t_scenehe *scene)
{
	scene->data.mlx_ptr = mlx_init();
	if (!scene->data.mlx_ptr)
		ft_error("Initializing MiniLibX", scene, EXIT_FAILURE);
	scene->data.win_ptr = mlx_new_window(scene->data.mlx_ptr, CANVAS_PIXEL,
			CANVAS_PIXEL, "MUEHEHE");
	if (!scene->data.win_ptr)
		ft_error("Creating window", scene, EXIT_FAILURE);
	scene->data.img_ptr = mlx_new_image(scene->data.mlx_ptr, CANVAS_PIXEL,
			CANVAS_PIXEL);
	if (!scene->data.img_ptr)
		ft_error("Creating image", scene, EXIT_FAILURE);
	scene->data.img_data = mlx_get_data_addr(scene->data.img_ptr,
			&scene->data.bpp, &scene->data.size_line, &scene->data.endian);
}
