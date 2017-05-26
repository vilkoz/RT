/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 20:01:30 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/26 12:45:13 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _STRUCTS_H
# define _STRUCTS_H

typedef struct		s_p2d
{
	double			x;
	double			y;
}					t_p2d;

/*
** struct for key events
*/

typedef struct		s_k
{
	int				gopa;
	int				rot_x;
	int				rot_y;
	int				rot_z;
	int				rot_so_x;
	int				rot_so_y;
	int				rot_so_z;
	int				bias;
	int				move_x;
	int				move_y;
	int				m_key;
}					t_k;

typedef struct		s_p3d
{
	double			x;
	double			y;
	double			z;
}					t_p3d;

typedef struct		s_v3d
{
	double			x;
	double			y;
	double			z;
}					t_v3d;

typedef struct		s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct		s_mat
{
	double			m[4][4];
}					t_mat;

typedef struct		s_vec
{
	t_v3d			dir;
	t_p3d			p;
}					t_vec;

typedef struct		s_tex
{
	void			*img;
	int				w;
	int				h;
}					t_tex;

typedef struct		s_material
{
	int				color;
	t_tex			tex;
	float			refl;
	float			bamp;
}					t_material;

typedef struct		s_cam
{
	t_p3d			pos;
	t_v3d			dir;
	t_v3d			dir_d;
	t_v3d			dir_r;
	t_p3d			sin;
	t_p3d			cos;
}					t_cam;

/*
** Object3D
*/

typedef struct		s_o3d
{
	void			*data;
	int				(*intersect)(const struct s_o3d *data,
						const t_p3d ray_start,
						const t_v3d ray,
						t_p3d *inter_p);
	int				(*get_color)(struct s_o3d *data, t_p3d inter_p);
	t_v3d			(*get_norm)(struct s_o3d *data, t_p3d inter_p);
	void			(*rotate)(const struct s_o3d *data, double angle,
						t_v3d axis);
	void			(*move)(const struct s_o3d *obj, t_p2d move,
						t_cam *cam);
	t_tex			tex;
	t_material		material;
}					t_o3d;

typedef struct		s_lin
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				d;
	int				d1;
	int				d2;
	int				error;
	int				error2;
	t_p2d			*p1;
	t_p2d			*p2;
}					t_lin;

typedef struct		s_lst
{
	int				y;
	char			*line;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_scene
{
	t_o3d			**objects;
	int				obj_num;
	t_p3d			**ls;
	int				ls_num;
	t_cam			cam;
	double			bias;
	int				cur_o;
	int				cur_ls;
}					t_scene;

typedef struct		s_e
{
	void			*mlx;
	void			*win;
	void			*img;
	int				h;
	int				w;
	int				v_x;
	int				v_y;
	int				fast_mode;
	t_k				k;
	t_scene			*s;
	t_o3d			*s_o;
}					t_e;

typedef struct		s_thread
{
	pthread_t		id;
	t_e				*e;
	t_p2d			y_area;
	int				i;
}					t_thread;

/*
** OBJECTS:
** sphere
*/

typedef struct		s_sphere
{
	t_p3d			center;
	double			radius;
	int				color;
	t_tex			tex;
}					t_sphere;

/*
** plane
*/

typedef struct		s_plane
{
	t_p3d			p;
	t_v3d			norm;
	int				color;
	t_tex			tex;
}					t_plane;

/*
** cylinder
*/

typedef struct		s_cyl
{
	t_p3d			center;
	t_v3d			dir;
	double			radius;
	double			h;
	int				color;
	struct s_disk	*top;
	struct s_disk	*bot;
}					t_cyl;

/*
** cone
*/

typedef struct		s_cone
{
	t_p3d			center;
	t_v3d			dir;
	double			h;
	int				color;
	double			a;
	double			sin_a;
	double			cos_a;
	struct s_disk	*top;
}					t_cone;

/*
** disk
*/

typedef struct		s_disk
{
	t_p3d			p;
	t_v3d			norm;
	double			radius;
	int				color;
	t_cone			*cone;
	t_cyl			*cyl;
}					t_disk;

#endif
