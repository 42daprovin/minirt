/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:12:16 by daprovin          #+#    #+#             */
/*   Updated: 2020/02/12 01:41:45 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include "../headers/mlx.h"

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
	//list->next->next = NULL;
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
