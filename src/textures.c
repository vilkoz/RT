/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 18:50:51 by vrybalko          #+#    #+#             */
/*   Updated: 2017/04/21 20:41:50 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_tex	new_tex(char *path)
{
	t_tex	t;

	if ((t.img = mlx_xpm_file_to_image(mlx_init(), path, &(t.w), &(t.h)))
		== NULL)
		perror(path);
	return (t);
}

int		ft_img_px_get(t_tex tex, int x, int y)
{
	int				bpp;
	int				sl;
	int				en;
	char			*imag;
	int				tmp;

	imag = mlx_get_data_addr(tex.img, &bpp, &sl, &en);
	tmp = 0;
	if (x >= 0 && x < tex.w && y >= 0 && y < tex.h)
		ft_memcpy((void *)&tmp, (void *)((imag + y * tex.w *
						(bpp / 8) + x * (bpp / 8))), 4);
	return (tmp);
}
