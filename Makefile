# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdjeffal <sdjeffal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/09/21 12:17:01 by sdjeffal          #+#    #+#              #
#*   Updated: 2015/12/12 06:14:33 by sdjeffal         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = clang
CFLAG = -Wall -Werror -Wextra -g

CPATH = src/
CFILES = \
	main.c    \
	env.c     \
	parsing.c \
	builtin.c \
	msgerror.c\
	ft_cd.c\
	ft_echo.c\
	ft_echo_option.c\
	ft_env.c\
	ft_lstenv.c\
	ft_launch.c\
	ft_pwd.c\
	ft_setenv.c\
	ft_unsetenv.c\
	ft_strsplitshell.c\
	ft_putprompt.c\
	utils.c\
	tools.c\

OPATH = obj/
OFILES = $(CFILES:.c=.o)
OBJ = $(addprefix $(OPATH), $(OFILES))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling \"$(NAME)\"..."
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) -Llibft -lft -o $(NAME)
	@echo "Successful compilation!---"

$(OPATH)%.o: $(CPATH)%.c $(INC)
	@mkdir -p $(OPATH)
	$(CC) $(CFLAGS) -I inc -c -o $@ $<

clean:
	@echo "Deleting the directory /obj..."
	make -C libft clean
	@rm -f $(OBJ)
	@echo "Deletion complete !"

fclean: clean
	@echo "Deleting binary "$(NAME)"..."
	make -C libft fclean
	@rm -f $(NAME)
	@rm -rf $(OPATH)
	@echo "Deletion complete !"/

re: fclean all
