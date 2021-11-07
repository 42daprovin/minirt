/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rtstruct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 08:52:47 by daprovin          #+#    #+#             */
/*   Updated: 2021/11/07 23:12:45 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include <math.h>

pthread_mutex_t	mut;

t_h			ft_objtype(t_data ndata, t_ray ray, int *clr, t_pt *intpt)
{
	t_h		h;

	h.r = 0;
	if (ndata.obj->id == SP)
		h = ft_intersp(ndata, ray, clr, intpt);
	else if (ndata.obj->id == PL)
		h = ft_interpl(ndata, ray, clr, intpt);
	else if (ndata.obj->id == SQ)
		h = ft_intersq(ndata, ray, clr, intpt);
	else if (ndata.obj->id == CY)
		h = ft_intercy(ndata, ray, clr, intpt);
	else if (ndata.obj->id == TR)
		h = ft_intertr(ndata, ray, clr, intpt);
	return (h);
}

t_ray		ft_reflexion(t_pt intpt, t_ray ray, t_vct n)
{
	double	cs;
	double	len;
	t_vct	tmpn;
	t_vct	refv;

	cs = -ft_dotprod(ray.vct, n);
	len = 2 * cs;
	tmpn.a = len * n.a;
	tmpn.b = len * n.b;
	tmpn.c = len * n.c;
	refv = ft_normalize(ft_addvect(tmpn, ray.vct));
	ray.vct = refv;
	ray.pt = intpt;
	return (ray);
}

double		ft_intersect2(t_ray ray, int *clr, t_structsupp *s, t_data *data, int *data_spec)
{
	t_data	ndata;
	t_h		h_p;
	double	rcf;

	ndata = *data;
	rcf = 0;
	while (ndata.obj)
	{
		h_p = ft_objtype(ndata, ray, clr, &(s->intpt));
		if (h_p.r == 1)
		{
			s->h.r = h_p.r;
			s->h.n = h_p.n;
			*data_spec = ndata.obj->spec;
			rcf = ndata.obj->rcf;
		}
		ndata.obj = ndata.obj->next;
	}
	return (rcf);
}

int			ft_intersect(t_ray ray, t_data *data, int *clr, int *depth, int *data_spec)
{
	t_structsupp	s;
	double			rcf;
	int				clr1;

	s.h.r = 0;
	s.intpt = ray.pt;
	rcf = ft_intersect2(ray, clr, &s, data, data_spec);
	if (s.h.r != 0)
		ft_shadding(clr, s.h.n, s.intpt, data, *data_spec);
	else
		*clr = 0;
	if (rcf != 0 && *depth < MAX_DEPTH)
	{
		clr1 = *clr;
		/* data->depth++; */
		(*depth)++;
		ray = ft_reflexion(s.intpt, ray, s.h.n);
		ft_intersect(ray, data, clr, depth, data_spec);
		*clr = ft_refclr(clr1, *clr, rcf);
	}
	return (1);
}

void		*cam_thread(void *v_thread)
{
	t_thread 	*thread;
	double			initx;
	double		inity;
	double		endx;
	double		endy;
	double			x;
	double			y;
	int			clr;

	thread = (t_thread *)v_thread;
	initx = thread->data->res->x / N_THREADS * thread->id;
	if (thread->id == N_THREADS - 1)
		endx = thread->data->res->x;
	else
		endx = thread->data->res->x / N_THREADS * (thread->id + 1);
	inity = 0;
	endy = thread->data->res->y;
	y = inity - 1;
	clr = 0;
	while (y++ < endy - 1)
	{
		x = initx - 1;
		while (x++ < endx -1)
		{
			clr = ft_supersampling(x, y, thread->data);
			thread->data->cam->imdt[(int)(y * (thread->data->size_line / 4) + x)] = clr;
		}
	}

	return (NULL);
}

int			ft_minirt(t_data *data)
{
	t_cam			*d;
	int				i;
	t_thread		*thread;

	thread = (t_thread *)malloc(sizeof(t_thread) * N_THREADS);
	d = data->cam;
	pthread_mutex_init(&mut, NULL);

	while (data->cam)
	{
		i = 0;
		while (i < N_THREADS)
		{
			thread[i].data = data;
			thread[i].id = i; 
			pthread_create(&(thread[i].t_id), NULL, cam_thread, (void *)(&thread[i]));
			i++;
		}
		i = 0;
		while (i < N_THREADS)
		{
			pthread_join(thread[i].t_id, NULL);
			i++;
		}
		data->cam = data->cam->next;
	}
	data->cam = d;
	return (0);
}
