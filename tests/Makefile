NAME = tester

SRCS = test.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = -I../srcs -I../minilibx-linux -I../libft/libft

LDLIBS = -lft -lmlx_Linux -lXext -lX11 -lm
LDFLAGS = -L../libft/libft -L../minilibx-linux -L/usr/lib

all: $(NAME)

$(NAME): $(OBJS) _miniRT.o
	$(CC) -o $@ $(CFLAGS) $(OBJS) _miniRT.o $(INCLUDES) $(LDFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) -c $<

_miniRT.o:
	make -C ..
	strip -N main ../miniRT.o -o _miniRT.o

test: all
	./$(NAME)

clean:
	rm -rf $(OBJS) _miniRT.o

fclean: clean
	rm -rf $(NAME)

re: fclean all
	make -C .. fclean

.PHONY: all clean fclean re test
