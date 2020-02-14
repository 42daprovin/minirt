/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rtutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 08:37:26 by daprovin          #+#    #+#             */
/*   Updated: 2020/02/14 09:16:12 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include "../headers/mlx.h"
#include <math.h>

double		ft_dist(t_pt p1, t_pt p2)
{
	double	d;

	d = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
	return (d);
}

int			ft_close(void)
{
	exit(1);
	return (0);
}

int			ft_checklgt(t_pt ipt, t_pt lgto, t_ray lr)
{
	t_vct	lobj2;
	double	cs;

	lobj2.a = lgto.x - ipt.x;
	lobj2.b = lgto.y - ipt.y;
	lobj2.c = lgto.z - ipt.z;
	cs = (lobj2.a * lr.vct.a) + (lobj2.b * lr.vct.b) + (lobj2.c * lr.vct.c);
	if (cs < 0)
		return (1);
	else
		return (0);
}
