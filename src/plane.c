/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 19:05:49 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/16 17:50:45 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_v3d	get_norm_plane(t_o3d *o, t_p3d inter_p)
{
	// int	c1;
	// int	c2;
	// int	c3;
	// t_p3d	g;
	// t_v3d	nx;
	// t_v3d	a;
	// t_v3d	perp;
	// t_p2d	p;
	// t_v3d	v_axis;
	//
	// (void)inter_p;
	// t_plane	*pl;
	// pl = (t_plane *)o->data;
	// if (o->tex.img)
	// {
	// 	nx = normalize(cross_product(pl->norm, normalize(new_v3d(0, 0, 1))));
	// 	a = v_sub(new_v3d_p(pl->p, new_p3d(0, 0, 0)),
	// 	new_v3d_p(inter_p, new_p3d(0, 0, 0)));
	// 	perp = v_sub(a, v_mul(nx, dot_product(a, nx)));
	// 	p.y = v_len(perp);
	// 	p.x = v_len(new_v3d_p(new_p3d(inter_p.x + perp.x, inter_p.y + perp.y,
	// 		inter_p.z + perp.z), pl->p));
	// 	c1 = gray_scale(ft_img_px_get(o->tex, ((int)(p.x) % o->tex.w),
	// 	((int)(p.y) % o->tex.h)));
	// 	c2 = gray_scale(ft_img_px_get(o->tex, ((int)(p.x + 1) % o->tex.w),
	// 	((int)(p.y) % o->tex.h)));
	// 	c3 = gray_scale(ft_img_px_get(o->tex, ((int)(p.x) % o->tex.w),
	// 	((int)(p.y + 1) % o->tex.h)));
	// 	g.x = c1 - c2;
	// 	g.y = c3 - c2;
	// 	perp = normalize(perp);
	// 	v_axis = cross_product(perp, pl->norm);
	// 	return (v_add(v_add(v_mul(perp, g.x), pl->norm), v_mul(v_axis, g.y)));
	// 	}
	(void)inter_p;
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
		p.x = (p.x < 0) ? o->tex.w - 1 - (abs((int)(p.x)) % o->tex.w) :
			(int)p.x % o->tex.w;
		p.y = (p.y < 0) ? o->tex.h - 1 - (abs((int)(p.y)) % o->tex.h) :
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
	return (TRUE);
}

void	rotate_plane(const t_o3d *obj, double angle, t_v3d axis)
{
	t_plane		*pl;

	pl = (t_plane *)obj->data;
	pl->norm = rotate_v_q(pl->norm, axis, angle);
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
	obj->rotate = rotate_plane;
	return (obj);
}
