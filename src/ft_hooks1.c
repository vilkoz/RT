/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 17:44:30 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/24 17:46:53 by vrybalko         ###   ########.fr       */
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

void	key_press_start(int key, t_e *e)
{
	(key == K_RA) ? e->k.rot_x = -1 : 23;
	(key == K_LA) ? e->k.rot_x = 1 : 23;
	(key == K_DA) ? e->k.rot_y = -1 : 23;
	(key == K_UA) ? e->k.rot_y = 1 : 23;
	(key == K_PUP) ? e->k.rot_z = -1 : 23;
	(key == K_PDN) ? e->k.rot_z = 1 : 23;
	(key == K_J) ? e->k.rot_so_x = -1 : 23;
	(key == K_L) ? e->k.rot_so_x = 1 : 23;
	(key == K_K) ? e->k.rot_so_y = -1 : 23;
	(key == K_I) ? e->k.rot_so_y = 1 : 23;
	(key == K_U) ? e->k.rot_so_z = -1 : 23;
	(key == K_O) ? e->k.rot_so_z = 1 : 23;
	(key == K_W) ? e->k.move_y = 1 : 23;
	(key == K_S) ? e->k.move_y = -1 : 23;
	(key == K_D) ? e->k.move_x = 1 : 23;
	(key == K_A) ? e->k.move_x = -1 : 23;
}

int		key_press(int key, t_e *e)
{
	if (key == K_ESC)
		exit(0);
	key_press_start(key, e);
	if (key == K_ENT)
	{
		e->fast_mode = (e->fast_mode + 1) % 2;
		if (is_key_pressed(e) || !e->fast_mode)
			mlx_loop_hook(e->mlx, loop_hook, e);
		return (0);
	}
	if (is_key_pressed(e) || !e->fast_mode)
	{
		e->fast_mode = 1;
		mlx_loop_hook(e->mlx, loop_hook, e);
	}
	return (0);
}

void	loop_hook_start(t_e *e)
{
	if (e->k.rot_x == 1)
		rotate_cam_x(&e->s->cam, (-10. * RAD));
	if (e->k.rot_x == -1)
		rotate_cam_x(&e->s->cam, (10. * RAD));
	if (e->k.rot_y == 1)
		rotate_cam_z(&e->s->cam, (10. * RAD));
	if (e->k.rot_y == -1)
		rotate_cam_z(&e->s->cam, (-10. * RAD));
	(e->k.rot_z == 1) ? rotate_cam_y(&e->s->cam, (10. * RAD)) : 23;
	(e->k.rot_z == -1) ? rotate_cam_y(&e->s->cam, (-10. * RAD)) : 23;
	if (e->k.move_x)
		e->s->cam.pos = v_to_p(v_add(p_to_v(e->s->cam.pos), v_mul(
		(e->k.move_x == 1) ? e->s->cam.dir_r : v_inv(e->s->cam.dir_r), 10.)));
	if (e->k.move_y)
		e->s->cam.pos = v_to_p(v_add(p_to_v(e->s->cam.pos), v_mul(
		(e->k.move_y == 1) ? e->s->cam.dir : v_inv(e->s->cam.dir), 10.)));
	if (e->k.rot_so_x == 1 && e->s_o)
		e->s_o->rotate(e->s_o, 10 * RAD, new_v3d(1, 0, 0));
	if (e->k.rot_so_x == -1 && e->s_o)
		e->s_o->rotate(e->s_o, -10 * RAD, new_v3d(1, 0, 0));
	if (e->k.rot_so_y == 1 && e->s_o)
		e->s_o->rotate(e->s_o, 10 * RAD, new_v3d(0, 1, 0));
	if (e->k.rot_so_y == -1 && e->s_o)
		e->s_o->rotate(e->s_o, -10 * RAD, new_v3d(0, 1, 0));
}

int		loop_hook(t_e *e)
{
	loop_hook_start(e);
	if (e->k.rot_so_z == 1 && e->s_o)
		e->s_o->rotate(e->s_o, 10 * RAD, new_v3d(0, 0, 1));
	if (e->k.rot_so_z == -1 && e->s_o)
		e->s_o->rotate(e->s_o, -10 * RAD, new_v3d(0, 0, 1));
	render(e);
	mlx_clear_window(e->mlx, e->win);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	if (e->fast_mode == 0 || !is_key_pressed(e))
		mlx_loop_hook(e->mlx, NULL, e);
	return (0);
}
