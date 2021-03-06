/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 17:36:47 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/24 19:47:34 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			anti_alias(t_p2d p, t_e *e)
{
	t_p3d	p2;
	t_p2d	p3;
	t_rgb	res;
	t_o3d	*obj;
	t_p3d	inter_p;

	p2 = new_p3d(-SAMPLES, -SAMPLES, 0);
	res = int_to_rgb(0);
	while (++p2.x < SAMPLES)
	{
		p2.y = -SAMPLES;
		while (++p2.y < SAMPLES)
		{
			p3 = new_p2d(p.x + (p2.x / (double)(e->w * SAMPLES)) *
			(double)(e->w / e->h), p.y + p2.y / (double)(e->h * SAMPLES));
			if (find_nearest(e->s, new_vec(pix_vector(p3, e->s), e->s->cam.pos),
				&inter_p, &obj))
				res = add_rgb_col(res, int_to_rgb(get_color(e->s, obj,
					new_vec(pix_vector(p3, e->s), inter_p), 3)));
		}
	}
	return (new_color(mul_rgb_col(res, 1. /
		((SAMPLES * 2 - 1) * (SAMPLES * 2 - 1)))));
}

int			fast_render(t_p2d p1, t_p2d p, t_e *e, int t_num)
{
	t_p3d				inter_p;
	t_o3d				*obj;
	int					res;
	t_p2d				i;

	res = 0;
	(void)t_num;
	if ((int)(p1.x) % 10 == 0 && (int)p1.y % 10 == 0)
	{
		if (find_nearest(e->s, new_vec(pix_vector(p, e->s), e->s->cam.pos),
			&inter_p, &obj))
			res = get_light_color(e->s, obj, inter_p);
		i.x = -1;
		while (++i.x < 10)
		{
			i.y = -1;
			while (++i.y < 10)
				ft_img_px_put(e, p1.x + i.x, p1.y + i.y, res);
		}
	}
	return (ft_img_px_get(new_raw_tex(e->img, e->w, e->h), p1.x, p1.y));
}

void		find_intersect(t_e *e, t_scene *s, t_p2d y_area, int i)
{
	t_p2d		p;
	t_p2d		p1;

	p1.y = y_area.x - 1;
	(void)s;
	while (++p1.y < y_area.y)
	{
		p1.x = 0 - 1;
		while (++p1.x < e->w)
		{
			p.x = ((p1.x - e->w / 2.0) / e->w) * ASP;
			p.y = (p1.y - e->h / 2.0) / e->h;
			ft_img_px_put(e, p1.x, p1.y,
				(e->fast_mode) ? fast_render(p1, p, e, i) : anti_alias(p, e));
		}
	}
}

void		*thread_start(void *t)
{
	t_thread	*t1;

	t1 = (t_thread *)t;
	find_intersect(t1->e, t1->e->s, t1->y_area, t1->i);
	return (NULL);
}

void		render(t_e *e)
{
	t_thread	t[THREADS];
	float		dy;
	float		starty;
	int			i;

	dy = (float)e->h / (float)THREADS;
	starty = 0;
	i = -1;
	while (++i < THREADS)
	{
		t[i].e = e;
		t[i].y_area = new_p2d((int)starty, (int)(starty + dy));
		t[i].i = i;
		pthread_create(&(t[i].id), NULL, thread_start, &(t[i]));
		starty += dy;
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(t[i].id, NULL);
}
