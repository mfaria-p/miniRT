/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_loop_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:57:42 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/12/12 15:07:15 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	scene_rotate(void *param)
{
	t_world	*w;
	t_vec	v;
	t_vec	euler;
	int		cursor[2];

	w = (t_world *)param;
	mlx_mouse_get_pos(w->img->mlx, w->img->win, cursor, cursor + 1);
	v = (t_vec){cursor[0], cursor[1], 0};
	euler = (t_vec){cursor[0] - w->dir_rot.x, cursor[1] - w->dir_rot.y, 0};
	euler = vec_scalar_prod(w->cam.pixel_size * ROT_FACTOR, euler);
	if (w->selected_obj == NULL)
		cam_rotate((t_cam *)&w->cam, euler);
	else if (w->selected_obj->shape.type != SPHERE)
		obj_rotate(w->selected_obj, euler, -vec_distance(w->dir_rot, v) * ROT_FACTOR);
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
	t_world	*world;
	void	*img;

	world = (t_world *)param;
	img = world->img->img;
	if (world->selected_light)
		light_translate((t_spotlight *)&world->light, world->dir_move, MOVE_FACTOR);
	else if (world->selected_obj == NULL)
		cam_translate((t_cam *)&world->cam, world->dir_move, MOVE_FACTOR);
	else
		obj_translate(world->selected_obj, world->dir_move, MOVE_FACTOR);
	render(world->img, (t_cam *)&world->cam, world);
	mlx_clear_window(world->img->mlx, world->img->win);
	mlx_put_image_to_window(world->img->mlx, world->img->win, img, 0, 0);
	return (0);
}
