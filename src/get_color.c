/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 23:57:04 by vrybalko          #+#    #+#             */
/*   Updated: 2017/04/26 18:39:53 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			get_reflect_color(t_scene *s, t_o3d *obj, t_vec v, int rn)
{
	t_v3d		norm;
	t_p3d		inter_p2;
	t_o3d		*obj2;

	if (rn > 0)
	{
		norm = obj->get_norm(obj, v.p);
		v.p = new_p3d(v.p.x + norm.x * 0.01, v.p.y + norm.y * 0.01,
			v.p.z + norm.z * 0.01);
		if (find_nearest(s, new_vec(normalize(v_sub(v.dir, v_mul(norm,
			2 * dot_product(v.dir, norm)))), v.p), &inter_p2, &obj2))
			return (get_color(s, obj2, new_vec(new_v3d_p(inter_p2, v.p),
				inter_p2), rn - 1));
		else
			return (0);
	}
	return (0);
}

int			get_light_color(t_scene *s, t_o3d *obj, t_p3d inter_p)
{
	double		cosv;
	int			light_c;
	int			ret_c;
	t_v3d		norm;
	int			i;

	norm = obj->get_norm(obj, inter_p);
	i = -1;
	while (++i < s->ls_num)
	{
		if (is_viewable(inter_p, *s->ls[i], s, obj))
		{
			light_c = add_colors(obj->get_color(obj, inter_p),
				mul_colors(0xffffff, 0.4));
			cosv = (dot_product(normalize(norm), normalize(new_v3d_p(*s->ls[i],
				inter_p))) - 0.95) * 20;
			if ((cosv) < 0.1)
				light_c = shade_colors(light_c, (1 - cosv) / 21);
			else
				light_c = add_colors(light_c, mul_colors(light_c, cosv));
		}
		else
			light_c = shade_colors(obj->get_color(obj, inter_p), 0.975);
		ret_c = (i == 0) ? light_c : mix_colors(ret_c, light_c);
	}
	return (ret_c);
}

int			get_color(t_scene *s, t_o3d *obj, t_vec v, int rn)
{
	int		res;

	res = 0;
	res = get_light_color(s, obj, v.p);
	if ((obj->material.refl) > EPSILON)
	{
		res = shade_colors(res, obj->material.refl);
		res = mix_colors(res, get_reflect_color(s, obj, v, rn));
	}
	return (res);
}
