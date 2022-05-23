# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/18 12:15:17 by cdefonte          #+#    #+#              #
#    Updated: 2022/05/23 16:41:59 by mbraets          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

HEADER		=	includes/philo.h
DHEADER		=	-Iincludes/

CC			=	cc

CFLAGS		=	-Werror -Wall -Wextra -g3
LIBFLAGS	=	$(DHEADER) -lpthread -pthread

SRCS		=	srcs/philo.c \
srcs/philo_free.c \
srcs/threads/routine.c \
srcs/threads/utils.c \
srcs/threads/setter_getter.c \
../shared/ft_atoi.c \
../shared/ft_calloc.c \
../shared/ft_memcpy.c


OBJS		=	$(SRCS:.c=.o)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ $(DHEADER)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFLAGS)

clean		:
				rm -rf $(OBJS)

fclean		:	clean
				rm -f $(NAME)

debug		:
				$(eval CFLAGS+=-DDEBUG)

run			:	debug all
				valgrind --tool=helgrind --tool=drd --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(NAME)

re			:	fclean all
.PHONY: all clean run fclean
