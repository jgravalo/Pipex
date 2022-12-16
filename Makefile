# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgravalo <jgravalo@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/08 11:34:02 by jgravalo          #+#    #+#              #
#    Updated: 2022/12/16 16:12:20 by jgravalo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS            = main.c pipex.c command.c utils.c
BONUS_SRCS		= main_bonus.c pipex.c command.c utils.c
OBJS            = $(SRCS:.c=.o)
BONUS_OBJS		= $(BONUS_SRCS:.c=.o)
CC              = gcc
RM              = rm -f
CFLAGS          = -Wall -Wextra -Werror
NAME			= pipex.a
all:            $(NAME)
$(NAME):        $(OBJS)
				ar rcs $(NAME) $(OBJS)
				ranlib ${NAME}
bonus:			$(OBJS) $(BONUS_OBJS)
				ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
				ranlib ${NAME}
clean:			
				$(RM) $(OBJS) $(BONUS_OBJS)
fclean:			clean
				$(RM) $(NAME)
re:             fclean $(NAME)
.PHONY:			all bonus clean fclean re
