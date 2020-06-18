# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/30 15:35:32 by daprovin          #+#    #+#              #
#    Updated: 2020/06/18 03:37:31 by daprovin         ###   ########.fr        #
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
	src/square.o \
	src/triangle.o \
	src/trianglelights.o \
	src/cylinder.o \
	src/ft_parsutils2.o \
	src/ft_error_utils.o \
	src/ft_bmp.o \
	src/square2.o \
	src/ft_lights2.o \
	src/ft_rtutils2.o \
	src/ft_rtutils3.o \
	src/supersampling.o \
	src/ft_parsobjs2.o \

GFLAGS := -Wall -Werror -Wextra
HEAD := headers

all: $(NAME)

$(NAME): $(OBJS)
	cd new_libft && make && cd ..
	gcc -o $(NAME) $(OBJS) new_libft/libft.a mlxlib/libmlx_Linux.a -lXext -lX11 -lm

%.o: %.c
	gcc $(GFLAGS) -I $(HEAD) -c $< -o $@ -lm

clean:
	cd new_libft && make clean && cd ..
	rm -f $(OBJS)

fclean: clean
	cd new_libft && make fclean && cd ..
	rm -f $(NAME)

re: fclean all
