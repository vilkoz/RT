/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:09:54 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/24 19:10:27 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			intersect_sphere(const t_o3d *data, const t_p3d ray_start,
						const t_v3d ray, t_p3d *inter_p)
{
	double		t0;
	double		t1;
	double		t;
	t_sphere	*sp;

	sp = (t_sphere *)data->data;
	if (!solve_quad(new_p3d(1., 2 * dot_product(ray, v_sub(p_to_v(ray_start),
		p_to_v(sp->center))),
		dot_product(*(t_v3d *)&sp->center, *(t_v3d *)&sp->center) +
		dot_product(*(t_v3d *)&ray_start, *(t_v3d *)&ray_start) -
		2 * dot_product(*(t_v3d *)&ray_start, *(t_v3d *)&sp->center)
		- sp->radius * sp->radius), &t0, &t1))
		return (FALSE);
	if (t0 > t1)
		SWAP_D(t0, t1);
	if (t0 < 0)
		if ((t0 = t1) < 0)
			return (FALSE);
	t = t0;
	*inter_p = v_to_p(v_add(p_to_v(ray_start), v_mul(ray, t)));
	if (distance(*inter_p, ray_start) < EPSILON)
		*inter_p = v_to_p(v_add(p_to_v(ray_start), v_mul(ray, t1)));
	return (1);
}

void		move_sphere(const t_o3d *obj, t_p2d move, t_cam *cam)
{
	t_sphere	*c;
	double		alpha;
	double		beta;
	double		dist;

	c = (t_sphere *)obj->data;
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
}

void		rotate_sphere(const t_o3d *o, double angle, t_v3d axis)
{
	(void)o;
	(void)angle;
	(void)axis;
}
