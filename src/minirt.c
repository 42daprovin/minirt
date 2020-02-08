/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:55:58 by daprovin          #+#    #+#             */
/*   Updated: 2020/02/08 19:39:57 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include "../headers/mlx.h"
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
	else
		return (1);
	return (r);
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

static void	ft_initdata(t_data *data)
{
	data->obj = NULL;
	data->lgt = NULL;
	data->cam = NULL;
	data->res = NULL;
	data->algt = NULL;
}

t_ray		ft_camrays(double x, double y, t_data *data)
{
	t_pt	pt;
	double	norm;
	t_ray	ray;

	pt.x = ((2 * ((x + 0.5) / (data->res->x))) - 1)
	//* ((data->res->x) / (data->res->y))
	* tan(((data->cam->fov) * (M_PI / 180)) / 2);
	pt.y = (1 - (2 * ((y + 0.5) / (data->res->y))))
	* tan(((data->cam->fov) * (M_PI / 180)) / 2);
	norm = sqrt(pow(pt.x, 2) + pow(pt.y, 2) + 1);
	ray.vct.a = (pt.x / norm);
	ray.vct.b = (pt.y / norm);
	ray.vct.c = (-1 / norm);
	ray.pt.x = 0;
	ray.pt.y = 0;
	ray.pt.z = 0;
	return (ray);
}
int			ft_intersp(t_data data, t_ray ray, int *clr, t_pt *intpt)
{
	t_vct	h_vc;
	double	h;
	double	t_co;
	double	d;

	h_vc.a = ((t_sp*)data.obj->fig)->c.x - data.cam->o.x;
	h_vc.b = ((t_sp*)data.obj->fig)->c.y - data.cam->o.y;
	h_vc.c = ((t_sp*)data.obj->fig)->c.z - data.cam->o.z;
	h = sqrt(pow(h_vc.a, 2) + pow(h_vc.b, 2) + pow(h_vc.c, 2));
	t_co = (ray.vct.a * h_vc.a) + (ray.vct.b * h_vc.b) + (ray.vct.c * h_vc.c);
	if (t_co < 0)
		return (0);
	d = sqrt(pow(h, 2) - pow(t_co, 2));
	if (d < 0 || d > (((t_sp*)data.obj->fig)->d) / 2)
		return (0);
	return (1);
}

int			ft_intersect(t_ray ray, t_data *data, int *clr)
{
	t_data	ndata;
	t_pt	intpt;
	int		r;

	r = 0;
	intpt = data->cam->o;
	ndata = *data;
	while (ndata.obj)
	{
		if (ndata.obj->id == SP)
			r = ft_intersp(ndata, ray, clr, &intpt);
		else if (ndata.obj->id == PL)
		{}
		else if (ndata.obj->id == SQ)
		{}
		else if (ndata.obj->id == CY)
		{}
		else if (ndata.obj->id == TR)
		{}
		ndata.obj = ndata.obj->next;
	}
	return (r);
}

int			ft_minirt(t_data *data, void *mlx_ptr, void *win_ptr)
{
	double	x;
	double	y;
	t_ray	ray;
	int		clr;

	x = 0;
	y = 0;
	while (x < data->res->x)
	{
		y = 0;
		while (y < data->res->y)
		{
			ray = ft_camrays(x, y, data);
			if (ft_intersect(ray, data, &clr))
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, 16711680);
			y++;
		}
		x++;
	}
	return (0);
}

int			ft_close(void)
{
	exit(1);
	return (0);
}

int			main(int ac, char **av)
{
	int		fd;
	void	*mlx_ptr;
	void	*win_ptr;
	char	*line;
	t_data	data;

	ft_initdata(&data);
	fd = open(av[1], O_RDONLY);
	while (gnl(fd, &line) > 0)
	{
		if (ft_selectdata(line, &data) > 0)
		{}//error
		free(line);
	}
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, data.res->x, data.res->y, "miniRT");
	ft_minirt(&data, mlx_ptr, win_ptr);
	mlx_hook(win_ptr, 17, 0, ft_close, (void *)0);
	mlx_loop(mlx_ptr);
	return (0);
}
