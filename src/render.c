/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 17:36:47 by vrybalko          #+#    #+#             */
/*   Updated: 2017/04/21 21:47:11 by vrybalko         ###   ########.fr       */
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
	p_b = new_p3d(p1.x + norm.x * 0.01, p1.y + norm.y * 0.01,
		p1.z + norm.z * 0.01);
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

t_p2d		new_p2d(double x, double y)
{
	t_p2d	p;

	p.x = x;
	p.y = y;
	return (p);
}

int			anti_alias(t_p2d p, t_scene *s)
{
	t_p3d	p2;
	t_p2d	p3;
	t_rgb	res;
	t_p3d	inter_p;
	t_o3d	*obj;

	p2 = new_p3d(-SAMPLES, -SAMPLES, 0);
	res = int_to_rgb(0);
	// res = 0;
	while (++p2.x < SAMPLES)
	{
		p2.y = -SAMPLES;
		while (++p2.y < SAMPLES)
		{
			p3 = new_p2d(p.x + (p2.x / (1300. * SAMPLES)) * (1300. / 700.),
				p.y + p2.y / (700. * SAMPLES));
			if (find_nearest(s, pix_vector(p3, s), &inter_p, &obj))
				res = add_rgb_col(res, int_to_rgb(get_light_color(s, obj, inter_p,
					obj->get_color(obj, inter_p))));
				// res = mix_colors(res, get_light_color(s, obj, inter_p,
				// 	obj->get_color(obj, inter_p)));
		}
	}
	return (new_color(mul_rgb_col(res, 1. / (SAMPLES * SAMPLES))));
	// return (res);
}

void		find_intersect(t_e *e, t_scene *s, t_p2d start, t_p2d end)
{
	t_p2d		p;
	t_p2d		p1;
	// t_p3d		inter_p;
	// t_o3d		*obj;

	p1.y = start.y -1;
	while (++p1.y < end.y)
	{
		p1.x = start.x -1;
		while (++p1.x < end.x)
		{
			p.x = ((p1.x - e->w / 2.0) / e->w) * ASP;
			p.y = (p1.y - e->h / 2.0) / e->h;
			// if (find_nearest(s, pix_vector(p, s), &inter_p, &obj))
				// ft_img_px_put(e, p1.x, p1.y, get_light_color(s,
				// 	obj, inter_p, obj->get_color(obj, inter_p)));
			ft_img_px_put(e, p1.x, p1.y, anti_alias(p, s));
			// if (e->v_x == p1.x && e->v_y == p1.y)
			// 	printf("inter_p = %f %f %f\n", inter_p.x, inter_p.y, inter_p.z);
		}
	}
}

void		*thread_start(void *t)
{
	t_thread	*t1;

	t1 = (t_thread *)t;
	find_intersect(t1->e, t1->e->s, t1->start, t1->end);
	return (NULL);
}

void		render(t_e *e)
{
	t_thread	**t;
	int			dy;
	int			starty;
	int			i;

	t = (t_thread **)malloc(sizeof(t_thread *) * THREADS);
	dy = e->h / THREADS;
	starty = 0;
	i = -1;
	while (++i < THREADS)
	{
		t[i] = malloc(sizeof(t_thread));
		t[i]->e = e;
		t[i]->start = new_p2d(0, starty);
		t[i]->end = new_p2d(e->w, starty + dy);
		pthread_create(&(t[i]->id), NULL, thread_start, (t[i]));
		starty += dy;
	}
	i = -1;
	while (++i < THREADS)
	{
		pthread_join(t[i]->id, NULL);
		free(t[i]);
	}
	free(t);
	// find_intersect(e, e->s);
	e->changed = 0;
}
