NAME = miniRT

SRCDIR = srcs
SRCS = iu_main.c iu_error.c iu_scene_parser_utils.c iu_scene_parser.c iu_window.c
HDRS = laag.h minirt.h

OBJDIR = objs
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

CC = cc
RTFLAGS = -Wall -Wextra -Werror -g -pg

LIBMLX_DIR = minilibx-linux
LIBMLX = $(LIBMLX_DIR)/libmlx.a

LIBFT_REPO = libft
LIBFT_DIR = $(LIBFT_REPO)/libft
LIBFT = $(LIBFT_DIR)/libft.a

LDLIBS = -lft -lmlx_Linux -lXext -lX11 -lm
LDFLAGS = -L$(LIBFT_DIR) -L$(LIBMLX_DIR) -L/usr/lib
INCLUDES = -I$(LIBFT_DIR) -I$(LIBMLX_DIR)

all: $(NAME)

$(NAME): $(addsuffix .o, $(NAME)) $(addprefix $(SRCDIR)/, $(SRCS)) $(addprefix $(SRCDIR)/, $(HDRS)) $(LIBFT) $(LIBMLX)
	$(CC) -o $@ $(RTFLAGS) $< $(INCLUDES) $(LDFLAGS) $(LDLIBS)

$(addsuffix .o, $(NAME)): $(OBJS)
	ld -r $^ -o $@

$(LIBFT):
	@git submodule update --init $(LIBFT_REPO)
	@make -C $(LIBFT_DIR) complete

$(LIBMLX):
	@git submodule update --init $(LIBMLX_DIR)
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

fclean: clean
	rm -rf $(NAME) $(LIBFT) $(LIBMLX) $(OBJDIR) prof

re: fclean all

.PHONY: all clean fclean re prof test
