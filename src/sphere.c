/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 19:05:49 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/03 20:45:33 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_v3d	get_norm_sphere(t_o3d *dat, t_p3d inter_p)
{
	t_sphere	*sp;
	t_v3d		res;

	sp = (t_sphere *)dat->data;
	res = new_v3d(inter_p.x - sp->center.x, inter_p.y - sp->center.y,
		inter_p.z - sp->center.z);
	return (normalize(res));
}

int		get_sphere_color(t_o3d *obj, t_p3d inter_p)
{
	t_p2d		p;
	t_sphere	*s;
	t_v3d		proj;
	t_v3d		tmp;

	if (obj->tex.img)
	{
		s = (t_sphere *)obj->data;
		tmp = v_mul(obj->get_norm(obj, inter_p), s->radius);
		proj = v_mul(new_v3d(1, 0, 0), dot_product(tmp, new_v3d(1, 0, 0)));
		proj = v_sub(tmp, proj);
		p.x = (acos(cos_vectors(proj, new_v3d(0, 0, 1))) / M_PI) * obj->tex.w;
		proj = v_mul(new_v3d(0, 0, 1), dot_product(tmp, new_v3d(0, 0, 1)));
		proj = v_sub(tmp, proj);
		p.y = (acos(cos_vectors(proj, new_v3d(1, 0, 0))) / M_PI) * obj->tex.h;
		return (ft_img_px_get(obj->tex, (int)p.x * 2 % obj->tex.w,
			(int)p.y * 2 % obj->tex.h));
	}
	else
		return (((t_sphere *)obj->data)->color);
}

int		solve_quad(t_p3d p, double *t0, double *t1)
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

int		intersect_sphere(const t_o3d *data, const t_p3d ray_start,
						const t_v3d ray, t_p3d *inter_p)
{
	double		t0;
	double		t1;
	double		t;
	t_sphere	*sp;

	sp = (t_sphere *)data->data;
	if (!solve_quad(new_p3d(1., 2 * (ray.x * (ray_start.x - sp->center.x) +
					ray.y * (ray_start.y - sp->center.y) +
					ray.z * (ray_start.z - sp->center.z)),
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
	*inter_p = new_p3d(ray_start.x + t * ray.x, ray_start.y + t * ray.y,
					ray_start.z + t * ray.z);
	return (1);
}

t_o3d	*new_sphere(t_p3d center, double radius, t_material material)
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
	obj->get_norm = get_norm_sphere;
	obj->tex = material.tex;
	obj->material = material;
	return (obj);
}
