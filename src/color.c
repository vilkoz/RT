/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 17:22:27 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/24 19:25:16 by vrybalko         ###   ########.fr       */
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
