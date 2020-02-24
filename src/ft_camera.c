/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 08:46:12 by daprovin          #+#    #+#             */
/*   Updated: 2020/02/24 11:23:05 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include "../headers/minirt.h"
#include "../headers/mlx.h"
#include <math.h>

t_ray		ft_rotx(t_ray ray, t_data *data, double ct)
{
	t_ray	rayx;

	if (data->cam->n.b >= 0)
	{
		rayx.vct.a = ray.vct.a;
		rayx.vct.b = (ct * ray.vct.b) - (sin(acos(ct)) * ray.vct.c);
		rayx.vct.c = (sin(acos(ct)) * ray.vct.b) + (ct * ray.vct.c);
	}
	else
	{
		rayx.vct.a = ray.vct.a;
		rayx.vct.b = (ct * ray.vct.b) + (sin(acos(ct)) * ray.vct.c);
		rayx.vct.c = (ct * ray.vct.c) - (sin(acos(ct)) * ray.vct.b);
	}
	return (rayx);
}

t_ray		ft_roty(t_ray ray, t_data *data, double ca)
{
	t_ray	rray;

	if (data->cam->n.a >= 0)
	{
		rray.vct.a = (ca * ray.vct.a) + (sin(acos(ca)) * ray.vct.c);
		rray.vct.b = ray.vct.b;
		rray.vct.c = (ca * ray.vct.c) - (sin(acos(ca)) * ray.vct.a);
	}
	else
	{
		rray.vct.a = (ca * ray.vct.a) - (sin(acos(ca)) * ray.vct.c);
		rray.vct.b = ray.vct.b;
		rray.vct.c = (ca * ray.vct.c) + (sin(acos(ca)) * ray.vct.a);
	}
	return (rray);
}

t_ray		ft_rotray(t_ray ray, t_data *data)
{
	double	ct;
	double	ca;
	t_vct	cvct;
	double	nproy;
	t_ray	rray;

	cvct = data->cam->n;
	//nproy = sqrt(pow(cvct.b, 2) + pow(cvct.c, 2));
	//ct = (cvct.c * (-1)) / nproy;
	//ca = (pow(cvct.b, 2) + pow(cvct.c, 2)) / nproy;
	nproy = sqrt(pow(cvct.a, 2) + pow(cvct.c, 2));
	if (nproy != 0)
	{
		ca = (cvct.c * (-1)) / nproy;
		ct = (pow(cvct.a, 2) + pow(cvct.c, 2)) / nproy;
	}
	else
	{
		ca = 1;
		ct = 0;
	}
	//rray = ft_rotx(ray, data, ct);
	//rray = ft_roty(rray, data, ca);
	rray = ft_roty(ray, data, ca);
	rray = ft_rotx(rray, data, ct);
	rray.pt.x = data->cam->o.x;
	rray.pt.y = data->cam->o.y;
	rray.pt.z = data->cam->o.z;
	return (rray);
}

t_ray		ft_camrays(double x, double y, t_data *data)
{
	t_pt	pt;
	double	norm;
	t_ray	ray;

	pt.x = ((2 * ((x + 0.5) / (data->res->x))) - 1)
	* ((data->res->x) / (data->res->y))
	* tan(((data->cam->fov) * (M_PI / 180)) / 2);
	pt.y = (1 - (2 * ((y + 0.5) / (data->res->y))))
	* tan(((data->cam->fov) * (M_PI / 180)) / 2);
	norm = sqrt(pow(pt.x, 2) + pow(pt.y, 2) + 1);
	ray.vct.a = (pt.x / norm);
	ray.vct.b = (pt.y / norm);
	ray.vct.c = (-1 / norm);
	ray.pt.x = 0;
	ray.pt.y = 0;
	ray.pt.z = 0;
	ray = ft_rotray(ray, data);
	return (ray);
}
