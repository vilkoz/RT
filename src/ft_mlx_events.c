/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 15:26:45 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/17 21:25:07 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		expose_hook(t_e *e)
{
	mlx_clear_window(e->mlx, e->win);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}

int		exit_hook(t_e *e)
{
	exit(0);
	(void)e;
	return (0);
}

int		move_button_rel(int key, int x, int y, t_e *e)
{
	(void)x;
	(void)y;
	(void)e;
	(void)key;
	if (e->k.m_key == 1)
	{
		printf("release %d %d %d\n", key, x, y);
		// if (e->s_o)
		// {
		// 	e->s_o->move(e->s_o, new_p2d((double)(x - e->v_x),
		// 		(double)(y - e->v_y)), &e->s->cam);
		// 	printf("moving %d %d %d\n", x - e->v_x, y - e->v_y, e->k.m_key);
		// 	mlx_loop_hook(e->mlx, loop_hook, e);
		// }
		e->k.m_key = 0;
	}
	return (0);
}

void	ft_mlx_events(t_e *e)
{
	mlx_hook(e->win, 2, 1, key_press, e);
	mlx_hook(e->win, 3, 2, key_release, e);
	mlx_mouse_hook(e->win, mouse_hook, e);
	mlx_hook(e->win, 6, 65, move_hook, e);
	mlx_hook(e->win, 5, 65, move_button_rel, e);
	mlx_hook(e->win, 17, 1L << 17, exit_hook, e);
	mlx_expose_hook(e->win, expose_hook, e);
}
