/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 18:55:20 by daprovin          #+#    #+#             */
/*   Updated: 2020/06/18 06:05:07 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"
#include "../headers/libft.h"
#include <errno.h>

void		ft_errorcheckermalloc(void)
{
	perror("Error");
	exit(1);
}

void		ft_checkerror(int error, int line)
{
	if (error == 1)
	{
		ft_putstr_fd("Error: something wrong in the .rt file, line ", 2);
		ft_putnbr_fd(line, 2);
		write(2, "\n", 1);
	}
	else if (error == 2)
		ft_putstr_fd("Error: only one resolution must be used\n", 2);
	else if (error == 3)
		ft_putstr_fd("Error: only one ambient light must be used\n", 2);
	exit(1);
}

void		ft_checkinput(int ac, char **av)
{
	if (ac == 1)
	{
		ft_putstr_fd("Error: need a scene\n", 2);
		exit(1);
	}
	else if (ac > 3)
	{
		ft_putstr_fd("Error: too many arguments\n", 2);
		exit(1);
	}
	if (ft_memcmp(ft_strchr(av[1], '.'), ".rt", 4) != 0)
	{
		ft_putstr_fd("Error: incorrect scene extension\n", 2);
		exit(1);
	}
	if (ac > 2 && ft_memcmp(av[2], "--save", 7) != 0)
	{
		ft_putstr_fd("Error: unknown argument\n", 2);
		exit(1);
	}
}

void		ft_checkdata(t_data *data)
{
	if (data->cam == NULL)
		ft_putstr_fd("Error: need at least 1 camera in the scene\n", 2);
	else if (data->algt == NULL)
		ft_putstr_fd("Error: need an ambient light in the scene\n", 2);
	else if (data->res == NULL)
		ft_putstr_fd("Error: need a resolution in the scene\n", 2);
	else
		return ;
	exit(1);
}
