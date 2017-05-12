/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   profiler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 17:15:15 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/12 19:03:18 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	profiler_start(t_e *e)
{
	t_st	time_val;

	gettimeofday(&time_val, NULL);
	e->time = (double)time_val.tv_sec + (double)time_val.tv_usec / 1000000.;
}

void	profiler_print(t_e *e, const char *s)
{
	t_st	time_val;
	double	old_time;

	old_time = e->time;
	gettimeofday(&time_val, NULL);
	e->time = (double)time_val.tv_sec + (double)time_val.tv_usec / 1000000.;
	printf("%s time = %.10f usec\n", s, (e->time - old_time));
}
