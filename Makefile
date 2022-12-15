NAME =		pipex.a

FILES_C =	pipex.c command.c utils.c

OBJS =		$(FILES_C:.c=.o)

#DEPS =		$(OBJS:.o=.d)

CC =		gcc

CFLAGS =	-Wall -Werror -Wextra -MMD -MP

RM =		rm -rf

MAKEFILE =	Makefile

all:
	@$(MAKE) $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c $(MAKEFILE)
	@echo "COMPILAD: $(CC) $(CFLAGS) $< -o $@"
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJS) #$(DEPS)

fclean:
	$(MAKE) clean
re:
	$(MAKE) fclean
	$(MAKE) all

#include $(DEPS)

.PHONY: all clean fclean re
