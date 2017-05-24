/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:13:25 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/24 19:15:59 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
	alpha = acos(cos_vectors(cam->dir, pix_vector_cam(new_p2d(move.x, 0),
		cam)));
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
