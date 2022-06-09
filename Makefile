# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoseo <yoseo@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/04 22:34:20 by yoseo             #+#    #+#              #
#    Updated: 2022/06/09 05:09:17 by yoseo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	philo
CC 			= 	cc
CFLAGS 		= 	-Wall -Wextra -Werror
SRC_DIR 	= 	./src/
INCLUE_DIR 	= 	./include/

SRC  		= 	main.c\
				time_help.c\
				philosopher.c\
				ft_utils.c\
				ft_time.c

SRCS		=	$(addprefix $(SRC_DIR), $(SRC))
OBJS 		= 	$(SRCS:%.c=%.o)

				
all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) -o $@ $^ -lpthread
	
%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $^ -I $(INCLUE_DIR)

clean : 
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

.PHONY : all clean fclean re bonus