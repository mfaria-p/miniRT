#include "iu_scene.h"

int ft_error(char *str, t_data *data, int e)
{
    if (data->fd)
        close(data->fd);
    if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
    if (e == EXIT_SUCCESS)
		exit(EXIT_SUCCESS);
	ft_printf("Error: %s\n", str);
	exit(EXIT_FAILURE);
}

/* void ft_checkfile(char * file, t_data *data)
{
    data->fd = open(file, O_RDONLY, 0444);
    if (data->fd == -1)
        ft_error("Invalid file", data, EXIT_FAILURE);
} */

//checkar com o edu s isto é uma cena
void	is_invalid_file(t_scenehe *scene)
{
	if (!scene->ambient_count)
		ft_error("Missing Ambient element", &scene->data, EXIT_FAILURE);
	if (!scene->camera_count)
        ft_error("Missing Camera element", &scene->data, EXIT_FAILURE);
    if (!scene->light_count)
        ft_error("Missing Light element", &scene->data, EXIT_FAILURE);

}