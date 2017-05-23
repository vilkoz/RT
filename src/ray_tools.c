/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 20:16:59 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/24 00:54:07 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_p2d		sphere_coords(t_o3d *dat, t_p3d inter_p)
{
	t_p2d		t;
	t_v3d		tmp;
	t_v3d		proj;
	t_sphere	*sp;
	t_v3d		res;

	sp = (t_sphere *)dat->data;
	res = normalize(new_v3d(inter_p.x - sp->center.x, inter_p.y - sp->center.y,
	inter_p.z - sp->center.z));
	tmp = v_mul(res, sp->radius);
	proj = v_mul(new_v3d(1, 0, 0), dot_product(tmp, new_v3d(1, 0, 0)));
	proj = v_sub(tmp, proj);
	t.x = (acos(cos_vectors(proj, new_v3d(0, 0, 1))) / M_PI) *
		(double)(dat->tex.w / 2);
	t.x += (same_dir(new_v3d(0, 0, 1), proj)) ? (double)dat->tex.w / 2. : 0.;
	proj = v_mul(new_v3d(1, 0, 0), dot_product(tmp, new_v3d(1, 0, 0)));
	if (same_dir(proj, new_v3d(1, 0, 0)))
		t.y = dat->tex.h / 2 - (v_len(proj) / sp->radius) * (dat->tex.h / 2);
	else
		t.y = (v_len(proj) / (double)sp->radius) * (double)dat->tex.h / 2 +
			(double)dat->tex.h / 2;
	t.x = (int)(t.x * 2.) % dat->tex.w;
	t.y = (int)t.y % dat->tex.h;
	return (t);
}

t_p2d		cylinder_coords(t_o3d *dat, t_p3d inter_p)
{
	t_v3d	zero;
	t_cyl	*sp;
	t_v3d	dp;
	t_p2d	r;

	sp = (t_cyl *)dat->data;
	dp = new_v3d_p(inter_p, sp->center);
	zero = normalize(cross_product(sp->dir, new_v3d(0, 0, 1)));
	r.y = v_len(v_mul(sp->dir, dot_product(dp, sp->dir)));
	dp = v_sub(v_mul(sp->dir, dot_product(dp, sp->dir)), dp);
	r.x = fabs(acos(cos_vectors(dp, zero)) / M_PI) * 2 *
		(double)sp->radius / (double)dat->material.tex.w;
	r.x = (r.x < 0) ? 1 - fabs(r.x) : r.x;
	return (r);
}

/*
** use new_vec(t_v3d plane_normal, t_p3d plane_origin) to create new vec
** v.p - plane origin
** v.dir - plane normal
** p - intersection point
*/

//TODO: FIX texture pidorasing

t_p2d		plane_coords(t_vec v, t_p3d p)
{
	t_p2d	r;
	t_v3d	nx;
	t_v3d	a;
	t_v3d	perp;
	t_v3d	x_axis;

	nx = normalize(cross_product(v.dir, normalize(new_v3d(1, 1, 1))));
	a = v_sub(new_v3d_p(v.p, new_p3d(0, 0, 0)),
	new_v3d_p(p, new_p3d(0, 0, 0)));
	perp = v_sub(a, v_mul(nx, dot_product(a, nx)));
	// r.y = same_dir(perp, cross_product(v.dir, nx)) ?
	// 	v_len(perp) : -v_len(perp);
	r.y = v_len(perp);
	x_axis = new_v3d_p(new_p3d(p.x + perp.x, p.y + perp.y,
		p.z + perp.z), v.p);
	// r.x = same_dir(x_axis, nx) ? v_len(x_axis) : -v_len(x_axis);
	r.x = v_len(x_axis);
	return (r);
}

int			same_dir(t_v3d v1, t_v3d v2)
{
	if (acos(dot_product(normalize(v1), normalize(v2))) / RAD > 90)
		return (FALSE);
	else
		return (TRUE);
}

t_v3d		v_inv(t_v3d v)
{
	return (v_sub(new_v3d(0, 0, 0), v));
}

double		v_sqr(t_v3d v)
{
	return (dot_product(v, v));
}

t_v3d		v_add(t_v3d v1, t_v3d v2)
{
	t_v3d		res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

t_v3d		v_sub(t_v3d v1, t_v3d v2)
{
	t_v3d		res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

double		v_len(t_v3d v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double		distance(t_p3d p1, t_p3d p2)
{
	return (sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) +
				(p1.z - p2.z) * (p1.z - p2.z)));
}

t_v3d		normalize(t_v3d v)
{
	double		len;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (len == 0)
		len = 1;
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

t_p3d		v_to_p(t_v3d v)
{
	t_p3d	p;

	p.x = v.x;
	p.y = v.y;
	p.z = v.z;
	return (p);
}

t_v3d		p_to_v(t_p3d v)
{
	t_v3d	p;

	p.x = v.x;
	p.y = v.y;
	p.z = v.z;
	return (p);
}
