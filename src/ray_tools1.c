/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tools1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 17:33:32 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/24 17:34:09 by vrybalko         ###   ########.fr       */
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

t_p2d		plane_coords(t_vec v, t_p3d p)
{
	t_p2d	r;
	t_v3d	nx;
	t_v3d	a;
	t_v3d	perp;
	t_v3d	x_axis;

	nx.x = acos(dot_product((new_v3d(1, 0, 0)), normalize(v.dir))) / RAD;
	if (fabs(nx.x) <= 45 || fabs(nx.x) >= 135)
		nx = normalize(cross_product(normalize(v.dir), (new_v3d(0, 0, 1))));
	else
		nx = normalize(cross_product(normalize(v.dir), (new_v3d(1, 0, 0))));
	a = v_sub(new_v3d_p(v.p, new_p3d(0, 0, 0)),
	new_v3d_p(p, new_p3d(0, 0, 0)));
	perp = v_sub(a, v_mul(nx, dot_product(a, nx)));
	r.y = same_dir(perp, cross_product(v.dir, nx)) ?
		v_len(perp) : -v_len(perp);
	x_axis = v_mul(nx, dot_product(a, nx));
	r.x = same_dir(x_axis, nx) ? v_len(x_axis) : -v_len(x_axis);
	return (r);
}

int			same_dir(t_v3d v1, t_v3d v2)
{
	if (acos(dot_product(normalize(v1), normalize(v2))) / RAD >= 90.0)
		return (FALSE);
	else
		return (TRUE);
}

t_v3d		v_inv(t_v3d v)
{
	return (v_sub(new_v3d(0, 0, 0), v));
}
