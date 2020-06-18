/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lights2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 18:59:43 by daprovin          #+#    #+#             */
/*   Updated: 2020/06/10 00:52:11 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		ft_3dshadow(int *clr, double cf[3])
{
	int		clrp[3];
	int		c;

	c = *clr;
	clrp[0] = *clr >> 16;
	*clr = c;
	clrp[1] = (*clr & 65280) >> 8;
	*clr = c;
	clrp[2] = *clr & 255;
	*clr = ((int)(clrp[0] * cf[0]) << 16) | ((int)(clrp[1] * cf[1]) << 8)
	| (int)(clrp[2] * cf[2]);
}

int			ft_clr(int clr[3], double spec, int clr2)
{
	int		c;
	int		clrp[3];

	c = clr2;
	clrp[0] = clr2 >> 16;
	clr2 = c;
	clrp[1] = (clr2 & 65280) >> 8;
	clr2 = c;
	clrp[2] = clr2 & 255;
	clr2 = c;
	c = ((int)(clr[0] * spec + clrp[0] * (1 - spec)) << 16)
	| ((int)(clr[1] * spec + clrp[1] * (1 - spec)) << 8)
	| (int)(clr[2] * spec + clrp[2] * (1 - spec));
	return (c);
}
