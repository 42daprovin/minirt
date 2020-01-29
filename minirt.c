/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:55:58 by daprovin          #+#    #+#             */
/*   Updated: 2020/01/29 19:22:04 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/libft.h"
#include "headers/minirt.h"
#include "headers/mlx.h"

int			ft_reso(char **split, t_data *data)
{
	t_res	*res;

	if (!(res = (t_res*)malloc(sizeof(t_res))))
		return (2);
	res->x = ft_atoi(split[1]);
	res->y = ft_atoi(split[2]);
	data->res = res;
	return (0);
}

int			ft_algt(char **split, t_data *data)
{
	t_algt	*algt;
	char	**color;

	if (!(algt = (t_algt*)malloc(sizeof(t_algt))))
		return (2);
	if (ft_strstrlen(split) != 3)
		return (1);
	if (ft_checkdoub(split[1]) || ft_checkargs(split[2]))
		return (1);
	algt->br = ft_doubatoi(split[1]);
	if (!(color = ft_split(split[2], ',')))
		return (2);
	(algt->clr)[0] = ft_atoi(color[0]);
	(algt->clr)[1] = ft_atoi(color[1]);
	(algt->clr)[2] = ft_atoi(color[2]);
	data->algt = algt;
	return (0);
}

static int	ft_slcdata1(char **split, t_data *data)
{
	int		r;

	if (**split == 'R')
		r = ft_reso(split, data);
	else if (**split == 'A')
		r = ft_algt(split, data);
	else if (**split == 'c')
		return (5);
	else if (**split == 'l')
		return (6);
	else
		return (1);
	return (r);
}

static int	ft_slcdata2(char **split, t_data *data)
{
	if (**split == 'p' && *((*split) + 1) == 'l')
		return (4);
	else if (**split == 's' && *((*split) + 1) == 'p')
	{}
	else if (**split == 's' && *((*split) + 1) == 'q')
	{}
	else if (**split == 'c' && *((*split) + 1) == 'y')
	{}
	else if (**split == 't' && *((*split) + 1) == 'r')
	{}
	else
		return (1);
	return (0);
}

static int	ft_selectdata(char *line, t_data *data)
{
	char	**split;
	int		r;

	if (!(split = ft_split(line, ' ')))
		return (2);
	if (!(*split))
	{
		free(split);
		return (0);
	}
	if (ft_strlen(*split) == 1)
		r = ft_slcdata1(split, data);
	else
		r = ft_slcdata2(split, data);
	free(split);
	return (r);
}

int			main(int ac, char **av)
{
	int		e;
	int		fd;
	char	*line;
	t_data	data;

	fd = open(av[1], O_RDONLY);
	while (gnl(fd, &line) > 0)
	{
		if (ft_selectdata(line, &data) > 0)
		{}//error
		free(line);
	}
	return (0);
}
