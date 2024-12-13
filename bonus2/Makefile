NAME	= pipex
SRCS	= pipex.c pipex_utils.c
GNL		= get_next_line.c get_next_line_utils.c
OBJS	= $(SRCS:.c=.o) $(GNL:.c=.o)
CC		= cc -Wall -Werror -Wextra
RM		= rm -rf

all: $(OBJS) Makefile pipex.h
	$(CC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re