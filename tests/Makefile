NAME = tester

SRCS = test.c

CC = cc
RTFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

LIBMLX_DIR = ../minilibx-linux
LIBMLX = $(LIBMLX_DIR)/libmlx.a

LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

LDLIBS = -lft -lmlx_Linux -lXext -lX11 -lm
LDFLAGS = -L$(LIBFT_DIR) -L$(LIBMLX_DIR) -L/usr/lib
INCLUDES = -I$(LIBFT_DIR) -I$(LIBMLX_DIR)

all = $(NAME)

$(NAME): $(SRCS) _miniRT.o
	$(CC) -g -o $@ $(RTFLAGS) $^ $(INCLUDES) $(LDFLAGS) $(LDLIBS)

_miniRT.o:
	make -C ..
	strip -N main ../miniRT.o -o _miniRT.o

clean:
	make -C .. clean

fclean:
	make -C .. fclean
	rm -rf $(NAME) _miniRT.o

re: fclean all

.PHONY: all clean fclean re
