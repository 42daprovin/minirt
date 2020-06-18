/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 18:26:19 by daprovin          #+#    #+#             */
/*   Updated: 2020/06/10 00:46:03 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include <math.h>

int			ft_samesquare(t_sq *sq, t_ray lr)
{
	t_vct	v;
	double	cs;

	v = ft_vctatob(sq->c, lr.pt);
	cs = ft_dotprod(v, sq->n);
	if (fabs(cs) < E)
		return (1);
	return (0);
}
