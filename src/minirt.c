/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:55:58 by daprovin          #+#    #+#             */
/*   Updated: 2020/01/31 19:41:37 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include "../headers/mlx.h"

int			ft_reso(char **split, t_data *data)
{
	t_res	*res;

	if (!(res = (t_res*)malloc(sizeof(t_res))))
		return (2);
	res->x = ft_atoi(split[1]);
	res->y = ft_atoi(split[2]);
	data->res = res;
	return (0);
}

int			ft_algt(char **split, t_data *data)
{
	t_algt	*algt;
	char	**color;

	if (!(algt = (t_algt*)malloc(sizeof(t_algt))))
		return (2);
	if (ft_strstrlen(split) != 3)
		return (1);
	if (ft_checkdoub(split[1]) || ft_checkargs(split[2]))
		return (1);
	algt->br = ft_doubatoi(split[1]);
	if (!(color = ft_split(split[2], ',')))
		return (2);
	(algt->clr)[0] = ft_atoi(color[0]);
	(algt->clr)[1] = ft_atoi(color[1]);
	(algt->clr)[2] = ft_atoi(color[2]);
	data->algt = algt;
	free(color);
	return (0);
}
void		ft_addbackcam(t_cam **dcam, t_cam *cam)
{
	t_cam *list;

	list = *dcam;
	if (!list)
	{
		*dcam = cam;
		return ;
	}
	while (list->next)
		list = list->next;
	list->next = cam;
	list->next->next = NULL;
}

int			ft_cam(char **split, t_data *data)
{
	t_cam	*cam;
	char	**fill;

	if (!(cam = (t_cam*)malloc(sizeof(t_cam))))
		return (2);
	if (ft_strstrlen(split) != 4)
		return (1);
	if (ft_checkargs(split[1]) || ft_checkargs(split[2])
	|| ft_checkdoub(split[3]))
		return (1);
	if (!(fill = ft_split(split[1], ',')))
		return (2);
	cam->o.x = ft_doubatoi(fill[0]);
	cam->o.y = ft_doubatoi(fill[1]);
	cam->o.z = ft_doubatoi(fill[2]);
	free(fill);
	if (!(fill = ft_split(split[2], ',')))
		return (2);
	cam->n.a = ft_doubatoi(fill[0]);
	cam->n.b = ft_doubatoi(fill[1]);
	cam->n.c = ft_doubatoi(fill[2]);
	free(fill);
	cam->fov = ft_doubatoi(split[3]);
	ft_addbackcam(&(data->cam), cam);
	return (0);
}

void		ft_addbacklgt(t_lgt **dlgt, t_lgt *lgt)
{
	t_lgt *list;

	list = *dlgt;
	if (!list)
	{
		*dlgt = lgt;
		return ;
	}
	while (list->next)
		list = list->next;
	list->next = lgt;
	list->next->next = NULL;
}

int			ft_lgt(char **split, t_data *data)
{
	t_lgt	*lgt;
	char	**fill;

	if (!(lgt = (t_lgt*)malloc(sizeof(t_lgt))))
		return (2);
	if (ft_strstrlen(split) != 4)
		return (1);
	if (ft_checkargs(split[1]) || ft_checkdoub(split[2])
	|| ft_checkargs(split[3]))
		return (1);
	if (!(fill = ft_split(split[1], ',')))
		return (2);
	lgt->o.x = ft_doubatoi(fill[0]);
	lgt->o.y = ft_doubatoi(fill[1]);
	lgt->o.z = ft_doubatoi(fill[2]);
	free(fill);
	if (!(fill = ft_split(split[3], ',')))
		return (2);
	(lgt->clr)[0] = ft_atoi(fill[0]);
	(lgt->clr)[1] = ft_atoi(fill[1]);
	(lgt->clr)[2] = ft_atoi(fill[2]);
	free(fill);
	lgt->br = ft_doubatoi(split[2]);
	ft_addbacklgt(&(data->lgt), lgt);
	return (0);
}

int			ft_fpt(char *spl, t_pt *pt)
{
	char	**fill;

	if (!(fill = ft_split(spl, ',')))
		return (2);
	pt->x = ft_doubatoi(fill[0]);
	pt->y = ft_doubatoi(fill[1]);
	pt->z = ft_doubatoi(fill[2]);
	free(fill);
	return (0);
}

int			ft_fvct(char *spl, t_vct *n)
{
	char	**fill;

	if (!(fill = ft_split(spl, ',')))
		return (2);
	n->a = ft_doubatoi(fill[0]);
	n->b = ft_doubatoi(fill[1]);
	n->c = ft_doubatoi(fill[2]);
	free(fill);
	return (0);
}

int			ft_fclr(char *spl, int (*clr)[3])
{
	char	**fill;

	if (!(fill = ft_split(spl, ',')))
		return (2);
	(*clr)[0] = ft_atoi(fill[0]);
	(*clr)[1] = ft_atoi(fill[1]);
	(*clr)[2] = ft_atoi(fill[2]);
	free(fill);
	return (0);
}

void		ft_addbackobj(t_obj **dobj, t_obj *obj)
{
	t_obj	*list;

	list = *dobj;
	if (!list)
	{
		*dobj = obj;
		return ;
	}
	while (list->next)
		list = list->next;
	list->next = obj;
}

int			ft_pl(char **spl, t_data *data)
{
	t_pl	*pl;
	t_obj	*obj;

	if (!(obj = (t_obj*)malloc(sizeof(t_obj))))
		return (2);
	if (!(pl = (t_pl*)malloc(sizeof(t_pl))))
		return (2);
	if (ft_strstrlen(spl) != 4)
		return (1);
	if (ft_checkargs(spl[1]) || ft_checkargs(spl[2]) || ft_checkargs(spl[3]))
		return (1);
	obj->id = PL;
	if (ft_fpt(spl[1], &(pl->pt)) || ft_fvct(spl[2], &(pl->n))
	|| ft_fclr(spl[3], &(pl->clr)))
		return (2);
	obj->fig = pl;
	obj->next = NULL;
	ft_addbackobj(&(data->obj), obj);
	return (0);
}

int			ft_sp(char **ssp, t_data *data)
{
	t_sp	*sp;
	t_obj	*obj;

	if (!(obj = (t_obj*)malloc(sizeof(t_obj))))
		return (2);
	if (!(sp = (t_sp*)malloc(sizeof(t_sp))))
		return (2);
	if (ft_strstrlen(ssp) != 4)
		return (1);
	if (ft_checkargs(ssp[1]) || ft_checkdoub(ssp[2]) || ft_checkargs(ssp[3]))
		return (1);
	obj->id = SP;
	if (ft_fpt(ssp[1], &(sp->c)) || ft_fclr(ssp[3], &(sp->clr)))
		return (2);
	sp->d = ft_doubatoi(ssp[2]);
	obj->fig = sp;
	obj->next = NULL;
	ft_addbackobj(&(data->obj), obj);
	return (0);
}

int			ft_sq(char **ssq, t_data *data)
{
	t_sq	*sq;
	t_obj	*obj;

	if (!(obj = (t_obj*)malloc(sizeof(t_obj))))
		return (2);
	if (!(sq = (t_sq*)malloc(sizeof(t_sq))))
		return (2);
	if (ft_strstrlen(ssq) != 5)
		return (1);
	if (ft_checkargs(ssq[1]) || ft_checkargs(ssq[2]) || ft_checkdoub(ssq[3])
	|| ft_checkargs(ssq[4]))
		return (1);
	obj->id = SQ;
	if (ft_fpt(ssq[1], &(sq->c)) || ft_fvct(ssq[2], &(sq->n))
	|| ft_fclr(ssq[4], &(sq->clr)))
		return (2);
	sq->l = ft_doubatoi(ssq[3]);
	obj->fig = sq;
	obj->next = NULL;
	ft_addbackobj(&(data->obj), obj);
	return (0);
}

int			ft_cy(char **scy, t_data *data)
{
	t_cy	*cy;
	t_obj	*obj;

	if (!(obj = (t_obj*)malloc(sizeof(t_obj))))
		return (2);
	if (!(cy = (t_cy*)malloc(sizeof(t_cy))))
		return (2);
	if (ft_strstrlen(scy) != 6)
		return (1);
	if (ft_checkargs(scy[1]) || ft_checkargs(scy[2]) || ft_checkdoub(scy[3])
	|| ft_checkdoub(scy[4]), ft_checkargs(scy[5]))
		return (1);
	obj->id = CY;
	if (ft_fpt(scy[1], &(cy->pt)) || ft_fvct(scy[2], &(cy->n))
	|| ft_fclr(scy[5], &(cy->clr)))
		return (2);
	cy->d = ft_doubatoi(scy[3]);
	cy->h = ft_doubatoi(scy[4]);
	obj->fig = cy;
	obj->next = NULL;
	ft_addbackobj(&(data->obj), obj);
	return (0);
}

int			ft_tr(char **str, t_data *data)
{
	t_tr	*tr;
	t_obj	*obj;

	if (!(tr = (t_tr*)malloc(sizeof(t_tr))))
		return (2);
	if (!(obj = (t_obj*)malloc(sizeof(t_obj))))
		return (2);
	if (ft_strstrlen(str) != 5)
		return (1);
	if (ft_checkargs(str[1]) || ft_checkargs(str[2]) || ft_checkargs(str[3])
	|| ft_checkargs(str[4]))
		return (1);
	obj->id = TR;
	if (ft_fpt(str[1], &(tr->A)) || ft_fpt(str[2], &(tr->B))
	|| ft_fpt(str[3], &(tr->C)) || ft_fclr(str[4], &(tr->clr)))
		return (2);
	obj->fig = tr;
	obj->next = NULL;
	ft_addbackobj(&(data->obj), obj);
	return (0);
}

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

int			main(int ac, char **av)
{
	int		e;
	int		fd;
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
	printf("%d", (((t_pl*)(data.obj->next->fig))->clr)[1]);
	return (0);
}
