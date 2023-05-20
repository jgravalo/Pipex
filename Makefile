SRCS	= src/pipex.c src/make_pipex.c src/utils.c src/ft_split_marks.c src/access_cmd.c src/errors.c

OBJS	= $(SRCS:.c=.o)

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra

RM		= rm -rf

NAME	= pipex

all:	$(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
clean:
		$(RM) $(OBJS)
fclean:	clean
		$(RM) $(NAME)
re:		fclean $(NAME)
.PHONY:	all clean fclean re
