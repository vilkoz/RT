/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 17:13:21 by vrybalko          #+#    #+#             */
/*   Updated: 2017/04/24 19:48:26 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		key_press(int key, t_e *e)
{
	if (key == 53)
		exit(0);
	(key == 123) ? e->k.rot_x = -1 : 23;
	(key == 124) ? e->k.rot_x = 1 : 23;
	(key == 125) ? e->k.rot_y = -1 : 23;
	(key == 126) ? e->k.rot_y = 1 : 23;
	(key == 116) ? e->k.rot_z = -1 : 23;
	(key == 121) ? e->k.rot_z = 1 : 23;
	(key == 24) ? e->k.bias = 1 : 23;
	(key == 27) ? e->k.bias = -1 : 23;
//	e->changed = 1;
	return (0);
}

int		key_release(int key, t_e *e)
{
	if (key == 53)
		exit(0);
	(key == 123 || key == 124) ? e->k.rot_x = 0 : 23;
	(key == 125 || key == 126) ? e->k.rot_y = 0 : 23;
	(key == 116 || key == 121) ? e->k.rot_z = 0 : 23;
	(key == 24 || key == 27) ? e->k.bias = 0 : 23;
	return (0);
}

int		loop_hook(t_e *e)
{
	if (e->changed == 0)
		return (0);
	(e->k.rot_x == 1) ? e->ang_x += 1 : 23;
	(e->k.rot_x == -1) ? e->ang_x -= 1 : 23;
	(e->k.rot_y == 1) ? e->ang_y += 1 : 23;
	(e->k.rot_y == -1) ? e->ang_y -= 1 : 23;
	(e->k.rot_z == 1) ? e->ang_z += 1 : 23;
	(e->k.rot_z == -1) ? e->ang_z -= 1 : 23;
	(e->k.bias == -1) ? e->bias -= 0.1 : 23;
	(e->k.bias == 1) ? e->bias += 0.1 : 23;
	render(e);
	mlx_clear_window(e->mlx, e->win);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_loop_hook(e->mlx, NULL, e);
	return (0);
}

int		mouse_hook(int key, int x, int y, t_e *e)
{
	e->v_y = y;
	e->v_x = x;
	(void)key;
	return (0);
}

int		move_hook(int x, int y, t_e *e)
{
	(void)y;
	(void)x;
	(void)e;
	return (0);
}
