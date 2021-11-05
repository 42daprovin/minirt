/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rtutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 08:37:26 by daprovin          #+#    #+#             */
/*   Updated: 2021/11/04 23:24:16 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include <math.h>

void			ft_chess(t_pt ipt, int *clr, double nb)
{
	int		i;
	int		j;

	i = (ipt.z < 0) ? (int)fabs(ipt.z) + 5 : (int)ipt.z;
	j = (ipt.x < 0) ? (int)fabs(ipt.x) + 5 : (int)ipt.x;
	if (i % 10 < 5 && fabs(nb) == 1)
		*clr = (~16777215) & 16777215;
	else
		*clr = 16777215;
	if (j % 10 < 5 && fabs(nb) == 1)
		*clr = (~*clr) & 16777215;
}

int				ft_refclr(int clr1, int clr, double crf)
{
	int		c;
	int		clrp[3];
	int		clr1p[3];

	c = clr;
	clrp[0] = clr >> 16;
	clr = c;
	clrp[1] = (clr & 65280) >> 8;
	clr = c;
	clrp[2] = clr & 255;
	c = clr1;
	clr1p[0] = clr1 >> 16;
	clr1 = c;
	clr1p[1] = (clr1 & 65280) >> 8;
	clr1 = c;
	clr1p[2] = clr1 & 255;
	c = ((int)(clr1p[0] * (1 - crf) + clrp[0] * crf) << 16)
	| ((int)(clr1p[1] * (1 - crf) + clrp[1] * crf) << 8)
	| (int)(clr1p[2] * (1 - crf) + clrp[2] * crf);
	return (c);
}

t_vct			ft_crossprod(t_vct v, t_vct u)
{
	t_vct	w;

	w.a = v.b * u.c - v.c * u.b;
	w.b = v.c * u.a - v.a * u.c;
	w.c = v.a * u.b - v.b * u.a;
	return (w);
}

t_vct			ft_subsvct(t_vct v, t_vct u)
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
	int			sizex;
	int			sizey;
	t_cam		*cam;

	cam = data->cam;
	data->mlx = mlx_init();
	mlx_get_screen_size(data->mlx, &sizex, &sizey);
	if (sizex < data->res->x)
		data->res->x = sizex;
	if (sizey < data->res->y)
		data->res->y = sizey;
	data->w_ptr =
	mlx_new_window(data->mlx, data->res->x, data->res->y, "miniRT");
	while (cam)
	{
		cam->imptr = mlx_new_image(data->mlx, data->res->x, data->res->y);
		cam->imdt =
		(int*)mlx_get_data_addr(cam->imptr, &im.bpp, &im.sl, &im.nd);
		cam = cam->next;
	}
	data->size_line = im.sl;
	data->bpp = im.bpp;
	return ;
}
