/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:17:44 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/24 00:50:18 by vrybalko         ###   ########.fr       */
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
	t_v3d new;

	new = cross_product(new_v3d(1, 0.5, 0), new_v3d(1, 1, 1));
	printf("vec = %f, %f, %f\n", new.x, new.y, new.z);
	e = ft_mlx_init(read_file(argv[1]));
	ft_mlx_events(e);
	mlx_loop_hook(e->mlx, loop_hook, e);
	mlx_loop(e->mlx);
	return (0);
}
