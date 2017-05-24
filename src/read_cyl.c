/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cyl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:33:17 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/24 19:34:24 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init_cyl(t_cyl *c, t_material *m)
{
	c->center.x = 0;
	c->center.y = 0;
	c->center.z = 0;
	c->dir.x = 0;
	c->dir.y = 0;
	c->dir.z = 1;
	c->radius = 100;
	c->h = 10000;
	c->color = 0xffa0;
	m->tex.img = NULL;
	m->refl = 0;
	m->bamp = 0;
}

void		add_cyl_top(t_scene *s)
{
	t_cyl		*c;
	t_p3d		top;
	t_p3d		bot;
	t_material	m;

	c = (t_cyl *)s->objects[s->cur_o - 1]->data;
	m = s->objects[s->cur_o - 1]->material;
	bot = v_to_p(v_sub(p_to_v(c->center), v_mul(c->dir, c->h)));
	top = v_to_p(v_add(p_to_v(c->center), v_mul(c->dir, c->h)));
	s->objects[s->cur_o] = new_disk(new_vec(c->dir, top), c->radius, c->color,
		m);
	s->cur_o++;
	s->objects[s->cur_o] = new_disk(new_vec(v_inv(c->dir), bot), c->radius,
		c->color, m);
	s->cur_o++;
	((t_cyl *)(s->objects[s->cur_o - 3]->data))->top =
		(t_disk*)s->objects[s->cur_o - 2]->data;
	((t_disk*)(s->objects[s->cur_o - 2]->data))->cyl =
		(t_cyl *)(s->objects[s->cur_o - 3]->data);
	((t_disk*)(s->objects[s->cur_o - 2]->data))->cone = NULL;
	((t_cyl *)(s->objects[s->cur_o - 3]->data))->bot =
		(t_disk*)s->objects[s->cur_o - 1]->data;
	((t_disk*)(s->objects[s->cur_o - 1]->data))->cyl =
		(t_cyl *)(s->objects[s->cur_o - 3]->data);
	((t_disk*)(s->objects[s->cur_o - 1]->data))->cone = NULL;
}

void		fill_cyl(char **arr, t_cyl *c, t_material *m)
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
		(i == 7) ? c->radius = (double)ft_atod(arr[i]) : 23;
		(i == 8) ? c->h = (double)ft_atod(arr[i]) : 23;
		if (i == 9 && ft_strchr(arr[i], 'x') != NULL)
			c->color = ft_atoi_base(ft_strchr(arr[i], 'x') + 1, 16);
		(i == 10) ? m->tex = new_tex(arr[i]) : m->tex;
		(i == 11) ? m->refl = ft_atod(arr[i]) : m->refl;
		(i == 12) ? m->bamp = ft_atod(arr[i]) : m->bamp;
	}
}

void		read_cyl(t_scene *s, char **arr)
{
	t_cyl		c;
	t_material	m;

	init_cyl(&c, &m);
	fill_cyl(arr, &c, &m);
	c.dir = (!c.dir.x && !c.dir.y && !c.dir.z) ? new_v3d(0, 1, 0) :
		c.dir;
	s->objects[s->cur_o] = new_cyl(new_vec(new_v3d(c.dir.x, c.dir.y, c.dir.z),
		new_p3d(c.center.x, c.center.y, c.center.z)), c.radius, c.h,
		new_material(c.color, m.tex, m.refl, m.bamp));
	s->cur_o++;
	add_cyl_top(s);
	free_arr(&arr);
}
