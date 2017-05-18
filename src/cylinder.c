/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 15:28:14 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/18 17:11:52 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_v3d	get_norm_cyl(t_o3d *dat, t_p3d inter_p)
{
	t_cyl	*sp;
	t_v3d	res;
	t_v3d	dp;

	sp = (t_cyl *)dat->data;
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

int		intersect_cyl(const t_o3d *data, const t_p3d ray_start,
						const t_v3d ray, t_p3d *inter_p)
{
	double		t0;
	double		t1;
	t_cyl		*sp;
	t_v3d		norm;

	sp = (t_cyl *)data->data;
	if (!solver(sp, new_vec(ray, ray_start), &t0, &t1))
		return (FALSE);
	if ((t0 < 0) && ((t0 = t1) < 0))
		return (FALSE);
	*inter_p = v_to_p(v_add(p_to_v(ray_start), v_mul(ray, t0)));
	norm = get_norm_cyl((t_o3d *)data, *inter_p);
	if (sp->h - v_len(v_sub(new_v3d_p(*inter_p, sp->center),
	v_mul(norm, sp->radius))) < 0 || distance(*inter_p, ray_start) < EPSILON)
	{
		*inter_p = v_to_p(v_add(p_to_v(ray_start), v_mul(ray, t1)));
		norm = get_norm_cyl((t_o3d *)data, *inter_p);
		if (sp->h - v_len(v_sub(new_v3d_p(*inter_p, sp->center),
			v_mul(norm, sp->radius))) < 0)
			return (FALSE);
	}
	return (TRUE);
}

void	rotate_cyl(const t_o3d *obj, double angle, t_v3d axis)
{
	t_cyl		*pl;

	pl = (t_cyl *)obj->data;
	pl->dir = rotate_v_q(pl->dir, axis, angle);
	pl->top->p = v_to_p(v_add(v_mul(pl->dir, pl->h), p_to_v(pl->center)));
	pl->top->norm = pl->dir;
	pl->bot->p = v_to_p(v_add(v_mul(v_inv(pl->dir), pl->h),
		p_to_v(pl->center)));
	pl->bot->norm = v_inv(pl->dir);
}

void	move_cyl(const t_o3d *obj, t_p2d move, t_cam *cam)
{
	t_cyl		*c;
	double		alpha;
	double		beta;
	double		dist;

	c = (t_cyl *)obj->data;
	dist = distance(cam->pos, c->center);
	alpha = acos(cos_vectors(cam->dir, pix_vector_cam(new_p2d(move.x, 0), cam)));
	beta = acos(cos_vectors(cam->dir, pix_vector_cam(new_p2d(0, move.y), cam)));
	move.x = dist * tan(alpha) * (move.x < 0 ? -1. : 1.);
	move.y = dist * tan(beta) * (move.y < 0 ? -1. : 1.);
	c->center = v_to_p(v_add(v_mul(cam->dir_r, move.x), p_to_v(c->center)));
	c->center = v_to_p(v_add(v_mul(cam->dir_d, move.y), p_to_v(c->center)));
	c->top->p = v_to_p(v_add(v_mul(cam->dir_r, move.x), p_to_v(c->top->p)));
	c->top->p = v_to_p(v_add(v_mul(cam->dir_d, move.y), p_to_v(c->top->p)));
	c->bot->p = v_to_p(v_add(v_mul(cam->dir_r, move.x), p_to_v(c->bot->p)));
	c->bot->p = v_to_p(v_add(v_mul(cam->dir_d, move.y), p_to_v(c->bot->p)));
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
	obj->rotate = rotate_cyl;
	obj->move = move_cyl;
	return (obj);
}
