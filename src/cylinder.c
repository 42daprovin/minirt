/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:44:14 by daprovin          #+#    #+#             */
/*   Updated: 2020/03/10 02:19:10 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include "../headers/mlx.h"
#include <math.h>

void		ft_intercy2(t_cy cy, t_ray ray, double *t0, double *t1)
{
	t_vct	v;
	t_vct	u;
	double	A;
	double	B;
	double	C;

	v = ft_escprod(ft_dotprod2(ray.vct, cy.n), cy.n);
	v.a = ray.vct.a - v.a;
	v.b = ray.vct.b - v.b;
	v.c = ray.vct.c - v.c;
	u = ft_escprod(ft_dotprod2(ft_vctatob(cy.pt, ray.pt), cy.n), cy.n);
	u = ft_subsvct(ft_vctatob(cy.pt, ray.pt), u);
	A = ft_dotprod2(v, v);
	B = 2 * ft_dotprod2(v, u);
	C = ft_dotprod2(u, u) - pow(cy.d / 2, 2);
	*t0 = (-B + sqrt(pow(B, 2) - 4 * A * C)) / (2 * A);
	*t1 = (-B - sqrt(pow(B, 2) - 4 * A * C)) / (2 * A);
	return ;
}

double		distpltopt(t_cy cy, t_pt *ipt, double (*t)[3], t_ray ray)
{
	double	h;
	double	d;

	(*t)[2] = fmin((*t)[0], (*t)[1]);
	if ((*t)[2] < E)
		(*t)[2] = fmax((*t)[0], (*t)[1]);
	ipt->x = ray.pt.x + ((*t)[2] * ray.vct.a);
	ipt->y = ray.pt.y + ((*t)[2] * ray.vct.b);
	ipt->z = ray.pt.z + ((*t)[2] * ray.vct.c);
	d = (-1) * cy.n.a * cy.pt.x - cy.n.b * cy.pt.y - cy.n.c * cy.pt.z;
	h = fabs(cy.n.a * ipt->x + cy.n.b * ipt->y + cy.n.c * ipt->z + d)
	/ sqrt(pow(cy.n.a, 2) + pow(cy.n.b, 2) + pow(cy.n.c, 2));
	if (h > cy.d / 2)
		(*t)[2] = fmax((*t)[0], (*t)[1]);
	else
		return (0);
	ipt->x = ray.pt.x + ((*t)[2] * ray.vct.a);
	ipt->y = ray.pt.y + ((*t)[2] * ray.vct.b);
	ipt->z = ray.pt.z + ((*t)[2] * ray.vct.c);
	d = (-1) * cy.n.a * cy.pt.x - cy.n.b * cy.pt.y - cy.n.c * cy.pt.z;
	h = fabs(cy.n.a * ipt->x + cy.n.b * ipt->y + cy.n.c * ipt->z + d)
	/ sqrt(pow(cy.n.a, 2) + pow(cy.n.b, 2) + pow(cy.n.c, 2));
	if (h > cy.d / 2)
		return (1);
	return (0);
}

t_vct		ft_setclrcy(t_cy cy, int *clr, t_pt ipt)
{
	int		clro[3];
	t_vct	vn;
	double	t;

	clro[0] = cy.clr[0];
	clro[1] = cy.clr[1];
	clro[2] = cy.clr[2];
	*clr = (clro[0] << 16) | (clro[1] << 8) | clro[2];
	t = ft_dotprod2(ft_vctatob(cy.pt, ipt), cy.n) / ft_dotprod2(cy.n, cy.n);
	vn = ft_subsvct(ft_vctatob(cy.pt, ipt), ft_escprod(t, cy.n));
	return (ft_normalize(vn));
}

t_h			ft_intercy(t_data data, t_ray ray, int *clr, t_pt *intpt)
{
	double	t[3];
	t_h		hh;
	t_pt	ipt;

	hh.r = 0;
	ft_intercy2(*(t_cy*)data.obj->fig, ray, &t[0], &t[1]);
	if (t[0] != t[0] && t[1] != t[1])
		return (hh);
	if (t[0] < E && t[1] < E)
		return (hh);
	//else if (t[0] < E || t[1] < E)
		//t[2] = fmax(t[0], t[1]);
	else if (distpltopt(*(t_cy*)data.obj->fig, &ipt, &t, ray))
		return (hh);
	if (ft_dist(ray.pt, *intpt) == 0
	|| ft_dist(ray.pt, ipt) < ft_dist(ray.pt, *intpt))
	{
		*intpt = ipt;
		hh.n = ft_setclrcy(*(t_cy*)data.obj->fig, clr, *intpt);
		if (t[2] == fmax(t[0], t[1]) && t[0] != t[1])
			hh.n = ft_escprod(-1, hh.n);
		hh.r = 1;
	}
	return (hh);
}

int			ft_interlgtcy(t_cy *cy, t_ray lr, t_pt lgto)
{
	double	t[3];
	t_pt	ipt;

	ft_intercy2(*cy, lr, &t[0], &t[1]);
	if (t[0] != t[0] && t[1] != t[1])
		return (0);
	if (t[0] < E && t[1] < E)
		return (0);
	//else if (t[0] < E || t[1] < E)
		//t[2] = fmax(t[0], t[1]);
	else if (distpltopt(*cy, &ipt, &t, lr))
		return (0);
	if (ft_checklgt(ipt, lgto, lr))
		return (0);
	return (1);
}
