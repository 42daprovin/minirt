/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rtutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 08:37:26 by daprovin          #+#    #+#             */
/*   Updated: 2020/02/18 16:18:36 by daprovin         ###   ########.fr       */
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

int			ft_changecam(int key, t_data *data)
{
	if (key == 124 && (data->cam->next != NULL))
	{
		data->cam = data->cam->next;
		ft_minirt(data);
	}
	if (key == 123 && (data->cam->back != NULL))
	{
		data->cam = data->cam->back;
		ft_minirt(data);
	}
	return (1);
}

t_vct		ft_addvect(t_vct v, t_vct u)
{
	 t_vct w;

	 w.a = v.a + u.a;
	 w.b = v.b + u.b;
	 w.c = v.c + u.c;
	 return (w);
}

t_vct		ft_normalize(t_vct v)
{
	double	n;

	n = sqrt(pow(v.a, 2) + pow(v.b, 2) + pow(v.c, 2));
	v.a = v.a / n;
	v.b = v.b / n;
	v.c = v.c / n;
	return (v);
}

double		ft_dotprod(t_vct v, t_vct u)
{
	double	d;

	d = (v.a * u.a + v.b * u.b + v.c * u.c);
	return (d);
}
