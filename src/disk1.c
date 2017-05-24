/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:51:41 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/24 19:51:50 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		move_disk_cone(t_cone *cone, t_p2d move, t_cam *cam)
{
	cone->center = v_to_p(v_add(v_mul(cam->dir_r, move.x),
		p_to_v(cone->center)));
	cone->center = v_to_p(v_add(v_mul(cam->dir_d, move.y),
		p_to_v(cone->center)));
	cone->top->p = v_to_p(v_add(v_mul(cam->dir_r, move.x),
		p_to_v(cone->top->p)));
	cone->top->p = v_to_p(v_add(v_mul(cam->dir_d, move.y),
		p_to_v(cone->top->p)));
}

void		move_disk_cyl(t_cyl *cyl, t_p2d move, t_cam *cam)
{
	cyl->center = v_to_p(v_add(v_mul(cam->dir_r, move.x),
		p_to_v(cyl->center)));
	cyl->center = v_to_p(v_add(v_mul(cam->dir_d, move.y),
		p_to_v(cyl->center)));
	cyl->top->p = v_to_p(v_add(v_mul(cam->dir_r, move.x),
		p_to_v(cyl->top->p)));
	cyl->top->p = v_to_p(v_add(v_mul(cam->dir_d, move.y),
		p_to_v(cyl->top->p)));
	cyl->bot->p = v_to_p(v_add(v_mul(cam->dir_r, move.x),
		p_to_v(cyl->bot->p)));
	cyl->bot->p = v_to_p(v_add(v_mul(cam->dir_d, move.y),
		p_to_v(cyl->bot->p)));
}

void		move_disk(const t_o3d *obj, t_p2d move, t_cam *cam)
{
	t_disk		*c;
	double		alpha;
	double		beta;
	double		dist;

	c = (t_disk *)obj->data;
	dist = distance(cam->pos, c->p);
	alpha = acos(cos_vectors(cam->dir,
		pix_vector_cam(new_p2d(move.x, 0), cam)));
	beta = acos(cos_vectors(cam->dir,
		pix_vector_cam(new_p2d(0, move.y), cam)));
	move.x = dist * tan(alpha) * (move.x < 0 ? -1. : 1.);
	move.y = dist * tan(beta) * (move.y < 0 ? -1. : 1.);
	if (c->cyl)
		move_disk_cyl(c->cyl, move, cam);
	else if (c->cone)
		move_disk_cone(c->cone, move, cam);
	else
	{
		c->p = v_to_p(v_add(v_mul(cam->dir_r, move.x),
			p_to_v(c->p)));
		c->p = v_to_p(v_add(v_mul(cam->dir_d, move.y),
			p_to_v(c->p)));
	}
}
