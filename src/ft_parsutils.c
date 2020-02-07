/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:16:17 by daprovin          #+#    #+#             */
/*   Updated: 2020/02/07 16:19:31 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include "../headers/mlx.h"

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
