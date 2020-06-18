/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rtutils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 19:12:53 by daprovin          #+#    #+#             */
/*   Updated: 2020/06/18 05:58:28 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include <math.h>

double		ft_dist(t_pt p1, t_pt p2)
{
	double	d;

	d = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
	return (d);
}

int			ft_close(void)
{
	exit(0);
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
	if (key == 65363 && (data->cam->next != NULL))
	{
		data->cam = data->cam->next;
		mlx_put_image_to_window(data->mlx, data->w_ptr, data->cam->imptr, 0, 0);
	}
	if (key == 65361 && (data->cam->back != NULL))
	{
		data->cam = data->cam->back;
		mlx_put_image_to_window(data->mlx, data->w_ptr, data->cam->imptr, 0, 0);
	}
	if (key == 65307)
	{
		exit(0);
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
