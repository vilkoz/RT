/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 17:25:07 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/17 17:41:56 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init_keys(t_k *k)
{
	ft_bzero((void*)k, sizeof(t_k));
}

t_e			*ft_mlx_init(t_scene *s)
{
	t_e		*e;

	e = (t_e *)malloc(sizeof(t_e));
	printf("%p\n", e);
	if ((e->mlx = mlx_init()) == NULL)
		return (NULL);
	e->h = 700;
	e->w = 1300;
	e->win = mlx_new_window(e->mlx, e->w, e->h, "rtv1");
	e->img = mlx_new_image(e->mlx, e->w, e->h);
	e->v_x = 0;
	e->v_y = 0;
	e->fast_mode = 1;
	e->s = s;
	e->s_o = NULL;
	init_keys(&e->k);
	return (e);
}
