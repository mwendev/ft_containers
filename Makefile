# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/18 11:39:36 by mwen              #+#    #+#              #
#    Updated: 2022/06/01 12:44:34 by mwen             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_containers
SRC		=	*.cpp
CC		=	c++
CFLAG	=	-Wall -Wextra -Werror -std=c++98

.SILENT:

all:	$(NAME)

$(NAME):
	$(CC) $(CFLAG) $(SRC) -D TEST=1 -o $(NAME)
	printf '\033[32m%s\n\033[0m' "Running tests on STL..."
	./$(NAME)

	$(CC) $(CFLAG) $(SRC) -D TEST=0 -o $(NAME)
	printf '\033[32m%s\n\033[0m' "Running tests on ft_containers..."
	./$(NAME)

	-diff STL_output.txt ft_containers_output.txt >> result.txt
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Check result.txt!"

clean:
	rm -rf objects result.txt
	/bin/rm -f *.o
	/bin/rm -rf ./objects/*.o
	rm -rf STL_output.txt ft_containers_output.txt
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Cleaned ft_containers"

fclean: clean
	/bin/rm -f $(NAME)
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Fcleaned ft_containers"

re: fclean all

.PHONY: clean fclean re all test