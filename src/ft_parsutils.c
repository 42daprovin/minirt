/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:16:17 by daprovin          #+#    #+#             */
/*   Updated: 2020/06/18 02:26:34 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"

int			ft_fpt(char *spl, t_pt *pt)
{
	char	**fill;

	if (!(fill = ft_split(spl, ',')))
		ft_errorcheckermalloc();
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
		ft_errorcheckermalloc();
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
		ft_errorcheckermalloc();
	(*clr)[0] = ft_atoi(fill[0]);
	(*clr)[1] = ft_atoi(fill[1]);
	(*clr)[2] = ft_atoi(fill[2]);
	free(fill);
	return (0);
}

int			ft_checkbr(char *str)
{
	if (ft_checkdoub(str))
		return (1);
	if (ft_doubatoi(str) > 1 || ft_doubatoi(str) < 0)
		return (1);
	return (0);
}
