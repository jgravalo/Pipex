FILES		= pipex.c make_pipex.c utils.c ft_split_marks.c access_cmd.c errors.c

SRCS		= $(addprefix src/, $(FILES))

BONUS_SRCS	= $(addprefix bonus/, $(FILES))

OBJS		= $(SRCS:.c=.o)

BONUS_OBJS	= $(BONUS_SRCS:.c=.o)

CC			= gcc

CFLAGS		= -Wall -Werror -Wextra

RM			= rm -rf

NAME		= pipex

all:	$(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus:	$(BONUS_OBJS)
		$(CC) $(CFLAGS) $(BONUS_OBJS) -o pipex_bonus

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)

re:		fclean $(NAME)

.PHONY:	all clean fclean re
