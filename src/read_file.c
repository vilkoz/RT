/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 18:57:56 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/24 19:40:52 by vrybalko         ###   ########.fr       */
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
		if ((l[0] == 's' || l[0] == 'p') && l[1] == ' ')
			num_o++;
		if (l[0] == 'y')
			num_o += 3;
		if (l[0] == 'o')
			num_o += 2;
		if (l[0] == 'l' && l[1] == ' ')
			num_ls++;
		tmp = tmp->next;
	}
	s->obj_num = num_o;
	s->ls_num = num_ls;
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
		(i == 1) ? cam.pos.x = ft_atod(arr[i]) : 23;
		(i == 2) ? cam.pos.y = ft_atod(arr[i]) : 24;
		(i == 3) ? cam.pos.z = ft_atod(arr[i]) : 23;
		(i == 4) ? cam.dir.x = ft_atod(arr[i]) : 23;
		(i == 5) ? cam.dir.y = ft_atod(arr[i]) : 23;
		(i == 6) ? cam.dir.z = ft_atod(arr[i]) : 23;
	}
	cam.dir = (!cam.dir.x && !cam.dir.y && !cam.dir.z) ? new_v3d(0, 1, 0) :
		cam.dir;
	s->cam = new_cam(new_p3d(cam.pos.x, cam.pos.y, cam.pos.z),
		new_v3d(cam.dir.x, cam.dir.y, cam.dir.z));
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
