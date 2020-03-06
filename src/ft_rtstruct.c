/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rtstruct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 08:52:47 by daprovin          #+#    #+#             */
/*   Updated: 2020/03/06 09:25:54 by daprovin         ###   ########.fr       */
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
		h = ft_intersq(ndata, ray, clr, intpt);
	else if (ndata.obj->id == CY)
	{}
	else if (ndata.obj->id == TR)
		h = ft_intertr(ndata, ray, clr, intpt);
	return (h);
}
t_ray		ft_reflexion(t_pt intpt, t_ray ray, t_vct n)
{
	double	cs;
	double	len;
	t_vct	tmpn;
	t_vct	refv;

	cs = -ft_dotprod(ray.vct, n);
	len = 2 * cs;
	tmpn.a = len * n.a;
	tmpn.b = len * n.b;
	tmpn.c = len * n.c;
	refv = ft_normalize(ft_addvect(tmpn, ray.vct));
	ray.vct = refv;
	ray.pt = intpt;
	return (ray);
}
int			ft_refclr(int clr1, int clr, double crf)
{
	int		c;
	int		clrp[3];
	int		clr1p[3];

	c = clr;
	clrp[0] = clr >> 16;
	clr = c;
	clrp[1] = (clr & 65280) >> 8;
	clr = c;
	clrp[2] = clr & 255;
	c = clr1;
	clr1p[0] = clr1 >> 16;
	clr1 = c;
	clr1p[1] = (clr1 & 65280) >> 8;
	clr1 = c;
	clr1p[2] = clr1 & 255;
	c = ((int)(clr1p[0] * (1 - crf) + clrp[0] * crf) << 16)
	| ((int)(clr1p[1] * (1 - crf) + clrp[1] * crf) << 8)
	| (int)(clr1p[2] * (1 - crf) + clrp[2] * crf);
	return (c);
}

int			ft_intersect(t_ray ray, t_data *data, int *clr)
{
	t_data	ndata;
	t_pt	intpt;
	t_h		h;
	t_h		h_p;
	double	rcf;
	int		clr1;

	h.r = 0;
	intpt = ray.pt;
	ndata = *data;
	rcf = 0;
	while (ndata.obj)
	{
		h_p = ft_objtype(ndata, ray, clr, &intpt);
		if (h_p.r == 1)
		{
			h.r = h_p.r;
			h.n = h_p.n;
			data->spec = ndata.obj->spec;
			rcf = ndata.obj->rcf;
		}
		ndata.obj = ndata.obj->next;
	}
	if (h.r != 0)
		ft_shadding(clr, h.n, intpt, data);
	//else
		//*clr = 0;
	if (rcf != 0 && data->depth < MAX_DEPTH)
	{
		clr1 = *clr;
		data->depth++;
		ray = ft_reflexion(intpt, ray, h.n);
		ft_intersect(ray, data, clr);
		*clr = ft_refclr(clr1, *clr, rcf);
	}
	return (h.r);
}

int			ft_minirt(t_data *data)
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
			data->depth = 0;
			if (ft_intersect(ray, data, &clr))
				mlx_pixel_put(data->mlx, data->w_ptr, x, y, clr);
			y++;
		}
		x++;
	}
	return (0);
}
