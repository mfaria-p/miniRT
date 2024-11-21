#include "minirt.h"
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
    camera.left = vector_cross_product(camera.axis, (t_vector){0, 1, 0});
    camera.up = vector_cross_product(camera.left, camera.axis);
    camera.scale = 3;
    camera.hsize = CANVAS_PIXEL;
    camera.vsize = CANVAS_PIXEL;
    camera.fov = scene->camera.fov * (M_PI / 180.0); // Convert FOV to radians
    camera.origin = (t_vector){scene->camera.x, scene->camera.y, scene->camera.z};
	camera.rotation.axis = vector_cross_product(camera.axis, (t_vector){0, 0, 1});
	camera.rotation.angle = acos(vector_cosine(camera.axis, (t_vector){0, 0, 1}));

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
    //initialize left and up
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
    
int	quit(void *param)
{
	volatile t_world	*world;

	world = (t_world *)param;
    mlx_do_key_autorepeaton(world->img->mlx);
	mlx_loop_end(world->img->mlx);
	world_destroy(world);
	exit(EXIT_SUCCESS);
}

int scene_rotate(void *param)
{
    t_world *world;
    void *img;
    t_vector v;
    int mouse_pos[2];

    world = (t_world *)param;
    img = world->img->img;
    (void)img;
    mlx_mouse_get_pos(world->img->mlx, world->img->win, mouse_pos, mouse_pos + 1);
    v = (t_vector){mouse_pos[0], mouse_pos[1], 0};
    camera_rotate(&world->camera,  (t_vector){(-world->direction_rot.y + mouse_pos[1]), \
		-world->direction_rot.x + mouse_pos[0], 0}, \
		-vector_distance(world->direction_rot, v) * ROT_FACTOR);
    render(world->img, &world->camera, world);
    mlx_clear_window(world->img->mlx, world->img->win);
    mlx_put_image_to_window(world->img->mlx, world->img->win, world->img->img, 0, 0);
    //mlx_destroy_image(world->img->mlx, img);
    return (0);
}


int	mouse_press_hook(int button, int x, int y, void *param)
{
    volatile t_world	*world;
    int mouse_pos[2];
    (void)x;
    (void)y;

    world = (volatile t_world *)param;
	if (button == 1)
    {
        world->direction_rot = (t_vector){world->camera.hsize/2, world->camera.vsize/2, 0};
        mlx_loop_hook(world->img->mlx, scene_rotate, param);
    }
    else if (button == 3) // Left click
    {
        mlx_mouse_get_pos(world->img->mlx, world->img->win, mouse_pos, mouse_pos + 1);
        world->selected_object = object_select(world, mouse_pos[0], mouse_pos[1]);
         if (world->selected_object)
        {
            printf("Object selected at (%d, %d)\n", mouse_pos[0], mouse_pos[1]);
        }
        else
        {
            printf("No object selected at (%d, %d)\n", mouse_pos[0], mouse_pos[1]);
        }
        mlx_loop_hook(world->img->mlx, animate, param);
    }
    /* else if (button == 3) // Right click
    {
        scene->tmp = (t_vector){x, y, 0};
        mlx_loop_hook(scene->mlx_ptr, scene_rotate_right, param);
    } */
    return (0);
}

int	animate(void *param)
{
	t_world		*world;
	void		*img;

	world = (t_world *)param;
	img = world->img->img;
    (void)img;
	//world->img->img = mlx_new_image(world->img->mlx, world->camera.hsize, world->camera.vsize);
	//world->img->addr = mlx_get_data_addr(world->img->img, &world->img->bpp, &world->img->len, &world->img->endian);
	render(world->img, &world->camera, world);
	mlx_clear_window(world->img->mlx, world->img->win);
	mlx_put_image_to_window(world->img->mlx, world->img->win, world->img->img, 0, 0);
	//mlx_destroy_image(world->img->mlx, img);
	return (0);
}

int	mouse_release_hook(int button, int x, int y, void *param)
{
	t_world	*world;

	(void)button;
	(void)x;
	(void)y;
	world = (t_world *)param;
	// if (button == 1 || button == 3)
	/*if (button == 1)*/
	/*{*/
	/*	// scene->tmp = (t_vector){x, y, 0};*/
	/*	mlx_loop_hook(world->img->mlx, animate, param);*/
	/*}*/
	mlx_loop_hook(world->img->mlx, animate, param);
	return (0);
}

