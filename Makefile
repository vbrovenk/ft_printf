# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/30 18:16:08 by vbrovenk          #+#    #+#              #
#    Updated: 2018/04/30 18:16:10 by vbrovenk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out

SRC = ft_printf.c my_countdigits.c my_itoa.c

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): libft/libft.a $(OBJ)
	gcc $(OBJ) $(LIBFT) -o $(NAME)

libft/libft.a:
	make -C libft/

%.o: %.c
	gcc -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	make -C libft/ fclean

re: fclean all
