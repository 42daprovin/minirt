/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:18:13 by daprovin          #+#    #+#             */
/*   Updated: 2020/02/19 19:06:53 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include "../headers/mlx.h"
#include <math.h>

t_vct		ft_setclrsp(t_data data, int *clr, t_pt intpt)
{
	double	n;
	t_vct	vn;
	int		clro[3];

	clro[0] = ((t_sp*)data.obj->fig)->clr[0];
	clro[1] = ((t_sp*)data.obj->fig)->clr[1];
	clro[2] = ((t_sp*)data.obj->fig)->clr[2];
	*clr = (clro[0] << 16) | (clro[1] << 8) | clro[2];
	vn.a = intpt.x - ((t_sp*)data.obj->fig)->c.x;
	vn.b = intpt.y - ((t_sp*)data.obj->fig)->c.y;
	vn.c = intpt.z - ((t_sp*)data.obj->fig)->c.z;
	n = sqrt(pow(vn.a, 2) + pow(vn.b, 2) + pow(vn.c, 2));
	vn.a = vn.a / n;
	vn.b = vn.b / n;
	vn.c = vn.c / n;
	return (vn);
}

int			ft_intersp2(double *h, t_data data, t_ray ray, double *t_co)
{
	t_vct	vct;

	vct.a = ((t_sp*)data.obj->fig)->c.x - ray.pt.x;
	vct.b = ((t_sp*)data.obj->fig)->c.y - ray.pt.y;
	vct.c = ((t_sp*)data.obj->fig)->c.z - ray.pt.z;
	*h = sqrt(pow(vct.a, 2) + pow(vct.b, 2) + pow(vct.c, 2));
	*t_co = (ray.vct.a * vct.a) + (ray.vct.b * vct.b) + (ray.vct.c * vct.c);
	if (*t_co < 0)
		return (1);
	return (0);

}

t_h			ft_intersp(t_data data, t_ray ray, int *clr, t_pt *intpt)
{
	t_pt	ipt;
	double	h;
	double	t_co;
	double	d;
	t_h		hh;

	hh.r = 0;
	if (ft_intersp2(&h, data, ray, &t_co))
		return (hh);
	d = sqrt(pow(h, 2) - pow(t_co, 2));
	if (d < 0 || d > (((t_sp*)data.obj->fig)->d) / 2)
		return (hh);
	h = t_co - sqrt(pow(((t_sp*)data.obj->fig)->d / 2, 2) - pow(d, 2));
	ipt.x = ray.pt.x + (h * ray.vct.a);
	ipt.y = ray.pt.y + (h * ray.vct.b);
	ipt.z = ray.pt.z + (h * ray.vct.c);
	if (ft_dist(ray.pt, *intpt) == 0
	|| ft_dist(ray.pt, ipt) < ft_dist(ray.pt, *intpt))
	{
		*intpt = ipt;
		hh.n = ft_setclrsp(data, clr, *intpt);
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

	h_vc.a = sp->c.x - lr.pt.x;
	h_vc.b = sp->c.y - lr.pt.y;
	h_vc.c = sp->c.z - lr.pt.z;
	h = sqrt(pow(h_vc.a, 2) + pow(h_vc.b, 2) + pow(h_vc.c, 2));
	t_co = (lr.vct.a * h_vc.a) + (lr.vct.b * h_vc.b) + (lr.vct.c * h_vc.c);
	if (t_co < 0)
		return (0);
	d = sqrt(pow(h, 2) - pow(t_co, 2));
	if (d < 0 || d > sp->d / 2)
		return (0);
	h = t_co - sqrt(pow(sp->d / 2, 2) - pow(d, 2));
	ipt.x = lr.pt.x + (h * lr.vct.a);
	ipt.y = lr.pt.y + (h * lr.vct.b);
	ipt.z = lr.pt.z + (h * lr.vct.c);
	if (ft_checklgt(ipt, lgto, lr))
		return (0);
	return (1);
}
