/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:28:18 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/24 19:30:41 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init_cone(t_cone *c, t_material *m)
{
	c->center.x = 0;
	c->center.y = 0;
	c->center.z = 0;
	c->dir.x = 0;
	c->dir.y = 0;
	c->dir.z = 1;
	c->a = 60;
	c->h = 10000;
	c->color = 0xffa0;
	m->tex.img = NULL;
	m->refl = 0;
}

void		add_cone_top(t_scene *s)
{
	t_cone		*c;
	t_p3d		top;
	double		radius;
	t_material	m;

	c = (t_cone *)s->objects[s->cur_o - 1]->data;
	m = s->objects[s->cur_o - 1]->material;
	top = v_to_p(v_add(p_to_v(c->center), v_mul(c->dir, c->h)));
	radius = (c->sin_a / c->cos_a) * c->h;
	s->objects[s->cur_o] = new_disk(new_vec(c->dir, top), radius, c->color, m);
	s->cur_o++;
	((t_cone *)(s->objects[s->cur_o - 2]->data))->top =
		(t_disk*)s->objects[s->cur_o - 1]->data;
	((t_disk*)(s->objects[s->cur_o - 1]->data))->cone =
		(t_cone *)(s->objects[s->cur_o - 2]->data);
	((t_disk*)(s->objects[s->cur_o - 1]->data))->cyl = NULL;
}

void		fill_cone(char **arr, t_cone *c, t_material *m)
{
	int			i;

	i = 0;
	while (arr[++i])
	{
		(i == 1) ? c->center.x = ft_atod(arr[i]) : 23;
		(i == 2) ? c->center.y = ft_atod(arr[i]) : 23;
		(i == 3) ? c->center.z = ft_atod(arr[i]) : 23;
		(i == 4) ? c->dir.x = ft_atod(arr[i]) : 23;
		(i == 5) ? c->dir.y = ft_atod(arr[i]) : 23;
		(i == 6) ? c->dir.z = ft_atod(arr[i]) : 23;
		(i == 7) ? c->a = (double)ft_atod(arr[i]) : 23;
		(i == 8) ? c->h = (double)ft_atod(arr[i]) : 23;
		if (i == 9 && ft_strchr(arr[i], 'x') != NULL)
			c->color = ft_atoi_base(ft_strchr(arr[i], 'x') + 1, 16);
		(i == 10) ? m->tex = new_tex(arr[i]) : m->tex;
		(i == 11) ? m->refl = ft_atod(arr[i]) : m->refl;
	}
}

void		read_cone(t_scene *s, char **arr)
{
	t_material	m;
	t_cone		c;

	init_cone(&c, &m);
	fill_cone(arr, &c, &m);
	c.dir = (!c.dir.x && !c.dir.y && !c.dir.z) ? new_v3d(0, 1, 0) :
		c.dir;
	s->objects[s->cur_o] = new_cone(new_vec(normalize(new_v3d(c.dir.x, c.dir.y,
		c.dir.z)), new_p3d(c.center.x, c.center.y, c.center.z)), c.h, c.a,
		new_material(c.color, m.tex, m.refl, 0));
	s->cur_o++;
	add_cone_top(s);
	free_arr(&arr);
}
