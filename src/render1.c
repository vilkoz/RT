/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:47:45 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/24 19:47:53 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			is_viewable(t_p3d p1, t_p3d p2, t_scene *s, t_o3d *obj1)
{
	int		i;
	t_o3d	*obj;
	t_p3d	inter_p;

	i = -1;
	(void)obj1;
	while (++i < s->obj_num)
	{
		obj = s->objects[i];
		if (obj->intersect(obj, p1, normalize(new_v3d_p(p2, p1)),
			&inter_p) && distance(inter_p, p1) > EPSILON)
		{
			if (distance(p1, inter_p) > distance(p1, p2))
				continue ;
			return (FALSE);
		}
	}
	return (TRUE);
}

/*
** p.x = min_distance
** p.y = current_distance
*/

int			find_nearest(t_scene *s, t_vec vec, t_p3d *inter_p, t_o3d **obj1)
{
	t_o3d	*obj;
	t_p3d	p;
	t_p3d	min_p;

	p = new_p3d(0, 0, -1);
	while (++p.z < s->obj_num)
	{
		obj = s->objects[(int)p.z];
		if (obj->intersect(obj, vec.p, vec.dir, inter_p))
		{
			p.y = distance(*inter_p, vec.p);
			(p.x == 0) ? p.x = p.y : 23;
			if (p.y <= p.x)
			{
				p.x = p.y;
				min_p = new_p3d(inter_p->x, inter_p->y, inter_p->z);
				*obj1 = obj;
			}
		}
	}
	(p.x != 0) ? *inter_p = new_p3d(min_p.x, min_p.y, min_p.z) : *inter_p;
	if (p.x == 0)
		return (FALSE);
	else
		return (TRUE);
}
