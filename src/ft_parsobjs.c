/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsobjs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:38:33 by daprovin          #+#    #+#             */
/*   Updated: 2020/02/07 15:53:40 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include "../headers/mlx.h"

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