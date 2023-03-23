SRCS	= pipex.c make_pipex.c access_cmd.c utils.c

OBJS	= $(SRCS:.c=.o)

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra

RM		= rm -f

NAME	= pipex

COMM1	= cat

COMM2	= hostname

INPUT	= pipex.c

OUTPUT	= output

all		= $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

#wall:	$(INPUT) $(COMM1) $(COMM2) $(OUTPUT)
#		echo "Expected:"
#		$(MAKE) < $(INPUT) $(COMM1) | $(COMM2) > $(OUTPUT)
#		echo "Me:"
#		$(MAKE) $(NAME) $(INPUT) $(COMM1) $(COMM2) $(OUTPUT)

clean:
		$(RM) $(OBJS)
fclean:	clean
		$(RM) $(NAME)
re:		fclean $(NAME)
.PHONY:	all clean fclean re
