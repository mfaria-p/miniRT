/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:34:10 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/12/03 17:34:11 by mfaria-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	static volatile t_world	world;
	t_scenehe				scenehe;
	size_t					filename_len;
	size_t					extension_len;

	init_scene(&scenehe);
	if (argc != 2)
		ft_error("Usage: ./miniRT <scene_description_file.rt>", &scenehe,
			EXIT_FAILURE);
	filename_len = ft_strlen(argv[1]);
	extension_len = ft_strlen(".rt");
	if (filename_len < extension_len || !ft_strnstr(argv[1] + filename_len
			- extension_len, ".rt", extension_len))
	{
		ft_error("Usage: ./miniRT <scene_description_file.rt>", &scenehe,
			EXIT_FAILURE);
	}
	printf("Parsing scene\n");
	parse_scene(argv[1], &scenehe);
	printf("Opening window\n");
	open_window(&scenehe);
	printf("Initializing world\n");
	world_init(&world);
	printf("Rendering scene\n");
	render_scene(&scenehe, &world);
	ft_error(NULL, &scenehe, EXIT_SUCCESS);
}
