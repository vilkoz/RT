/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 17:36:47 by vrybalko          #+#    #+#             */
/*   Updated: 2017/04/21 21:02:11 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			is_viewable(t_p3d p1, t_p3d p2, t_scene *s, t_o3d *obj1)
{
	int		i;
	t_o3d	*obj;
	t_v3d	norm;
	t_p3d	inter_p;
	t_p3d	p_b;

	i = -1;
	norm = obj1->get_norm(obj1->data, p1);
	p_b = new_p3d(p1.x + norm.x * s->bias, p1.y + norm.y * s->bias,
		p1.z + norm.z * s->bias);
	while (++i < s->obj_num)
	{
		obj = s->objects[i];
		if (obj->intersect(obj->data, p_b, normalize(new_v3d_p(p2, p_b)),
			&inter_p))
		{
			if (distance(p1, inter_p) > distance(p1, p2))
				continue ;
			return (FALSE);
		}
	}
	return (TRUE);
}

int			get_light_color(t_scene *s, t_o3d *obj, t_p3d inter_p, int c)
{
	double		cosv;
	int			light_c;
	int			ret_c;
	t_v3d		norm;
	int			i;

	norm = obj->get_norm(obj->data, inter_p);
	i = -1;
	while (++i < s->ls_num)
	{
		if (is_viewable(inter_p, *s->ls[i], s, obj))
		{
			light_c = add_colors(c, mul_colors(0xffffff, 0.4));
			cosv = (dot_product(normalize(norm), normalize(new_v3d_p(*s->ls[i],
				inter_p))) - 0.95) * 20;
			if ((cosv) < 0.1)
				light_c = shade_colors(light_c, (1 - cosv) / 21);
			else
				light_c = add_colors(light_c, mul_colors(light_c, cosv));
		}
		else
			light_c = shade_colors(c, 0.975);
		ret_c = (i == 0) ? light_c : mix_colors(ret_c, light_c);
	}
	return (ret_c);
}

/*
** p.x = min
** p.y = dist
*/

int			find_nearest(t_scene *s, t_v3d dir, t_p3d *inter_p, t_o3d **obj1)
{
	t_o3d	*obj;
	t_p3d	p;
	t_p3d	min_p;

	p = new_p3d(0, 0, -1);
	while (++p.z < s->obj_num)
	{
		obj = s->objects[(int)p.z];
		if (obj->intersect(obj->data, s->cam.pos, dir, inter_p))
		{
			p.y = distance(*inter_p, s->cam.pos);
			(p.x == 0) ? p.x = p.y : 23;
			if (p.y <= p.x)
			{
				p.x = p.y;
				min_p = new_p3d(inter_p->x, inter_p->y, inter_p->z);
				*obj1 = obj;
			}
		}
	}
	*inter_p = (p.x != 0) ? new_p3d(min_p.x, min_p.y, min_p.z) : *inter_p;
	if (p.x == 0)
		return (FALSE);
	else
		return (TRUE);
}

void		find_intersect(t_e *e, t_scene *s)
{
	t_p2d		p;
	t_p2d		p1;
	t_p3d		inter_p;
	t_o3d		*obj;

	p1.y = -1;
	while (++p1.y < e->h)
	{
		p1.x = -1;
		while (++p1.x < e->w)
		{
			p.x = ((p1.x - e->w / 2.0) / e->w) * ASP;
			p.y = (p1.y - e->h / 2.0) / e->h;
			if (find_nearest(s, pix_vector(p, s), &inter_p, &obj))
				ft_img_px_put(e, p1.x, p1.y, get_light_color(s,
					obj, inter_p, obj->get_color(obj, inter_p)));
			if (e->v_x == p1.x && e->v_y == p1.y)
				printf("inter_p = %f %f %f\n", inter_p.x, inter_p.y, inter_p.z);
		}
	}
}

void		render(t_e *e)
{
	e->s->bias = e->bias;
	find_intersect(e, e->s);
	e->changed = 0;
}
