/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:45:28 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/24 19:45:51 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		rotate_plane(const t_o3d *obj, double angle, t_v3d axis)
{
	t_plane		*pl;

	pl = (t_plane *)obj->data;
	pl->norm = rotate_v_q(pl->norm, axis, angle);
}
