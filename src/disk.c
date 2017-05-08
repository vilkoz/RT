/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 14:01:38 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/06 21:07:35 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_v3d		get_norm_disk(t_o3d *o, t_p3d inter_p)
{
	(void)inter_p;
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
		p.y = (p.y < 0) ? o->tex.h - 1 - (abs((int)(p.y)) % o->tex.h) :
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
	|| distance(*inter_p, ray_start) < EPSILON)
		return (FALSE);
	return (TRUE);
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
	return (obj);
}
