# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/27 16:46:18 by craimond          #+#    #+#              #
#    Updated: 2024/01/03 16:06:35 by craimond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
SRCS = $(addsuffix _bonus.c, main routine routine_utils list_utils utils)
OBJS = ${SRCS:.c=.o}
HEADER = philosophers_bonus.h

$(NAME): $(OBJS) $(HEADER)
	@cc -Wall -Wextra -Werror -lpthread $(OBJS) -o $(NAME)
	@echo compiled $(NAME)

.c.o:
	@cc -Wall -Wextra -Werror -c $< -o $@

all: $(NAME)

bonus: $(NAME)

clean:
	@rm -rf $(OBJS)
	@echo removed object files

fclean: clean
	@rm -rf $(NAME)
	@echo removed $(NAME)

re: fclean all

debug: $(HEADER)
	@gcc -g -Wall -Wextra -Werror $(SRCS) -lpthread -o $(NAME)
	@echo starting debugger with default input
	@gdb --args ./$(NAME) $(NPHILOS) $(TIMETODIE) $(TIMETOEAT) $(TIMETOSLEEP)
	@fclean

.PHONY: all bonus debug clean fclean re