/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsobjs2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 18:54:36 by daprovin          #+#    #+#             */
/*   Updated: 2020/06/18 02:27:08 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include <math.h>

static void		ft_fillcu(int i, char **scu, t_sq sq2, t_data *data)
{
	t_obj	*obj;
	t_sq	*sq;

	if (!(obj = (t_obj*)malloc(sizeof(t_obj))))
		ft_errorcheckermalloc();
	if (!(sq = (t_sq*)malloc(sizeof(t_sq))))
		ft_errorcheckermalloc();
	*sq = sq2;
	obj->id = SQ;
	obj->spec = ft_atoi(scu[4]);
	obj->rcf = ft_doubatoi(scu[5]);
	obj->fig = sq;
	obj->next = NULL;
	sq->n.a = (i == 0 || i == 1) ? 1 : 0;
	sq->n.b = (i == 2 || i == 3) ? 1 : 0;
	sq->n.c = (i == 4 || i == 5) ? 1 : 0;
	sq->c.x = (i == 0) ? sq->c.x + (sq->l / 2) : sq->c.x;
	sq->c.x = (i == 1) ? sq->c.x - (sq->l / 2) : sq->c.x;
	sq->c.y = (i == 2) ? sq->c.y + (sq->l / 2) : sq->c.y;
	sq->c.y = (i == 3) ? sq->c.y - (sq->l / 2) : sq->c.y;
	sq->c.z = (i == 4) ? sq->c.z + (sq->l / 2) : sq->c.z;
	sq->c.z = (i == 5) ? sq->c.z - (sq->l / 2) : sq->c.z;
	ft_addbackobj(&(data->obj), obj);
}

int				ft_cu(char **scu, t_data *data)
{
	int		i;
	t_sq	sq;

	if (ft_strstrlen(scu) != 6)
		return (1);
	if (ft_checkargs(scu[1]) || ft_checkdoub(scu[2]) || ft_checkcolor(scu[3])
	|| ft_checkcf(scu[4]) || ft_checkcf(scu[5]))
		return (1);
	i = 0;
	if (ft_fpt(scu[1], &(sq.c)) || ft_fvct("0,0,0", &(sq.n))
	|| ft_fclr(scu[3], &(sq.clr)))
		ft_errorcheckermalloc();
	sq.l = ft_doubatoi(scu[2]);
	while (i < 6)
	{
		ft_fillcu(i, scu, sq, data);
		i++;
	}
	return (0);
}
