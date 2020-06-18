/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rtutils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 19:14:56 by daprovin          #+#    #+#             */
/*   Updated: 2020/06/09 19:16:40 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include <math.h>

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
