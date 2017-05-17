/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 19:12:32 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/17 18:34:39 by kshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_v3d	get_norm_cone(t_o3d *dat, t_p3d inter_p)
{
	t_cone	*sp;
	t_v3d	r;
	t_v3d	dp;
	t_v3d	n;

	sp = (t_cone *)dat->data;
	dp = (new_v3d_p(inter_p, sp->center));
	r = (v_sub(dp, v_mul(sp->dir, dot_product(sp->dir, dp))));
	n = cross_product(dp, r);
	n = cross_product(n, r);
	return (normalize(r));
}

int		get_cone_color(t_o3d *obj, t_p3d inter_p)
{
	t_cone	*c;
	t_p2d	t;
	t_v3d	p;
	t_v3d	zero;

	if (obj->material.tex.img)
	{
		c = (t_cone*)obj->data;
		p = new_v3d_p(inter_p, c->center);
		t.y = v_len(v_mul(c->dir, dot_product(p, c->dir)));
		zero = normalize(cross_product(c->dir, new_v3d(0, 0, 1)));
		p = v_sub(v_mul(c->dir, dot_product(p, c->dir)), p);
		t.x = fabs(acos(cos_vectors(p, zero)) / M_PI) * 2;
		t.x = (t.x < 0) ? 1 - fabs(t.x) : t.x;
		return (ft_img_px_get(obj->material.tex,
			(int)(t.x * (double)obj->material.tex.w) % obj->material.tex.w,
			(int)t.y % obj->material.tex.h));
	}
	return (((t_cone *)obj->data)->color);
}

int		solve_quad_rot(const void *data, t_vec v, double *t0, double *t1)
{
	t_cone		*sp;
	t_v3d		ray;
	t_v3d		dp;
	t_p3d		ray_start;

	sp = (t_cone *)data;
	ray = v.dir;
	ray_start = v.p;
	dp = new_v3d_p(ray_start, sp->center);
	if (!solve_quad(new_p3d(
		COSA2 * v_sqr(v_sub(ray, v_mul(sp->dir, dot_product(ray, sp->dir)))) -
		SINA2 * dot_product(ray, sp->dir) * dot_product(ray, sp->dir),
		2 * COSA2 * dot_product(v_sub(ray, v_mul(sp->dir, dot_product(ray,
		sp->dir))), v_sub(dp, v_mul(sp->dir, dot_product(dp, sp->dir))))
		- 2 * SINA2 * dot_product(ray, sp->dir) * dot_product(dp, sp->dir),
		COSA2 * v_sqr(v_sub(dp, v_mul(sp->dir, dot_product(dp, sp->dir))))
		- SINA2 * dot_product(dp, sp->dir) * dot_product(dp, sp->dir)), t0, t1))
		return (FALSE);
	return (TRUE);
}

int		intersect_cone(const t_o3d *data, const t_p3d ray_start,
						const t_v3d ray, t_p3d *inter_p)
{
	double		t0;
	double		t1;
	t_cone		*sp;
	t_v3d		dp;

	sp = (t_cone *)data->data;
	if (!solve_quad_rot(data->data, new_vec(ray, ray_start), &t0, &t1))
		return (FALSE);
	if (t0 > t1)
		SWAP_D(t0, t1);
	if ((t0 < 0) && ((t0 = t1) < 0))
		return (FALSE);
	*inter_p = v_to_p(v_add(p_to_v(ray_start), v_mul(ray, t0)));
	dp = new_v3d_p(*inter_p, sp->center);
	if (!same_dir(dp, sp->dir))
		return (FALSE);
	if (sp->h - v_len(v_sub(dp, v_sub(dp, v_mul(sp->dir,
		dot_product(sp->dir, dp))))) < 0 || distance(*inter_p, ray_start) < EPSILON)
	{
		*inter_p = v_to_p(v_add(p_to_v(ray_start), v_mul(ray, t1)));
		dp = new_v3d_p(*inter_p, sp->center);
		if (sp->h - v_len(v_sub(dp, v_sub(dp, v_mul(sp->dir,
			dot_product(sp->dir, dp))))) < 0)
			return (FALSE);
	}
	return (TRUE);
}

t_o3d	*new_cone(t_vec v, double h, double alpha, t_material material)
{
	t_cone		*sp;
	t_o3d		*obj;

	sp = (t_cone *)malloc(sizeof(t_cone));
	sp->center = v.p;
	sp->dir = v.dir;
	sp->color = material.color;
	sp->h = h;
	sp->a = alpha * RAD;
	sp->sin_a = sin(sp->a);
	sp->cos_a = cos(sp->a);
	obj = (t_o3d *)malloc(sizeof(t_o3d));
	obj->data = (void *)sp;
	obj->get_color = get_cone_color;
	obj->intersect = intersect_cone;
	obj->get_norm = get_norm_cone;
	obj->tex = material.tex;
	obj->material = material;
	return (obj);
}
