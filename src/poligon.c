/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poligon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosobliv <aosobliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 18:51:48 by aosobliv          #+#    #+#             */
/*   Updated: 2017/05/03 17:47:29 by aosobliv         ###   ########.fr       */
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

int		in_poligon(t_poly *poly, t_p3d inter_p)
{
	int		c;
	int		i;

	c = 0;
	i = -1;
	while (++i + 1 != poly->count)
		c += line_intersect( точка , plane_coords(new_v3d(0, 0, 1),
			poly->poly[i]), plane_coords(new_v3d(0, 0, 1) , poly->poly[i + 1]));
	c += line_intersect( точка , plane_coords(new_v3d(0, 0, 1) , poly->poly[0]),
		plane_coords(new_v3d(0, 0, 1) , poly->poly[poly->count]));
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

t_o3d	*new_poly(t_poly *poly, t_material material)
{
	t_o3d		*obj;

	poly->color = material.color;
	obj = (t_o3d *)malloc(sizeof(t_o3d));
	obj->data = (void *)poly;
	obj->get_color = get_poly_color;
	obj->intersect = intersect_poly;
	obj->get_norm = get_norm_poly;
	obj->tex = material.tex;
	obj->material = material;
	return (obj);
}
