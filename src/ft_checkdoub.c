/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkdoub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 18:34:05 by daprovin          #+#    #+#             */
/*   Updated: 2020/06/18 02:48:25 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

int		ft_checkdoub(char *str)
{
	int		i;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == '.' && i == 0)
			return (1);
		if (*(str + i) == '.' && *(str + i + 1) == '\0')
			return (1);
		if (*(str + i) == '.' && *(str + i + 1) == '.')
			return (1);
		if (!(ft_isdigit(*(str + i))) && *(str + i) != '.' && *(str + i) != '-')
			return (1);
		if (*(str + i) == '-' && *(str + i + 1) == '-')
			return (1);
		i++;
	}
	return (0);
}
