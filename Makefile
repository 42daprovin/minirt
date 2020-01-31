# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/30 15:35:32 by daprovin          #+#    #+#              #
#    Updated: 2020/01/30 16:40:41 by daprovin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

OBJS := \
	src/minirt.o \
	src/ft_checkargs.o \
	src/ft_checkdoub.o \
	src/ft_doubatoi.o \
	src/ft_strstrlen.o \

GFLAGS := -Wall -Werror -Wextra
HEAD := headers/

all: $(NAME)

$(NAME): $(OBJS)
	gcc -o $(NAME) $(OBJS) src/libft.a

%.o: %.c
	gcc -I $(HEAD) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all