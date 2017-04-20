/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 17:25:07 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/24 00:26:49 by tor              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init_keys(t_k *k)
{
	k->gopa = 23;
	k->rot_x = 0;
	k->rot_y = 0;
	k->rot_z = 0;
	k->bias = 0;
}

t_e			*ft_mlx_init(t_scene *s)
{
	t_e		*e;

	e = (t_e *)malloc(sizeof(t_e));
	if ((e->mlx = mlx_init()) == NULL)
		return (NULL);
	e->h = 700;
	e->w = 1300;
	e->win = mlx_new_window(e->mlx, e->w, e->h, "rtv1");
	e->img = mlx_new_image(e->mlx, e->w, e->h);
	e->ang_x = -2;
	e->ang_y = -130;
	e->ang_z = -13;
	e->bias = 0.01;
	e->v_x = 0;
	e->v_y = 0;
	e->changed = 1;
	e->s = s;
	init_keys(&e->k);
	return (e);
}
