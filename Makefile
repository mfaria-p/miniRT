NAME = miniRT

SRCDIR = srcs

LAAG_SRCS = laag_double_equals.c laag_vector1.c laag_vector2.c laag_vector3.c laag_quaternion.c laag_matrix1.c laag_matrix2.c laag_matrix3.c laag_matrix4.c

IU_SRCS = iu_loop_hook.c iu_main.c iu_hooks.c iu_init.c iu_error.c iu_render.c iu_scene_parser_utils.c iu_scene_parser_utils2.c iu_scene_checker.c iu_scene_checker2.c iu_scene_parser.c iu_scene_parser2.c iu_scene_parser3.c iu_window.c

RT_SRCS =  ray.c ray_intersections.c light.c light_interface.c shape.c object.c object_create.c object_select.c intersections.c world.c hit.c camera.c camera_interface.c

SRCS = $(LAAG_SRCS) $(RT_SRCS) $(IU_SRCS)

HDRS = laag.h minirt.h

OBJDIR = objs
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

CC = cc
RTFLAGS = -Wall -Wextra -Werror -O2 -g #-fsanitize=address #-pg

LIBMLX_DIR = minilibx-linux
LIBMLX = $(LIBMLX_DIR)/libmlx.a

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

LDLIBS = -lft -lmlx_Linux -lXext -lX11 -lm
LDFLAGS = -L$(LIBFT_DIR) -L$(LIBMLX_DIR) -L/usr/lib
INCLUDES = -I$(LIBFT_DIR) -I$(LIBMLX_DIR)

all: $(NAME)

$(NAME): $(addsuffix .o, $(NAME)) $(addprefix $(SRCDIR)/, $(SRCS)) $(addprefix $(SRCDIR)/, $(HDRS)) $(LIBFT) $(LIBMLX)
	$(CC) -g -o $@ $(RTFLAGS) $< $(INCLUDES) $(LDFLAGS) $(LDLIBS)

$(addsuffix .o, $(NAME)): $(OBJS)
	ld -r $^ -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR) complete

$(LIBMLX):
	@make -C $(LIBMLX_DIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -o $@ $(RTFLAGS) -c $< $(INCLUDES)

$(OBJDIR):
	mkdir $(OBJDIR)

prof:
	@make RTFLAGS="$(RTFLAGS) -pg" re
	./$(NAME)
	gprof $(NAME) > prof

test:
	@make -s -C tests re test

clean:
	rm -rf $(OBJS) miniRT.o
	make -C $(LIBFT_DIR) clean
	make -C $(LIBMLX_DIR) clean

cleanrt:
	rm -rf $(OBJS) miniRT.o

fclean: clean
	rm -rf $(NAME) $(LIBFT) $(LIBMLX) $(OBJDIR) prof

fcleanrt: cleanrt
	rm -rf $(NAME) $(OBJDIR)

re: fclean all

rert: fcleanrt all

.PHONY: all clean fclean re prof test
