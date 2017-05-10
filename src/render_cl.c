/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 18:14:52 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/10 21:31:06 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec		*new_vec_mal(t_v3d v, t_p3d p)
{
	t_vec	*new;

	new = (t_vec*)malloc(sizeof(t_vec));
	ft_memcpy((void*)&new->dir, (void*)&v, sizeof(t_v3d));
	ft_memcpy((void*)&new->p, (void*)&p, sizeof(t_p3d));
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
	arr = (float*)malloc(sizeof(float) * (6 * size));
	tmp = e->vectors;
	i = 0;
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

float		*blackbox(float *vectors, float *scene);

void		render_cl(t_e *e)
{
	float		*vectors;

	find_intersect_cl(e, e->s);
	vectors = return_vec_array(e);
	vectors = blackbox(vectors, e->scene);
}
