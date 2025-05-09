FILES		= pipex.c make_pipex.c utils.c ft_split_marks.c access_cmd.c errors.c

BONUS_FILES	= pipex.c init.c end.c exec.c utils.c utils_two.c

SRCS		= $(addprefix src/, $(FILES))

BONUS_SRCS	= $(addprefix bonus/, $(BONUS_FILES))

OBJS		= $(SRCS:.c=.o)

BONUS_OBJS	= $(BONUS_SRCS:.c=.o)

CC			= cc

CFLAGS		= -Wall -Werror -Wextra

RM			= rm -rf

NAME		= pipex

$(NAME): $(OBJS) makefile inc/pipex.h
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all:	$(NAME)

$(OBJS): src/%.o : src/%.c makefile inc/pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BONUS_OBJS) makefile inc/pipex_bonus.h
	$(CC) $(CFLAGS) $(BONUS_OBJS) -o pipex_bonus

$(BONUS_OBJS): bonus/%.o : bonus/%.c makefile inc/pipex_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS) $(BONUS_OBJS)

fclean:	clean
		$(RM) $(NAME) pipex_bonus

re:		fclean $(NAME)

.PHONY:	all clean fclean re