/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 19:18:37 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/01 20:19:29 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_H
# define QUATERNION_H

typedef struct	s_quat
{
	double		x;
	double		y;
	double		z;
	double		w;
}				t_quat;

t_quat			new_quat(t_v3d	v, double ang);
t_quat			q_mul(t_quat q, double k);
double			q_len(t_quat q);
t_quat			q_norm(t_quat q);
t_quat			q_inv(t_quat q);
t_quat			q_mul_q(t_quat q1, t_quat q2);
t_quat			q_mul_v(t_quat q, t_v3d v);
t_v3d			q_transform_v(t_quat q, t_v3d v);
t_v3d			rotate_v_q(t_v3d v, t_v3d axis, double ang);
void			rotate_cam_q(t_cam *cam, double a_x, double a_y, double a_z);

#endif
