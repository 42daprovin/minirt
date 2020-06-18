/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:18:13 by daprovin          #+#    #+#             */
/*   Updated: 2020/06/10 00:45:06 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include <math.h>

t_vct		ft_setclrsp(t_data data, int *clr, t_pt intpt)
{
	t_vct	vn;
	int		clro[3];

	clro[0] = ((t_sp*)data.obj->fig)->clr[0];
	clro[1] = ((t_sp*)data.obj->fig)->clr[1];
	clro[2] = ((t_sp*)data.obj->fig)->clr[2];
	*clr = (clro[0] << 16) | (clro[1] << 8) | clro[2];
	vn = ft_vctatob(((t_sp*)data.obj->fig)->c, intpt);
	vn = ft_normalize(vn);
	return (vn);
}

int			ft_intersp2(t_supp *s, t_data data, t_ray ray, double *t_co)
{
	t_vct	vct;

	vct.a = ((t_sp*)data.obj->fig)->c.x - ray.pt.x;
	vct.b = ((t_sp*)data.obj->fig)->c.y - ray.pt.y;
	vct.c = ((t_sp*)data.obj->fig)->c.z - ray.pt.z;
	s->h = sqrt(pow(vct.a, 2) + pow(vct.b, 2) + pow(vct.c, 2));
	*t_co = (ray.vct.a * vct.a) + (ray.vct.b * vct.b) + (ray.vct.c * vct.c);
	s->d = sqrt(pow(s->h, 2) - pow(*t_co, 2));
	if (s->d < 0 || s->d > (((t_sp*)data.obj->fig)->d) / 2)
		return (1);
	s->h = *t_co - sqrt(pow(((t_sp*)data.obj->fig)->d / 2, 2) - pow(s->d, 2));
	if (s->h < E)
		s->h =
		*t_co + sqrt(pow(((t_sp*)data.obj->fig)->d / 2, 2) - pow(s->d, 2));
	if (s->h <= 3 * E)
		return (1);
	return (0);
}

t_h			ft_intersp(t_data data, t_ray ray, int *clr, t_pt *intpt)
{
	t_pt	ipt;
	double	t_co;
	t_supp	s;
	t_h		hh;

	hh.r = 0;
	if (ft_intersp2(&s, data, ray, &t_co))
		return (hh);
	ipt.x = ray.pt.x + (s.h * ray.vct.a);
	ipt.y = ray.pt.y + (s.h * ray.vct.b);
	ipt.z = ray.pt.z + (s.h * ray.vct.c);
	if (ft_dist(ray.pt, *intpt) == 0
	|| ft_dist(ray.pt, ipt) < ft_dist(ray.pt, *intpt))
	{
		*intpt = ipt;
		hh.n = ft_setclrsp(data, clr, *intpt);
		if (fabs(t_co)
		- fabs(sqrt(pow(((t_sp*)data.obj->fig)->d / 2, 2) - pow(s.d, 2))) < E)
			hh.n = ft_escprod(-1, hh.n);
		hh.r = 1;
	}
	return (hh);
}

int			ft_interlgtsp(t_sp *sp, t_ray lr, t_pt lgto)
{
	t_vct	h_vc;
	double	h;
	double	t_co;
	double	d;
	t_pt	ipt;

	h_vc = ft_vctatob(lr.pt, sp->c);
	h = sqrt(pow(h_vc.a, 2) + pow(h_vc.b, 2) + pow(h_vc.c, 2));
	t_co = (lr.vct.a * h_vc.a) + (lr.vct.b * h_vc.b) + (lr.vct.c * h_vc.c);
	d = sqrt(pow(h, 2) - pow(t_co, 2));
	if (d < 0 || d > sp->d / 2)
		return (0);
	h = t_co - sqrt(pow(sp->d / 2, 2) - pow(d, 2));
	if (h < 0)
		h = t_co + sqrt(pow(sp->d / 2, 2) - pow(d, 2));
	if (h < 2 * E)
		return (0);
	ipt.x = lr.pt.x + (h * lr.vct.a);
	ipt.y = lr.pt.y + (h * lr.vct.b);
	ipt.z = lr.pt.z + (h * lr.vct.c);
	if (ft_checklgt(ipt, lgto, lr))
		return (0);
	return (1);
}
