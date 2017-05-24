/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tools3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 17:35:28 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/24 17:36:02 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_v3d		normalize(t_v3d v)
{
	double		len;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (len == 0)
		len = 1;
	if (len - 1.0 < EPS)
		return (v);
	return (new_v3d(v.x / len, v.y / len, v.z / len));
}

t_v3d		rotate_v_x(t_v3d v, double sin_al, double cos_al)
{
	double		y;
	double		z;

	y = v.y * cos_al - v.z * sin_al;
	z = v.y * sin_al + v.z * cos_al;
	return (new_v3d(v.x, y, z));
}

t_v3d		rotate_v_y(t_v3d v, double sin_al, double cos_al)
{
	double		x;
	double		z;

	x = v.x * cos_al - v.z * sin_al;
	z = v.x * sin_al + v.z * cos_al;
	return (new_v3d(x, v.y, z));
}

t_v3d		rotate_v_z(t_v3d v, double sin_al, double cos_al)
{
	double		x;
	double		y;

	x = v.x * cos_al - v.y * sin_al;
	y = v.x * sin_al + v.y * cos_al;
	return (new_v3d(x, y, v.z));
}

t_v3d		new_v3d(double x, double y, double z)
{
	t_v3d	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}
