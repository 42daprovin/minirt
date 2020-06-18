/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 08:41:38 by daprovin          #+#    #+#             */
/*   Updated: 2020/06/18 02:46:28 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include <math.h>

static double	ft_intersq2(t_data data, t_ray ray)
{
	t_sq	sq;
	double	d;
	double	cs;
	double	t;

	sq = *((t_sq*)data.obj->fig);
	cs = (ray.vct.a * sq.n.a) + (ray.vct.b + sq.n.b) + (ray.vct.c * sq.n.c);
	if (cs == 0)
		return (cs);
	d = (-1) * sq.n.a * sq.c.x - sq.n.b * sq.c.y - sq.n.c * sq.c.z;
	t = (-d - sq.n.a * ray.pt.x - sq.n.b * ray.pt.y - sq.n.c * ray.pt.z)
	/ (sq.n.a * ray.vct.a + sq.n.b * ray.vct.b + sq.n.c * ray.vct.c);
	return (t);
}

static int		ft_isnotinsq(t_pt ipt, t_sq sq)
{
	t_vct	r;
	t_vct	pc;
	double	cs;
	double	h;

	if (sq.n.b == 1 || sq.n.b == -1)
	{
		r.a = 0;
		r.b = sq.n.c;
		r.c = -sq.n.b;
	}
	else
	{
		r.a = -sq.n.c;
		r.b = 0;
		r.c = sq.n.a;
	}
	pc = ft_vctatob(sq.c, ipt);
	cs = fabs(ft_dotprod(pc, r));
	if (cs < sqrt(2) / 2)
		cs = cos(M_PI_2 - acos(cs));
	h = (sq.l / 2) / cs;
	if (sqrt(pow(pc.a, 2) + pow(pc.b, 2) + pow(pc.c, 2)) > h)
		return (1);
	return (0);
}

static t_vct	ft_setclrsq(t_data data, int *clr, t_pt ipt, t_ray ray)
{
	int		clro[3];
	t_vct	ivct;
	t_vct	n;

	clro[0] = ((t_sq*)data.obj->fig)->clr[0];
	clro[1] = ((t_sq*)data.obj->fig)->clr[1];
	clro[2] = ((t_sq*)data.obj->fig)->clr[2];
	*clr = (clro[0] << 16) | (clro[1] << 8) | clro[2];
	ivct.a = ray.pt.x - ipt.x;
	ivct.b = ray.pt.y - ipt.y;
	ivct.c = ray.pt.z - ipt.z;
	n = ((t_sq*)data.obj->fig)->n;
	if (ivct.a * n.a + ivct.b * n.b + ivct.c * n.c < 0)
	{
		n.a = n.a * (-1);
		n.b = n.b * (-1);
		n.c = n.c * (-1);
	}
	return (n);
}

t_h				ft_intersq(t_data data, t_ray ray, int *clr, t_pt *intpt)
{
	t_h		hh;
	double	t;
	t_pt	ipt;

	hh.r = 0;
	t = ft_intersq2(data, ray);
	if (t <= E)
		return (hh);
	ipt.x = ray.pt.x + t * ray.vct.a;
	ipt.y = ray.pt.y + t * ray.vct.b;
	ipt.z = ray.pt.z + t * ray.vct.c;
	if (ft_isnotinsq(ipt, *((t_sq*)data.obj->fig)))
		return (hh);
	if (ft_dist(ray.pt, *intpt) == 0
	|| ft_dist(ray.pt, ipt) < ft_dist(ray.pt, *intpt))
	{
		*intpt = ipt;
		hh.n = ft_setclrsq(data, clr, *intpt, ray);
		hh.r = 1;
	}
	return (hh);
}

int				ft_interlgtsq(t_sq *sq, t_ray lr, t_pt lgto)
{
	double	t;
	double	cs;
	t_pt	ipt;
	double	d;

	cs = (lr.vct.a * sq->n.a) + (lr.vct.b * sq->n.b) + (lr.vct.c * sq->n.c);
	if (cs == 0)
		return (0);
	d = (-1) * sq->n.a * sq->c.x - sq->n.b * sq->c.y - sq->n.c * sq->c.z;
	t = (-d - sq->n.a * lr.pt.x - sq->n.b * lr.pt.y - sq->n.c * lr.pt.z)
	/ (sq->n.a * lr.vct.a + sq->n.b * lr.vct.b + sq->n.c * lr.vct.c);
	if (t <= 0)
		return (0);
	ipt.x = lr.pt.x + (t * lr.vct.a);
	ipt.y = lr.pt.y + (t * lr.vct.b);
	ipt.z = lr.pt.z + (t * lr.vct.c);
	if (ft_isnotinsq(ipt, *sq))
		return (0);
	if (ft_samesquare(sq, lr))
		return (0);
	if (ft_checklgt(ipt, lgto, lr))
		return (0);
	return (1);
}
