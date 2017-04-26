/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 17:22:27 by vrybalko          #+#    #+#             */
/*   Updated: 2017/04/26 20:47:37 by kshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		new_color(t_rgb res)
{
	res.r = (res.r < 0) ? 0 : res.r;
	res.r = (res.r > 255) ? 255 : res.r;
	res.g = (res.g < 0) ? 0 : res.g;
	res.g = (res.g > 255) ? 255 : res.g;
	res.b = (res.b < 0) ? 0 : res.b;
	res.b = (res.b > 255) ? 255 : res.b;
	return (res.r << 16 | res.g << 8 | res.b);
}

t_rgb	int_to_rgb(int c)
{
	t_rgb	r;

	r.r = (c & 0xff0000) >> 16;
	r.g = (c & 0xff00) >> 8;
	r.b = c & 0xff;
	return (r);
}

t_rgb	add_rgb_col(t_rgb c1, t_rgb c2)
{
	t_rgb	res;

	res.r = c1.r + c2.r;
	res.g = c1.g + c2.g;
	res.b = c1.b + c2.b;
	return (res);
}

t_rgb	mul_rgb_col(t_rgb c, double k)
{
	t_rgb	res;

	res.r = c.r * k;
	res.g = c.g * k;
	res.b = c.b * k;
	return (res);
}

int		add_colors(int cl1, int cl2)
{
	t_rgb	c1;
	t_rgb	c2;
	t_rgb	res;

	c1 = int_to_rgb(cl1);
	c2 = int_to_rgb(cl2);
	res.r = c1.r + c2.r;
	res.g = c1.g + c2.g;
	res.b = c1.b + c2.b;
	return (new_color(res));
}

int		mix_colors(int cl1, int cl2)
{
	t_rgb	c1;
	t_rgb	c2;
	t_rgb	res;

	c1 = int_to_rgb(cl1);
	c2 = int_to_rgb(cl2);
	res.r = sqrt(c1.r * c1.r + c2.r * c2.r);
	res.g = sqrt(c1.g * c1.g + c2.g * c2.g);
	res.b = sqrt(c1.b * c1.b + c2.b * c2.b);
	return (new_color(res));
}

int		mul_colors(int cl1, double k)
{
	t_rgb		res;

	res = int_to_rgb(cl1);
	res.r = res.r * k;
	res.g = res.g * k;
	res.b = res.b * k;
	return (new_color(res));
}

int		shade_colors(int cl1, double k)
{
	t_rgb		res;

	res = int_to_rgb(cl1);
	res.r *= 1 - k;
	res.g *= 1 - k;
	res.b *= 1 - k;
	return (new_color(res));
}

int		gray_scale(int color)
{
	t_rgb 	c;
	int		avg;

	c = int_to_rgb(color);
	avg = (c.r + c.g + c.b) / 3;
	c.r = avg;
	c.g = c.r;
	c.b = c.g;
	return (new_color(c));
}
