/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:30:49 by daprovin          #+#    #+#             */
/*   Updated: 2020/02/14 20:29:46 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include "../headers/mlx.h"
#include <math.h>

t_vct		ft_setclrpl(t_data data, int *clr, t_pt ipt)
{
	int		clro[3];
	t_vct	ivct;
	t_vct	n;
	double	cs;

	clro[0] = ((t_pl*)data.obj->fig)->clr[0];
	clro[1] = ((t_pl*)data.obj->fig)->clr[1];
	clro[2] = ((t_pl*)data.obj->fig)->clr[2];
	*clr = (clro[0] << 16) | (clro[1] << 8) | clro[2];
	ivct.a = data.cam->o.x - ipt.x;
	ivct.b = data.cam->o.x - ipt.y;
	ivct.c = data.cam->o.x - ipt.z;
	n = ((t_pl*)data.obj->fig)->n;
	if (ivct.a * n.a + ivct.b * n.b + ivct.c * n.c < 0)
	{
		n.a = n.a * (-1);
		n.b = n.b * (-1);
		n.c = n.c * (-1);
	}
	return (n);
}

t_h			ft_interpl(t_data data, t_ray ray, int *clr, t_pt *intpt)
{
	double	cs;
	t_h		hh;
	double	t;
	double	d;
	t_pl	pl;
	t_pt	ipt;

	hh.r = 0;
	pl = *((t_pl*)data.obj->fig);
	cs = (ray.vct.a * pl.n.a) + (ray.vct.b * pl.n.b) + (ray.vct.c * pl.n.c);
	if (cs == 0)
		return (hh);
	d =  (-1) * pl.n.a * pl.pt.x - pl.n.b * pl.pt.y - pl.n.c * pl.pt.z;
	t = (-d - pl.n.a * ray.pt.x - pl.n.b *ray.pt.y - pl.n.c * ray.pt.z)
	/ (pl.n.a * ray.vct.a + pl.n.b * ray.vct.b + pl.n.c * ray.vct.c);
	if (t < 0)
		return (hh);
	ipt.x = ray.pt.x + t * ray.vct.a;
	ipt.y = ray.pt.y + t * ray.vct.b;
	ipt.z = ray.pt.z + t * ray.vct.c;
	if (ft_dist(data.cam->o, *intpt) == 0
	|| ft_dist(data.cam->o, ipt) < ft_dist(data.cam->o, *intpt))
	{
		*intpt = ipt;
		hh.n = ft_setclrpl(data, clr, *intpt);
		hh.r = 1;
	}
	return (hh);
}

int			ft_interlgtpl(t_pl pl, t_ray lr, t_pt lgto)//cambiar entera copiando el
                                                       //metodo de arriba
{
	double	ang;
	double	d;
	t_pt	ipt;

	ang = (lr.vct.a * pl.n.a) + (lr.vct.b * pl.n.b) + (lr.vct.c * pl.n.c);
	if (ang == 0)
		return (0);
	if (ang < 0)
		ang = ang * (-1);
	d = fabs(pl.n.a * lr.pt.x + pl.n.b * lr.pt.y + pl.n.c * lr.pt.z
	+ ((-1) * pl.n.a * pl.pt.x - pl.n.b * pl.pt.y - pl.n.c * pl.pt.z));
	if (d == 0)
		return (0);
	ipt.x = lr.pt.x + ((d / ang) * lr.vct.a);
	ipt.y = lr.pt.y + ((d / ang) * lr.vct.b);
	ipt.z = lr.pt.z + ((d / ang) * lr.vct.c);
	if (ft_checklgt(ipt, lgto, lr))
		return (0);
	return (1);
}
