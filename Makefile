# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/30 15:35:32 by daprovin          #+#    #+#              #
#    Updated: 2020/02/14 10:30:52 by daprovin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

OBJS := \
	src/minirt.o \
	src/ft_checkargs.o \
	src/ft_checkdoub.o \
	src/ft_doubatoi.o \
	src/ft_strstrlen.o \
	src/ft_parsutilslst.o \
	src/ft_parsutils.o \
	src/ft_parsobjs.o \
	src/ft_parsnobjs.o \
	src/ft_camera.o \
	src/ft_lights.o \
	src/ft_rtstruct.o \
	src/ft_rtutils.o \
	src/sphere.o \
	src/plane.o \

GFLAGS := -Wall -Werror -Wextra
HEAD := headers/

all: $(NAME)

$(NAME): $(OBJS)
	gcc -o $(NAME) $(OBJS) src/libft.a libmlx.dylib

%.o: %.c
	gcc -I $(HEAD) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
