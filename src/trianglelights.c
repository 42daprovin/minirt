/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trianglelights.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 10:31:20 by daprovin          #+#    #+#             */
/*   Updated: 2020/06/18 05:13:20 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include <math.h>

static int		ft_sametriangle(t_tr tr, t_ray lr)
{
	t_vct	v;
	t_vct	n;
	double	cs;

	v = ft_vctatob(tr.a, lr.pt);
	n = ft_crossprod(ft_vctatob(tr.a, tr.b), ft_vctatob(tr.a, tr.c));
	cs = ft_dotprod(v, n);
	if (fabs(cs) < E)
		return (1);
	return (0);
}

int				ft_interlgttr(t_tr *tr, t_ray lr, t_pt lgto)
{
	double	t;
	t_pt	ipt;

	t = ft_intertr2(*tr, lr);
	if (t <= E)
		return (0);
	ipt.x = lr.pt.x + t * lr.vct.a;
	ipt.y = lr.pt.y + t * lr.vct.b;
	ipt.z = lr.pt.z + t * lr.vct.c;
	if (p_is_outside_tr(*tr, ipt))
		return (0);
	if (ft_sametriangle(*tr, lr))
		return (0);
	if (ft_checklgt(ipt, lgto, lr))
		return (0);
	return (1);
}
