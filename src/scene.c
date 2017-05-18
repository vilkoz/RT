/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 16:27:17 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/18 16:50:35 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_cam		new_cam(t_p3d pos, t_v3d dir)
{
	t_cam		cam;

	cam.pos = pos;
	cam.dir = normalize(dir);
	cam.dir_d = normalize((cross_product(cam.dir,
		normalize(new_v3d(0, 0, 1)))));
	cam.dir_r = normalize((cross_product(cam.dir_d, dir)));
	cam.cos.x = cos(cam.dir.x);
	cam.cos.y = cos(cam.dir.y);
	cam.cos.z = cos(cam.dir.z);
	cam.sin.x = sin(cam.dir.x);
	cam.sin.y = sin(cam.dir.y);
	cam.sin.z = sin(cam.dir.z);
	return (cam);
}

t_v3d		pix_vector_cam(t_p2d p, t_cam *s)
{
	t_v3d		dir;

	dir = new_v3d(s->pos.x + 1. * s->dir.x,
		s->pos.y + 1. * s->dir.y,
		s->pos.z + 1. * s->dir.z);
	dir = new_v3d(dir.x + p.x * s->dir_r.x,
		dir.y + p.x * s->dir_r.y,
		dir.z + p.x * s->dir_r.z);
	dir = new_v3d(dir.x + p.y * s->dir_d.x,
		dir.y + p.y * s->dir_d.y,
		dir.z + p.y * s->dir_d.z);
	dir = new_v3d(dir.x - s->pos.x, dir.y - s->pos.y,
		dir.z - s->pos.z);
	return (normalize(dir));
}

t_v3d		pix_vector(t_p2d p, t_scene *s)
{
	t_v3d		dir;

	dir = new_v3d(s->cam.pos.x + 1. * s->cam.dir.x,
		s->cam.pos.y + 1. * s->cam.dir.y,
		s->cam.pos.z + 1. * s->cam.dir.z);
	dir = new_v3d(dir.x + p.x * s->cam.dir_r.x,
		dir.y + p.x * s->cam.dir_r.y,
		dir.z + p.x * s->cam.dir_r.z);
	dir = new_v3d(dir.x + p.y * s->cam.dir_d.x,
		dir.y + p.y * s->cam.dir_d.y,
		dir.z + p.y * s->cam.dir_d.z);
	dir = new_v3d(dir.x - s->cam.pos.x, dir.y - s->cam.pos.y,
		dir.z - s->cam.pos.z);
	return (normalize(dir));
}

// void		rotate_cam_x(t_cam *cam, double ang)
// {
// 	// t_v3d		new_x;
// 	// t_v3d		new_y;
// 	// t_v3d		new_z;
// 	// t_mat		res;
// 	// t_mat		inv;
// 	//
// 	// new_x = cam->dir;
// 	// new_z = cross_product(new_x, normalize(new_v3d(1, 1, 1)));
// 	// new_y = cross_product(new_z, new_x);
// 	// res = new_mat(new_x, new_y, new_z);
// 	// inv = mat_inverse(res);
// 	// res = mat_mul(mat_mul(inv, new_mat_ang_x(ang)),
// 	// 	new_mat(new_x, new_y, new_z));
// 	// inv = new_mat1(new_v3d(cam->dir.x, cam->dir.y, cam->dir.z));
// 	// res = mat_mul(res, inv);
// 	// cam->dir.x = res.m[0][0];
// 	// cam->dir.y = res.m[1][0];
// 	// cam->dir.z = res.m[2][0];
// 	cam->dir = rotate_v_x(cam->dir, sin(ang), cos(ang));
// 	cam->dir_d = rotate_v_x(cam->dir_d, sin(ang), cos(ang));
// 	cam->dir_r = rotate_v_x(cam->dir_r, sin(ang), cos(ang));
// }

t_scene		*new_scene(int obj_num, t_o3d **obj, t_p3d ls, t_cam cam)
{
	t_scene		*new;

	(void)ls;
	new = (t_scene *)malloc(sizeof(t_scene));
	new->obj_num = obj_num;
	new->objects = obj;
	new->ls = NULL;
	new->ls_num = 0;
	new->cam = cam;
	new->cur_o = 0;
	new->cur_ls = 0;
	return (new);
}
