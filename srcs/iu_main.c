/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:34:10 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/12/12 11:03:54 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	static t_world	world;
	t_scenehe		scenehe;
	size_t			flen;
	size_t			elen;

	init_scene(&scenehe);
	if (argc != 2)
		ft_error("Usage: ./miniRT <scene.rt>", &scenehe, EXIT_FAILURE);
	flen = ft_strlen(argv[1]);
	elen = ft_strlen(".rt");
	if (flen < elen || !ft_strnstr(argv[1] + flen - elen, ".rt", elen))
		ft_error("Usage: ./miniRT <scene.rt>", &scenehe, EXIT_FAILURE);
	parse_scene(argv[1], &scenehe);
	open_window(&scenehe);
	world_init(&world);
	render_scene(&scenehe, &world);
	ft_error(NULL, &scenehe, EXIT_SUCCESS);
}
