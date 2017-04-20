/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 18:57:56 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/24 19:00:29 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		read_error(char *s, int type)
{
	if (type == 1)
		perror(s);
	else if (type == 2)
		ft_putstr_fd("structure of file is incorrect!\n", 2);
	else if (type == 3)
		ft_putstr_fd("no light source on scene\n", 2);
	exit(1);
}

void		count_obj(t_scene *s, t_list *lst)
{
	t_list		*tmp;
	char		*l;
	int			num_o;
	int			num_ls;

	tmp = lst;
	num_o = 0;
	num_ls = 0;
	while (tmp)
	{
		l = (char *)(tmp->content);
		if (ft_strlen(l) == 0 || ft_strlen(l) == 1)
			read_error(NULL, 2);
		if ((l[0] == 's' || l[0] == 'p' || l[0] == 'y' || l[0] == 'o') &&
			l[1] == ' ')
			num_o++;
		if (l[0] == 'l' && l[1] == ' ')
			num_ls++;
		tmp = tmp->next;
	}
	s->obj_num = num_o;
	s->ls_num = num_ls;
}

void		free_arr(char ***arr)
{
	int		i;

	i = -1;
	while ((*arr)[++i] != NULL)
		free((*arr)[i]);
	free(*arr);
	if (arr != NULL)
		*arr = NULL;
}

void		read_sphere(t_scene *s, char **arr)
{
	int			i;
	t_sphere	sp;

	i = 0;
	sp.center.x = 0;
	sp.center.y = 0;
	sp.center.z = 0;
	sp.radius = 10;
	sp.color = 0xff50ff;
	while (arr[++i] != NULL)
	{
		(i == 1) ? sp.center.x = ft_atoi(arr[i]) : 23;
		(i == 2) ? sp.center.y = ft_atoi(arr[i]) : 23;
		(i == 3) ? sp.center.z = ft_atoi(arr[i]) : 23;
		(i == 4) ? sp.radius = (double)ft_atoi(arr[i]) : 23;
		if (i == 5 && ft_strchr(arr[i], 'x') != NULL)
			sp.color = ft_atoi_base(ft_strchr(arr[i], 'x') + 1, 16);
	}
	s->objects[s->cur_o] = new_sphere(new_p3d(sp.center.x, sp.center.y,
		sp.center.z), sp.radius, sp.color);
	s->cur_o++;
	free_arr(&arr);
}

void		read_light(t_scene *s, char **arr)
{
	t_p3d	p;
	int		i;

	p.x = 1000;
	p.y = 1000;
	p.z = 1000;
	i = 0;
	while (arr[++i] != NULL)
	{
		(i == 1) ? p.x = ft_atoi(arr[i]) : 23;
		(i == 2) ? p.y = ft_atoi(arr[i]) : 23;
		(i == 3) ? p.z = ft_atoi(arr[i]) : 23;
	}
	s->ls[s->cur_ls] = (t_p3d *)malloc(sizeof(t_p3d));
	*s->ls[s->cur_ls] = new_p3d(p.x, p.y, p.z);
	s->cur_ls++;
	free_arr(&arr);
}

void		read_plane(t_scene *s, char **arr)
{
	t_plane		p;
	int			i;

	p.p.x = 0;
	p.p.y = 1;
	p.p.z = 2;
	p.norm = new_v3d(0, 1, 0);
	p.color = 0xff50ff;
	i = 0;
	while (arr[++i] != NULL)
	{
		(i == 1) ? p.p.x = ft_atoi(arr[i]) : 23;
		(i == 2) ? p.p.y = ft_atoi(arr[i]) : 23;
		(i == 3) ? p.p.z = ft_atoi(arr[i]) : 23;
		(i == 4) ? p.norm.x = ft_atoi(arr[i]) : 23;
		(i == 5) ? p.norm.y = ft_atoi(arr[i]) : 23;
		(i == 6) ? p.norm.z = ft_atoi(arr[i]) : 23;
		if (i == 7 && ft_strchr(arr[i], 'x') != NULL)
			p.color = ft_atoi_base(ft_strchr(arr[i], 'x') + 1, 16);
	}
	p.norm = (!p.norm.x && !p.norm.y && !p.norm.z) ? new_v3d(0, 1, 0) : p.norm;
	s->objects[s->cur_o] = new_plane(new_p3d(p.p.x, p.p.y, p.p.z),
		new_v3d(p.norm.x, p.norm.y, p.norm.z), p.color);
	s->cur_o++;
	free_arr(&arr);
}

void		read_cam(t_scene *s, char **arr)
{
	t_cam	cam;
	int		i;

	i = -1;
	cam.pos.x = 100;
	cam.pos.y = 100;
	cam.pos.x = 100;
	cam.dir.x = 0;
	cam.dir.y = -1;
	cam.dir.z = 0;
	while (arr[++i] != NULL)
	{
		(i == 1) ? cam.pos.x = ft_atoi(arr[i]) : 23;
		(i == 2) ? cam.pos.y = ft_atoi(arr[i]) : 24;
		(i == 3) ? cam.pos.z = ft_atoi(arr[i]) : 23;
		(i == 4) ? cam.dir.x = ft_atoi(arr[i]) : 23;
		(i == 5) ? cam.dir.y = ft_atoi(arr[i]) : 23;
		(i == 6) ? cam.dir.z = ft_atoi(arr[i]) : 23;
	}
	cam.dir = (!cam.dir.x && !cam.dir.y && !cam.dir.z) ? new_v3d(0, 1, 0) :
		cam.dir;
	s->cam = new_cam(new_p3d(cam.pos.x, cam.pos.y, cam.pos.z),
		new_v3d(cam.dir.x, cam.dir.y, cam.dir.z));
	free_arr(&arr);
}

