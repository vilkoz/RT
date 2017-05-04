/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 16:11:37 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/04 21:17:56 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RTV1_H
# define _RTV1_H
# define EPSILON 0.00000001
# define RAD (0.0175433)
# define SIGN(x) ((x < 0) ? -1 : 1)
# define FALSE 0
# define TRUE 1
# define SWAP(a, b) do{(a) ^= (b); (b) ^= (a); (a) ^= (b);} while(0);
# define SWAP_D(a, b) do{double tmp = (a); (a) = (b); (b) = (tmp);} while(0);
# define COSA (sp->cos_a)
# define SINA (sp->sin_a)
# define COSA2 (sp->cos_a) * (sp->cos_a)
# define SINA2 (sp->sin_a) * (sp->sin_a)
# define ASP ((double)((double)e->w / (double)e->h))
# define SAMPLES 2
# define THREADS 1

# include "../libft/libft.h"
# include "mlx.h"
# include "keys.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <time.h>
# include <pthread.h>

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
	int				bias;
	int				move_x;
	int				move_y;
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
}					t_material;

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

typedef struct		s_cam
{
	t_p3d			pos;
	t_v3d			dir;
	t_v3d			dir_d;
	t_v3d			dir_r;
	t_p3d			sin;
	t_p3d			cos;
}					t_cam;

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
}					t_disk;

# include "quaternion.h"

t_e					*ft_mlx_init(t_scene *s);
void				ft_img_px_put(t_e *e, int x, int y, int rgb);
void				ft_mlx_events(t_e *e);
int					loop_hook(t_e *e);
int					key_press(int key, t_e *e);
int					key_release(int key, t_e *e);
int					mouse_hook(int key, int x, int y, t_e *e);
int					move_hook(int x, int y, t_e *e);

/*
** render.c
*/

void				render(t_e *e);
int					find_nearest(t_scene *s, t_vec vec, t_p3d *inter_p,
						t_o3d **obj1);
int					is_viewable(t_p3d p1, t_p3d p2, t_scene *s, t_o3d *obj1);

/*
** ray_tools.c
*/

t_p2d				plane_coords(t_vec v, t_p3d p);
int					same_dir(t_v3d v1, t_v3d v2);
t_v3d				v_inv(t_v3d v);
double				v_sqr(t_v3d v);
t_v3d				v_add(t_v3d v1, t_v3d v2);
double				v_len(t_v3d v);
t_v3d				v_sub(t_v3d v1, t_v3d v2);
double				distance(t_p3d p1, t_p3d p2);
t_v3d				new_v3d(double x, double y, double z);
t_v3d				new_v3d_p(t_p3d p1, t_p3d p2);
t_p3d				new_p3d(double x, double y, double z);
t_p2d				new_p2d(double x, double y);
t_vec				new_vec(t_v3d v, t_p3d p);
double				dot_product(t_v3d v1, t_v3d v2);
t_v3d				rotate_v_x(t_v3d v, double sin_al, double cos_al);
t_v3d				rotate_v_y(t_v3d v, double sin_al, double cos_al);
t_v3d				rotate_v_z(t_v3d v, double sin_al, double cos_al);
t_v3d				normalize(t_v3d v);
t_v3d				cross_product(t_v3d a, t_v3d b);
t_v3d				v_mul(t_v3d v, double n);
t_p3d				rot_p(t_p3d p, t_v3d ang, t_p3d center);
t_p3d				v_to_p(t_v3d v);
t_v3d				p_to_v(t_p3d v);

/*
** scene.c
*/

t_scene				*new_scene(int obj_num, t_o3d **obj, t_p3d ls, t_cam cam);
t_cam				new_cam(t_p3d pos, t_v3d dir);
double				cos_vectors(t_v3d v1, t_v3d v2);
t_v3d				pix_vector(t_p2d p, t_scene *s);

/*
** color.c
*/

int					new_color(t_rgb res);
t_rgb				int_to_rgb(int c);
int					add_colors(int cl1, int cl2);
t_rgb				add_rgb_col(t_rgb c1, t_rgb c2);
t_rgb				mul_rgb_col(t_rgb c, double k);
int					mul_colors(int cl1, double k);
int					shade_colors(int cl1, double k);
int					mix_colors(int cl1, int cl2);
int					gray_scale(int color);

/*
** objects
*/

int					solve_quad(t_p3d p, double *t0, double *t1);
t_o3d				*new_sphere(t_p3d center, double radius,
						t_material material);
t_o3d				*new_plane(t_p3d p, t_v3d norm, t_material material);
int					intersect_plane(const t_o3d *data, const t_p3d ray_start,
						const t_v3d ray, t_p3d *inter_p);
t_o3d				*new_cyl(t_vec v, double radius, double h,
						t_material material);
t_o3d				*new_cone(t_vec v, double h, double alpha,
						t_material material);
t_o3d				*new_disk(t_vec v, double radius, int color,
						t_material material);

/*
** matrix.c
*/

t_mat				mat_inverse(t_mat a);
t_mat				mat_mul(t_mat a, t_mat b);
t_mat				new_mat(t_v3d x, t_v3d y, t_v3d z);
t_mat				new_mat_ang_x(double ang);
t_mat				new_mat1(t_v3d x);

/*
** read_file.c
*/

t_scene				*read_file(char *name);

/*
** textures.c
*/

t_tex				new_tex(char *path);
int					ft_img_px_get(t_tex tex, int x, int y);
t_tex				new_raw_tex(void *img, int w, int h);

/*
** get_color.c
*/

int					get_reflect_color(t_scene *s, t_o3d *obj, t_vec v, int rn);
int					get_light_color(t_scene *s, t_o3d *obj, t_p3d inter_p);
int					get_color(t_scene *s, t_o3d *obj, t_vec v, int rn);

/*
** material.c
*/

t_material			new_material(int color, t_tex tex, float refl);

/*
** camera.c
*/

void				rotate_cam_x(t_cam *cam, double ang);
void				rotate_cam_y(t_cam *cam, double ang);
void				rotate_cam_z(t_cam *cam, double ang);

#endif
