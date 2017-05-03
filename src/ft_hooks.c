/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 17:13:21 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/03 01:31:13 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		is_key_pressed(t_e *e)
{
	int		*k_i;
	int		i;
	int		res;
	size_t	size;

	k_i = (int*)&e->k;
	size = sizeof(t_k) / sizeof(int);
	res = 0;
	i = -1;
	while ((size_t)++i < size)
		res |= k_i[i];
	return ((res) ? TRUE : FALSE);
}

int		key_press(int key, t_e *e)
{
	if (key == K_ESC)
		exit(0);
	(key == K_RA) ? e->k.rot_x = -1 : 23;
	(key == K_LA) ? e->k.rot_x = 1 : 23;
	(key == K_DA) ? e->k.rot_y = -1 : 23;
	(key == K_UA) ? e->k.rot_y = 1 : 23;
	(key == K_PUP) ? e->k.rot_z = -1 : 23;
	(key == K_PDN) ? e->k.rot_z = 1 : 23;
	(key == K_W) ? e->k.move_y = 1 : 23;
	(key == K_S) ? e->k.move_y = -1 : 23;
	(key == K_D) ? e->k.move_x = 1 : 23;
	(key == K_A) ? e->k.move_x = -1 : 23;
	(key == K_ENT) ? e->fast_mode = (e->fast_mode + 1) % 2 : 23;
	if (is_key_pressed(e) || !e->fast_mode)
		mlx_loop_hook(e->mlx, loop_hook, e);
	return (0);
}

int		key_release(int key, t_e *e)
{
	if (key == K_ESC)
		exit(0);
	(key == K_LA || key == K_RA) ? e->k.rot_x = 0 : 23;
	(key == K_DA || key == K_UA) ? e->k.rot_y = 0 : 23;
	(key == K_W || key == K_S) ? e->k.move_y = 0 : 23;
	(key == K_A || key == K_D) ? e->k.move_x = 0 : 23;
	(key == K_PDN || key == K_PUP) ? e->k.rot_z = 0 : 23;
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
	if (e->k.move_x)
		e->s->cam.pos = v_to_p(v_add(p_to_v(e->s->cam.pos), v_mul(
		(e->k.move_x == 1) ? e->s->cam.dir_r : v_inv(e->s->cam.dir_r), 10.)));
	if (e->k.move_y)
		e->s->cam.pos = v_to_p(v_add(p_to_v(e->s->cam.pos), v_mul(
		(e->k.move_y == 1) ? e->s->cam.dir : v_inv(e->s->cam.dir), 10.)));
	render(e);
	mlx_clear_window(e->mlx, e->win);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	if (e->fast_mode == 0 || !is_key_pressed(e))
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
