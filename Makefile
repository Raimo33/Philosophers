# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/27 16:46:18 by craimond          #+#    #+#              #
#    Updated: 2023/12/28 16:08:27 by craimond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = main.c list_utils.c utils.c
OBJS = ${SRCS:.c=.o}
HEADER = philosophers.h

$(NAME): $(OBJS)
	@cc -Wall -Wextra -Werror $(OBJS) -o $(NAME)
	@echo compiled $(NAME)

all: $(NAME)

clean:
	@rm -rf $(OBJS)