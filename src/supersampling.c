/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supersampling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 23:21:20 by daprovin          #+#    #+#             */
/*   Updated: 2021/11/07 23:15:07 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include <math.h>

void	ft_splitclr(int clr, int *spl)
{
	int		c;

	c = clr;
	spl[0] = clr >> 16;
	clr = c;
	spl[1] = (clr & 65280) >> 8;
	clr = c;
	spl[2] = clr & 255;
}

int		ft_clrmean(int clr[4])
{
	int		fclr;
	int		spl[4][3];
	int		aux[3];

	ft_splitclr(clr[0], &spl[0][0]);
	ft_splitclr(clr[1], &spl[1][0]);
	ft_splitclr(clr[2], &spl[2][0]);
	ft_splitclr(clr[3], &spl[3][0]);
	aux[0] = (spl[0][0] + spl[1][0] + spl[2][0] + spl[3][0]) / 4;
	aux[1] = (spl[0][1] + spl[1][1] + spl[2][1] + spl[3][1]) / 4;
	aux[2] = (spl[0][2] + spl[1][2] + spl[2][2] + spl[3][2]) / 4;
	fclr = (aux[0] << 16) | (aux[1] << 8) | aux[2];
	return (fclr);
}

int		ft_supersampling(double x, double y, t_data *data)
{
	int		i;
	int		c[2];
	int		clr[4];
	double	k[2];
	int		depth;
	int		spec = 0;

	k[0] = 0.25;
	k[1] = 0.75;
	c[0] = 0;
	i = 0;
	while (c[0] < 2)
	{
		c[1] = 0;
		while (c[1] < 2)
		{
			clr[i] = 0;
			ft_intersect(ft_camrays(x + k[c[0]], y + k[c[1]], data, &depth),
			data, &clr[i], &depth, &spec);
			i++;
			c[1]++;
		}
		c[0]++;
	}
	return (ft_clrmean(clr));
}
