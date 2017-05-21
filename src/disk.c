/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 14:01:38 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/21 23:30:10 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_v3d		get_norm_disk(t_o3d *o, t_p3d inter_p)
{
	int		c[3];
	t_p3d	g;
	t_p2d	p;
	t_disk	*pl;
	t_v3d	axis;

	pl = (t_disk *)o->data;
	if (o->tex.img)
	{
		p = plane_coords(new_vec(pl->norm, pl->p), inter_p);
		p.x = (p.x < 0) ? o->tex.w - 1 - (abs((int)(p.x)) % o->tex.w) :
			(int)p.x % o->tex.w;
		p.y = (p.y < 0) ? o->tex.h - 2 - (abs((int)(p.y)) % o->tex.h) :
			(int)p.y % o->tex.h;
		c[0] = gray_scale(ft_img_px_get(o->tex, (int)p.x, (int)p.y));
		c[1] = gray_scale(ft_img_px_get(o->tex, (int)p.x + 1, (int)p.y));
		c[2] = gray_scale(ft_img_px_get(o->tex, (int)p.x, (int)p.y + 1));
		g.x = ((double)(c[0] - c[1]) * o->material.bamp);
		g.y = ((double)(c[0] - c[2]) * o->material.bamp);
		axis = normalize((cross_product(pl->norm,
			normalize(new_v3d(0, 0, 1)))));
		return (v_add(v_add(v_mul(axis, g.x), pl->norm),
			v_mul(normalize((cross_product(axis, pl->norm))), g.y)));

	}
	return (((t_disk*)(o->data))->norm);
}

int			get_color_disk(t_o3d *o, t_p3d inter_p)
{
	t_p2d	p;
	t_disk	*pl;

	pl = (t_disk *)o->data;
	if (o->tex.img)
	{
		p = plane_coords(new_vec(pl->norm, pl->p), inter_p);
		p.x = (p.x < 0) ? o->tex.w - 1 - (abs((int)(p.x)) % o->tex.w) :
			(int)p.x % o->tex.w;
		p.y = (p.y < 0) ? o->tex.h - 2 - (abs((int)(p.y)) % o->tex.h) :
			(int)p.y % o->tex.h;
		return (ft_img_px_get(o->tex, (int)p.x, (int)p.y));
	}
	else
		return (pl->color);
}

int			intersect_disk(const t_o3d *o, const t_p3d ray_start,
				const t_v3d ray, t_p3d *inter_p)
{
	t_disk		*pl;
	t_v3d		w;
	double		dot;

	pl = (t_disk *)o->data;
	if (fabs(dot = dot_product(pl->norm, ray)) < EPSILON)
		return (FALSE);
	w = new_v3d(ray_start.x - pl->p.x, ray_start.y - pl->p.y,
		ray_start.z - pl->p.z);
	if ((dot = -dot_product(pl->norm, w) / dot) < 0)
		return (FALSE);
	*inter_p = new_p3d(ray_start.x + ray.x * dot, ray_start.y + ray.y * dot,
		ray_start.z + ray.z * dot);
	if (dot_product(new_v3d_p(*inter_p, ray_start), ray) < 0)
		return (FALSE);
	if (v_len(new_v3d_p(*inter_p, pl->p)) > pl->radius
	|| distance(ray_start, *inter_p) < EPSILON)
		return (FALSE);
	return (TRUE);
}

void		rotate_disk(const t_o3d *o, double angle, t_v3d axis)
{
	t_disk		*pl;

	pl = (t_disk *)o->data;
	if (pl->cyl)
	{
		pl->cyl->dir = rotate_v_q(pl->cyl->dir, axis, angle);
		pl->cyl->top->p = v_to_p(v_add(v_mul(pl->cyl->dir, pl->cyl->h),
			p_to_v(pl->cyl->center)));
		pl->cyl->top->norm = pl->cyl->dir;
		pl->cyl->bot->p = v_to_p(v_add(v_mul(v_inv(pl->cyl->dir), pl->cyl->h),
			p_to_v(pl->cyl->center)));
		pl->cyl->bot->norm = v_inv(pl->cyl->dir);
	}
	else if (pl->cone)
	{
		pl->cone->dir = rotate_v_q(pl->cone->dir, axis, angle);
		pl->cone->top->p = v_to_p(v_add(v_mul(pl->cone->dir, pl->cone->h),
			p_to_v(pl->cone->center)));
		pl->cone->top->norm = pl->cone->dir;
	}
	else
		pl->norm = rotate_v_q(pl->norm, axis, angle);
}

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

t_o3d		*new_disk(t_vec v, double radius, int color, t_material material)
{
	t_disk		*d;
	t_o3d		*obj;

	d = (t_disk *)malloc(sizeof(t_disk));
	d->p = v.p;
	d->norm = v.dir;
	d->radius = radius;
	d->color = color;
	obj = (t_o3d *)malloc(sizeof(t_o3d));
	obj->data = (void*)d;
	obj->get_color = get_color_disk;
	obj->intersect = intersect_disk;
	obj->get_norm = get_norm_disk;
	obj->tex = material.tex;
	obj->material = material;
	obj->rotate = rotate_disk;
	obj->move = move_disk;
	return (obj);
}
