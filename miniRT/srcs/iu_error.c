#include "iu_scene.h"

int ft_error(char *str, t_data *data, int e)
{
    if (data->fd)
        close(data->fd);
    if (e == EXIT_SUCCESS)
		exit(EXIT_SUCCESS);
	ft_printf("Error: %s\n", str);
	exit(EXIT_FAILURE);
}