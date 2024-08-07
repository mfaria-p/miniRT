/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:31:34 by ecorona-          #+#    #+#             */
/*   Updated: 2024/08/07 14:49:24 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_proj	tick(t_env env, t_proj proj)
{
	t_proj	new_proj;

	new_proj.position = vector_add(proj.position, proj.velocity);
	new_proj.velocity = vector_add(vector_add(proj.velocity, env.gravity), env.wind);
	return (new_proj);
}

t_vector	to_canvapos(t_vector u, int h)
{
	t_vector	v;

	v.x = u.x;
	v.y = h - u.y;
	v.z = u.z;
	return (v);
}

int	v_inbound(t_vector u, int w, int h)
{
	return (u.x >= 0 && u.x < w && u.y >= 0 && u.y < h);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	put_vector(t_img *img, t_vector u, int color)
{
	my_mlx_pixel_put(img, u.x, u.y, color);
}

int	argb(t_uint8 a, t_uint8 r, t_uint8 g, t_uint8 b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

int	main(void)
{
	void	*mlx_ptr;
	void	*mlx_win;
	t_img	img;
	int		w;
	int		h;
	t_proj	proj;
	t_env	env;

	ft_memset(&img, 0, sizeof(img));
	mlx_ptr = mlx_init();
	mlx_get_screen_size(mlx_ptr, &w, &h);
	w /= 2;
	h /= 2;
	mlx_win = mlx_new_window(mlx_ptr, w, h, "Hello World!");
	img.img = mlx_new_image(mlx_ptr, w, h);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.endian);

	proj.position = (t_vector){0, 0, 0};
	proj.velocity = (t_vector){1, 3, 0};
	env.gravity = (t_vector){0, -.02, 0};
	env.wind = (t_vector){-.001, 0, 0};
	while (v_inbound(proj.position, w, h))
	{
		put_vector(&img, to_canvapos(proj.position, h), 0x00FF0000);
		proj = tick(env, proj);
	}
	mlx_put_image_to_window(mlx_ptr, mlx_win, img.img, 0, 0);
	mlx_loop(mlx_ptr);
	return (0);
}
