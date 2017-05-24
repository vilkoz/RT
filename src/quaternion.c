/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 19:17:35 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/24 17:52:21 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_quat		q_mul_v(t_quat a, t_v3d b)
{
	t_quat	r;

	r.w = -a.x * b.x - a.y * b.y - a.z * b.z;
	r.x = a.w * b.x + a.y * b.z - a.z * b.y;
	r.y = a.w * b.y - a.x * b.z + a.z * b.x;
	r.z = a.w * b.z + a.x * b.y - a.y * b.x;
	return (r);
}

t_v3d		q_transform_v(t_quat q, t_v3d v)
{
	t_quat	t;
	t_quat	inv;
	t_v3d	res;

	t = q_mul_v(q, v);
	inv = q_inv(q);
	t = q_mul_q(t, inv);
	t = q_norm(t);
	res.x = t.x;
	res.y = t.y;
	res.z = t.z;
	return (normalize(res));
}

t_quat		q_from_angles(double a_x, double a_y, double a_z)
{
	t_quat	q_bank;
	t_quat	q_alt;
	t_quat	q_heading;

	q_heading.x = 0;
	q_heading.y = 0;
	q_heading.z = sin(a_z / 2.);
	q_heading.w = cos(a_z / 2.);
	q_alt.x = 0;
	q_alt.y = sin(a_y / 2.);
	q_alt.z = 0;
	q_alt.w = cos(a_y / 2.);
	q_bank.x = sin(a_x / 2.);
	q_bank.y = 0;
	q_bank.z = 0;
	q_bank.w = cos(a_x / 2.);
	return (q_mul_q(q_mul_q(q_heading, q_alt), q_bank));
}

t_v3d		rotate_v_q(t_v3d v, t_v3d axis, double ang)
{
	t_quat	rot;

	rot = new_quat(axis, ang);
	return (q_transform_v(rot, v));
}

void		rotate_cam_q(t_cam *cam, double a_x, double a_y, double a_z)
{
	t_quat	rot_q;

	rot_q = q_from_angles(a_x, a_y, a_z);
	cam->dir = q_transform_v(rot_q, cam->dir);
	cam->dir_r = q_transform_v(rot_q, cam->dir_r);
	cam->dir_d = q_transform_v(rot_q, cam->dir_d);
}