int scene_translate(void *param)
{
    t_world *world;
    void *img;

    world = (t_world *)param;
    img = world->img->img;
    (void)img;
    camera_translate((t_camera *) &world->camera, world->direction_move, MOVE_FACTOR);
    render(world->img, &world->camera, world);
    mlx_clear_window(world->img->mlx, world->img->win);
    mlx_put_image_to_window(world->img->mlx, world->img->win, world->img->img, 0, 0);
    //mlx_destroy_image(world->img->mlx, img);
    return (0);
}

int	key_press_hook(int keycode, void *param)
{
	volatile t_world	*world;
	t_camera			camera;

	world = (volatile t_world *)param;
	camera = (t_camera)world->camera;
	if (keycode == XK_ESCAPE)
		quit(param);
    if (keycode == XK_W)
    {
        world->direction_move = camera.axis;
        mlx_loop_hook(world->img->mlx, scene_translate, param);
    }
    if (keycode == XK_S)
    {
        world->direction_move = vector_scalar_product(-1, camera.axis);
        mlx_loop_hook(world->img->mlx, scene_translate, param);
    }
    if (keycode == XK_A)
    {
		world->direction_move = vector_rotate(camera.left, camera.rotation.axis, camera.rotation.angle);
        mlx_loop_hook(world->img->mlx, scene_translate, param);
    }
    if (keycode == XK_D)
    {
		world->direction_move = vector_rotate(camera.left, camera.rotation.axis, camera.rotation.angle);
        world->direction_move = vector_scalar_product(-1, world->direction_move);
        mlx_loop_hook(world->img->mlx, scene_translate, param);
    }
	if (keycode == XK_SPACE)
	{
		world->direction_move = vector_rotate(camera.up, camera.rotation.axis, camera.rotation.angle);
        mlx_loop_hook(world->img->mlx, scene_translate, param);
	}
	if (keycode == XK_SHIFT)
	{
		world->direction_move = vector_rotate(camera.up, camera.rotation.axis, camera.rotation.angle);
        world->direction_move = vector_scalar_product(-1, world->direction_move);
        mlx_loop_hook(world->img->mlx, scene_translate, param);
	}
    if (world->selected_object && world->selected_object->shape.type == SPHERE)
    {
        if (keycode == XK_Up)
        {
            printf("Scaling up\n");
            world->selected_object->shape.scale += 0.1;
        }
        if (keycode == XK_Down)
        {
            printf("Scaling down\n");
            world->selected_object->shape.scale -= 0.1;
            if (world->selected_object->shape.scale < 0.1)
                world->selected_object->shape.scale = 0.1;
        }
        mlx_loop_hook(world->img->mlx, animate, param);
    }
    
    return (0);
}

int	key_release_hook(int keycode, void *param)
{
	volatile t_world	*world;
    (void)  world;

	world = (volatile t_world *)param;
    if (keycode == XK_W || keycode == XK_S || keycode == XK_A || keycode == XK_D || keycode == XK_SPACE || keycode == XK_SHIFT || keycode == XK_Up || keycode == XK_Down)
        mlx_loop_hook(world->img->mlx, animate, param);
    
    return (0);
}


void render_scene(t_scenehe *scene, volatile t_world *world)
{
    t_light_source light;
    static t_camera camera;
    t_object	*object;
    int i;
	printf("Initializing ambient light");
	world->ambient = vector_scalar_product(scene->ambient.ratio, (t_vector){scene->ambient.color.r / 255.0, scene->ambient.color.g / 255.0, scene->ambient.color.b / 255.0});
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

    world->scene = scene;
    mlx_do_key_autorepeatoff(world->img->mlx);
    mlx_hook(world->img->win, DestroyNotify, StructureNotifyMask, quit, (void *)world);
    mlx_hook(world->img->win, ButtonPress, ButtonPressMask, mouse_press_hook, (void *)world);
    mlx_hook(world->img->win, ButtonRelease, ButtonReleaseMask, mouse_release_hook, (void *)world);
    mlx_hook(world->img->win, KeyPress, KeyPressMask, key_press_hook, (void *)world);
    mlx_hook(world->img->win, KeyRelease, KeyReleaseMask, key_release_hook, (void *)world);
    render(&img, &camera, world);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
    mlx_do_key_autorepeaton(world->img->mlx);
	mlx_loop(world->img->mlx);
    quit((void *)world);
    exit(EXIT_SUCCESS);
}
