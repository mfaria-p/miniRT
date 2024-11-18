#include "iu_scene.h"
#include <math.h>

static t_camera init_camera2(t_scenehe *scene)
{
    if (!scene) {
        fprintf(stderr, "Error: Scene is NULL\n");
        exit(EXIT_FAILURE); // Exit if scene is NULL
    }
    t_camera camera;
    double half_view;
    double aspect;
    camera.axis = (t_vector){scene->camera.orient_x, scene->camera.orient_y, scene->camera.orient_z};
    camera.scale = 2;
    camera.hsize = CANVAS_PIXEL;
    camera.vsize = CANVAS_PIXEL;
    camera.fov = scene->camera.fov * (M_PI / 180.0); // Convert FOV to radians
    camera.origin = (t_vector){scene->camera.x, scene->camera.y, scene->camera.z};
    camera.rotation.axis = (t_vector){0, 0, 0}; // Set to appropriate rotation axis if needed
    camera.rotation.angle = 0; // Set to appropriate rotation angle if needed

    half_view = tan(camera.fov / 2);
    aspect = (double)camera.hsize / camera.vsize;
    if (camera.hsize > camera.vsize) {
        camera.half_width = half_view;
        camera.half_height = half_view / aspect;
    } else {
        camera.half_width = half_view * aspect;
        camera.half_height = half_view;
    }
    camera.pixel_size = (camera.half_width * camera.scale * 2) / camera.hsize;
    return (camera);
}

static t_img img_init(t_data *data)
{
    t_img img;
    img.win = data->win_ptr;
    img.mlx = data->mlx_ptr;
    img.img = data->img_ptr;
    img.addr = data->img_data;
    img.bpp = data->bpp;
    img.len = data->size_line;
    img.endian = data->endian;
    return (img);
}
    

void render_scene(t_scenehe *scene, t_world *world)
{
    t_light_source light;
    static t_camera camera;
    t_object	*object;
    int i;
    printf("Initializing light source\n");
	light = light_init(
        (t_vector){scene->light.x, scene->light.y, scene->light.z},
        (t_vector){scene->light.color.r / 255.0, scene->light.color.g / 255.0, scene->light.color.b / 255.0},
        scene->light.brightness
    );
	world->light = light;
    printf("Initializing camera\n");
    camera = init_camera2(scene);
    world->camera = camera;
    
    printf("Adding spheres to the world\n");
    i = 0;
    while (i < scene->sphere_count) {
        t_sphere *sphere = &scene->spheres[i];
        object = object_sphere_create(
            (t_vector){sphere->x, sphere->y, sphere->z},
            (t_vector){sphere->color.r / 255.0, sphere->color.g / 255.0, sphere->color.b / 255.0},
            sphere->diameter
        );
        world_object_add(world, object);
        i++;
    }

    printf("Adding planes to the world\n");
    i = 0;
    while (i < scene->plane_count) {
        t_plane *plane = &scene->planes[i];
        object = object_plane_create(
            (t_vector){plane->x, plane->y, plane->z},
            (t_vector){plane->color.r / 255.0, plane->color.g / 255.0, plane->color.b / 255.0},
            (t_vector){plane->orient_x, plane->orient_y, plane->orient_z}
        );
        world_object_add(world, object);
        i++;
    }

    printf("Adding cylinders to the world\n");
    i = 0;
    while (i < scene->cylinder_count) {
        t_cylinder *cylinder = &scene->cylinders[i];
        object = object_cylinder_create(
            (t_vector){cylinder->x, cylinder->y, cylinder->z},
            (t_vector){cylinder->color.r / 255.0, cylinder->color.g / 255.0, cylinder->color.b / 255.0},
            (t_vector){cylinder->orient_x, cylinder->orient_y, cylinder->orient_z},
            cylinder->diameter,
            cylinder->height
        );
        world_object_add(world, object);
        i++;
    }
    
    t_img img;
    img = img_init(&scene->data);
    world->img = &img;

    /* mlx_key_hook(data->win_ptr, key_hook, data);
    mlx_hook(data->win_ptr, 17, 0, close_hook, data);
    mlx_loop(data->mlx_ptr); */

    /* mlx_do_key_autorepeatoff(data->mlx_ptr); */
	// mlx_hook(mlx_win, DestroyNotify, StructureNotifyMask, quit, (void *)&scene);
	//mlx_hook(data->win_ptr, ButtonPress, ButtonPressMask, mouse_press_hook, (void *)&scene);
	//mlx_hook(data->win_ptr, ButtonRelease, ButtonReleaseMask, mouse_release_hook, (void *)&scene);
	// mlx_key_hook(mlx_win, key_hook, (void *)scene);
	/* scene2.tmp = (t_vector){0, 0, 0};
	mlx_loop_hook(data->mlx_ptr, animate, (void *)&scene);
	mlx_loop(data->mlx_ptr);
 */
    printf("Rendering scene with %d spheres, %d planes, %d cylinders\n", scene->sphere_count, scene->plane_count, scene->cylinder_count);
    printf("scene2.img: %p\n", (void *)&img);
    printf("camera: %p\n", (void *)&camera);
    printf("world: %p\n", (void *)world);
    printf("Starting render function\n");

    // clean_data(&scene->data);
    // clean_scene(scene);
    render(&img, &camera, world);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_loop(world->img->mlx);
}
