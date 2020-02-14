/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lights.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:09:35 by daprovin          #+#    #+#             */
/*   Updated: 2020/02/14 17:14:02 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include "../headers/mlx.h"
#include <math.h>

int			ft_interlgt(t_pt lgto, t_ray lr, t_data *data)
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
			{}//r = fmax(ft_interlgtpl(*((t_pl*)ndata.obj->fig), lr, lgto), r);
		else if (ndata.obj->id == SQ)
		{}
		else if (ndata.obj->id == CY)
		{}
		else if (ndata.obj->id == TR)
		{}
		ndata.obj = ndata.obj->next;
	}
	return (r);
}

void		ft_3dshadow(int *clr, double cf)
{
	int		clrp[3];
	int		c;

	c = *clr;
	clrp[0] = *clr >> 16;
	*clr = c;
	clrp[1] = (*clr & 65280) >> 8;
	*clr = c;
	clrp[2] = *clr & 255;
	*clr = ((int)(clrp[0] * cf) << 16) | ((int)(clrp[1] * cf) << 8)
	| (int)(clrp[2] * cf);
}

double		ft_changecf(double cf, t_vct lv, t_vct n, t_data data)
{
	double	lang;
	double	ncf;

	lang = (lv.a * n.a) + (lv.b * n.b) + (lv.c * n.c);
	ncf = (cf + (data.lgt->br * fmax(lang, 0)) > 1) ? 1
	: cf + (data.lgt->br * fmax(lang, 0));
	return (ncf);
}

void		ft_shadding(int *clr, t_vct n, t_pt ip, t_data *data)
{
	t_data	ndata;
	t_ray	lr;
	double	norm;
	double	cf;

	cf = data->algt->br;
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
			cf = ft_changecf(cf, lr.vct, n, ndata);
		ndata.lgt = ndata.lgt->next;
	}
	ft_3dshadow(clr, cf);
	return ;
}
