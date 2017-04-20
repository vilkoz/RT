/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_img_px_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 15:59:57 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/13 16:27:13 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_img_px_put(t_e *e, int x, int y, int rgb)
{
	int				bpp;
	int				sl;
	int				en;
	char			*imag;
	unsigned int	tmp;

	imag = mlx_get_data_addr(e->img, &bpp, &sl, &en);
	tmp = (mlx_get_color_value(e->mlx, rgb));
	if (x > 0 && x < e->w && y > 0 && y < e->h)
		ft_memcpy((void *)((imag + y * e->w *
						(bpp / 8) + x * (bpp / 8))), (void *)&tmp, 4);
}