void		init_cyl(t_cyl *c)
{
	c->center.x = 0;
	c->center.y = 0;
	c->center.z = 0;
	c->dir.x = 0;
	c->dir.y = 0;
	c->dir.z = 1;
	c->radius = 100;
	c->h = 10000;
	c->color = 0xffa0;
}

void		read_cyl(t_scene *s, char **arr)
{
	t_cyl	c;
	int		i;

	i = 0;
	init_cyl(&c);
	while (arr[++i])
	{
		(i == 1) ? c.center.x = ft_atoi(arr[i]) : 23;
		(i == 2) ? c.center.y = ft_atoi(arr[i]) : 23;
		(i == 3) ? c.center.z = ft_atoi(arr[i]) : 23;
		(i == 4) ? c.dir.x = ft_atoi(arr[i]) : 23;
		(i == 5) ? c.dir.y = ft_atoi(arr[i]) : 23;
		(i == 6) ? c.dir.z = ft_atoi(arr[i]) : 23;
		(i == 7) ? c.radius = (double)ft_atoi(arr[i]) : 23;
		(i == 8) ? c.h = (double)ft_atoi(arr[i]) : 23;
		if (i == 9 && ft_strchr(arr[i], 'x') != NULL)
			c.color = ft_atoi_base(ft_strchr(arr[i], 'x') + 1, 16);
	}
	c.dir = (!c.dir.x && !c.dir.y && !c.dir.z) ? new_v3d(0, 1, 0) :
		c.dir;
	s->objects[s->cur_o] = new_cyl(new_vec(new_v3d(c.dir.x, c.dir.y, c.dir.z),
		new_p3d(c.center.x, c.center.y, c.center.z)), c.radius, c.h, c.color);
	s->cur_o++;
	free_arr(&arr);
}

void		init_cone(t_cone *c)
{
	c->center.x = 0;
	c->center.y = 0;
	c->center.z = 0;
	c->dir.x = 0;
	c->dir.y = 0;
	c->dir.z = 1;
	c->a = 60;
	c->h = 10000;
	c->color = 0xffa0;
}

void		read_cone(t_scene *s, char **arr)
{
	t_cone	c;
	int		i;

	i = 0;
	init_cone(&c);
	while (arr[++i])
	{
		(i == 1) ? c.center.x = ft_atoi(arr[i]) : 23;
		(i == 2) ? c.center.y = ft_atoi(arr[i]) : 23;
		(i == 3) ? c.center.z = ft_atoi(arr[i]) : 23;
		(i == 4) ? c.dir.x = ft_atoi(arr[i]) : 23;
		(i == 5) ? c.dir.y = ft_atoi(arr[i]) : 23;
		(i == 6) ? c.dir.z = ft_atoi(arr[i]) : 23;
		(i == 7) ? c.a = (double)ft_atoi(arr[i]) : 23;
		(i == 8) ? c.h = (double)ft_atoi(arr[i]) : 23;
		if (i == 9 && ft_strchr(arr[i], 'x') != NULL)
			c.color = ft_atoi_base(ft_strchr(arr[i], 'x') + 1, 16);
	}
	c.dir = (!c.dir.x && !c.dir.y && !c.dir.z) ? new_v3d(0, 1, 0) :
		c.dir;
	s->objects[s->cur_o] = new_cone(new_vec(normalize(new_v3d(c.dir.x, c.dir.y,
		c.dir.z)), new_p3d(c.center.x, c.center.y, c.center.z)), c.h, c.color,
		c.a);
	s->cur_o++;
	free_arr(&arr);
}

void		read_lines(t_scene *s, t_list *lst)
{
	t_list		*tmp;
	char		*l;

	tmp = lst;
	s->objects = (t_o3d **)malloc(sizeof(t_o3d *) * s->obj_num);
	s->ls = (t_p3d **)malloc(sizeof(t_p3d *) * s->ls_num);
	while (tmp)
	{
		l = (char *)tmp->content;
		if (l[0] == 'l')
			read_light(s, ft_strsplit(l, ' '));
		if (l[0] == 's')
			read_sphere(s, ft_strsplit(l, ' '));
		if (l[0] == 'p')
			read_plane(s, ft_strsplit(l, ' '));
		if (l[0] == 'y')
			read_cyl(s, ft_strsplit(l, ' '));
		if (l[0] == 'o')
			read_cone(s, ft_strsplit(l, ' '));
		if (l[0] == 'c')
			read_cam(s, ft_strsplit(l, ' '));
		tmp = tmp->next;
	}
}

void		del_lst(void *content, size_t size)
{
	if (content != NULL)
		free(content);
	(void)size;
}

t_scene		*read_file(char *name)
{
	int			fd;
	t_scene		*s;
	t_cam		cam;
	char		*line;
	t_list		*lst;

	lst = NULL;
	if ((fd = open(name, O_RDONLY)) == -1)
		read_error(name, 1);
	cam = new_cam(new_p3d(200, 700, 0), normalize(new_v3d(0, -1, 0)));
	s = new_scene(0, NULL, new_p3d(255, 1000, -300), cam);
	while (get_next_line(fd, &line) > 0)
	{
		ft_lstadd(&lst, ft_lstnew((void*)line, ft_strlen(line) *
			sizeof(char) + 1));
		free(line);
	}
	count_obj(s, lst);
	read_lines(s, lst);
	ft_lstdel(&lst, del_lst);
	if (s->obj_num == 0)
		read_error(name, 2);
	if (s->ls_num == 0)
		read_error(name, 3);
	return (s);
}
