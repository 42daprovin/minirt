/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:44:14 by daprovin          #+#    #+#             */
/*   Updated: 2020/03/09 11:35:21 by daprovin         ###   ########.fr       */
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
	t[2] = fmin(t[0], t[1]);
	ipt.x = ray.pt.x + (t[2] * ray.vct.a);
	ipt.y = ray.pt.y + (t[2] * ray.vct.b);
	ipt.z = ray.pt.z + (t[2] * ray.vct.c);
	if (ft_dist(ray.pt, *intpt) == 0
	|| ft_dist(ray.pt, ipt) < ft_dist(ray.pt, *intpt))
	{
		*intpt = ipt;
		hh.n = ft_escprod(-1, data.cam->n);
		*clr = 255 << 16;
		hh.r = 1;
	}
	return (hh);
}
