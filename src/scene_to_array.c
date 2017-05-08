/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_to_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 15:48:02 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/08 17:29:32 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

size_t	count_size(t_list *lst)
{
	t_list		*tmp;
	size_t		size;

	tmp = lst;
	size = 0;
	while (tmp)
	{
		size += tmp->content_size;
		tmp = tmp->next;
	}
	return (size);
}

int		write_object_to_arr(float *arr, float *o, int obj_num)
{
	int		i;

	i = 0;
	while (++i < o[0])
		arr[i] = o[i];
	arr[0] = obj_num;
	return (i);
}

float	*write_array(t_list *lst)
{
	float	*tmp;
	t_list	*tmp_l;
	int		i;
	int		obj_num;
	int		size;

	size = (int)(count_size(lst) / sizeof(float));
	tmp = (float*)malloc(sizeof(float) * (size + 1));
	i = 1;
	obj_num = 0;
	tmp_l = lst;
	while (i < size && tmp_l)
	{
		i += write_object_to_arr(&tmp[i], (float*)tmp_l->content, obj_num);
		tmp_l = tmp_l->next;
		obj_num++;
	}
	tmp[0] = size;
	return (tmp);
}

void	del(void *a, size_t size)
{
	(void)size;
	ft_memdel(&a);
}

float	*scene_to_array(t_scene *s)
{
	t_list		*lst;
	float		*tmp;
	int			i;

	i = -1;
	lst = NULL;
	while (++i < s->obj_num)
	{
		tmp = s->objects[i]->to_float(s->objects[i]->data);
		ft_lstadd(&lst, ft_lstnew((void*)tmp, (tmp[0] * sizeof(float))));
		ft_memdel((void**)&tmp);
	}
	tmp = write_array(lst);
	ft_lstdel(&lst, del);
	return (tmp);
}
