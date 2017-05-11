/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 18:14:52 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/11 17:24:49 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec		*new_vec_mal(t_v3d v, t_p3d p)
{
	t_vec	*new;

	new = (t_vec*)malloc(sizeof(t_vec));
	new->dir.x = v.x;
	new->dir.y = v.y;
	new->dir.z = v.z;
	new->p.x = p.x;
	new->p.y = p.y;
	new->p.z = p.z;
	return (new);
}

void		fill_anti_alias(t_p2d p, t_e *e)
{
	t_p3d	p2;
	t_p2d	p3;
	t_rgb	res;
	t_vec	*v;

	p2 = new_p3d(-SAMPLES, -SAMPLES, 0);
	res = int_to_rgb(0);
	while (++p2.x < SAMPLES)
	{
		p2.y = -SAMPLES;
		while (++p2.y < SAMPLES)
		{
			p3 = new_p2d(p.x + (p2.x / (double)(e->w * SAMPLES)) *
			(double)(e->w / e->h), p.y + p2.y / (double)(e->h * SAMPLES));
			v = new_vec_mal(pix_vector(p3, e->s), e->s->cam.pos);
			ft_lstadd(&e->vectors, ft_lstnew((void*)v, sizeof(t_vec)));
			free(v);
		}
	}
}

void		find_intersect_cl(t_e *e, t_scene *s)
{
	t_p2d		p;
	t_p2d		p1;

	p1.y = -1;
	(void)s;
	while (++p1.y < e->h)
	{
		p1.x = 0 - 1;
		while (++p1.x < e->w)
		{
			p.x = ((p1.x - e->w / 2.0) / e->w) * ASP;
			p.y = (p1.y - e->h / 2.0) / e->h;
			fill_anti_alias(p, e);
		}
	}
}

size_t		count_list(t_list *lst)
{
	t_list		*tmp;
	size_t		i;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void		del(void *data, size_t size)
{
	(void)size;
	ft_memdel(&data);
}

float		*return_vec_array(t_e *e)
{
	float		*arr;
	size_t		size;
	int			i;
	t_list		*tmp;

	size = count_list(e->vectors);
	arr = (float*)malloc(sizeof(float) * (6 * size + 1));
	tmp = e->vectors;
	arr[0] = size;
	i = 1;
	while (tmp)
	{
		arr[i + 0] = ((t_vec*)tmp->content)->dir.x;
		arr[i + 1] = ((t_vec*)tmp->content)->dir.y;
		arr[i + 2] = ((t_vec*)tmp->content)->dir.z;
		arr[i + 3] = ((t_vec*)tmp->content)->p.x;
		arr[i + 4] = ((t_vec*)tmp->content)->p.y;
		arr[i + 5] = ((t_vec*)tmp->content)->p.z;
		tmp = tmp->next;
		i += 6;
	}
	ft_lstdel(&e->vectors, del);
	return (arr);
}

#define SAMPLES2 ((SAMPLES * 2 - 1) * (SAMPLES * 2 - 1))
#define SAMPLE_R (SAMPLES * 2 - 1)

int			draw_antialiased(t_p2d p, t_e *e)
{
	t_p3d	p2;
	t_p2d	p3;
	t_rgb	res;
	t_o3d	*obj;
	t_p3d	inter_p;
	float	*cur;

	p2 = new_p3d(-SAMPLES, -SAMPLES, 0);
	res = int_to_rgb(0);
	while (++p2.x < SAMPLES)
	{
		p2.y = -SAMPLES;
		while (++p2.y < SAMPLES)
		{
			cur =
&e->int_vec[(int)(p.y * e->w * SAMPLE_R + 6 * p.x * SAMPLE_R + 0)];
			if (cur[1] == 1)
			{
				p3 = new_p2d(((p.x - e->w / 2.0) / e->w) * ASP + (p2.x /
(double)(e->w * SAMPLES)) * (double)(e->w / e->h), (p.y - e->h / 2.0) / e->h +
p2.y / (double)(e->h * SAMPLES));
				obj = e->s->objects[(int)cur[0]];
				inter_p = new_p3d(cur[2], cur[3], cur[4]);
				res = add_rgb_col(res, int_to_rgb(get_color(e->s, obj,
					new_vec(pix_vector(p3, e->s), inter_p), 3)));
			}
		}
	}
	return (new_color(mul_rgb_col(res, 1. /
		((SAMPLES * 2 - 1) * (SAMPLES * 2 - 1)))));
}

void		draw_intersected(t_e *e)
{
	t_p2d		p1;

	p1.y = -1;
	while (++p1.y < e->h)
	{
		p1.x = 0 - 1;
		while (++p1.x < e->w)
		{
			ft_img_px_put(e, p1.x, p1.y, draw_antialiased(p1, e));
		}
	}
}

float		*blackbox(float *vectors, float *scene);

void		render_cl(t_e *e)
{
	float		*vectors;

	find_intersect_cl(e, e->s);
	vectors = return_vec_array(e);
	e->int_vec = blackbox(vectors, e->scene);
	draw_intersected(e);
}
