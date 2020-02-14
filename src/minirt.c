/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:55:58 by daprovin          #+#    #+#             */
/*   Updated: 2020/02/14 19:14:02 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include "../headers/mlx.h"
#include <math.h>

static int	ft_slcdata1(char **split, t_data *data)
{
	int		r;

	if (**split == 'R')
		r = ft_reso(split, data);
	else if (**split == 'A')
		r = ft_algt(split, data);
	else if (**split == 'c')
		r = ft_cam(split, data);
	else if (**split == 'l')
		r = ft_lgt(split, data);
	else
		return (1);
	return (r);
}

static int	ft_slcdata2(char **split, t_data *data)
{
	int		r;

	if (**split == 'p' && *((*split) + 1) == 'l')
		r = ft_pl(split, data);
	else if (**split == 's' && *((*split) + 1) == 'p')
		r = ft_sp(split, data);
	else if (**split == 's' && *((*split) + 1) == 'q')
		r = ft_sq(split, data);
	else if (**split == 'c' && *((*split) + 1) == 'y')
		r = ft_cy(split, data);
	else if (**split == 't' && *((*split) + 1) == 'r')
		r = ft_tr(split, data);
	else
		return (1);
	return (r);
}

static int	ft_selectdata(char *line, t_data *data)
{
	char	**split;
	int		r;

	if (!(split = ft_split(line, ' ')))
		return (2);
	if (!(*split))
	{
		free(split);
		return (0);
	}
	if (ft_strlen(*split) == 1)
		r = ft_slcdata1(split, data);
	else
		r = ft_slcdata2(split, data);
	free(split);
	return (r);
}

static void	ft_initdata(t_data *data)
{
	data->obj = NULL;
	data->lgt = NULL;
	data->cam = NULL;
	data->res = NULL;
	data->algt = NULL;
}
/*
t_ray		ft_rotx(t_ray ray, t_data *data, double ct)
{
	t_ray	rayx;

	if (data->cam->n.b >= 0)
	{
		rayx.vct.a = ray.vct.a;
		rayx.vct.b = (ct * ray.vct.b) - (sin(acos(ct)) * ray.vct.c);
		rayx.vct.c = (sin(acos(ct)) * ray.vct.b) + (ct * ray.vct.c);
	}
	else
	{
		rayx.vct.a = ray.vct.a;
		rayx.vct.b = (ct * ray.vct.b) + (sin(acos(ct)) * ray.vct.c);
		rayx.vct.c = (ct * ray.vct.c) - (sin(acos(ct)) * ray.vct.b);
	}
	return (rayx);
}

t_ray		ft_roty(t_ray ray, t_data *data, double ca)
{
	t_ray	rray;

	if (data->cam->n.a >= 0)
	{
		rray.vct.a = (ca * ray.vct.a) + (sin(acos(ca)) * ray.vct.c);
		rray.vct.b = ray.vct.b;
		rray.vct.c = (ca * ray.vct.c) - (sin(acos(ca)) * ray.vct.a);
	}
	else
	{
		rray.vct.a = (ca * ray.vct.a) - (sin(acos(ca)) * ray.vct.c);
		rray.vct.b = ray.vct.b;
		rray.vct.c = (ca * ray.vct.c) + (sin(acos(ca)) * ray.vct.a);
	}
	return (rray);
}

t_ray		ft_rotray(t_ray ray, t_data *data)
{
	double	ct;
	double	ca;
	t_vct	cvct;
	double	nproy;
	t_ray	rray;

	cvct = data->cam->n;
	nproy = sqrt(pow(cvct.b, 2) + pow(cvct.c, 2));
	ct = (cvct.c * (-1)) / nproy;
	ca = (pow(cvct.b, 2) + pow(cvct.c, 2)) / nproy;
	rray = ft_rotx(ray, data, ct);
	rray = ft_roty(rray, data, ca);
	rray.pt.x = data->cam->o.x;
	rray.pt.y = data->cam->o.y;
	rray.pt.z = data->cam->o.z;
	return (rray);
}

t_ray		ft_camrays(double x, double y, t_data *data)
{
	t_pt	pt;
	double	norm;
	t_ray	ray;

	pt.x = ((2 * ((x + 0.5) / (data->res->x))) - 1)
	* ((data->res->x) / (data->res->y))
	* tan(((data->cam->fov) * (M_PI / 180)) / 2);
	pt.y = (1 - (2 * ((y + 0.5) / (data->res->y))))
	* tan(((data->cam->fov) * (M_PI / 180)) / 2);
	norm = sqrt(pow(pt.x, 2) + pow(pt.y, 2) + 1);
	ray.vct.a = (pt.x / norm);
	ray.vct.b = (pt.y / norm);
	ray.vct.c = (-1 / norm);
	ray.pt.x = 0;
	ray.pt.y = 0;
	ray.pt.z = 0;
	ray = ft_rotray(ray, data);
	return (ray);
}

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

double		ft_dist(t_pt p1, t_pt p2)
{
	double	d;

	d = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
	return (d);
}

int			ft_intersp2(double *h, t_data data, t_ray ray, double *t_co)
{
	t_vct	vct;

	vct.a = ((t_sp*)data.obj->fig)->c.x - data.cam->o.x;
	vct.b = ((t_sp*)data.obj->fig)->c.y - data.cam->o.y;
	vct.c = ((t_sp*)data.obj->fig)->c.z - data.cam->o.z;
	*h = sqrt(pow(vct.a, 2) + pow(vct.b, 2) + pow(vct.c, 2));
	*t_co = (ray.vct.a * vct.a) + (ray.vct.b * vct.b) + (ray.vct.c * vct.c);
	if (t_co < 0)
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
	hh.r = 1;
	h = t_co - sqrt(pow(((t_sp*)data.obj->fig)->d / 2, 2) - pow(d, 2));
	ipt.x = data.cam->o.x + (h * ray.vct.a);
	ipt.y = data.cam->o.y + (h * ray.vct.b);
	ipt.z = data.cam->o.z + (h * ray.vct.c);
	if (ft_dist(data.cam->o, *intpt) == 0
	|| ft_dist(data.cam->o, ipt) < ft_dist(data.cam->o, *intpt))
	{
		*intpt = ipt;
		hh.n = ft_setclrsp(data, clr, *intpt);
	}
	return (hh);
}

t_h			ft_objtype(t_data ndata, t_ray ray, int *clr, t_pt *intpt)
{
	t_h		h;

	h.r = 0;
	if (ndata.obj->id == SP)
		h = ft_intersp(ndata, ray, clr, intpt);
	else if (ndata.obj->id == PL)
	{}
	else if (ndata.obj->id == SQ)
	{}
	else if (ndata.obj->id == CY)
	{}
	else if (ndata.obj->id == TR)
	{}
	return (h);
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
		{}
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

int			ft_intersect(t_ray ray, t_data *data, int *clr)
{
	t_data	ndata;
	t_pt	intpt;
//	int		r;
	t_h		h;
	t_h		h_p;

	h.r = 0;
	intpt = data->cam->o;
	ndata = *data;
	while (ndata.obj)
	{
		h_p = ft_objtype(ndata, ray, clr, &intpt);
		h.r = fmax(h_p.r, h.r);
		h.n = h_p.n;
		ndata.obj = ndata.obj->next;
	}
	if (h.r != 0)
		ft_shadding(clr, h.n, intpt, data);
	return (h.r);
}

int			ft_minirt(t_data *data, void *mlx_ptr, void *win_ptr)
{
	double	x;
	double	y;
	t_ray	ray;
	int		clr;

	x = 0;
	y = 0;
	clr = 0;
	while (x < data->res->x)
	{
		y = 0;
		while (y < data->res->y)
		{
			ray = ft_camrays(x, y, data);
			if (ft_intersect(ray, data, &clr))
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, clr);
			y++;
		}
		x++;
	}
	return (0);
}

int			ft_close(void)
{
	exit(1);
	return (0);
}
*/
int			main(int ac, char **av)
{
	int		fd;
	void	*mlx_ptr;
	void	*win_ptr;
	char	*line;
	t_data	data;

	ft_initdata(&data);
	fd = open(av[1], O_RDONLY);
	while (gnl(fd, &line) > 0)
	{
		if (ft_selectdata(line, &data) > 0)
		{}//error
		free(line);
	}
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, data.res->x, data.res->y, "miniRT");
	ft_minirt(&data, mlx_ptr, win_ptr);
	mlx_hook(win_ptr, 17, 0, ft_close, (void *)0);
	mlx_loop(mlx_ptr);
	return (0);
}
