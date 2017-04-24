/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 15:28:14 by vrybalko          #+#    #+#             */
/*   Updated: 2017/04/24 20:36:59 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_v3d	get_norm_cyl(void *dat, t_p3d inter_p)
{
	t_cyl	*sp;
	t_v3d	res;
	t_v3d	dp;

	sp = (t_cyl *)dat;
	dp = new_v3d_p(inter_p, sp->center);
	res = v_sub(dp, v_mul(sp->dir, dot_product(sp->dir, dp)));
	return (normalize(res));
}

int		get_cyl_color(t_o3d *obj, t_p3d inter_p)
{
	t_cyl	*c;
	t_p2d	t;
	t_v3d	p;
	t_v3d	zero;

	if (obj->material.tex.img)
	{
		c = (t_cyl*)obj->data;
		p = new_v3d_p(inter_p, c->center);
		t.y = v_len(v_mul(c->dir, dot_product(p, c->dir)));
		zero = normalize(cross_product(c->dir, new_v3d(0, 0, 1)));
		p = v_sub(v_mul(c->dir, dot_product(p, c->dir)), p);
		t.x = fabs(acos(cos_vectors(p, zero)) / M_PI) * 2 * (double)c->radius /
			(double)obj->material.tex.w;
		t.x = (t.x < 0) ? 1 - fabs(t.x) : t.x;
		return (ft_img_px_get(obj->material.tex,
			(int)(t.x * (double)obj->material.tex.w) % obj->material.tex.w,
			(int)t.y % obj->material.tex.h));
	}
	return (((t_cyl *)obj->data)->color);
}

int		solver(t_cyl *sp, t_vec v, double *t0, double *t1)
{
	t_p3d		ray_start;
	t_v3d		ray;
	t_v3d		dp;

	ray_start = v.p;
	ray = v.dir;
	dp = new_v3d_p(ray_start, sp->center);
	if (!solve_quad(new_p3d(v_sqr(v_sub(ray, v_mul(sp->dir, dot_product(ray,
		sp->dir)))), 2 * dot_product(v_sub(ray, v_mul(sp->dir, dot_product(ray,
		sp->dir))), v_sub(dp, v_mul(sp->dir, dot_product(dp, sp->dir)))),
		v_sqr(v_sub(dp, v_mul(sp->dir, dot_product(dp, sp->dir)))) -
		sp->radius * sp->radius), t0, t1))
		return (FALSE);
	return (TRUE);
}

int		intersect_cyl(const void *data, const t_p3d ray_start,
						const t_v3d ray, t_p3d *inter_p)
{
	double		t0;
	double		t1;
	t_cyl		*sp;
	t_v3d		norm;

	sp = (t_cyl *)data;
	if (!solver(sp, new_vec(ray, ray_start), &t0, &t1))
		return (FALSE);
	if ((t0 < 0) && ((t0 = t1) < 0))
		return (FALSE);
	*inter_p = new_p3d(ray_start.x + t0 * ray.x, ray_start.y + t0 * ray.y,
					ray_start.z + t0 * ray.z);
	norm = get_norm_cyl((void *)data, *inter_p);
	if (sp->h - v_len(v_sub(new_v3d_p(*inter_p, sp->center),
		v_mul(norm, sp->radius))) < 0)
	{
		*inter_p = new_p3d(ray_start.x + t1 * ray.x, ray_start.y + t1 * ray.y,
						ray_start.z + t1 * ray.z);
		norm = get_norm_cyl((void *)data, *inter_p);
		if (sp->h - v_len(v_sub(new_v3d_p(*inter_p, sp->center),
			v_mul(norm, sp->radius))) < 0)
			return (FALSE);
	}
	return (TRUE);
}

t_o3d	*new_cyl(t_vec v, double radius, double h, t_material material)
{
	t_cyl		*sp;
	t_o3d		*obj;

	sp = (t_cyl *)malloc(sizeof(t_cyl));
	sp->center = v.p;
	sp->dir = normalize(v.dir);
	sp->radius = radius;
	sp->color = material.color;
	sp->h = h;
	obj = (t_o3d *)malloc(sizeof(t_o3d));
	obj->data = (void *)sp;
	obj->get_color = get_cyl_color;
	obj->intersect = intersect_cyl;
	obj->get_norm = get_norm_cyl;
	obj->tex = material.tex;
	obj->material = material;
	return (obj);
}
