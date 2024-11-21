# ifndef IU_SCENE_H
#define IU_SCENE_H

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include "../libft/libft/ft_printf.h"
#include "../libft/libft/get_next_line.h"
#include "../libft/libft/libft.h"
#include "../minilibx-linux/mlx.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define MOVE_FACTOR .1
#define ROT_FACTOR .001

# define XK_ESCAPE 0xff1b
# define XK_W 0x0077
# define XK_S 0x0073
# define XK_A 0x0061
# define XK_D 0x0064
# define XK_SPACE 0x0020
# define XK_SHIFT 0xffe1

typedef struct s_data {
    void *mlx_ptr; 
    void *win_ptr; 
    void *img_ptr;
    char *img_data;
    int bpp;
    int size_line;
    int endian;
    int fd;
} t_data;

typedef struct s_color {
    int r;
    int g;
    int b;
} t_color;

typedef struct s_ambient {
    float ratio;
    t_color color;
} t_ambient; // PODE FICAR

typedef struct s_camerahe {
    float x, y, z;
    float orient_x, orient_y, orient_z;
    float fov;
} t_camerahe;

typedef struct s_light {
    float x, y, z;
    float brightness;
    t_color color;
} t_light;

typedef struct s_sphere {
    float x, y, z;
    float diameter;
    t_color color;
} t_sphere;

typedef struct s_plane {
    float x, y, z;
    float orient_x, orient_y, orient_z;
    t_color color;
} t_plane;

typedef struct s_cylinder {
    float x, y, z;
    float orient_x, orient_y, orient_z;
    float diameter;
    float height;
    t_color color;
} t_cylinder;

typedef struct s_scenehe {
    t_data data;
    char *line;
    char **params;
    t_ambient ambient;
    t_camerahe camera;
    t_light light;
    t_sphere *spheres;
    int sphere_count;
    t_plane *planes;
    int plane_count;
    t_cylinder *cylinders;
    int cylinder_count;
    int camera_count;
    int light_count;
    int ambient_count;
} t_scenehe;

//window related functions
void open_window(t_scenehe *scene);
//error handling
//void ft_checkfile(char * file, t_data *data);
void	is_invalid_file(t_scenehe *scene);
int ft_error(char *str, t_scenehe *scene, int e);
void clean_scene(t_scenehe *scene);
void clean_data(t_data *data);

//checks before parsing functions
void check_ambient(const char *line, t_scenehe *scene);
void check_camera(const char *line, t_scenehe *scene) ;
void check_light(const char *line, t_scenehe *scene) ;
void check_sphere(const char *line, t_scenehe *scene) ;
void check_plane(const char *line, t_scenehe *scene) ;
void check_cylinder(const char *line, t_scenehe *scene) ;
void	check_vector(char ***str, t_scenehe *scene, int j);
void	check_colors(char ***str, t_scenehe *scene, int j);

//scene parsing functions
void process_line(char *line, t_scenehe *scene);
void parse_scene(const char *filename, t_scenehe *scene);
void parse_ambient(const char *line, t_scenehe *scene);
void parse_camera(const char *line, t_scenehe *scene);
void parse_light(const char *line, t_scenehe *scene);
void parse_sphere(const char *line, t_scenehe *scene);
void parse_plane(const char *line, t_scenehe *scene);
void parse_cylinder(const char *line, t_scenehe *scene);

//scene parsing utility functions
int parse_int(const char **str);
float parse_float(const char **str);
void skip_spaces(const char **str);
void parse_color(const char **str, t_color *color, t_scenehe *scene);
void *ft_realloc(void *ptr, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int	is_float(char *str);
int	is_int(char *str);
void	free_array(char *arr[]);
int	array_length(char *arr[]);

//hooks
int	quit(void *param);
int	mouse_press_hook(int button, int x, int y, void *param);
int scene_rotate(void *param);
int	mouse_release_hook(int button, int x, int y, void *param);
int	animate(void *param);
int	key_release_hook(int keycode, void *param);
int	key_press_hook(int keycode, void *param);


#endif
