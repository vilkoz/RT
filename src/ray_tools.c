/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 20:16:59 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/24 17:38:30 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_v3d		cross_product(t_v3d a, t_v3d b)
{
	t_v3d		res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

t_v3d		v_mul(t_v3d v, double n)
{
	v.x *= n;
	v.y *= n;
	v.z *= n;
	return (v);
}

t_v3d		v_mul_v(t_v3d v1, t_v3d v2)
{
	t_v3d	v;

	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	v.z = v1.z * v2.z;
	return (v);
}

double		cos_vectors(t_v3d v1, t_v3d v2)
{
	double	a;

	a = (dot_product(v1, v2) /
		(sqrt(dot_product(v1, v1)) * sqrt(dot_product(v2, v2))));
	if (a > 1.0)
		return (1.0);
	if (a < -1.0)
		return (-1.0);
	return (a);
}
