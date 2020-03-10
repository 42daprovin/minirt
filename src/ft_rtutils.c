/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rtutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 08:37:26 by daprovin          #+#    #+#             */
/*   Updated: 2020/03/10 18:30:07 by daprovin         ###   ########.fr       */
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
	double	n1;
	double	n2;

	n1 = sqrt(pow(v.a, 2) + pow(v.b, 2) + pow(v.c, 2));
	n2 = sqrt(pow(u.a, 2) + pow(u.b, 2) + pow(u.c, 2));
	d = (v.a * u.a + v.b * u.b + v.c * u.c) / (n1 * n2);
	return (d);
}

double		ft_dotprod2(t_vct v, t_vct u)
{
	double	d;

	d = (v.a * u.a + v.b * u.b + v.c * u.c);
	return (d);
}

t_vct		ft_escprod(double k, t_vct v)
{
	v.a = k * v.a;
	v.b = k * v.b;
	v.c = k * v.c;
	return (v);
}

t_vct		ft_vctatob(t_pt a, t_pt b)
{
	t_vct v;

	v.a = b.x - a.x;
	v.b = b.y - a.y;
	v.c = b.z - a.z;
	return (v);
}

t_vct		ft_crossprod(t_vct v, t_vct u)
{
	t_vct	w;

	w.a = v.b * u.c - v.c * u.b;
	w.b = v.c * u.a - v.a * u.c;
	w.c = v.a * u.b - v.b * u.a;
	return (w);
}

t_vct		ft_subsvct(t_vct v, t_vct u)
{
	t_vct	w;

	w.a = v.a - u.a;
	w.b = v.b - u.b;
	w.c = v.c - u.c;
	return (w);
}

void			init_mlx(t_data *data)
{
	t_mlximg	im;

	data->mlx = mlx_init();
	data->w_ptr =
	mlx_new_window(data->mlx, data->res->x, data->res->y, "miniRT");
	data->imptr = mlx_new_image(data->mlx, data->res->x, data->res->y);
	data->imdt = (int*)mlx_get_data_addr(data->imptr, &im.bpp, &im.sl, &im.nd);
	data->size_line = im.sl;
	return ;
}

/*int				ft_checkinput(int ac,char **av)
{
	int		i;

	if (ac < 2 || ac > 3)
		return (3);
} in progress






