/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 23:57:04 by vrybalko          #+#    #+#             */
/*   Updated: 2017/04/23 01:01:06 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			get_reflect_color(t_scene *s, t_o3d *obj, t_p3d inter_p, t_v3d fall)
{
	// static int	rec_count = 3;
	t_v3d		norm;
	t_v3d		ref_ray;
	t_p3d		inter_p2;
	t_o3d		*obj2;

	// if (--rec_count > 0)
	// {
		norm = obj->get_norm(obj->data, inter_p);
		inter_p = new_p3d(inter_p.x + norm.x * 0.01, inter_p.y + norm.y * 0.01,
			inter_p.z + norm.z * 0.01);
		ref_ray = normalize(v_sub(fall,
			v_mul(norm, 2 * dot_product(fall, norm))));
		if (find_nearest(s, new_vec(ref_ray, inter_p), &inter_p2, &obj2))
			return (get_light_color(s, obj2, inter_p2));
		else
			return (0);
	// }
	// return (0);
}

int			get_light_color(t_scene *s, t_o3d *obj, t_p3d inter_p)
{
	double		cosv;
	int			light_c;
	int			ret_c;
	t_v3d		norm;
	int			i;

	norm = obj->get_norm(obj->data, inter_p);
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

int			get_color(t_scene *s, t_o3d *obj, t_p3d inter_p, t_v3d fall)
{
	int		res;

	res = 0;
	res = get_light_color(s, obj, inter_p);
	if ((obj->material.refl) > EPSILON)
	{
		res = shade_colors(res, obj->material.refl);
		res = mix_colors(res, get_reflect_color(s, obj, inter_p, fall));
	}
	return (res);
}
