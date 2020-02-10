/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doubatoi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:37:49 by daprovin          #+#    #+#             */
/*   Updated: 2020/02/10 18:42:27 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include <math.h>

double	ft_doubatoi(char *str)
{
	double		n;
	long		r;
	char		**split;
	int			i;

	if (ft_isinstr('.', str))
	{
		split = ft_split(str, '.');//seguridad
		r = ft_atoi(split[1]);
		i = 1;
		n = r;
		while (r / 10 != 0)
		{
			r = r / 10;
			i++;
		}
		if (*str != '-')
			n = (ft_atoi(split[0]) * pow(10, i) + n) / pow(10, i);
		else
			n = (ft_atoi(split[0]) * pow(10, i) - n) / pow(10, i);
	}
	else
		return (ft_atoi(str));
	return (n);
}
