NAME = miniRT

SRCS = test.c

laag_SRCS = test2.c

OBJS = $(SRCS:.c=.o) $(laag_SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

LIBMLX_DIR = minilibx-linux

LIBMLX = $(LIBMLX_DIR)/libmlx.a

LIBMLX_FLAGS = -I$(LIBMLX_DIR) -L$(LIBMLX_DIR) -L/usr/lib -lmlx_Linux -lXext -lX11

LIBFT_REPO = libft

LIBFT_DIR = libft/libft

LIBFT = $(LIBFT_DIR)/libft/libft.a

LIBFT_FLAGS = -I$(LIBFT_DIR) -L$(LIBFT_DIR) -lft

all: $(NAME)

$(NAME): $(LIBMLX) $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) $(FTFLAGS) -lm -o $@

$(LIBFT):
	@git submodule update --init $(LIBFT_REPO)
	@make -C $(LIBFT_DIR) complete

$(LIBMLX):
	@git submodule update --init $(LIBMLX_DIR)
	@make -C $(LIBMLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $<

clean:
	rm -rf $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(LIBMLX_DIR) clean

fclean: clean
	rm -rf $(NAME) $(LIBFT) $(LIBMLX)

re: fclean all

.PHONY: all clean fclean re del
