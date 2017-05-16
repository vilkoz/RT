/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 18:14:52 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/16 15:24:58 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

float		*blackbox(float *vectors, float *scene)
{
	(void)scene;
	return (vectors);
}

/*
** find_intersect_cl works for 2.6 sec
** so arch of this shit shoud be redone
*/

void		render_cl(t_e *e)
{
	// profiler_print(e, "inter vectors");
	// e->int_vec = blackbox(vectors, e->scene);
	// draw_intersected(e);
}
