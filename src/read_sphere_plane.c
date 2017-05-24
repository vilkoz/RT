/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_sphere_plane.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:37:03 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/24 19:37:44 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init_sphere(t_sphere *sp, t_material *m)
{
	sp->center.x = 0;
	sp->center.y = 0;
	sp->center.z = 0;
	sp->radius = 10;
	sp->color = 0xff50ff;
	sp->tex.img = NULL;
	m->refl = 0;
	m->bamp = 0;
}

void		read_sphere(t_scene *s, char **arr)
{
	int			i;
	t_sphere	sp;
	t_material	m;

	i = 0;
	init_sphere(&sp, &m);
	while (arr[++i] != NULL)
	{
		(i == 1) ? sp.center.x = ft_atod(arr[i]) : 23;
		(i == 2) ? sp.center.y = ft_atod(arr[i]) : 23;
		(i == 3) ? sp.center.z = ft_atod(arr[i]) : 23;
		(i == 4) ? sp.radius = (double)ft_atod(arr[i]) : 23;
		if (i == 5 && ft_strchr(arr[i], 'x') != NULL)
			sp.color = ft_atoi_base(ft_strchr(arr[i], 'x') + 1, 16);
		if (i == 6 && ft_strcmp("NULL", arr[i]))
			sp.tex = new_tex(arr[i]);
		(i == 7) ? m.refl = ft_atod(arr[i]) : m.refl;
		(i == 8) ? m.bamp = ft_atod(arr[i]) : m.bamp;
	}
	s->objects[s->cur_o] = new_sphere(new_p3d(sp.center.x, sp.center.y,
	sp.center.z), sp.radius, new_material(sp.color, sp.tex, m.refl, m.bamp));
	s->cur_o++;
	free_arr(&arr);
}

void		read_light(t_scene *s, char **arr)
{
	t_p3d	p;
	int		i;

	p.x = 1000;
	p.y = 1000;
	p.z = 1000;
	i = 0;
	while (arr[++i] != NULL)
	{
		(i == 1) ? p.x = ft_atod(arr[i]) : 23;
		(i == 2) ? p.y = ft_atod(arr[i]) : 23;
		(i == 3) ? p.z = ft_atod(arr[i]) : 23;
	}
	s->ls[s->cur_ls] = (t_p3d *)malloc(sizeof(t_p3d));
	*s->ls[s->cur_ls] = new_p3d(p.x, p.y, p.z);
	s->cur_ls++;
	free_arr(&arr);
}

void		init_plane(t_plane *p, t_material *m)
{
	p->p = new_p3d(0, 1, 2);
	p->norm = new_v3d(0, 1, 0);
	p->color = 0xff50ff;
	p->tex.img = NULL;
	m->refl = 0;
	m->bamp = 0;
}

void		read_plane(t_scene *s, char **arr)
{
	t_plane		p;
	t_material	m;
	int			i;

	i = 0;
	init_plane(&p, &m);
	while (arr[++i] != NULL)
	{
		(i == 1) ? p.p.x = ft_atod(arr[i]) : 23;
		(i == 2) ? p.p.y = ft_atod(arr[i]) : 23;
		(i == 3) ? p.p.z = ft_atod(arr[i]) : 23;
		(i == 4) ? p.norm.x = ft_atod(arr[i]) : 23;
		(i == 5) ? p.norm.y = ft_atod(arr[i]) : 23;
		(i == 6) ? p.norm.z = ft_atod(arr[i]) : 23;
		if (i == 7 && ft_strchr(arr[i], 'x') != NULL)
			p.color = ft_atoi_base(ft_strchr(arr[i], 'x') + 1, 16);
		(i == 8) ? p.tex = new_tex(arr[i]) : p.tex;
		(i == 9) ? m.refl = (ft_atod(arr[i])) : m.refl;
		(i == 10) ? m.bamp = ft_atod(arr[i]) : m.bamp;
	}
	p.norm = (!p.norm.x && !p.norm.y && !p.norm.z) ? new_v3d(0, 1, 0) : p.norm;
	s->objects[s->cur_o] = new_plane(new_p3d(p.p.x, p.p.y, p.p.z), new_v3d(
p.norm.x, p.norm.y, p.norm.z), new_material(p.color, p.tex, m.refl, m.bamp));
	s->cur_o++;
	free_arr(&arr);
}
