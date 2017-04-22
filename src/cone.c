/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 19:12:32 by vrybalko          #+#    #+#             */
/*   Updated: 2017/04/23 00:26:07 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_v3d	get_norm_cone(void *dat, t_p3d inter_p)
{
	t_cone	*sp;
	t_v3d	r;
	t_v3d	dp;
	t_v3d	n;

	sp = (t_cone *)dat;
	dp = (new_v3d_p(inter_p, sp->center));
	r = (v_sub(dp, v_mul(sp->dir, dot_product(sp->dir, dp))));
	n = cross_product(dp, r);
	n = cross_product(n, r);
	return (normalize(r));
}

int		get_cone_color(t_o3d *obj, t_p3d inter_p)
{
	(void)inter_p;
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

int		intersect_cone(const void *data, const t_p3d ray_start,
						const t_v3d ray, t_p3d *inter_p)
{
	double		t0;
	double		t1;
	t_cone		*sp;
	t_v3d		dp;

	sp = (t_cone *)data;
	if (!solve_quad_rot(data, new_vec(ray, ray_start), &t0, &t1))
		return (FALSE);
	if (t0 > t1)
		SWAP_D(t0, t1);
	if ((t0 < 0) && ((t0 = t1) < 0))
		return (FALSE);
	*inter_p = new_p3d(ray_start.x + t0 * ray.x, ray_start.y + t0 * ray.y,
		ray_start.z + t0 * ray.z);
	dp = new_v3d_p(*inter_p, sp->center);
	if (sp->h - v_len(v_sub(dp, v_sub(dp, v_mul(sp->dir,
		dot_product(sp->dir, dp))))) < 0)
	{
		*inter_p = new_p3d(ray_start.x + t1 * ray.x, ray_start.y + t1 * ray.y,
			ray_start.z + t1 * ray.z);
		dp = new_v3d_p(*inter_p, sp->center);
		if (sp->h - v_len(v_sub(dp, v_sub(dp, v_mul(sp->dir,
			dot_product(sp->dir, dp))))) < 0)
			return (FALSE);
	}
	return (TRUE);
}

t_o3d	*new_cone(t_vec v, double h, int color, double alpha)
{
	t_cone		*sp;
	t_o3d		*obj;

	sp = (t_cone *)malloc(sizeof(t_cone));
	sp->center = v.p;
	sp->dir = v.dir;
	sp->color = color;
	sp->h = h;
	sp->a = alpha * RAD;
	sp->sin_a = sin(sp->a);
	sp->cos_a = cos(sp->a);
	obj = (t_o3d *)malloc(sizeof(t_o3d));
	obj->data = (void *)sp;
	obj->get_color = get_cone_color;
	obj->intersect = intersect_cone;
	obj->get_norm = get_norm_cone;
	obj->material.refl = 0;
	return (obj);
}
