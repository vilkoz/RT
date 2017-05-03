/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 19:17:35 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/02 00:46:35 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_quat		new_quat(t_v3d	v, double ang)
{
	t_quat	q;

	q.w = cos(ang / 2.);
	q.x = v.x * sin(ang / 2.);
	q.y = v.y * sin(ang / 2.);
	q.z = v.z * sin(ang / 2.);
	return (q_norm(q));
	// {
	// t_quat		q;
	// double		rl;
	// double		ca;
	// double		sq;
	// double		cq;
	//
	// if ((rl = sqrt(dot_product(v, v))) < EPSILON)
	// {
	// 	q.x = 0.;
	// 	q.y = 0.;
	// 	q.z = 0.;
	// 	q.w = 1.;
	// 	return (q);
	// }
	// ca = cos(ang);
	// cq = sqrt((1.0 + ca) / 2.0);
	// sq = sqrt((1.0 - ca) / 2.0);
	// v = v_mul(v, sq / rl);
	// q.x = v.x;
	// q.y = v.y;
	// q.z = v.z;
	// q.w = cq;
	// return (q);
	// }
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

t_quat		q_mul_q(t_quat a, t_quat b)
{
	t_quat	r;

	r.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
	r.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
	r.y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x;
	r.z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w;
	return (r);
}

t_quat		q_mul_v(t_quat a, t_v3d b)
{
	t_quat	r;

	r.w = -a.x * b.x - a.y * b.y - a.z * b.z;
	r.x = a.w * b.x + a.y * b.z - a.z * b.y;
	r.y = a.w * b.y - a.x * b.z + a.z * b.x;
	r.z = a.w * b.z + a.x * b.y - a.y * b.x;
	return (r);
}

// t_quat		q_mul_v(t_quat q, t_v3d v)
// {
// 	t_quat	r;
// 	t_quat	mul;
//
// 	mul.x = v.x;
// 	mul.y = v.y;
// 	mul.z = v.z;
// 	mul.w = 0;
// 	r = q_mul_q(q, mul);
// 	return (r);
// }

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
