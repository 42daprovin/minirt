/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rtstruct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 08:52:47 by daprovin          #+#    #+#             */
/*   Updated: 2020/02/14 12:22:37 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include "../headers/mlx.h"
#include <math.h>

t_h			ft_objtype(t_data ndata, t_ray ray, int *clr, t_pt *intpt)
{
	t_h		h;

	h.r = 0;
	if (ndata.obj->id == SP)
		h = ft_intersp(ndata, ray, clr, intpt);
	else if (ndata.obj->id == PL)
		h = ft_interpl(ndata, ray, clr, intpt);
	else if (ndata.obj->id == SQ)
	{}
	else if (ndata.obj->id == CY)
	{}
	else if (ndata.obj->id == TR)
	{}
	return (h);
}

int			ft_intersect(t_ray ray, t_data *data, int *clr)
{
	t_data	ndata;
	t_pt	intpt;
	t_h		h;
	t_h		h_p;

	h.r = 0;
	intpt = data->cam->o;
	ndata = *data;
	while (ndata.obj)
	{
		h_p = ft_objtype(ndata, ray, clr, &intpt);
		//h.r = fmax(h_p.r, h.r);
		//h.n = h_p.n;
		if (h_p.r == 1)
		{
			h.r = h_p.r;
			h.n = h_p.n;
		}
		ndata.obj = ndata.obj->next;
	}
	if (h.r != 0)
		ft_shadding(clr, h.n, intpt, data);
	return (h.r);
}

int			ft_minirt(t_data *data, void *mlx_ptr, void *win_ptr)
{
	double	x;
	double	y;
	t_ray	ray;
	int		clr;

	x = 0;
	y = 0;
	clr = 0;
	while (x < data->res->x)
	{
		y = 0;
		while (y < data->res->y)
		{
			ray = ft_camrays(x, y, data);
			if (ft_intersect(ray, data, &clr))
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, clr);
			y++;
		}
		x++;
	}
	return (0);
}
