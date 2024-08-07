NAME = tester

SRCS = test.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = -I../srcs -I../minilibx-linux -I../libft/libft

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $(CFLAGS) $(OBJS) $(INCLUDES)

%.o: %.c
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) -c $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
