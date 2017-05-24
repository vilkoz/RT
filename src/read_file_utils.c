/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:39:39 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/24 19:40:11 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		del_lst(void *content, size_t size)
{
	if (content != NULL)
		free(content);
	(void)size;
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
