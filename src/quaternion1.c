/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 17:48:20 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/24 17:48:49 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_quat		new_quat(t_v3d v, double ang)
{
	t_quat	q;

	q.w = cos(ang / 2.);
	q.x = v.x * sin(ang / 2.);
	q.y = v.y * sin(ang / 2.);
	q.z = v.z * sin(ang / 2.);
	return (q_norm(q));
}

t_quat		q_mul(t_quat q, double k)
{
	q.w *= k;
	q.x *= k;
	q.y *= k;
	q.z *= k;
	return (q);
}

double		q_len(t_quat q)
{
	return (sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z));
}

t_quat		q_norm(t_quat q)
{
	double	len;

	if (fabs(len = q_len(q)) < EPSILON)
		return (q_mul(q, 1. / len));
	else
		return (q);
}

t_quat		q_inv(t_quat q)
{
	t_quat	res;

	res.x = -q.x;
	res.y = -q.y;
	res.z = -q.z;
	res.w = q.w;
	return (res);
}
