NAME = tester

SRCS = test.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = -I../srcs -I../minilibx-linux -I../libft/libft

all: $(NAME)

$(NAME): $(OBJS) _miniRT.o
	$(CC) -o $@ $(CFLAGS) $(OBJS) _miniRT.o $(INCLUDES)

%.o: %.c
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) -c $<

_miniRT.o:
	make -C ..
	strip -N main ../miniRT _miniRT.o

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)
	make -C .. clean

re: fclean all
	make -C .. fclean

.PHONY: all clean fclean re
