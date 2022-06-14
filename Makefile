# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoseo <yoseo@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/04 22:34:20 by yoseo             #+#    #+#              #
#    Updated: 2022/06/13 01:54:32 by yoseo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	philo
CC 			= 	cc
CFLAGS 		= 	-Wall -Wextra -Werror
SRC_DIR 	= 	./src/
INCLUE_DIR 	= 	./include/

SRC  		= 	main.c\
				philo_act.c\
				ft_utils.c\
				try_philo.c\
				ft_time.c\
				monitoring.c

SRCS		=	$(addprefix $(SRC_DIR), $(SRC))
OBJS 		= 	$(SRCS:%.c=%.o)

				
all : $(NAME)

racecheck : 
	$(CC) -o philo -fsanitize=thread -g $(SRCS) -I $(INCLUE_DIR);
	
$(NAME) : $(OBJS)
	$(CC) -o $@ $^ -pthread
	
%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $^ -I $(INCLUE_DIR)

clean : 
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all


.PHONY : all clean fclean re bonus