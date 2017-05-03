/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:17:44 by vrybalko          #+#    #+#             */
/*   Updated: 2017/04/26 17:01:43 by aosobliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			main(int argc, char **argv)
{
	t_e		*e;

	if (argc != 2)
	{
		ft_putstr_fd("usage: ./RTv1 scene_file\n", 2);
		exit(1);
	}
	if (ft_strstr(argv[1], ".obj") != 0)
	{
		e = ft_mlx_init(NULL);
		read_poligon(argv[1]);
	}
	else
	{
		e = ft_mlx_init(read_file(argv[1]));
		ft_mlx_events(e);
	}
	mlx_loop_hook(e->mlx, loop_hook, e);
	mlx_loop(e->mlx);
	return (0);
}
