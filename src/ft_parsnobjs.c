/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsnobjs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:57:35 by daprovin          #+#    #+#             */
/*   Updated: 2020/02/07 16:11:29 by daprovin         ###   ########.fr       */
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

