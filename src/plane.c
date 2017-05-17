/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 19:05:49 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/17 18:24:19 by kshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_v3d	get_norm_plane(t_o3d *o, t_p3d inter_p)
{
	int		c[3];
	t_p3d	g;
	t_p2d	p;
	t_plane	*pl;
	t_v3d	axis;

	if (o->tex.img)
	{
		pl = (t_plane *)o->data;
		p = plane_coords(new_vec(pl->norm, pl->p), inter_p);
		p.x = (p.x < 0) ? (o->tex.w - 1) - (abs((int)(p.x)) % o->tex.w) :
			(int)p.x % o->tex.w;
		p.y = (p.y < 0) ? (o->tex.h - 2) - (abs((int)(p.y)) % o->tex.h) :
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
	return (((t_plane *)o->data)->norm);
}

int		get_plane_color(t_o3d *o, t_p3d inter_p)
{
	t_p2d	p;
	t_plane	*pl;

	pl = (t_plane *)o->data;
	if (o->tex.img)
	{
		p = plane_coords(new_vec(pl->norm, pl->p), inter_p);
		p.x = (p.x < 0) ? (o->tex.w - 1) - (abs((int)(p.x)) % o->tex.w) :
			(int)p.x % o->tex.w;
		p.y = (p.y < 0) ? (o->tex.h - 2) - (abs((int)(p.y)) % o->tex.h) :
			(int)p.y % o->tex.h;
		return (ft_img_px_get(o->tex, (int)p.x, (int)p.y));
	}
	else
		return (pl->color);
}

int		intersect_plane(const t_o3d *data, const t_p3d ray_start,
						const t_v3d ray, t_p3d *inter_p)
{
	t_plane		*pl;
	t_v3d		w;
	double		dot;

	pl = (t_plane *)data->data;
	if (fabs(dot = dot_product(pl->norm, ray)) < EPSILON)
		return (FALSE);
	w = new_v3d(ray_start.x - pl->p.x, ray_start.y - pl->p.y,
		ray_start.z - pl->p.z);
	if ((dot = -dot_product(pl->norm, w) / dot) < 0)
		return (FALSE);
	*inter_p = new_p3d(ray_start.x + ray.x * dot, ray_start.y + ray.y * dot,
		ray_start.z + ray.z * dot);
	if (dot_product(new_v3d(inter_p->x - ray_start.x, inter_p->y - ray_start.y,
		inter_p->z - ray_start.z), ray) < 0)
		return (FALSE);
	if (distance(ray_start, *inter_p) < EPSILON)
		return (FALSE);
	return (TRUE);
}

t_o3d	*new_plane(t_p3d p, t_v3d norm, t_material material)
{
	t_plane		*sp;
	t_o3d		*obj;

	sp = (t_plane *)malloc(sizeof(t_plane));
	sp->p = p;
	sp->norm = norm;
	sp->color = material.color;
	obj = (t_o3d *)malloc(sizeof(t_o3d));
	obj->data = (void *)sp;
	obj->get_color = get_plane_color;
	obj->intersect = intersect_plane;
	obj->get_norm = get_norm_plane;
	obj->tex = material.tex;
	obj->material = material;
	return (obj);
}
