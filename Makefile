NAME = miniRT

SRCDIR = srcs
SRCS = test.c vector.c quaternion.c matrix.c

OBJDIR = objs
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBMLX_DIR = minilibx-linux
LIBMLX = $(LIBMLX_DIR)/libmlx.a

LIBFT_REPO = libft
LIBFT_DIR = $(LIBFT_REPO)/libft
LIBFT = $(LIBFT_DIR)/libft.a

LDLIBS = -lft -lmlx_Linux -lXext -lX11 -lm
LDFLAGS = -L$(LIBFT_DIR) -L$(LIBMLX_DIR) -L/usr/lib
INCLUDES = -I$(LIBFT_DIR) -I$(LIBMLX_DIR)

all: $(NAME)

$(NAME): $(addsuffix .o, $(NAME)) $(LIBFT) $(LIBMLX)
	$(CC) -o $@ $(CFLAGS) $< $(INCLUDES) $(LDFLAGS) $(LDLIBS)

$(addsuffix .o, $(NAME)): $(OBJS)
	ld -r $^ -o $@

$(LIBFT):
	@git submodule update --init $(LIBFT_REPO)
	@make -C $(LIBFT_DIR) complete

$(LIBMLX):
	@git submodule update --init $(LIBMLX_DIR)
	@make -C $(LIBMLX_DIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -o $@ $(CFLAGS) -c $< $(INCLUDES)

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -rf $(OBJS) miniRT.o
	make -C $(LIBFT_DIR) clean
	make -C $(LIBMLX_DIR) clean

fclean: clean
	rm -rf $(NAME) $(LIBFT) $(LIBMLX) $(OBJDIR)

re: fclean all

.PHONY: all clean fclean re
