/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:30:49 by daprovin          #+#    #+#             */
/*   Updated: 2020/03/06 10:24:54 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include "../headers/mlx.h"
#include <math.h>

t_vct			ft_setclrpl(t_data data, int *clr, t_pt ipt, t_ray ray)
{
	int		clro[3];
	t_vct	ivct;
	t_vct	n;
	double	cs;

	clro[0] = ((t_pl*)data.obj->fig)->clr[0];
	clro[1] = ((t_pl*)data.obj->fig)->clr[1];
	clro[2] = ((t_pl*)data.obj->fig)->clr[2];
	*clr = (clro[0] << 16) | (clro[1] << 8) | clro[2];
	ivct.a = ray.pt.x - ipt.x;
	ivct.b = ray.pt.y - ipt.y;
	ivct.c = ray.pt.z - ipt.z;
	n = ((t_pl*)data.obj->fig)->n;
	if (ivct.a * n.a + ivct.b * n.b + ivct.c * n.c < 0)
	{
		n.a = n.a * (-1);
		n.b = n.b * (-1);
		n.c = n.c * (-1);
	}
	return (n);
}

double			ft_interpl2(t_data data, t_ray ray)
{
	t_pl	pl;
	double	d;
	double	cs;
	double	t;

	pl = *((t_pl*)data.obj->fig);
	cs = (ray.vct.a * pl.n.a) + (ray.vct.b * pl.n.b) + (ray.vct.c * pl.n.c);
	if (cs == 0)
		return (cs);
	d =  (-1) * pl.n.a * pl.pt.x - pl.n.b * pl.pt.y - pl.n.c * pl.pt.z;
	t = (-d - pl.n.a * ray.pt.x - pl.n.b *ray.pt.y - pl.n.c * ray.pt.z)
	/ (pl.n.a * ray.vct.a + pl.n.b * ray.vct.b + pl.n.c * ray.vct.c);
	if (t < 0)
		return (t);
	return (t);
}

t_h					ft_interpl(t_data data, t_ray ray, int *clr, t_pt *intpt)
{
	t_h		hh;
	double	t;
	t_pt	ipt;

	hh.r = 0;
	t = ft_interpl2(data,ray);
	if (t <= E)
		return (hh);
	ipt.x = ray.pt.x + t * ray.vct.a;
	ipt.y = ray.pt.y + t * ray.vct.b;
	ipt.z = ray.pt.z + t * ray.vct.c;
	if (ft_dist(ray.pt, *intpt) == 0
	|| ft_dist(ray.pt, ipt) < ft_dist(ray.pt, *intpt))
	{
		*intpt = ipt;
		hh.n = ft_setclrpl(data, clr, *intpt, ray);
		hh.r = 1;
	}
	return (hh);
}
static int			ft_sameplane(t_pl *pl, t_ray lr)
{
	t_vct	v;
	double	cs;

	v.a = lr.pt.x - pl->pt.x;
	v.b = lr.pt.y - pl->pt.y;
	v.c = lr.pt.z - pl->pt.z;
	cs = v.a * pl->n.a + v.b * pl->n.b + v.c * pl->n.c;
	if (fabs(cs) < E)
		return (1);
	return (0);
}

int					ft_interlgtpl(t_pl *pl, t_ray lr, t_pt lgto)
{
	double	cs;
	double	d;
	t_pt	ipt;
	double	t;

	if (ft_sameplane(pl, lr))
		return (0);
	cs = (lr.vct.a * pl->n.a) + (lr.vct.b * pl->n.b) + (lr.vct.c * pl->n.c);
	if (cs == 0)
		return (0);
	d =  (-1) * pl->n.a * pl->pt.x - pl->n.b * pl->pt.y - pl->n.c * pl->pt.z;
	t = (-d - pl->n.a * lr.pt.x - pl->n.b * lr.pt.y - pl->n.c * lr.pt.z)
	/ (pl->n.a * lr.vct.a + pl->n.b * lr.vct.b + pl->n.c * lr.vct.c);
	if (t <= 0)
		return (0);
	ipt.x = lr.pt.x + (t * lr.vct.a);
	ipt.y = lr.pt.y + (t * lr.vct.b);
	ipt.z = lr.pt.z + (t * lr.vct.c);
	if (ft_checklgt(ipt, lgto, lr))
		return (0);
	return (1);
}
