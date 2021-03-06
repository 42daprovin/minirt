/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 17:24:31 by daprovin          #+#    #+#             */
/*   Updated: 2020/06/18 05:14:34 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include <math.h>

double			ft_intertr2(t_tr tr, t_ray ray)
{
	double	d;
	double	cs;
	double	t;
	t_vct	n;

	n = ft_crossprod(ft_vctatob(tr.a, tr.b), ft_vctatob(tr.a, tr.c));
	n = ft_normalize(n);
	cs = ft_dotprod(ray.vct, n);
	if (cs == 0)
		return (cs);
	d = (-1) * n.a * tr.a.x - n.b * tr.a.y - n.c * tr.a.z;
	t = (-d - n.a * ray.pt.x - n.b * ray.pt.y - n.c * ray.pt.z)
	/ (n.a * ray.vct.a + n.b * ray.vct.b + n.c * ray.vct.c);
	return (t);
}

int				p_is_outside_tr(t_tr tr, t_pt p)
{
	t_vct	vp;
	t_vct	l;
	t_vct	l2;
	double	cs;

	vp = ft_vctatob(tr.a, p);
	l = ft_vctatob(tr.a, tr.b);
	l2 = ft_vctatob(tr.a, tr.c);
	cs = ft_dotprod(ft_crossprod(l, vp), ft_crossprod(l, l2));
	if (cs < 0)
		return (1);
	vp = ft_vctatob(tr.b, p);
	l = ft_vctatob(tr.b, tr.c);
	l2 = ft_vctatob(tr.b, tr.a);
	cs = ft_dotprod(ft_crossprod(l, vp), ft_crossprod(l, l2));
	if (cs < 0)
		return (1);
	vp = ft_vctatob(tr.c, p);
	l = ft_vctatob(tr.c, tr.a);
	l2 = ft_vctatob(tr.c, tr.b);
	cs = ft_dotprod(ft_crossprod(l, vp), ft_crossprod(l, l2));
	if (cs < 0)
		return (1);
	return (0);
}

t_vct			ft_setclrtr(t_data data, int *clr, t_pt ipt, t_ray ray)
{
	int		clro[3];
	t_vct	ivct;
	t_vct	n;
	t_tr	tr;

	tr = *((t_tr*)data.obj->fig);
	clro[0] = ((t_tr*)data.obj->fig)->clr[0];
	clro[1] = ((t_tr*)data.obj->fig)->clr[1];
	clro[2] = ((t_tr*)data.obj->fig)->clr[2];
	*clr = (clro[0] << 16) | (clro[1] << 8) | clro[2];
	ivct = ft_vctatob(ipt, ray.pt);
	n = ft_crossprod(ft_vctatob(tr.a, tr.b), ft_vctatob(tr.a, tr.c));
	n = ft_normalize(n);
	if (ft_dotprod(ivct, n) < 0)
	{
		n.a = n.a * (-1);
		n.b = n.b * (-1);
		n.c = n.c * (-1);
	}
	return (n);
}

t_h				ft_intertr(t_data data, t_ray ray, int *clr, t_pt *intpt)
{
	t_h		hh;
	double	t;
	t_pt	ipt;

	hh.r = 0;
	t = ft_intertr2(*((t_tr*)data.obj->fig), ray);
	if (t <= E)
		return (hh);
	ipt.x = ray.pt.x + t * ray.vct.a;
	ipt.y = ray.pt.y + t * ray.vct.b;
	ipt.z = ray.pt.z + t * ray.vct.c;
	if (p_is_outside_tr(*((t_tr*)data.obj->fig), ipt))
		return (hh);
	if (ft_dist(ray.pt, *intpt) == 0
	|| ft_dist(ray.pt, ipt) < ft_dist(ray.pt, *intpt))
	{
		*intpt = ipt;
		hh.n = ft_setclrtr(data, clr, *intpt, ray);
		hh.r = 1;
	}
	return (hh);
}
