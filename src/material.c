/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 23:18:26 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/03 20:14:09 by kshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_material	new_material(int color, t_tex tex, float refl)
{
	t_material	new;

	new.color = color;
	new.tex = tex;
	new.refl = refl;
	new.bamp = 1122;
	return (new);
}
