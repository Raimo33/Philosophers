# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/27 16:46:18 by craimond          #+#    #+#              #
#    Updated: 2023/12/28 16:19:02 by craimond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = main.c list_utils.c utils.c
OBJS = ${SRCS:.c=.o}
HEADER = philosophers.h

$(NAME): $(OBJS) $(HEADER)
	@cc -Wall -Wextra -Werror $(OBJS) -o $(NAME)
	@echo compiled $(NAME)

.c.o:
	@cc -Wall -Wextra -Werror -c $< -o $@

all: $(NAME)

clean:
	@rm -rf $(OBJS)
	@echo removed object files

fclean: clean
	@rm -rf $(NAME)
	@echo removed $(NAME)

re: fclean all

.PHONY: all clean fclean re