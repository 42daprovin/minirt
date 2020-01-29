/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkargs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 18:54:26 by daprovin          #+#    #+#             */
/*   Updated: 2020/01/29 19:04:05 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/libft.h"
#include "headers/minirt.h"

int		ft_checkargs(char *str)
{
	char	**split;
	int		r;

	if (!(split = ft_split(str, ',')))
		return (2);
	if (ft_strstrlen(split) != 3)
		r = 1;
	else
		r = 0;
	free(split);
	return (r);
}
