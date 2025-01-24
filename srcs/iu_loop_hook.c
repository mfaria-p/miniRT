/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_loop_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:57:42 by mfaria-p          #+#    #+#             */
/*   Updated: 2025/01/24 14:29:49 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	scene_rotate(void *param)
{
	t_world	*w;
	t_vec	euler;
	int		cursor[2];

	w = (t_world *)param;
	mlx_mouse_get_pos(w->img->mlx, w->img->win, cursor, cursor + 1);
	euler = (t_vec){cursor[1] - w->dir_rot.y, cursor[0] - w->dir_rot.x, 0};
	euler = vec_scalar_prod(w->cam.pixel_size * ROT_FACTOR, euler);
	if (w->selected_obj == NULL)
		cam_rotate((t_cam *)&w->cam, euler);
	else if (w->selected_obj->shape.type != SPHERE)
		obj_rotate(w->selected_obj, vec_scalar_prod(-1, euler));
	render(w->img, (t_cam *)&w->cam, w);
	mlx_clear_window(w->img->mlx, w->img->win);
	mlx_put_image_to_window(w->img->mlx, w->img->win, w->img->img, 0, 0);
	return (0);
}

int	animate(void *param)
{
	t_world	*world;
	void	*img;

	world = (t_world *)param;
	img = world->img->img;
	render(world->img, (t_cam *)&world->cam, world);
	mlx_clear_window(world->img->mlx, world->img->win);
	mlx_put_image_to_window(world->img->mlx, world->img->win, img, 0, 0);
	return (0);
}

int	scene_translate(void *param)
{
	t_world	*w;
	void	*img;

	w = (t_world *)param;
	img = w->img->img;
	if (w->selected_light)
		light_translate((t_spotlight *)&w->light, w->dir_move, MOVE_FACTOR);
	else if (w->selected_obj == NULL)
		cam_translate((t_cam *)&w->cam, w->dir_move, MOVE_FACTOR);
	else
		obj_translate(w->selected_obj, w->dir_move, MOVE_FACTOR);
	render(w->img, (t_cam *)&w->cam, w);
	mlx_clear_window(w->img->mlx, w->img->win);
	mlx_put_image_to_window(w->img->mlx, w->img->win, img, 0, 0);
	return (0);
}
