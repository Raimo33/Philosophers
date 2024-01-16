# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/27 16:46:18 by craimond          #+#    #+#              #
#    Updated: 2024/01/15 14:52:13 by craimond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = main.c routine.c routine_utils.c list_utils.c utils.c
OBJS = ${SRCS:.c=.o}
HEADER = philosophers.h

#debugging options
NPHILOS = 5
TIMETODIE = 20000
TIMETOEAT = 1000
TIMETOSLEEP = 700

$(NAME): $(OBJS) $(HEADER)
	@cc -Wall -Wextra -Werror -lpthread $(OBJS) -o $(NAME)
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

debug: $(HEADER)
	@gcc -g -Wall -Wextra -Werror $(SRCS) -lpthread -o $(NAME)
	@echo starting debugger with default input
	@gdb --args ./$(NAME) $(NPHILOS) $(TIMETODIE) $(TIMETOEAT) $(TIMETOSLEEP)
	@fclean

.PHONY: all clean fclean re debug