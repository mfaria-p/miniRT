/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:28:23 by ecorona-          #+#    #+#             */
/*   Updated: 2024/08/07 17:10:12 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "libft.h"
# include "laag.h"
# include <math.h>

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}	t_img;

typedef struct s_projectile
{
	t_vector	position;
	t_vector	velocity;
}	t_proj;

typedef struct s_environment
{
	t_vector	gravity;
	t_vector	wind;
}	t_env;

t_proj		tick(t_env env, t_proj proj);
t_vector	to_canvapos(t_vector u, int h);
int			v_inbound(t_vector u, int w, int h);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
void		put_vector(t_img *img, t_vector u, int color);
int			argb(t_uint8 a, t_uint8 r, t_uint8 g, t_uint8 b);

#endif
