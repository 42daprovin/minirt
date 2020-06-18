/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rtstruct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 08:52:47 by daprovin          #+#    #+#             */
/*   Updated: 2020/06/18 02:48:40 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
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
		h = ft_intercy(ndata, ray, clr, intpt);
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

double		ft_intersect2(t_ray ray, int *clr, t_structsupp *s, t_data *data)
{
	t_data	ndata;
	t_h		h_p;
	double	rcf;

	ndata = *data;
	rcf = 0;
	while (ndata.obj)
	{
		h_p = ft_objtype(ndata, ray, clr, &(s->intpt));
		if (h_p.r == 1)
		{
			s->h.r = h_p.r;
			s->h.n = h_p.n;
			data->spec = ndata.obj->spec;
			rcf = ndata.obj->rcf;
		}
		ndata.obj = ndata.obj->next;
	}
	return (rcf);
}

int			ft_intersect(t_ray ray, t_data *data, int *clr)
{
	t_structsupp	s;
	double			rcf;
	int				clr1;

	s.h.r = 0;
	s.intpt = ray.pt;
	rcf = ft_intersect2(ray, clr, &s, data);
	if (s.h.r != 0)
		ft_shadding(clr, s.h.n, s.intpt, data);
	else
		*clr = 0;
	if (rcf != 0 && data->depth < MAX_DEPTH)
	{
		clr1 = *clr;
		data->depth++;
		ray = ft_reflexion(s.intpt, ray, s.h.n);
		ft_intersect(ray, data, clr);
		*clr = ft_refclr(clr1, *clr, rcf);
	}
	return (1);
}

int			ft_minirt(t_data *data)
{
	double	x;
	double	y;
	int		clr;
	t_cam	*d;

	d = data->cam;
	while (data->cam)
	{
		y = -1;
		clr = 0;
		while (y++ < data->res->y)
		{
			x = -1;
			while (x++ < data->res->x)
			{
				clr = ft_supersampling(x, y, data);
				data->cam->imdt[(int)(y * (data->size_line / 4) + x)] = clr;
			}
		}
		data->cam = data->cam->next;
	}
	data->cam = d;
	return (0);
}
