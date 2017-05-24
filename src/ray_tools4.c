/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tools4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 17:36:24 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/24 17:36:43 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_v3d		new_v3d_p(t_p3d p1, t_p3d p2)
{
	t_v3d	v;

	v.x = p1.x - p2.x;
	v.y = p1.y - p2.y;
	v.z = p1.z - p2.z;
	return (v);
}

t_p3d		new_p3d(double x, double y, double z)
{
	t_p3d	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_p2d		new_p2d(double x, double y)
{
	t_p2d	p;

	p.x = x;
	p.y = y;
	return (p);
}

t_vec		new_vec(t_v3d v, t_p3d p)
{
	t_vec	new;

	new.dir = v;
	new.p = p;
	return (new);
}

double		dot_product(t_v3d v1, t_v3d v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
