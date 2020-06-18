/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lights.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:09:35 by daprovin          #+#    #+#             */
/*   Updated: 2020/06/09 19:06:14 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include <math.h>

int				ft_interlgt(t_pt lgto, t_ray lr, t_data *data)
{
	t_data	ndata;
	int		r;

	ndata = *data;
	r = 0;
	while (ndata.obj)
	{
		if (ndata.obj->id == SP)
			r = fmax(ft_interlgtsp((t_sp*)ndata.obj->fig, lr, lgto), r);
		else if (ndata.obj->id == PL)
			r = fmax(ft_interlgtpl((t_pl*)ndata.obj->fig, lr, lgto), r);
		else if (ndata.obj->id == SQ)
			r = fmax(ft_interlgtsq((t_sq*)ndata.obj->fig, lr, lgto), r);
		else if (ndata.obj->id == CY)
			r = fmax(ft_interlgtcy((t_cy*)ndata.obj->fig, lr, lgto), r);
		else if (ndata.obj->id == TR)
			r = fmax(ft_interlgttr((t_tr*)ndata.obj->fig, lr, lgto), r);
		ndata.obj = ndata.obj->next;
	}
	return (r);
}

void			ft_changecf(double (*cf)[3], t_vct lv, t_vct n, t_data data)
{
	double	lang;
	double	ncf[3];

	lang = (lv.a * n.a) + (lv.b * n.b) + (lv.c * n.c);
	ncf[0] = ((*cf)[0]
	+ ((data.lgt->clr[0] * data.lgt->br / 255) * fmax(lang, 0)) > 1) ? 1
	: (*cf)[0] + ((data.lgt->clr[0] * data.lgt->br / 255) * fmax(lang, 0));
	ncf[1] = ((*cf)[1]
	+ ((data.lgt->clr[1] * data.lgt->br / 255) * fmax(lang, 0)) > 1) ? 1
	: (*cf)[1] + ((data.lgt->clr[1] * data.lgt->br / 255) * fmax(lang, 0));
	ncf[2] = ((*cf)[2]
	+ ((data.lgt->clr[2] * data.lgt->br / 255) * fmax(lang, 0)) > 1) ? 1
	: (*cf)[2] + ((data.lgt->clr[2] * data.lgt->br / 255) * fmax(lang, 0));
	(*cf)[0] = ncf[0];
	(*cf)[1] = ncf[1];
	(*cf)[2] = ncf[2];
	return ;
}

int				ft_shine(t_ray lr, t_vct n, t_data d, int *clr)
{
	double	dot;
	double	len;
	t_vct	tmpn;
	t_vct	refv;
	double	spec;

	lr.vct.a = -lr.vct.a;
	lr.vct.b = -lr.vct.b;
	lr.vct.c = -lr.vct.c;
	dot = -(n.a * lr.vct.a + n.b * lr.vct.b + n.c * lr.vct.c);
	len = 2 * dot;
	tmpn.a = len * n.a;
	tmpn.b = len * n.b;
	tmpn.c = len * n.c;
	refv = ft_normalize(ft_addvect(tmpn, lr.vct));
	spec = fmax(-ft_dotprod(refv, d.cam->n), 0);
	spec = pow(spec, 10);
	return (ft_clr(d.lgt->clr, spec, *clr));
}

static void		ft_newcf(double (*cf)[3], t_algt *algt)
{
	(*cf)[0] = algt->clr[0] * algt->br / 255;
	(*cf)[1] = algt->clr[1] * algt->br / 255;
	(*cf)[2] = algt->clr[2] * algt->br / 255;
	return ;
}

void			ft_shadding(int *clr, t_vct n, t_pt ip, t_data *data)
{
	t_data	ndata;
	t_ray	lr;
	double	norm;
	double	cf[3];

	ft_newcf(&cf, data->algt);
	lr.pt = ip;
	ndata = *data;
	while (ndata.lgt)
	{
		norm = sqrt(pow(ndata.lgt->o.x - ip.x, 2)
		+ pow(ndata.lgt->o.y - ip.y, 2) + pow(ndata.lgt->o.z - ip.z, 2));
		lr.vct.a = (ndata.lgt->o.x - ip.x) / norm;
		lr.vct.b = (ndata.lgt->o.y - ip.y) / norm;
		lr.vct.c = (ndata.lgt->o.z - ip.z) / norm;
		if (!(ft_interlgt(ndata.lgt->o, lr, data)))
		{
			ft_changecf(&cf, lr.vct, n, ndata);
			if (data->spec)
				*clr = ft_shine(lr, n, ndata, clr);
		}
		ndata.lgt = ndata.lgt->next;
	}
	ft_3dshadow(clr, cf);
	return ;
}
