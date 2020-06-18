/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 19:06:01 by daprovin          #+#    #+#             */
/*   Updated: 2020/06/18 05:58:39 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include <math.h>

void		fill_bmp(char **data, t_data *d)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = 122;
	y = d->res->y;
	while (y--)
	{
		x = -1;
		while (++x < d->res->x)
		{
			j = (x * (d->bpp / 8)) + (y * d->size_line);
			*(*data + i++) = *((char *)d->cam->imdt + j++);
			*(*data + i++) = *((char *)d->cam->imdt + j++);
			*(*data + i++) = *((char *)d->cam->imdt + j);
		}
	}
}

void		header_bmp(char **data, t_data *d)
{
	unsigned int	size;

	size = d->res->x * d->res->y * 3;
	*(unsigned short *)*data = *(const unsigned int *)(unsigned long)"BM";
	*(unsigned int *)(*data + 2) = (size + 122);
	*(unsigned int *)(*data + 6) = 0u;
	*(unsigned char *)(*data + 10) = 122;
	*(unsigned int *)(*data + 14) = 122 - 14;
	*(unsigned int *)(*data + 18) = d->res->x;
	*(unsigned int *)(*data + 22) = d->res->y;
	*(unsigned short *)(*data + 26) = 1;
	*(unsigned short *)(*data + 28) = 24;
	*(unsigned int *)(*data + 30) = 0;
	*(unsigned int *)(*data + 34) = (unsigned int)size;
	*(unsigned int *)(*data + 38) = 3780;
	*(unsigned int *)(*data + 42) = 3780;
	*(int *)(*data + 46) = 0;
	*(int *)(*data + 50) = 0;
}

void		export_bmp(char *filename, t_data *d)
{
	int				fd;
	unsigned int	size;
	unsigned int	i;
	char			*data;

	size = d->res->x * d->res->y * 3;
	if (!(data = malloc(size + 122)))
		ft_errorcheckermalloc();
	i = 0;
	while (i < size + 122)
		data[i++] = 0;
	header_bmp(&data, d);
	fill_bmp(&data, d);
	if ((fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644)) <= 0)
		ft_errorcheckermalloc();
	write(fd, data, (size + 122));
	close(fd);
	exit(0);
}

char		*bmp_filename(char *file, int i)
{
	char	*filename;
	int		n;

	if (!(filename = malloc(sizeof(char) * (i + 5))))
		ft_errorcheckermalloc();
	n = -1;
	while (n++ <= i)
		*(filename + n) = *(file + n);
	*(unsigned int *)(filename + n) =
	*(const unsigned int *)(unsigned long)"bmp\0";
	return (filename);
}

void		ft_save_image(t_data d, int ac, char *file)
{
	if (ac == 3)
		export_bmp(bmp_filename(file, ft_strlen(file) - 4), &d);
	else
		mlx_put_image_to_window(d.mlx, d.w_ptr, d.cam->imptr, 0, 0);
	return ;
}
