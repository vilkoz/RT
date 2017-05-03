/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poligon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosobliv <aosobliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 18:51:48 by aosobliv          #+#    #+#             */
/*   Updated: 2017/05/03 20:55:25 by aosobliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_v3d	get_norm_poly(void *dat, t_p3d inter_p)
{
	(void)inter_p;
	return (((t_poly *)dat)->norm);
}

int		get_poly_color(t_o3d *obj, t_p3d inter_p)
{
	(void)inter_p;
	return (((t_poly *)obj->data)->color);
}

int		line_intersect(t_p2d point, t_p2d a, t_p2d b)
{
	if ((((a.y <= point.y) && (point.y < b.y))
		|| ((b.y <= point.y) && (point.y < a.y))) &&
			(point.x > (b.x - a.x) * (point.y - a.y / (b.y - a.y) + a.x)))
		return (1);
  return (0);
}

// plane_coords принимает t_vec
// ** use new_vec(t_v3d plane_normal, t_p3d plane_origin) to create new vec
// ** v.p - plane origin (точка через которую плоскость проходит, относительно нее будут считаться координаты)
// ** v.dir - plane normal (нормаль к плоскости)

int		in_poligon(t_poly *poly, t_p3d inter_p)
{
	int		c;
	int		i;
	t_p2d	in_p;
	t_vec	curr;

	c = 0;
	i = -1;
	curr = new_vec(poly->norm, poly->P[0]);
	in_p = plane_coords(curr, inter_p);
	while (++i < poly->count - 1)
		c += line_intersect(in_p, plane_coords(curr,
			poly->P[i]), plane_coords(curr, poly->P[i + 1]));
	c += line_intersect(in_p, plane_coords(curr, poly->P[0]),
		plane_coords(curr, poly->P[poly->count - 1]));
	if (c % 2 == 0 && c != 0)
		return (1);
	return (0);
}

int		intersect_poly(const void *data, t_p3d *inter_p)
{
	t_poly	poly;
	poly = *(t_poly *)data;
	if (in_poligon(&poly, *inter_p) == 0)
		return (FALSE);
	return (1);
}

t_o3d	*new_poly(t_p3d *P, int count, t_material material)
{
	t_o3d		*obj;
	t_poly		*poly;

	poly = (t_poly *)malloc(sizeof(t_poly));
	poly->P = P;
	poly->count = count;
	poly->norm = normalize(cross_product(new_v3d_p(poly->P[0], poly->P[1]),
		new_v3d_p(poly->P[0], poly->P[2])));
	poly->color = material.color;
	obj = (t_o3d *)malloc(sizeof(t_o3d));
	obj->data = (void *)poly;
	obj->get_color = get_poly_color;
	obj->get_norm = get_norm_poly;
	obj->intersect = (int (*)(const void *, const t_p3d, const t_v3d, t_p3d *))
		intersect_poly;
	obj->tex = material.tex;
	obj->material = material;
	return (obj);
}
