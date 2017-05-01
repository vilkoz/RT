/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 18:19:24 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/02 01:01:35 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		rotate_cam_x(t_cam *cam, double ang)
{
	cam->dir = rotate_v_q(cam->dir, cam->dir_d, ang);
	cam->dir_r = rotate_v_q(cam->dir_r, cam->dir_d, ang);
	cam->dir_d = rotate_v_q(cam->dir_d, cam->dir_d, ang);
}

void		rotate_cam_y(t_cam *cam, double ang)
{
	cam->dir = rotate_v_q(cam->dir, cam->dir, ang);
	cam->dir_d = rotate_v_q(cam->dir_d, cam->dir, ang);
	cam->dir_r = rotate_v_q(cam->dir_r, cam->dir, ang);
}

void		rotate_cam_z(t_cam *cam, double ang)
{
	cam->dir = rotate_v_q(cam->dir, cam->dir_r, ang);
	cam->dir_d = rotate_v_q(cam->dir_d, cam->dir_r, ang);
	cam->dir_r = rotate_v_q(cam->dir_r, cam->dir_r, ang);
}
