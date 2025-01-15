/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:32:36 by ecorona-          #+#    #+#             */
/*   Updated: 2025/01/14 21:42:12 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minirt.h"
#include "../libft/libft.h"
#include "../libft/ft_printf.h"
#include "../libft/get_next_line.h"

void sphere_intersect_01(void);

int	main(void) {
	sphere_intersect_01();
}

void sphere_intersect_01(void) {
	t_obj *sphere = obj_sphere_create((t_sphere){0, 0, 0, 2, (t_color){200,40,60}});
	t_ray ray = {(t_vec){0, 0, 5}, (t_vec){0, 0, -2}};
	t_roots root = ray_sphere_intersect(ray, sphere);
	t_vec p1 = ray_position(ray, root.x1);
	t_vec p2 = ray_position(ray, root.x2);

	int result;
	result = vec_equals(p1, (t_vec){0, 0, 1}) && vec_equals(p2, (t_vec){0, 0, -1});
	result = result || (vec_equals(p1, (t_vec){0, 0, -1}) && vec_equals(p2, (t_vec){0, 0, 1}));
	result = result && root.count == 2;
	if (!result) {
		printf("FAIL\n");
		free(sphere);
		exit(EXIT_SUCCESS);
	}
	free(sphere);
}
