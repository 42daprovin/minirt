/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:20:51 by daprovin          #+#    #+#             */
/*   Updated: 2020/02/08 17:42:22 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/mlx.h"
#include <stdlib.h>
#include <stdio.h>	//borrar

int		ft_close(void)
{
	exit(1);
	return (0);
}

int		ft_tecla(int key, void *s)
{
	printf("tecla = %d\n", key);
	return (0);
}

int main()
{
	void *mlx_ptr;
	void *win_ptr;
	int x;
	int y;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "miniRT");
	x = 10;
	y = 20;
	while (y < 480)
	{
		//printf("%d", 1);
		mlx_pixel_put(mlx_ptr, win_ptr, x, y, 16711680);
		mlx_pixel_put(mlx_ptr, win_ptr, x + 1, y, 16711680);
		y++;
	}
	mlx_hook(win_ptr, 17, 0, ft_close, (void *)0);
	mlx_hook(win_ptr, 2, 0, ft_tecla, (void *)0);
	mlx_loop(mlx_ptr);
	return (0);
}
