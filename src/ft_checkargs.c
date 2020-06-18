/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkargs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 18:54:26 by daprovin          #+#    #+#             */
/*   Updated: 2020/06/18 02:25:18 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"

int		ft_checkargs(char *str)
{
	char	**split;
	int		r;

	if (!(split = ft_split(str, ',')))
		ft_errorcheckermalloc();
	if (ft_strstrlen(split) != 3)
	{
		free(split);
		return (1);
	}
	if (ft_checkdoub(split[0]) || ft_checkdoub(split[1])
	|| ft_checkdoub(split[2]))
		r = 1;
	else
		r = 0;
	free(split);
	return (r);
}
