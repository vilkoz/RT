/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_poligon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosobliv <aosobliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 20:07:28 by aosobliv          #+#    #+#             */
/*   Updated: 2017/04/26 20:15:07 by aosobliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

typedef	struct	s_p3_aa
{
	double		x;
	double		y;
	double		z;
	int			s;
}				t_p3_aa;

typedef struct	s_polygo
{
	int			v_size;
	int			vt_size;
	int			vn_size;
	int			f_size;
	t_p3_aa		*v;
	t_p3_aa		*vt;
	t_p3_aa		*vn;
	t_p3_aa		*f;
}				t_polygo;

typedef struct	s_gey_list
{

}				t_gey_list;

void	count_size(t_polygo *poly, char *file)
{
	int		fd;
	char	*line;
	t_list	*lst;

	if ((fd = open(file, O_RDONLY)) == -1)
		perror(file);
	while (get_next_line(fd, &line) > 0)
	{
		(line[0] == 'v' && (line[1] != 't' && line[1] != 'n')) ? poly->v_size++ : 0;
		(line[0] == 'v' && line[1] == 't') ? poly->vt_size++ : 0;
		(line[0] == 'v' && line[1] == 'n') ? poly->vn_size++ : 0;
		line[0] == 'f' ? poly->f_size++ : 0;
		ft_lstadd(&lst, ft_lstnew((void*)line, ft_strlen(line) *
			sizeof(char) + 1));
		free(line);
	}
	while (lst)
	{
		printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
	close(fd);
}

void	read_poligon(char *file)
{
	t_polygo	*poly;

	poly = (t_polygo *)malloc(sizeof(t_polygo));
	poly->v_size = 0;
	poly->vt_size = 0;
	poly->vn_size = 0;
	poly->f_size = 0;
	count_size(poly, file);
	// printf("%s\n", ".Obj file");
	// printf("v=%d\nvt=%d\nvn=%d\nf=%d", poly->v_size,poly->vt_size,
	// 	poly->vn_size,poly->f_size);
	exit(112);
}
