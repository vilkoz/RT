/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 18:50:51 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/17 18:26:30 by kshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_tex	new_raw_tex(void *img, int w, int h)
{
	t_tex	t;

	t.img = img;
	t.w = w;
	t.h = h;
	return (t);
}

t_tex	new_tex(char *path)
{
	t_tex	t;

	if (!ft_strcmp(path, "NULL"))
	{
		t.img = NULL;
		return (t);
	}
	if ((t.img = mlx_xpm_file_to_image(mlx_init(), path, &(t.w), &(t.h)))
		== NULL)
		perror(path);
	return (t);
}

int		get_tex_color_bnw_cylinder(t_o3d *dat, double x, double y)
{
	int	color;

	color = gray_scale(ft_img_px_get(dat->material.tex,
		(int)(x * (double)dat->material.tex.w) % dat->material.tex.w,
		(int)y % dat->material.tex.h));
	return (color);
}

int		get_tex_color_bnw_sphere(t_o3d *dat, double x, double y)
{
	int	color;

	color = gray_scale(ft_img_px_get(dat->tex, (int)(x) % dat->tex.w,
		(int)(y) % dat->tex.h));
	return (color);
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
