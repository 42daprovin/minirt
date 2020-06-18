/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:55:58 by daprovin          #+#    #+#             */
/*   Updated: 2020/06/18 02:24:22 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include <math.h>

static int	ft_slcdata1(char **split, t_data *data)
{
	int		r;

	if (**split == 'R')
		r = ft_reso(split, data);
	else if (**split == 'A')
		r = ft_algt(split, data);
	else if (**split == 'c')
		r = ft_cam(split, data);
	else if (**split == 'l')
		r = ft_lgt(split, data);
	else if (**split == 'T')
		r = ft_clrtext(split, data);
	else
		return (1);
	return (r);
}

static int	ft_slcdata2(char **split, t_data *data)
{
	int		r;

	if (**split == 'p' && *((*split) + 1) == 'l')
		r = ft_pl(split, data);
	else if (**split == 's' && *((*split) + 1) == 'p')
		r = ft_sp(split, data);
	else if (**split == 's' && *((*split) + 1) == 'q')
		r = ft_sq(split, data);
	else if (**split == 'c' && *((*split) + 1) == 'y')
		r = ft_cy(split, data);
	else if (**split == 't' && *((*split) + 1) == 'r')
		r = ft_tr(split, data);
	else if (**split == 'c' && *((*split) + 1) == 'u')
		r = ft_cu(split, data);
	else
		return (1);
	return (r);
}

static int	ft_selectdata(char *line, t_data *data)
{
	char	**split;
	int		r;

	if (!(split = ft_split(line, ' ')))
		ft_errorcheckermalloc();
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

static void	ft_initdata(t_data *data)
{
	data->depth = 0;
	data->obj = NULL;
	data->lgt = NULL;
	data->cam = NULL;
	data->res = NULL;
	data->algt = NULL;
	data->spec = 0;
	data->line = 1;
	data->clrtext = 'n';
}

int			main(int ac, char **av)
{
	int			fd;
	char		*line;
	t_data		data;
	int			r;

	ft_checkinput(ac, av);
	ft_initdata(&data);
	fd = open(av[1], O_RDONLY);
	if (fd < 3)
		ft_errorcheckermalloc();
	while (gnl(fd, &line) > 0)
	{
		if ((r = ft_selectdata(line, &data)) > 0)
			ft_checkerror(r, data.line);
		free(line);
		data.line++;
	}
	ft_checkdata(&data);
	init_mlx(&data);
	ft_minirt(&data);
	ft_save_image(data, ac, av[1]);
	mlx_hook(data.w_ptr, 2, (1L << 0), ft_changecam, &data);
	mlx_hook(data.w_ptr, 17, (1L << 17), ft_close, (void *)0);
	mlx_loop(data.mlx);
	return (0);
}
