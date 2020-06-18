/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsutils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 15:03:07 by daprovin          #+#    #+#             */
/*   Updated: 2020/06/18 02:29:04 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include <math.h>

int			ft_checkint(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])))
			return (1);
		i++;
	}
	return (0);
}

int			ft_checkcolor(char *str)
{
	char	**split;
	int		r;
	int		i;

	if (!(split = ft_split(str, ',')))
		ft_errorcheckermalloc();
	if (ft_strstrlen(split) != 3)
	{
		free(split);
		return (1);
	}
	r = 0;
	if (ft_checkint(split[0]) || ft_checkint(split[1]) || ft_checkint(split[2]))
		r = 1;
	i = -1;
	while (++i < 3)
		if (ft_atoi(split[i]) > 255 || ft_atoi(split[i]) < 0)
			r = 1;
	return (r);
}

int			ft_checkcf(char *str)
{
	if (ft_checkdoub(str))
		return (1);
	if (ft_doubatoi(str) > 1 || ft_doubatoi(str) < 0)
		return (1);
	return (0);
}
