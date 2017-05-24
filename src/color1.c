/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:24:44 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/24 19:25:14 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
	t_rgb	c;
	int		avg;

	c = int_to_rgb(color);
	avg = (c.r + c.g + c.b) / 3;
	c.r = avg;
	c.g = c.r;
	c.b = c.g;
	return (new_color(c));
}
