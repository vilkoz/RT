/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 19:05:49 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/24 19:10:21 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_v3d		get_norm_sphere(t_o3d *dat, t_p3d inter_p)
{
	t_sphere	*sp;
	t_v3d		res;

	sp = (t_sphere *)dat->data;
	res = new_v3d(inter_p.x - sp->center.x, inter_p.y - sp->center.y,
		inter_p.z - sp->center.z);
	return (normalize(res));
}

t_v3d		get_norm_bump_sphere(t_o3d *dat, t_p3d inter_p)
{
	t_sphere	*sp;
	t_v3d		res;
	int			c[3];
	t_p2d		t;

	sp = (t_sphere *)dat->data;
	res = normalize(new_v3d(inter_p.x - sp->center.x, inter_p.y - sp->center.y,
		inter_p.z - sp->center.z));
	if (dat->tex.img)
	{
		t = sphere_coords(dat, inter_p);
		c[0] = get_tex_color_bnw_sphere(dat, t.x, t.y);
		c[1] = get_tex_color_bnw_sphere(dat, (t.x + 1), t.y);
		c[2] = get_tex_color_bnw_sphere(dat, t.x, (t.y + 1));
		t.x = ((double)(c[0] - c[1]) * dat->material.bamp / 2.);
		t.y = ((double)(c[0] - c[2]) * dat->material.bamp / 2.);
		res = v_add(v_add(v_mul(normalize(cross_product(res,
			new_v3d(0, 1, 0))), t.x), res), v_mul(normalize(cross_product(res,
				cross_product(res, new_v3d(0, 1, 0)))), t.y));
	}
	return (normalize(res));
}

int			get_sphere_color(t_o3d *obj, t_p3d inter_p)
{
	t_p2d		p;
	t_sphere	*s;
	t_v3d		proj;
	t_v3d		tmp;

	if (!obj->tex.img)
		return (((t_sphere *)obj->data)->color);
	s = (t_sphere *)obj->data;
	tmp = v_mul(get_norm_sphere(obj, inter_p), s->radius);
	proj = v_mul(new_v3d(1, 0, 0), dot_product(tmp, new_v3d(1, 0, 0)));
	proj = v_sub(tmp, proj);
	p.x = (acos(cos_vectors(proj, new_v3d(0, 0, 1))) / M_PI) *
		(double)(obj->tex.w / 2);
	p.x += (same_dir(new_v3d(0, 0, 1), proj)) ? (double)obj->tex.w / 2. : 0.;
	proj = v_mul(new_v3d(1, 0, 0), dot_product(tmp, new_v3d(1, 0, 0)));
	if (same_dir(proj, new_v3d(1, 0, 0)))
		p.y = obj->tex.h / 2 - (v_len(proj) / s->radius) * (obj->tex.h / 2);
	else
		p.y = (v_len(proj) / (double)s->radius) * (double)obj->tex.h / 2 +
			(double)obj->tex.h / 2;
	return (ft_img_px_get(obj->tex, (int)(p.x * 2.) % obj->tex.w,
		(int)(p.y) % obj->tex.h));
}

int			solve_quad(t_p3d p, double *t0, double *t1)
{
	double		d;
	double		q;

	if ((d = p.y * p.y - 4 * p.x * p.z) < 0)
		return (FALSE);
	else if (d < EPSILON)
	{
		*t0 = -0.5 * p.y / p.x;
		*t1 = *t1;
	}
	else
	{
		q = (p.y > 0) ? -0.5 * (p.y + sqrt(d)) : -0.5 * (p.y - sqrt(d));
		*t0 = q / p.x;
		*t1 = p.z / q;
	}
	if (*t0 > *t1)
		SWAP_D(*t0, *t1);
	return (TRUE);
}

t_o3d		*new_sphere(t_p3d center, double radius, t_material material)
{
	t_sphere	*sp;
	t_o3d		*obj;

	sp = (t_sphere *)malloc(sizeof(t_sphere));
	sp->center = center;
	sp->radius = radius;
	sp->color = material.color;
	obj = (t_o3d *)malloc(sizeof(t_o3d));
	obj->data = (void *)sp;
	obj->get_color = get_sphere_color;
	obj->intersect = intersect_sphere;
	obj->get_norm = get_norm_bump_sphere;
	obj->tex = material.tex;
	obj->material = material;
	obj->rotate = rotate_sphere;
	obj->move = move_sphere;
	return (obj);
}
