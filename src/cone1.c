/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:19:55 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/24 19:26:42 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		rotate_cone(const t_o3d *obj, double angle, t_v3d axis)
{
	t_cone		*pl;

	pl = (t_cone *)obj->data;
	pl->dir = rotate_v_q(pl->dir, axis, angle);
	pl->top->p = v_to_p(v_add(v_mul(pl->dir, pl->h), p_to_v(pl->center)));
	pl->top->norm = pl->dir;
}

void		move_cone(const t_o3d *obj, t_p2d move, t_cam *cam)
{
	t_cone		*c;
	double		alpha;
	double		beta;
	double		dist;

	c = (t_cone *)obj->data;
	dist = distance(cam->pos, c->center);
	alpha = acos(cos_vectors(cam->dir,
		pix_vector_cam(new_p2d(move.x, 0), cam)));
	beta = acos(cos_vectors(cam->dir,
		pix_vector_cam(new_p2d(0, move.y), cam)));
	move.x = dist * tan(alpha) * (move.x < 0 ? -1. : 1.);
	move.y = dist * tan(beta) * (move.y < 0 ? -1. : 1.);
	c->center = v_to_p(v_add(v_mul(cam->dir_r, move.x),
		p_to_v(c->center)));
	c->center = v_to_p(v_add(v_mul(cam->dir_d, move.y),
		p_to_v(c->center)));
	c->top->p = v_to_p(v_add(v_mul(cam->dir_r, move.x),
		p_to_v(c->top->p)));
	c->top->p = v_to_p(v_add(v_mul(cam->dir_d, move.y),
		p_to_v(c->top->p)));
}
