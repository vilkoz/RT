/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 19:05:49 by vrybalko          #+#    #+#             */
/*   Updated: 2017/04/20 21:36:15 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_v3d	get_norm_plane(void *dat, t_p3d inter_p)
{
	(void)inter_p;
	return (((t_plane *)dat)->norm);
}

int		ft_img_px_get(void *img, int x, int y)
{
	int				bpp;
	int				sl;
	int				en;
	char			*imag;
	int				tmp;

	imag = mlx_get_data_addr(img, &bpp, &sl, &en);
	tmp = 0;
	if (x >= 0 && x < 64 && y >= 0 && y < 64)
		ft_memcpy((void *)&tmp, (void *)((imag + y * 64 *
						(bpp / 8) + x * (bpp / 8))), 4);
	return (tmp);
}

int		get_plane_color(void *data, t_p3d inter_p)
{
	t_v3d	nx;
	t_v3d	ny;
	t_v3d	a;
	t_v3d	p;
	t_v3d	perp;
	t_p3d	point;
	double	dx;
	double	dy;
	t_plane	*pl;

	pl = (t_plane *)data;
	nx = normalize(cross_product(pl->norm, normalize(new_v3d(0, 0, 1))));
	ny = normalize(cross_product(nx, pl->norm));
	a = new_v3d_p(pl->p, new_p3d(0, 0, 0));
	p = new_v3d_p(inter_p, new_p3d(0, 0, 0));
	perp = v_sub(v_sub(a, p), v_mul(nx, dot_product(v_sub(a, p), nx)));
	point = new_p3d(pl->p.x + inter_p.x, pl->p.y + inter_p.y,
		pl->p.z + inter_p.z);
	dy = v_len(perp);
	dx = v_len(new_v3d_p(point, pl->p));
	return (ft_img_px_get(pl->tex, ((int)(dx) % 64), ((int)(dy) % 64)));
}

int		intersect_plane(const void *data, const t_p3d ray_start,
						const t_v3d ray, t_p3d *inter_p)
{
	t_plane		*pl;
	t_v3d		w;
	double		dot;

	pl = (t_plane *)data;
	if (fabs(dot = dot_product(pl->norm, ray)) < EPSILON)
		return (FALSE);
	w = new_v3d(ray_start.x - pl->p.x, ray_start.y - pl->p.y,
		ray_start.z - pl->p.z);
	if ((dot = -dot_product(pl->norm, w) / dot) < 0)
		return (FALSE);
	*inter_p = new_p3d(ray_start.x + ray.x * dot, ray_start.y + ray.y * dot,
		ray_start.z + ray.z * dot);
	if (dot_product(new_v3d(inter_p->x - ray_start.x, inter_p->y - ray_start.y,
		inter_p->z - ray_start.z), ray) < 0)
		return (FALSE);
	return (TRUE);
}

t_o3d	*new_plane(t_p3d p, t_v3d norm, int color)
{
	t_plane		*sp;
	t_o3d		*obj;

	sp = (t_plane *)malloc(sizeof(t_plane));
	sp->p = p;
	sp->norm = norm;
	sp->color = color;
	obj = (t_o3d *)malloc(sizeof(t_o3d));
	int 		i;
	sp->tex = mlx_xpm_file_to_image(mlx_init(), "tex/wood.xpm", &i, &i);
	if (sp->tex == NULL)
	{
		perror("tex/wood.xpm");
		exit (1);
	}
	obj->data = (void *)sp;
	obj->get_color = get_plane_color;
	obj->intersect = intersect_plane;
	obj->get_norm = get_norm_plane;
	return (obj);
}
