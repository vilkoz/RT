/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 17:13:21 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/02 21:22:35 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		key_press(int key, t_e *e)
{
	if (key == K_ESC)
		exit(0);
	(key == K_RA) ? e->k.rot_x = -1 : 23;
	(key == K_LA) ? e->k.rot_x = 1 : 23;
	(key == K_DA) ? e->k.rot_y = -1 : 23;
	(key == K_UA) ? e->k.rot_y = 1 : 23;
	(key == 116) ? e->k.rot_z = -1 : 23;
	(key == 121) ? e->k.rot_z = 1 : 23;
	(key == K_W) ? e->k.move.y = 1 : 23;
	(key == K_S) ? e->k.move.y = -1 : 23;
	(key == K_D) ? e->k.move.x = 1 : 23;
	(key == K_A) ? e->k.move.x = -1 : 23;
	(key == K_ENT) ? e->fast_mode = (e->fast_mode + 1) % 2 : 23;
	mlx_loop_hook(e->mlx, loop_hook, e);
	return (0);
}

int		key_release(int key, t_e *e)
{
	if (key == K_ESC)
		exit(0);
	(key == K_LA || key == K_RA) ? e->k.rot_x = 0 : 23;
	(key == K_DA || key == K_UA) ? e->k.rot_y = 0 : 23;
	(key == K_W || key == K_S) ? e->k.move.y = 0 : 23;
	(key == K_A || key == K_D) ? e->k.move.x = 0 : 23;
	(key == 116 || key == 121) ? e->k.rot_z = 0 : 23;
	(key == 24 || key == 27) ? e->k.bias = 0 : 23;
	return (0);
}

int		loop_hook(t_e *e)
{
	if (e->k.rot_x == 1)
		rotate_cam_x(&e->s->cam, (-1. * RAD));
	if (e->k.rot_x == -1)
		rotate_cam_x(&e->s->cam, (1. * RAD));
	if (e->k.rot_y == 1)
		rotate_cam_z(&e->s->cam, (1. * RAD));
	if (e->k.rot_y == -1)
		rotate_cam_z(&e->s->cam, (-1. * RAD));
	(e->k.rot_z == 1) ? rotate_cam_y(&e->s->cam, (1. * RAD)) : 23;
	(e->k.rot_z == -1) ? rotate_cam_y(&e->s->cam, (-1. * RAD)) : 23;
	(e->k.bias == -1) ? e->bias -= 0.1 : 23;
	(e->k.bias == 1) ? e->bias += 0.1 : 23;
	if (e->k.move.x)
		e->s->cam.pos = v_to_p(v_add(p_to_v(e->s->cam.pos), v_mul(
		(e->k.move.x == 1) ? e->s->cam.dir_r : v_inv(e->s->cam.dir_r), 10.)));
	if (e->k.move.y)
		e->s->cam.pos = v_to_p(v_add(p_to_v(e->s->cam.pos), v_mul(
		(e->k.move.y == 1) ? e->s->cam.dir : v_inv(e->s->cam.dir), 10.)));
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
