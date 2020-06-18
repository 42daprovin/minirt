/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsutilslst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:12:16 by daprovin          #+#    #+#             */
/*   Updated: 2020/06/09 18:48:06 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"

void		ft_addbackcam(t_cam **dcam, t_cam *cam)
{
	t_cam *list;

	list = *dcam;
	cam->next = NULL;
	if (!list)
	{
		cam->back = NULL;
		*dcam = cam;
		return ;
	}
	while (list->next)
		list = list->next;
	cam->back = list;
	list->next = cam;
}

void		ft_addbacklgt(t_lgt **dlgt, t_lgt *lgt)
{
	t_lgt *list;

	list = *dlgt;
	if (!list)
	{
		*dlgt = lgt;
		(*dlgt)->next = NULL;
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
