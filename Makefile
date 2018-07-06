# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/24 11:01:01 by vbrovenk          #+#    #+#              #
#    Updated: 2018/03/24 11:01:03 by vbrovenk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC =	ft_printf.c \
		print_dec.c \
		print_unsigned.c \
		print_hex.c \
		print_octal.c \
		print_percent.c \
		print_string.c \
		print_char.c \
		print_uni_string.c \
		is_functions.c \
		help_functions.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

OFF=\033[0m
RED=\033[31m
REDBOLD=\033[1;31m
GREEN=\033[32m
GREENBOLD=\033[1;32m
YELLOW=\033[33m
YELLOWBOLD=\033[1;33m

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./libft
	@ar rc $(NAME) $(OBJ) ./libft/*.o
	@echo "$(YELLOW) $(NAME) $(YELLOWBOLD)-(OK)- $(OFF)" 

%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)Compiling $(GREENBOLD)$<$(OFF) $(GREEN)done.$(OFF)"

clean:
	@rm -rf $(OBJ)
	@make clean -C libft
	@echo "$(RED)Objects $(REDBOLD)$(OBJ)$(OFF) $(RED)have been destroyed.$(OFF)"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C libft 
	@echo "$(RED)Binary $(REDBOLD)$(NAME)$(OFF) $(RED)have been destroyed.$(OFF)"

re: fclean all
